# Mediciones

Mediciones de _tiempo_ de los métodos.

# Resultados de Mediciones (Mi Entorno - WSL)

## Mediciones para $e^{-x^2}$

Para calcular el error relativo se utiliza un valor de referencia igual a $0.8820813907$. A diferencia del entorno de prueba A (50 ejecuciones promediadas), estos resultados reflejan una única ejecución secuencial para evidenciar la varianza estocástica natural de los generadores pseudoaleatorios por cada escalón.

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| --- | --- | --- | --- | --- |
| $N = 1 \times 10^3$ | 1 | 0.000053 | 0.8825631730 | 0.054619 |
| $N = 1 \times 10^4$ | 1 | 0.000221 | 0.8757254370 | 0.720563 |
| $N = 1 \times 10^5$ | 1 | 0.001947 | 0.8841037045 | 0.229266 |
| $N = 1 \times 10^6$ | 1 | 0.019249 | 0.8820411985 | 0.004557 |
| $N = 1 \times 10^7$ | 1 | 0.191395 | 0.8823785947 | 0.033693 |
| $N = 1 \times 10^8$ | 1 | 1.912796 | 0.8820943949 | 0.001474 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| --- | --- | --- | --- | --- |
| $N = 1 \times 10^3$ | 2 | 0.000103 | 0.8667881971 | 1.733762 |
| $N = 1 \times 10^4$ | 2 | 0.000152 | 0.8771041987 | 0.564255 |
| $N = 1 \times 10^5$ | 2 | 0.001015 | 0.8773956209 | 0.531217 |
| $N = 1 \times 10^6$ | 2 | 0.009645 | 0.8819278864 | 0.017403 |
| $N = 1 \times 10^7$ | 2 | 0.096186 | 0.8821487783 | 0.007640 |
| $N = 1 \times 10^8$ | 2 | 0.965921 | 0.8821898837 | 0.012300 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| --- | --- | --- | --- | --- |
| $N = 1 \times 10^3$ | 4 | 0.000115 | 0.8975504351 | 1.753698 |
| $N = 1 \times 10^4$ | 4 | 0.000094 | 0.8796025780 | 0.281019 |
| $N = 1 \times 10^5$ | 4 | 0.000607 | 0.8846507287 | 0.291281 |
| $N = 1 \times 10^6$ | 4 | 0.005581 | 0.8817437603 | 0.038277 |
| $N = 1 \times 10^7$ | 4 | 0.048292 | 0.8821120270 | 0.003473 |
| $N = 1 \times 10^8$ | 4 | 0.916172 | 0.8821248983 | 0.004932 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| --- | --- | --- | --- | --- |
| $N = 1 \times 10^3$ | 8 | 0.000142 | 0.8972249676 | 1.716800 |
| $N = 1 \times 10^4$ | 8 | 0.000176 | 0.8825883323 | 0.057471 |
| $N = 1 \times 10^5$ | 8 | 0.000300 | 0.8808320160 | 0.141639 |
| $N = 1 \times 10^6$ | 8 | 0.002464 | 0.8824619875 | 0.043148 |
| $N = 1 \times 10^7$ | 8 | 0.087929 | 0.8821059239 | 0.002781 |
| $N = 1 \times 10^8$ | 8 | 0.894645 | 0.8820540159 | 0.003103 |

---

Aquí tienes los resultados para la función $\sin(x^2)$ formateados en Markdown, listos para que los agregues a tu informe final junto a los datos de tu compañero.

Al igual que en la prueba anterior, notarás que tu tiempo baja a la mitad al pasar de 1 a 2 procesos (de 3.75s a 1.90s), pero nuevamente se estanca al usar 4 y 8 procesos (1.85s y 1.89s respectivamente), confirmando el límite físico de tu hardware frente al equipo de tu compañero, quien logró procesar esta misma función en 1.10 segundos con 8 procesos.

---

## Mediciones para $\sin(x^2)$ (Mi Entorno - WSL)

