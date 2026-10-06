# Mediciones

Mediciones de _tiempo_ de los métodos.

# Resultados de Mediciones (Tomas)

## Entorno

| | |
| :--- | :--- |
| Fecha | 2026-10-03 |
| CPU | AMD Ryzen 3 3200G: **4 núcleos** (4 hilos) |
| RAM | 16 GB |
| Sistema | Windows 10 + WSL 1 (Ubuntu 24.04) |
| Compilador | gcc 13.3.0 |
| MPI | OpenMPI 4.1.6 |

## Cómo se midió

- **Funciones:** $e^{-x^2}$ y $\sin(x^2)$ en el intervalo **[0, 2]**.
- **N:** de $10^3$ a $10^9$.
- **Procesos:** 1 (serial), 2, 4 y 8. La CPU tiene 4 núcleos, así que con 8 hay más procesos que núcleos.
- **Tiempo:** promedio de **10 ejecuciones** (3 para $N = 10^9$). Mide solo el cálculo, sin el arranque del programa. Igual que en los programas originales.



## Método de valor medio

### Mediciones para $e^{-x^2}$

Para calcular el error relativo se utiliza un valor de referencia igual a $0.8820813907$. Tiempo: promedio de 10 ejecuciones (3 para $N = 10^9$).

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 1 (serial) | 0.000009 | 0.8820814030 | 1.4e-06 |
| $N = 1 \times 10^4$ | 1 (serial) | 0.000071 | 0.8820813909 | 1.4e-08 |
| $N = 1 \times 10^5$ | 1 (serial) | 0.000751 | 0.8820813908 | 1.4e-10 |
| $N = 1 \times 10^6$ | 1 (serial) | 0.007425 | 0.8820813908 | 2.0e-13 |
| $N = 1 \times 10^7$ | 1 (serial) | 0.075072 | 0.8820813908 | 7.8e-12 |
| $N = 1 \times 10^8$ | 1 (serial) | 0.767207 | 0.8820813908 | 1.1e-10 |
| $N = 1 \times 10^9$ | 1 (serial) | 8.206291 | 0.8820813908 | 1.5e-12 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 2 | 0.000015 | 0.8820814030 | 1.4e-06 |
| $N = 1 \times 10^4$ | 2 | 0.000042 | 0.8820813909 | 1.4e-08 |
| $N = 1 \times 10^5$ | 2 | 0.000416 | 0.8820813908 | 1.4e-10 |
| $N = 1 \times 10^6$ | 2 | 0.004934 | 0.8820813908 | 8.9e-13 |
| $N = 1 \times 10^7$ | 2 | 0.046892 | 0.8820813908 | 5.3e-12 |
| $N = 1 \times 10^8$ | 2 | 0.473586 | 0.8820813908 | 3.4e-11 |
| $N = 1 \times 10^9$ | 2 | 3.724908 | 0.8820813908 | 8.2e-12 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 4 | 0.000017 | 0.8820814030 | 1.4e-06 |
| $N = 1 \times 10^4$ | 4 | 0.000035 | 0.8820813909 | 1.4e-08 |
| $N = 1 \times 10^5$ | 4 | 0.000222 | 0.8820813908 | 1.4e-10 |
| $N = 1 \times 10^6$ | 4 | 0.002863 | 0.8820813908 | 1.1e-12 |
| $N = 1 \times 10^7$ | 4 | 0.026870 | 0.8820813908 | 4.6e-12 |
| $N = 1 \times 10^8$ | 4 | 0.279113 | 0.8820813908 | 3.6e-12 |
| $N = 1 \times 10^9$ | 4 | 1.885142 | 0.8820813908 | 1.9e-12 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 8 | 0.000043 | 0.8820814030 | 1.4e-06 |
| $N = 1 \times 10^4$ | 8 | 0.000052 | 0.8820813909 | 1.4e-08 |
| $N = 1 \times 10^5$ | 8 | 0.000259 | 0.8820813908 | 1.4e-10 |
| $N = 1 \times 10^6$ | 8 | 0.001670 | 0.8820813908 | 1.5e-12 |
| $N = 1 \times 10^7$ | 8 | 0.021224 | 0.8820813908 | 2.9e-12 |
| $N = 1 \times 10^8$ | 8 | 0.171943 | 0.8820813908 | 1.1e-11 |
| $N = 1 \times 10^9$ | 8 | 2.015963 | 0.8820813908 | 3.4e-12 |

