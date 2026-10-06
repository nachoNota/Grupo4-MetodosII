# Informe Final de Evaluación Parcial: Integración Numérica y Métodos de Monte Carlo

Este documento consolida los análisis de rendimiento, escalabilidad y precisión obtenidos por el equipo al implementar métodos de Monte Carlo mediante MPI. Las pruebas abarcan el cálculo del área de una figura irregular 2D (entre $y = x^2$ e $y = \sqrt{x}$) y la integración 1D de las funciones $e^{-x^2}$ y $\sin(x^2)$ utilizando el Método del Valor Medio y Muestreo Aleatorio (*Hit or Miss*). Las ejecuciones se realizaron en tres entornos de hardware distintos para aislar las limitaciones físicas y el comportamiento estocástico del algoritmo.

## 1. Análisis de Precisión y Convergencia

La experimentación confirma que la precisión de los métodos probabilísticos está directamente atada a la magnitud de simulaciones ($N$) y a los límites arquitectónicos del procesador, independientemente de la cantidad de procesos distribuidos.

* **Convergencia Inicial:** En el cálculo de áreas irregulares 2D, el error absoluto disminuye drásticamente a medida que $N$ crece, convergiendo exitosamente hacia el valor matemático real de 0.333333. Las leves fluctuaciones observadas entre magnitudes (por ejemplo, al pasar a $N = 10^8$) responden a la varianza natural de los generadores pseudoaleatorios.


* **Límites de Precisión por Hardware:** En el Método del Valor Medio, el error disminuye de forma muy regular hasta $N = 10^6$, dividiéndose por 100 cada vez que $N$ se multiplica por 10. Sin embargo, a partir de $N \approx 10^6$ o $10^7$, el error deja de bajar y oscila entre $10^{-13}$ y $10^{-10}$ %. Esto se debe a que la computadora almacena aproximadamente 16 dígitos por número de punto flotante; al acumular millones de sumas consecutivas, la pérdida de precisión por redondeo anula los beneficios de agregar más iteraciones. Por lo tanto, en la práctica, utilizar más de $10^6$ puntos no mejora el resultado.


* **Independencia del Paralelismo:** Dividir el trabajo en múltiples procesos no altera negativamente la precisión. Aunque con más procesos el orden de las sumas se modifica alterando los últimos decimales, el error relativo se mantiene acotado por debajo de $10^{-10}$ %, e incluso suele ser ligeramente menor en $N$ masivos debido a que cada proceso local acumula menos redondeo. Las pruebas secuenciales evidencian la varianza estocástica natural por cada ejecución, mientras que el promedio de 50 ejecuciones suaviza la curva de convergencia acercándose al valor teórico de referencia (0.8820813907 para $e^{-x^2}$ y 0.8047764893 para $\sin(x^2)$).



## 2. Rendimiento Paralelo y Escalabilidad (Speedup)

El impacto de la paralelización con MPI depende estrictamente del volumen de procesamiento y de la cantidad de núcleos físicos disponibles en cada entorno.

* **Sobrecarga de Comunicación (Overhead):** MPI requiere entre 0.55 y 1 segundo inicial únicamente para arrancar el entorno. Para cargas de trabajo pequeñas ($N = 10^3$), la paralelización es contraproducente, ya que la comunicación de red y la recolección de resultados tardan más que la resolución matemática secuencial, la cual toma microsegundos. Recién a partir de $N = 10^8$ el tiempo de cálculo justifica el costo de inicialización de la librería.


* **Cuellos de Botella Físicos:** El entorno de pruebas con 4 núcleos físicos demostró una escalabilidad eficiente hasta los 4 procesos (alcanzando un *Speedup* de hasta 3.3x). Forzar la ejecución con 8 procesos sobre 4 núcleos físicos generó mediciones inestables e imposibles, evidenciando que la sobresuscripción compite por los recursos del sistema operativo. Un fenómeno similar de estancamiento se registró al alcanzar un techo de *Speedup* estricto de 2.0x, indicando que el hardware subyacente limitó la asignación a solo 2 núcleos físicos efectivos.


* **Escalabilidad Óptima:** En arquitecturas con mayor disponibilidad de núcleos reales, el algoritmo escala de forma lineal. Al promediar 50 ejecuciones, el tiempo para $N = 10^8$ simulaciones de $e^{-x^2}$ disminuyó progresivamente de 3.38 segundos en estado serial a 0.63 segundos utilizando 8 procesos dedicados.



## 3. Comparativa de Métodos (Valor Medio vs. Muestreo Aleatorio)

La evaluación directa entre el Método del Valor Medio y el Muestreo Aleatorio (*Hit or Miss*) revela una diferencia sustancial en la eficiencia computacional para integrales 1D.

* **Costo Computacional:** El Muestreo Aleatorio es considerablemente más costoso por punto evaluado, ya que exige generar números pseudoaleatorios para ambas coordenadas cartesianas. Para $10^8$ simulaciones de $\sin(x^2)$, el muestreo aleatorio consumió 2.60 segundos, mientras que el valor medio resolvió la misma magnitud en 1.06 segundos.


* **Relación Tiempo-Precisión:** Para alcanzar un margen de error inferior al 0.01 %, el muestreo aleatorio requirió procesar $10^8$ puntos (invirtiendo entre 1 y 2.6 segundos), un nivel de precisión que el Método del Valor Medio alcanzó con apenas 100 evaluaciones en fracciones de microsegundo.



## 4. Conclusiones y Propuestas de Mejoras

La implementación de Monte Carlo paralelizado divide la carga pura de procesamiento casi a la perfección sin verse penalizado por tiempos de red cuando $N$ es lo suficientemente grande. Para optimizar futuros trabajos y sortear las limitaciones físicas registradas, es imperativo realizar ajustes tanto lógicos como arquitectónicos.

La función nativa `rand()` de C utilizada como generador pseudoaleatorio presenta un cuello de botella severo; reemplazarla por algoritmos avanzados como *Xorshift* o *Mersenne Twister* garantiza mayor entropía e incrementa la velocidad general a niveles comparables con duplicar la cantidad de procesos en MPI. A nivel de hardware, se debe evitar la sobresuscripción asegurando una correspondencia uno a uno entre los procesos lanzados y los núcleos físicos reales de la CPU. Para maximizar el rendimiento en simulaciones de escala industrial, se sugiere transicionar a un paralelismo híbrido que combine MPI para la distribución entre múltiples nodos de un clúster y OpenMP para la gestión de hilos en la memoria compartida local.