Para calcular el error relativo se utiliza un valor de referencia igual a $0.8047764893$. Los resultados a continuación corresponden a una única ejecución por configuración para contrastar la varianza frente al promedio de 50 ejecuciones del entorno de prueba A.

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| --- | --- | --- | --- | --- |
| $N = 1 \times 10^3$ | 1 | 0.000072 | 0.8185376657 | 1.709938 |
| $N = 1 \times 10^4$ | 1 | 0.000418 | 0.7970027737 | 0.965947 |
| $N = 1 \times 10^5$ | 1 | 0.003788 | 0.8043325404 | 0.055164 |
| $N = 1 \times 10^6$ | 1 | 0.037532 | 0.8046404613 | 0.016903 |
| $N = 1 \times 10^7$ | 1 | 0.375265 | 0.8046125315 | 0.020373 |
| $N = 1 \times 10^8$ | 1 | 3.755120 | 0.8047901248 | 0.001694 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| --- | --- | --- | --- | --- |
| $N = 1 \times 10^3$ | 2 | 0.000061 | 0.7865574350 | 2.263865 |
| $N = 1 \times 10^4$ | 2 | 0.000244 | 0.8058781260 | 0.136887 |
| $N = 1 \times 10^5$ | 2 | 0.001939 | 0.8004399920 | 0.538845 |
| $N = 1 \times 10^6$ | 2 | 0.018981 | 0.8044326252 | 0.042728 |
| $N = 1 \times 10^7$ | 2 | 0.189595 | 0.8043797772 | 0.049295 |
| $N = 1 \times 10^8$ | 2 | 1.905279 | 0.8047633973 | 0.001627 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| --- | --- | --- | --- | --- |
| $N = 1 \times 10^3$ | 4 | 0.000066 | 0.8162845529 | 1.429970 |
| $N = 1 \times 10^4$ | 4 | 0.000187 | 0.7839238173 | 2.591113 |
| $N = 1 \times 10^5$ | 4 | 0.001070 | 0.7999913536 | 0.594592 |
| $N = 1 \times 10^6$ | 4 | 0.009608 | 0.8045164600 | 0.032311 |
| $N = 1 \times 10^7$ | 4 | 0.144502 | 0.8046983888 | 0.009705 |
| $N = 1 \times 10^8$ | 4 | 1.858429 | 0.8048739434 | 0.012109 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| --- | --- | --- | --- | --- |
| $N = 1 \times 10^3$ | 8 | 0.000122 | 0.7949790642 | 1.217409 |
| $N = 1 \times 10^4$ | 8 | 0.000217 | 0.8049670109 | 0.023674 |
| $N = 1 \times 10^5$ | 8 | 0.000565 | 0.7984725204 | 0.783319 |
| $N = 1 \times 10^6$ | 8 | 0.004881 | 0.8045707141 | 0.025569 |
| $N = 1 \times 10^7$ | 8 | 0.170797 | 0.8044378819 | 0.042075 |
| $N = 1 \times 10^8$ | 8 | 1.898389 | 0.8047847155 | 0.001022 |

---

# Informe de Evaluación Parcial 1: Integración Numérica y Cálculo de Áreas Irregulares

Este informe detalla la implementación y el análisis de rendimiento del método probabilístico de Monte Carlo para calcular el área de la figura irregular delimitada por las curvas $y = x^2$ e $y = \sqrt{x}$ en el intervalo $[0, 1]$. El área matemática exacta de referencia es $0.333333$.

## 1. Análisis de Convergencia (Precisión vs. Tiempo)

Para analizar la convergencia del método, se mantuvo fija la ejecución en 4 procesos simultáneos, variando la magnitud de las simulaciones totales ($N$).

| Simulaciones ($N$) | Área Calculada | Error Absoluto | Tiempo de Ejecución |
| --- | --- | --- | --- |
| 1,000 | 0.342000 | 0.008667 | 0.000075 s |
| 10,000 | 0.331600 | 0.001733 | 0.000177 s |
| 100,000 | 0.334030 | 0.000697 | 0.000941 s |
| 1,000,000 | 0.333423 | 0.000090 | 0.007793 s |
| 10,000,000 | 0.333344 | 0.000011 | 0.105764 s |
| 100,000,000 | 0.333306 | 0.000027 | 1.495004 s |
| 1,000,000,000 | 0.333337 | 0.000004 | 15.513516 s |

