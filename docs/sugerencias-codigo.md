# Sugerencias sobre el código

Detectadas durante las mediciones del 2026-10-03, con $e^{-x^2}$ y $\sin(x^2)$ en [0, 2]. **Ninguna está aplicada**: el código de `main` no se modificó. Los números vienen de [`mediciones.md`](mediciones.md) y de [`datos/`](datos/).

Prioridades:

- 🔴 **bloquea**: impide compilar o medir.
- 🟠 **afecta resultados**: puede cambiar las conclusiones.
- 🟡 **mejora**: calidad o mantenimiento.
- ⚪ **descartada**: se midió y no vale la pena.

---

## 🔴 1. `muestreo_aleatorio_hpc.c` no compila

En la línea 10 dice `loasdng long hits_totales = 0;`. Debería ser `long long hits_totales = 0;`.

## 🟠 2. `muestreo_aleatorio_hpc.c` no es la versión paralela de `muestreo_aleatorio_serial.c`

- La versión serial integra $e^{-x^2}$ y $\sin(x^2)$.
- La versión "hpc" calcula π tirando dardos, con N fijo en 10⁷ y otro generador de números aleatorios.

Por eso no se puede comparar serial vs. paralelo para el muestreo aleatorio. Justamente es el método donde paralelizar más rinde (ver `informe.md`, punto 5).

**Sugerencia:** que la versión paralela haga lo mismo que la serial:

- cada proceso toma `n / size` puntos con su propio generador;
- se suman los resultados con `MPI_Reduce`.

El cálculo de π puede quedar en otro archivo para la Fase 2.

## 🟠 3. Números aleatorios en paralelo: `rand()` con semilla `time(NULL)`

**Medido** con una copia de `muestreo_aleatorio_hpc.c` que tiene corregida solo la línea 10 (datos en `datos/muestreo_aleatorio_hpc_corregido.txt`):

- Con 4 procesos, **dos de cinco ejecuciones dieron exactamente el mismo resultado** (π ≈ 3.141210). Arrancaron en el mismo segundo, así que usaron la misma semilla.
- `rand()` es lento: unos **48 ns por punto**, contra ~3 ns del generador xorshift que ya usa `muestreo_aleatorio_serial.c`.
- En Windows, `rand()` solo genera 32 768 valores distintos.

**Sugerencia:** usar el mismo xorshift de la versión serial, con una semilla fija distinta por proceso. Así hay resultados reproducibles y secuencias independientes:

```c
static uint64_t splitmix64(uint64_t x){
  x += 0x9E3779B97F4A7C15ULL;
  x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
  x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
  return x ^ (x >> 31);
}
/* ... */
estado = splitmix64(SEMILLA_BASE + rank);
```

## 🟠 4. `muestreo_aleatorio_hpc.c` pierde puntos si N no es múltiplo de la cantidad de procesos

`N_local = N_total / size` redondea hacia abajo, pero después se divide por `N_total`. Por ejemplo, con 3 procesos se generan 9 999 999 puntos y se divide por 10 000 000. **Sugerencia:** dividir por `N_local * size`.

## 🟠 5. El intervalo está fijo en el código

Los tres `main` tienen `a = 0.0, b = 1.0`, pero el grupo mide en [0, 2]. Por eso cada uno terminó modificando el programa o usando otro aparte.

**Sugerencia:** recibir `a` y `b` por argumento, por ejemplo `./valor_medio_serial N a b`, con [0, 1] por defecto.

## 🟠 6. Se imprimen pocos dígitos y no se calcula el error

Con `%.12f` el error del valor medio se pierde desde N ≈ 10⁵: el resultado ya coincide con la referencia en los 12 decimales que se ven.

**Sugerencia:**

- imprimir con `%.17g`;
- imprimir directamente el error relativo contra el valor de referencia (0.8820813907624216 y 0.8047764893437561 en [0, 2]).

## 🟠 7. Con N grande, el error lo domina el redondeo de la suma

Al hacer `suma += f(x)` millones de veces, cada suma redondea un poco y esos redondeos se acumulan. **Medido**: con $e^{-x^2}$ y N = 10⁸, el método aporta un error de 3×10⁻¹⁵ %, pero el programa da 1×10⁻¹⁰ %. Por eso en `mediciones.md` el error deja de bajar desde N ≈ 10⁶.

**Sugerencia:** usar suma compensada de Kahan. Solo cambia el bucle:

```c
double suma = 0.0, c = 0.0;
for (long i = 0; i < n; i++){
  double y = f(a + (i + 0.5) * h) - c;
  double t = suma + y;
  c = (t - suma) - y;
  suma = t;
}
```

**Medido** (`-O2`, promedio de 5 ejecuciones):

| | $e^{-x^2}$, N = 10⁸ | $\sin(x^2)$, N = 10⁹ |
| :--- | :--- | :--- |
| suma normal | 0.751 s · error 9.3e-13 | 10.88 s · error 9.0e-13 |
| Kahan | 0.875 s · error **0** | 11.88 s · error **1.1e-16** |

Cuesta un 9–17 % más de tiempo y elimina el error de redondeo.

⚠️ **No compilar con `-ffast-math`:** el compilador simplifica la corrección y la elimina. Lo comprobamos: con ese flag, el error volvió a 9.3e-13.

## 🟡 8. Medir todos de la misma forma

Para que los números del grupo se puedan comparar:

- **Mismos flags de compilación.** Con `-O0` el programa es 1.35–1.65 veces más lento que con `-O2`. `-O3 -march=native -ffast-math` no mejora nada. Propuesta: `-O2` para todos.
- **Varias ejecuciones** y promedio, o mediana si hay valores muy raros. Una sola ejecución puede variar hasta 2.5 veces.
- **No usar más procesos que núcleos.** Con 8 procesos en 4 núcleos medí speedups de 5.14x, que son imposibles: la medición deja de ser confiable.
- **Dejar claro si el tiempo incluye el arranque de MPI.** El arranque suma entre 0.55 y 1 s.
- **Para instalar MPI en WSL con Ubuntu 24.04:** usar OpenMPI (`sudo apt install openmpi-bin libopenmpi-dev`). El paquete `mpich` de esa versión no reparte el trabajo entre procesos.

## 🟡 9. Código repetido

`f_exponencial`, `f_seno` y `tiempo_actual()` están copiadas en tres archivos. **Sugerencia:** moverlas a un `funciones.h` común.

## 🟡 10. `long` y `atol` no son portables

En Windows, `long` es de 32 bits: N > 2 147 483 647 desborda. Además `atol("1e9")` devuelve 1 sin avisar.

**Sugerencia:** usar `long long` y `strtoll`, validando lo que se leyó.

## ⚪ 11. Descartada: sacar el puntero a función

La idea era que llamar a `f` por puntero impidiera optimizar. **Medido** (`-O2`, N = 10⁸):

| | $e^{-x^2}$ | $\sin(x^2)$ |
| :--- | :--- | :--- |
| con puntero (como está) | 0.751 s | 1.078 s |
| función escrita dentro del bucle | 0.776 s | 1.068 s |

No hay diferencia. Conviene dejarlo como está, porque es más claro.

## ✅ Algo que conviene NO cambiar

En el valor medio, `x = a + (i + 0.5) * h` se calcula de nuevo en cada paso. Está bien así. La alternativa "más rápida" `x += h` acumularía error en la posición de los puntos.
