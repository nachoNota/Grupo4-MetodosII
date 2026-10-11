#!/bin/bash
# Re-medición de tiempos y aproximaciones del programa MPI (valor medio).
#
# Uso:
#   ./medir.sh                         -> corre la lista TRABAJOS_DEFECTO (abajo)
#   ./medir.sh 1:1000 8:1000000000     -> corre solo esos trabajos (formato P:N)
#   ./medir.sh --todo                  -> repite TODAS las combinaciones (P x N)
#   ./medir.sh --faltantes             -> corre solo las combinaciones (P x N) que todavía
#                                         no tienen sus corridas completas en el archivo SALIDA
#   SOLO_LISTAR=1 ./medir.sh --faltantes   -> solo muestra qué correría, sin medir nada
#
# Variables opcionales (se pasan antes del comando):
#   EJECUTABLE   ruta del programa MPI         (por defecto ./valor_medio)
#   EJECUCIONES  corridas por combinación      (por defecto 30)
#   MPIRUN_OPTS  opciones extra de mpirun      (por defecto vacío)
#   SALIDA       archivo CSV con cada corrida  (por defecto mediciones_crudas.csv)
#   PIN          si vale 1, fija cada proceso MPI a su propio núcleo (usa taskset);
#                llena primero un hilo de cada núcleo físico y recién después los hilos hermanos
#   Ejemplo: EJECUCIONES=10 MPIRUN_OPTS="--oversubscribe" ./medir.sh 16:1000000000
#
# IMPORTANTE: usá en MPIRUN_OPTS las MISMAS opciones que usaste en las otras mediciones
# (por ejemplo --oversubscribe o --use-hwthread-cpus si mpirun te las pedía para P=12/16).

export LC_ALL=C

EJECUTABLE="${EJECUTABLE:-./valor_medio}"
EJECUCIONES="${EJECUCIONES:-30}"
MPIRUN_OPTS="${MPIRUN_OPTS:-}"
SALIDA="${SALIDA:-mediciones_crudas.csv}"
SEMILLA_BASE="${SEMILLA_BASE:-$(date +%s)}"
PIN="${PIN:-}"

VALORES_N=(1000 10000 100000 1000000 10000000 100000000 1000000000)
VALORES_P=(1 2 4 8 12 16)

# Lo que quedó dudoso en las mediciones anteriores:
#   - 1 proceso, todos los N (la referencia de todo el speedup)
#   - 16 procesos con N >= 1e8
#   - 8 procesos con N = 1e9
TRABAJOS_DEFECTO=(
  1:1000 1:10000 1:100000 1:1000000 1:10000000 1:100000000 1:1000000000
  16:100000000 16:1000000000
  8:1000000000
)

if [ "$1" = "--todo" ]; then
  TRABAJOS=()
  for p in "${VALORES_P[@]}"; do for n in "${VALORES_N[@]}"; do TRABAJOS+=("$p:$n"); done; done
elif [ "$1" = "--faltantes" ]; then
  TRABAJOS=()
  for p in "${VALORES_P[@]}"; do
    for n in "${VALORES_N[@]}"; do
      hechas=0
      if [ -s "$SALIDA" ]; then
        # cada corrida guarda 2 filas (exp y sin)
        hechas=$(awk -F, -v n="$n" -v p="$p" 'NR > 1 && $2 == n && $3 == p { c++ } END { print c + 0 }' "$SALIDA")
      fi
      if [ "$hechas" -lt $((2 * EJECUCIONES)) ]; then TRABAJOS+=("$p:$n"); fi
    done
  done
elif [ "$#" -gt 0 ]; then
  TRABAJOS=("$@")
else
  TRABAJOS=("${TRABAJOS_DEFECTO[@]}")
fi

for t in "${TRABAJOS[@]}"; do
  if ! [[ "$t" =~ ^[0-9]+:[0-9]+$ ]]; then
    echo "Trabajo inválido: '$t'."
    echo "Usá  ./medir.sh  (lista por defecto), ./medir.sh --faltantes, ./medir.sh --todo"
    echo "o trabajos con formato P:N, por ejemplo  ./medir.sh 8:1000000000"
    exit 1
  fi
done

if [ -n "$SOLO_LISTAR" ]; then
  echo "Trabajos que correría (${#TRABAJOS[@]}):"
  printf '%s ' "${TRABAJOS[@]}"; echo
  exit 0
fi

