# Mediciones

Mediciones de _tiempo_ de los métodos.

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