### Mediciones para $\sin(x^2)$

Para calcular el error relativo se utiliza un valor de referencia igual a $0.8047764893$. Tiempo: promedio de 10 ejecuciones (3 para $N = 10^9$).

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 1 (serial) | 0.000012 | 0.8047769251 | 5.4e-05 |
| $N = 1 \times 10^4$ | 1 (serial) | 0.000102 | 0.8047764937 | 5.4e-07 |
| $N = 1 \times 10^5$ | 1 (serial) | 0.000968 | 0.8047764894 | 5.4e-09 |
| $N = 1 \times 10^6$ | 1 (serial) | 0.010901 | 0.8047764893 | 5.2e-11 |
| $N = 1 \times 10^7$ | 1 (serial) | 0.107087 | 0.8047764893 | 6.9e-14 |
| $N = 1 \times 10^8$ | 1 (serial) | 1.059926 | 0.8047764893 | 1.1e-11 |
| $N = 1 \times 10^9$ | 1 (serial) | 11.519314 | 0.8047764893 | 1.1e-10 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 2 | 0.000009 | 0.8047769251 | 5.4e-05 |
| $N = 1 \times 10^4$ | 2 | 0.000051 | 0.8047764937 | 5.4e-07 |
| $N = 1 \times 10^5$ | 2 | 0.000710 | 0.8047764894 | 5.4e-09 |
| $N = 1 \times 10^6$ | 2 | 0.006140 | 0.8047764893 | 5.2e-11 |
| $N = 1 \times 10^7$ | 2 | 0.059623 | 0.8047764893 | 4.3e-12 |
| $N = 1 \times 10^8$ | 2 | 0.524027 | 0.8047764893 | 1.1e-11 |
| $N = 1 \times 10^9$ | 2 | 5.177253 | 0.8047764893 | 6.7e-11 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 4 | 0.000007 | 0.8047769251 | 5.4e-05 |
| $N = 1 \times 10^4$ | 4 | 0.000033 | 0.8047764937 | 5.4e-07 |
| $N = 1 \times 10^5$ | 4 | 0.000305 | 0.8047764894 | 5.4e-09 |
| $N = 1 \times 10^6$ | 4 | 0.003324 | 0.8047764893 | 5.5e-11 |
| $N = 1 \times 10^7$ | 4 | 0.028832 | 0.8047764893 | 1.9e-12 |
| $N = 1 \times 10^8$ | 4 | 0.308925 | 0.8047764893 | 5.7e-12 |
| $N = 1 \times 10^9$ | 4 | 2.776161 | 0.8047764893 | 2.4e-11 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 8 | 0.000026 | 0.8047769251 | 5.4e-05 |
| $N = 1 \times 10^4$ | 8 | 0.000034 | 0.8047764937 | 5.4e-07 |
| $N = 1 \times 10^5$ | 8 | 0.000215 | 0.8047764894 | 5.4e-09 |
| $N = 1 \times 10^6$ | 8 | 0.001869 | 0.8047764893 | 5.4e-11 |
| $N = 1 \times 10^7$ | 8 | 0.024666 | 0.8047764893 | 1.9e-12 |
| $N = 1 \times 10^8$ | 8 | 0.256151 | 0.8047764893 | 4.2e-12 |
| $N = 1 \times 10^9$ | 8 | 2.609726 | 0.8047764893 | 3.0e-12 |

### Lectura: el error

![Error del valor medio según la cantidad de procesos](img/error_por_procesos.png)

- **Hasta $N = 10^6$ el error baja de forma muy regular:** cada vez que N se multiplica por 10, el error se divide por 100. Por ejemplo, con $e^{-x^2}$: 1.4e-06 % → 1.4e-08 % → 1.4e-10 %.
- **Desde $N \approx 10^6$–$10^7$ el error deja de bajar** y oscila entre $10^{-13}$ y $10^{-10}$ %.
  - **Por qué:** la computadora guarda unos 16 dígitos por número. Al sumar $10^8$ alturas una por una se pierde un poquito en cada suma, y esas pérdidas se acumulan.
  - **Comprobación:** repetí la misma suma sin redondeo y el error del método a $N = 10^8$ es apenas $3 \times 10^{-15}$ %. Todo lo demás es redondeo.
  - **En la práctica:** $10^{-10}$ % es despreciable, pero **usar más de $10^6$ puntos no mejora el resultado**.