if [ ! -x "$EJECUTABLE" ]; then
  echo "No encuentro el ejecutable '$EJECUTABLE'."
  echo "Compilalo con:  mpicc -O2 valor_medio.c -o valor_medio -lm"
  exit 1
fi

if [ -s "$SALIDA" ]; then
  echo "Aviso: '$SALIDA' ya existe; las corridas nuevas se AGREGAN al final."
  echo "       (si querés empezar de cero, borralo o usá otro nombre con SALIDA=...)"
else
  echo "funcion,N,P,corrida,semilla,tiempo_s,valor" > "$SALIDA"
fi

# extraer "<salida completa>" "<nombre de función>"  ->  imprime "valor tiempo"
extraer() {
  local linea valor tiempo
  linea=$(printf '%s\n' "$1" | grep -F "$2" | head -n 1)
  valor=$(printf '%s\n' "$linea" | awk -F'Area: ' '{print $2}' | awk '{print $1}')
  tiempo=$(printf '%s\n' "$linea" | awk -F'Tiempo: ' '{print $2}' | awk '{print $1}')
  echo "$valor $tiempo"
}

LANZADOR=("$EJECUTABLE")
if [ -n "$PIN" ]; then
  if ! command -v taskset > /dev/null 2>&1; then
    echo "PIN=1 necesita el comando 'taskset' (paquete util-linux) y no lo encuentro."
    exit 1
  fi
  PIN_SCRIPT=$(mktemp /tmp/pin_rank.XXXXXX)
  trap 'rm -f "$PIN_SCRIPT"' EXIT
  cat > "$PIN_SCRIPT" << 'EOS'
#!/bin/bash
# Fija este proceso a una CPU según su rank: primero un hilo de cada núcleo físico,
# después los hilos hermanos (hyperthreads). Sirve para Open MPI y MPICH.
rank=${OMPI_COMM_WORLD_RANK:-${PMI_RANK:-${PMIX_RANK:-${MPI_LOCALRANKID:-0}}}}
mapfile -t orden < <(lscpu -p=CPU,CORE | grep -v '^#' \
  | awk -F, '{ i[$2]++; print i[$2]-1, $2, $1 }' | sort -n -k1,1 -k2,2 | awk '{print $3}')
cpu=${orden[$(( rank % ${#orden[@]} ))]}
exec taskset -c "$cpu" "$@"
EOS
  chmod +x "$PIN_SCRIPT"
  LANZADOR=("$PIN_SCRIPT" "$EJECUTABLE")
  echo "Modo PIN=1: cada proceso queda fijado a su propio núcleo."
fi

for trabajo in "${TRABAJOS[@]}"; do
  P=${trabajo%%:*}
  N=${trabajo##*:}
  echo ">>> P=$P  N=$N  ($EJECUCIONES corridas)"

  for ((i = 1; i <= EJECUCIONES; i++)); do
    # Semilla distinta en cada corrida (y distinta entre combinaciones)
    semilla=$(( (SEMILLA_BASE + 1000003 * i + 7 * P) % 2147483647 ))

    # $MPIRUN_OPTS va sin comillas a propósito (para que se separe en palabras)
    salida=$(mpirun --oversubscribe -np "$P" $MPIRUN_OPTS "${LANZADOR[@]}" "$N" "$semilla" 2>&1)

    for f in "exp(-x^2)" "sin(x^2)"; do
      read -r valor tiempo <<< "$(extraer "$salida" "$f")"
      if [ -z "$valor" ] || [ -z "$tiempo" ]; then
        echo "ERROR: la corrida $i (P=$P, N=$N) no devolvió datos para $f. Salida completa:"
        echo "$salida"
        exit 1
      fi
      echo "$f,$N,$P,$i,$semilla,$tiempo,$valor" >> "$SALIDA"
    done
  done

  # Resumen rápido de la combinación (promedio de lo que haya en el archivo)
  awk -F, -v n="$N" -v p="$P" '
    NR > 1 && $2 == n && $3 == p { s[$1] += $6; v[$1] += $7; c[$1]++ }
    END { for (f in s) printf "    %-10s tiempo medio = %.6f s | valor medio = %.8f | %d corridas\n", f, s[f]/c[f], v[f]/c[f], c[f] }
  ' "$SALIDA"
done

echo "--------------------------------------------------------"
echo "Listo. Cada corrida quedó guardada en: $SALIDA"
echo "Para analizar:  python3 analisis_mpi.py $SALIDA -o salida_analisis"