* **Convergencia confirmada:** A medida que la cantidad de iteraciones $N$ crece, el error absoluto disminuye drásticamente, demostrando la capacidad del método para aproximarse al valor real de 0.333333.
* **Naturaleza probabilística:** En el escalón de $N = 100,000,000$, el error sufre un leve incremento respecto a la magnitud anterior (de 0.000011 a 0.000027). Este es un comportamiento inherente y esperado en las aproximaciones estocásticas debido a fluctuaciones estadísticas en los generadores pseudoaleatorios.
* **Costo computacional:** El tiempo de ejecución escala de manera proporcional y lineal respecto al incremento de $N$. Al multiplicar las simulaciones por 10 (de 100 millones a mil millones), el tiempo computacional también se multiplicó aproximadamente por 10 (de 1.49 s a 15.51 s).

## 2. Análisis de Rendimiento Paralelo (Speedup)

Para medir la escalabilidad del algoritmo mediante la librería MPI, se fijó una carga de cálculo pesada ($N = 100,000,000$) y se ejecutó el programa incrementando la cantidad de procesos ($p$).

| Procesos | Tiempo de Ejecución | Speedup ($T_1 / T_p$) | Eficiencia |
| --- | --- | --- | --- |
| 1 | 3.030402 s | 1.00x | 100% |
| 2 | 1.572587 s | 1.92x | 96% |
| 3 | 1.503641 s | 2.01x | 67% |
| 4 | 1.486591 s | 2.03x | 50% |

* **Escalabilidad inicial eficiente:** Al dividir el trabajo entre 2 procesos, se logró un *Speedup* de 1.92x (eficiencia del 96%). Esto indica que el algoritmo Monte Carlo paralelizado divide la carga pura de procesamiento casi a la perfección sin verse penalizado por tiempos de comunicación de la red.


* **Identificación de cuellos de botella por Hardware:** A partir del tercer y cuarto proceso, la ganancia de tiempo se vuelve marginal y el *Speedup* encuentra un techo estricto alrededor de 2.0x. Este estancamiento sugiere una limitación en los recursos físicos del entorno de ejecución (probablemente el procesador subyacente cuenta con solo 2 núcleos físicos dedicados o asignados a la máquina virtual). Forzar una mayor cantidad de procesos sobre los mismos núcleos introduce un leve tiempo ocioso y de alternancia (*overhead*) que impide superar la eficiencia inicial.



## 3. Conclusiones Generales y Propuestas de Mejora

La implementación mediante MPI resulta sumamente eficiente para los métodos de Monte Carlo gracias a la naturaleza independiente del cálculo en cada iteración, lo que minimiza el impacto del tiempo de comunicación (*Tcom*) en la ejecución general. Sin embargo, para futuros trabajos que requieran simulaciones de escala industrial, se recomiendan las siguientes mejoras:

* **Mejora del Generador de Números Aleatorios:** La función nativa `rand()` de C tiene un periodo corto y no garantiza la máxima entropía para problemas científicos complejos. Se sugiere implementar un generador robusto como el *Mersenne Twister*.
* **Paralelismo Híbrido (MPI + OpenMP):** Combinar MPI para distribuir la carga entre distintos nodos físicos o servidores, con la librería OpenMP para manejar eficientemente múltiples hilos (threads) de memoria compartida dentro de cada nodo individual.


* **Ejecución en Clústeres Dedicados:** Trasladar la ejecución del algoritmo a la arquitectura de una supercomputadora o clúster HPC, asegurando correspondencia uno a uno entre los procesos MPI generados y los núcleos físicos del hardware, para así lograr métricas de *Speedup* lineales en órdenes de magnitud mayores.

## Método de valor medio

-

## Método de muestreo aleatorio

-