- **Paralelizar no cambia el error.**
  - Hasta $N = 10^5$ las cuatro curvas del gráfico coinciden exactamente: con 2, 4 u 8 procesos se evalúan los mismos puntos, solo se reparten.
  - Desde ahí aparecen diferencias en los últimos dígitos, porque se suma en otro orden. A veces el error con más procesos es algo mayor y a veces menor, pero **siempre queda por debajo de $10^{-10}$ %**, igual que el serial. Con N muy grande ($10^8$–$10^9$) suele ser menor, porque cada proceso suma menos números y acumula menos redondeo.

### Lectura: el tiempo y el speedup

**Speedup** = tiempo serial / tiempo paralelo: cuántas veces más rápido. **Eficiencia** = speedup / procesos: 100 % significa que cada proceso agregado rinde por completo.

![Speedup y eficiencia del valor medio con MPI](img/speedup.png)

Speedup promedio de las dos funciones (eficiencia entre paréntesis):

| $N$ | 2 procesos | 4 procesos | 8 procesos ⚠️ |
| :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 0.97x (49 %) | 1.09x (27 %) | 0.33x (4 %) |
| $N = 1 \times 10^4$ | 1.85x (92 %) | 2.55x (64 %) | 2.19x (27 %) |
| $N = 1 \times 10^5$ | 1.58x (79 %) | 3.27x (82 %) | 3.70x (46 %) |
| $N = 1 \times 10^6$ | 1.64x (82 %) | 2.94x (73 %) | 5.14x (64 %) |
| $N = 1 \times 10^7$ | 1.70x (85 %) | 3.25x (81 %) | 3.94x (49 %) |
| $N = 1 \times 10^8$ | 1.82x (91 %) | 3.09x (77 %) | 4.30x (54 %) |

- **Con $N = 10^3$ paralelizar no conviene:** el cálculo dura microsegundos, y repartir el trabajo y juntar los resultados cuesta más que hacerlo directamente.
- **Desde $N = 10^4$:**
  - 2 procesos van **1.6 a 1.9 veces más rápido**, con eficiencia de 80–90 %.
  - 4 procesos van **2.5 a 3.3 veces más rápido**, con eficiencia de 65–80 %. Rinden un poco menos por proceso porque ocupan todos los núcleos y compiten con Windows y WSL.
- **No usar los resultados con 8 procesos:** la CPU tiene 4 núcleos, así que un speedup de 5.14x es imposible. Cuando hay más procesos que núcleos, la forma de medir (esperar a todos y tomar el reloj del proceso 0) deja de ser confiable.
- **$N = 10^9$ no está en esta tabla:** con solo 3 ejecuciones dio eficiencias de más del 100 %, que tampoco son reales y se deben al ruido del entorno.

### Lectura: tiempo total, incluido el arranque de MPI

Los tiempos de las tablas en principio no incluyen el arranque del programa. Este gráfico mide el tiempo total de los programas originales, que calculan las dos funciones, con la mediana de 5 ejecuciones:

![Tiempo total incluyendo el arranque de MPI](img/tiempo_total.png)

- **MPI tarda entre 0.55 y 1 segundo solo en arrancar**, aunque después el cálculo sea instantáneo.
- Con $N = 10^3$ o $10^6$ el programa serial termina en 0.03–0.05 s, y cualquier versión con MPI tarda 0.55 s o más.
- **Recién cerca de $N = 10^8$** el cálculo dura lo suficiente para que paralelizar compense el arranque.

---

## Método de muestreo aleatorio

