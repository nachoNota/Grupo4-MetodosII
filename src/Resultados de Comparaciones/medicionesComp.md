### 6.4 Comparativa de Rendimiento entre Métodos

Para validar el costo computacional intrínseco de cada algoritmo, se contrastaron los tiempos de ejecución del Método del Valor Medio frente al Muestreo Aleatorio (Acierto y Error) bajo idénticas condiciones.

**Comparativa Local para $e^{-x^2}$ ($N = 10^8$ simulaciones)**

| Procesos | Tiempo Valor Medio (s) | Tiempo Muestreo Aleatorio (s) | Diferencia de Tiempo |
| --- | --- | --- | --- |
| 1 | 1.006 | 7.135 | + 6.129 s |
| 4 | 0.292 | 2.033 | + 1.741 s |
| 8 | 0.164 | 1.086 | + 0.922 s |
| 16 | 0.197 | 0.812 | + 0.615 s |

**Comparativa Local para $\sin(x^2)$ ($N = 10^8$ simulaciones)**

| Procesos | Tiempo Valor Medio (s) | Tiempo Muestreo Aleatorio (s) | Diferencia de Tiempo |
| --- | --- | --- | --- |
| 1 | 2.617 | 9.984 | + 7.367 s |
| 4 | 0.754 | 2.748 | + 1.994 s |
| 8 | 0.427 | 1.430 | + 1.003 s |
| 16 | 0.340 | 0.882 | + 0.542 s |

**Comparativa en Clúster HPC para $e^{-x^2}$ - 96 Cores ($N = 10^{10}$ simulaciones)**

| Procesos | Tiempo Valor Medio (s) | Tiempo Muestreo Aleatorio (s) | Diferencia de Tiempo |
| --- | --- | --- | --- |
| 1 | 212.80 | 409.81 | + 197.01 s |
| 32 | 7.43 | 12.80 | + 5.37 s |
| 64 | 5.98 | 6.66 | + 0.68 s |
| 96 | 4.17 | 5.98 | + 1.81 s |

**Comparativa en Clúster HPC para $\sin(x^2)$ - 96 Cores ($N = 10^{10}$ simulaciones)**

| Procesos | Tiempo Valor Medio (s) | Tiempo Muestreo Aleatorio (s) | Diferencia de Tiempo |
| --- | --- | --- | --- |
| 1 | 413.059 | 520.625 | + 107.566 s |
| 32 | 13.436 | 16.299 | + 2.863 s |
| 64 | 8.513 | 8.502 | - 0.011 s |
| 96 | 6.083 | 6.975 | + 0.892 s |