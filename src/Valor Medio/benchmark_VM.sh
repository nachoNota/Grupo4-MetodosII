#!/bin/bash
export LC_ALL=C

EJECUTABLE="./val"
PROCESOS=8
EJECUCIONES=50

VALOR_REAL_SENO="0.8047764893437561"
VALOR_REAL_EXP="0.8820813907624216" 

SALIDA="resultados_tabla.csv"

echo "Funcion,N_Simulaciones,Procesos,Tiempo_Promedio_segs,Valor_Aproximado,Error_Relativo_Porcentual" > $SALIDA
VALORES_N=(1000 10000 100000 1000000 10000000 100000000)

echo "Iniciando pruebas automáticas para exponencial y seno..."

for N in "${VALORES_N[@]}"; do
    suma_tiempo_seno=0
    suma_valor_seno=0
    suma_tiempo_exp=0
    suma_valor_exp=0
    
    echo -n "Procesando N = $N con $EJECUCIONES ejecuciones... "

    for ((i=1; i<=EJECUCIONES; i++)); do
        # 1. Ejecutamos 1 sola vez y guardamos toda la salida del programa
        SALIDA_MPI=$(mpirun -np $PROCESOS $EJECUTABLE $N 2>/dev/null)
        
        #  PROCESAR SENO 
        LINEA_SENO=$(echo "$SALIDA_MPI" | grep -F "sin(x^2)")
        VALOR_SENO=$(echo "$LINEA_SENO" | awk -F'Area: ' '{print $2}' | awk '{print $1}')
        TIEMPO_SENO=$(echo "$LINEA_SENO" | awk -F'Tiempo: ' '{print $2}' | awk '{print $1}')
        
        VALOR_SENO=${VALOR_SENO:-0}
        TIEMPO_SENO=${TIEMPO_SENO:-0}
        
        suma_valor_seno=$(awk -v s="$suma_valor_seno" -v v="$VALOR_SENO" 'BEGIN { printf "%.10f", s + v }')
        suma_tiempo_seno=$(awk -v s="$suma_tiempo_seno" -v t="$TIEMPO_SENO" 'BEGIN { printf "%.6f", s + t }')

        #  PROCESAR EXPONENCIAL 
        LINEA_EXP=$(echo "$SALIDA_MPI" | grep -F "exp(-x^2)")
        VALOR_EXP=$(echo "$LINEA_EXP" | awk -F'Area: ' '{print $2}' | awk '{print $1}')
        TIEMPO_EXP=$(echo "$LINEA_EXP" | awk -F'Tiempo: ' '{print $2}' | awk '{print $1}')
        
        VALOR_EXP=${VALOR_EXP:-0}
        TIEMPO_EXP=${TIEMPO_EXP:-0}
        
        suma_valor_exp=$(awk -v s="$suma_valor_exp" -v v="$VALOR_EXP" 'BEGIN { printf "%.10f", s + v }')
        suma_tiempo_exp=$(awk -v s="$suma_tiempo_exp" -v t="$TIEMPO_EXP" 'BEGIN { printf "%.6f", s + t }')
    done

    # Calcular promedios SENO
    prom_valor_seno=$(awk -v s="$suma_valor_seno" -v e="$EJECUCIONES" 'BEGIN { printf "%.10f", s / e }')
    prom_tiempo_seno=$(awk -v s="$suma_tiempo_seno" -v e="$EJECUCIONES" 'BEGIN { printf "%.6f", s / e }')
    
    # Calcular promedios EXPONENCIAL
    prom_valor_exp=$(awk -v s="$suma_valor_exp" -v e="$EJECUCIONES" 'BEGIN { printf "%.10f", s / e }')
    prom_tiempo_exp=$(awk -v s="$suma_tiempo_exp" -v e="$EJECUCIONES" 'BEGIN { printf "%.6f", s / e }')

    # Calcular errores relativos
    error_seno=$(awk -v real="$VALOR_REAL_SENO" -v prom="$prom_valor_seno" 'BEGIN {
        diff = real - prom; if (diff < 0) diff = -diff; printf "%.6f", (diff / real) * 100
    }')
    
    error_exp=$(awk -v real="$VALOR_REAL_EXP" -v prom="$prom_valor_exp" 'BEGIN {
        diff = real - prom; if (diff < 0) diff = -diff; printf "%.6f", (diff / real) * 100
    }')

    # Guardar resultados en el CSV
    echo "exp(-x^2),$N,$PROCESOS,$prom_tiempo_exp,$prom_valor_exp,$error_exp" >> $SALIDA
    echo "sin(x^2),$N,$PROCESOS,$prom_tiempo_seno,$prom_valor_seno,$error_seno" >> $SALIDA
    
    echo "¡Listo!"
done

echo "--------------------------------------------------------"
echo "Resultados guardados en $SALIDA:"
cat $SALIDA