`muestreo_aleatorio_serial.c` usa una **semilla fija**: cada ejecución da exactamente el mismo resultado, y solo se promedia el tiempo. Las mediciones con más procesos están en [Versión con MPI](#versión-con-mpi).

### Mediciones para $e^{-x^2}$

Para calcular el error relativo se utiliza un valor de referencia igual a $0.8820813907$. Tiempo: promedio de 10 ejecuciones.

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 1 (serial) | 0.000013 | 0.9098117817 | 3.143745 |
| $N = 1 \times 10^4$ | 1 (serial) | 0.000099 | 0.8822185492 | 0.015549 |
| $N = 1 \times 10^5$ | 1 (serial) | 0.001041 | 0.8836481523 | 0.177621 |
| $N = 1 \times 10^6$ | 1 (serial) | 0.010236 | 0.8833274987 | 0.141269 |
| $N = 1 \times 10^7$ | 1 (serial) | 0.109270 | 0.8821851729 | 0.011766 |
| $N = 1 \times 10^8$ | 1 (serial) | 1.087412 | 0.8821465345 | 0.007385 |

### Mediciones para $\sin(x^2)$

Para calcular el error relativo se utiliza un valor de referencia igual a $0.8047764893$. Tiempo: promedio de 10 ejecuciones.

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 1 (serial) | 0.000025 | 0.7837681271 | 2.610459 |
| $N = 1 \times 10^4$ | 1 (serial) | 0.000234 | 0.7966625256 | 1.008226 |
| $N = 1 \times 10^5$ | 1 (serial) | 0.002573 | 0.8053299116 | 0.068767 |
| $N = 1 \times 10^6$ | 1 (serial) | 0.026064 | 0.8059389043 | 0.144439 |
| $N = 1 \times 10^7$ | 1 (serial) | 0.263809 | 0.8045575535 | 0.027205 |
| $N = 1 \times 10^8$ | 1 (serial) | 2.599077 | 0.8047395852 | 0.004586 |

### Lectura: el error

![Error relativo de ambos métodos según N](img/error_vs_n.png)

- **El error baja, pero lento y a los saltos.** Con $e^{-x^2}$, $N = 10^4$ dio 0.016 % y $N = 10^5$ dio 0.18 %, más error con más puntos. Es el azar: algunas tiradas salen mejor que otras.
- La **línea punteada** es el error "típico" que calcula el propio programa para cada N. Los resultados reales andan alrededor de esa línea, que baja a razón de **÷10 cada ×100 puntos**.
- **Frente al valor medio:** con $N = 10^6$ el muestreo aleatorio tiene 0.14 % de error y el valor medio $2 \times 10^{-13}$ %.

### Lectura: precisión según el tiempo invertido

![Precisión obtenida según el tiempo](img/error_vs_tiempo.png)

- Con el mismo tiempo de cálculo, **el valor medio es muchísimo más preciso** en una dimensión. El muestreo aleatorio además cuesta más por punto, porque tiene que generar el número al azar: $10^8$ puntos tardan 1.09 s contra 0.77 s con $e^{-x^2}$, y 2.60 s contra 1.06 s con $\sin(x^2)$.
- Para bajar de 0.01 % de error, el muestreo aleatorio necesitó $10^8$ puntos, es decir de 1 a 2.6 segundos. El valor medio lo logra con 100 puntos, en microsegundos.

### Versión con MPI

Programa: `muestreo_aleatorio_hpc.c`, es una versión paralela corregida del muestreo aleatorio que le copié a Ignacio. Cada proceso elige al azar su parte de los puntos y al final se suman los resultados.

Diferencias con las tablas anteriores:

- **Tiempo: mediana de 10 ejecuciones**, no promedio. Algunas ejecuciones sueltas tardaron hasta 165 veces más por ruido del sistema, y con el promedio aparecían speedups imposibles, como 4.5x con 2 procesos.
- **El speedup se calcula contra 1 proceso de este mismo programa**, no contra `muestreo_aleatorio_serial.c`, porque el serial usa otro generador de números al azar, más rápido. Ver [Lectura: el speedup con MPI](#lectura-el-speedup-con-mpi).

### Mediciones con MPI para $e^{-x^2}$

Para calcular el error relativo se utiliza un valor de referencia igual a $0.8820813907$. Tiempo: mediana de 10 ejecuciones.

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 1 | 0.000046 | 0.8931810603 | 1.258350 |
| $N = 1 \times 10^4$ | 1 | 0.000209 | 0.8929286440 | 1.229734 |
| $N = 1 \times 10^5$ | 1 | 0.001874 | 0.8796017207 | 0.281116 |
| $N = 1 \times 10^6$ | 1 | 0.022982 | 0.8823241121 | 0.027517 |
| $N = 1 \times 10^7$ | 1 | 0.245903 | 0.8822575913 | 0.019976 |
| $N = 1 \times 10^8$ | 1 | 2.364920 | 0.8820884516 | 0.000800 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 2 | 0.000063 | 0.8775029069 | 0.519055 |
| $N = 1 \times 10^4$ | 2 | 0.000157 | 0.8771613586 | 0.557775 |
| $N = 1 \times 10^5$ | 2 | 0.001112 | 0.8821909936 | 0.012425 |
| $N = 1 \times 10^6$ | 2 | 0.013336 | 0.8820349025 | 0.005270 |
| $N = 1 \times 10^7$ | 2 | 0.127098 | 0.8825150304 | 0.049161 |
| $N = 1 \times 10^8$ | 2 | 1.246757 | 0.8820732008 | 0.000928 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 4 | 0.000072 | 0.8687444376 | 1.511987 |
| $N = 1 \times 10^4$ | 4 | 0.000122 | 0.8933042495 | 1.272316 |
| $N = 1 \times 10^5$ | 4 | 0.000631 | 0.8788948135 | 0.361257 |
| $N = 1 \times 10^6$ | 4 | 0.007513 | 0.8825393504 | 0.051918 |
| $N = 1 \times 10^7$ | 4 | 0.076511 | 0.8820877207 | 0.000718 |
| $N = 1 \times 10^8$ | 4 | 0.724099 | 0.8820541091 | 0.003093 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 8 | 0.000076 | 0.9088249745 | 3.031873 |
| $N = 1 \times 10^4$ | 8 | 0.000118 | 0.8755119417 | 0.744767 |
| $N = 1 \times 10^5$ | 8 | 0.000663 | 0.8833791428 | 0.147124 |
| $N = 1 \times 10^6$ | 8 | 0.006033 | 0.8838122884 | 0.196229 |
| $N = 1 \times 10^7$ | 8 | 0.059999 | 0.8822819458 | 0.022737 |
| $N = 1 \times 10^8$ | 8 | 0.630073 | 0.8820698479 | 0.001309 |

### Mediciones con MPI para $\sin(x^2)$

Para calcular el error relativo se utiliza un valor de referencia igual a $0.8047764893$. Tiempo: mediana de 10 ejecuciones.

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 1 | 0.000044 | 0.8190317579 | 1.771333 |
| $N = 1 \times 10^4$ | 1 | 0.000317 | 0.7927915167 | 1.489230 |
| $N = 1 \times 10^5$ | 1 | 0.003140 | 0.8055972036 | 0.101980 |
| $N = 1 \times 10^6$ | 1 | 0.042662 | 0.8047915697 | 0.001874 |
| $N = 1 \times 10^7$ | 1 | 0.410594 | 0.8047076172 | 0.008558 |
| $N = 1 \times 10^8$ | 1 | 3.603016 | 0.8047992819 | 0.002832 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 2 | 0.000036 | 0.8320423522 | 3.388004 |
| $N = 1 \times 10^4$ | 2 | 0.000211 | 0.7937660355 | 1.368138 |
| $N = 1 \times 10^5$ | 2 | 0.001805 | 0.8108395555 | 0.753385 |
| $N = 1 \times 10^6$ | 2 | 0.020480 | 0.8040825826 | 0.086224 |
| $N = 1 \times 10^7$ | 2 | 0.205615 | 0.8047652082 | 0.001402 |
| $N = 1 \times 10^8$ | 2 | 1.828716 | 0.8047158019 | 0.007541 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 4 | 0.000026 | 0.7576513669 | 5.855678 |
| $N = 1 \times 10^4$ | 4 | 0.000106 | 0.7948871538 | 1.228830 |
| $N = 1 \times 10^5$ | 4 | 0.001593 | 0.8077170165 | 0.365384 |
| $N = 1 \times 10^6$ | 4 | 0.015297 | 0.8042941025 | 0.059940 |
| $N = 1 \times 10^7$ | 4 | 0.121965 | 0.8051272644 | 0.043587 |
| $N = 1 \times 10^8$ | 4 | 1.220403 | 0.8047428140 | 0.004184 |

| $N$ (Simulaciones) | Procesos | Tiempo de Ejecución (segs) | Valor Aproximado | Error Relativo (%) |
| :--- | :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 8 | 0.000096 | 0.8022213882 | 0.317492 |
| $N = 1 \times 10^4$ | 8 | 0.000168 | 0.7921377274 | 1.570469 |
| $N = 1 \times 10^5$ | 8 | 0.001027 | 0.8069312429 | 0.267746 |
| $N = 1 \times 10^6$ | 8 | 0.011210 | 0.8046244393 | 0.018893 |
| $N = 1 \times 10^7$ | 8 | 0.107097 | 0.8046319459 | 0.017961 |
| $N = 1 \times 10^8$ | 8 | 0.996736 | 0.8048438094 | 0.008365 |

### Lectura: el speedup con MPI

![Speedup y eficiencia del muestreo aleatorio con MPI](img/speedup_muestreo.png)

Speedup frente a 1 proceso, promedio de las dos funciones (eficiencia entre paréntesis):

| $N$ | 2 procesos | 4 procesos | 8 procesos ⚠️ |
| :--- | :--- | :--- | :--- |
| $N = 1 \times 10^3$ | 0.98x (49 %) | 1.18x (29 %) | 0.54x (7 %) |
| $N = 1 \times 10^4$ | 1.42x (71 %) | 2.36x (59 %) | 1.84x (23 %) |
| $N = 1 \times 10^5$ | 1.71x (86 %) | 2.47x (62 %) | 2.94x (37 %) |
| $N = 1 \times 10^6$ | 1.90x (95 %) | 2.92x (73 %) | 3.81x (48 %) |
| $N = 1 \times 10^7$ | 1.97x (98 %) | 3.29x (82 %) | 3.97x (50 %) |
| $N = 1 \times 10^8$ | 1.93x (97 %) | 3.11x (78 %) | 3.68x (46 %) |

- **Con $N = 10^3$ paralelizar no conviene**, igual que en el valor medio: el cálculo dura microsegundos.
- **Desde $N = 10^6$:**
  - 2 procesos van **1.9 a 2.0 veces más rápido**, con eficiencia de 95–98 %.
  - 4 procesos van **2.9 a 3.3 veces más rápido**, con eficiencia de 73–82 %.
  - Con 2 procesos escala mejor que el valor medio (80–90 %). Probablemente porque cada punto cuesta más (hay que generar el número al azar), y entonces repartir y juntar pesa menos en proporción.
- **8 procesos:** igual que antes, hay más procesos que núcleos y la medición no es confiable.
- **`rand()` es lento.** Con 1 proceso, este programa tarda **1.3 a 2.4 veces más** que `muestreo_aleatorio_serial.c`, que usa el generador xorshift. Con $N = 10^8$ y $e^{-x^2}$: 2.36 s contra 1.08 s. Es decir, con 2 procesos (1.25 s) recién iguala al serial con 1 proceso. Cambiar el generador rinde casi lo mismo que duplicar los procesos (ver [`sugerencias-codigo.md`](sugerencias-codigo.md), punto 3).

### Lectura: el error con MPI

![Error del muestreo aleatorio según la cantidad de procesos](img/error_muestreo_procesos.png)

- **Paralelizar no cambia el error.** Con 1, 2, 4 u 8 procesos el error promedio de 10 ejecuciones es prácticamente el mismo y sigue la línea punteada: **÷10 cada ×100 puntos**. Por ejemplo, con $e^{-x^2}$ y $N = 10^6$: 0.060 %, 0.059 %, 0.053 % y 0.069 %.
- A diferencia del valor medio, con más procesos no se evalúan los mismos puntos, porque cada proceso tiene su propia semilla. Pero la cantidad total de puntos es la misma, y de eso depende la precisión.
- En las tablas, una ejecución suelta puede salir mucho mejor o peor que otra. Por ejemplo, con $e^{-x^2}$ y $N = 10^7$: 0.049 % con 2 procesos y 0.0007 % con 4. Es el azar, no la cantidad de procesos.
