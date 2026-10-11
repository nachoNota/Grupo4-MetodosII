# Integración numérica y áreas irregulares con Monte Carlo en paralelo (MPI)

Proyecto 4: Integración Numérica y Cálculo de Áreas Irregulares.

Implementación en C con MPI de dos métodos de Monte Carlo, y un estudio de su convergencia, tiempo de ejecución, speedup y eficiencia:

- **Método del valor medio:** aproxima integrales definidas en una dimensión, promediando el valor de la función en puntos aleatorios.
- **Muestreo aleatorio (acierto y fallo):** aproxima el área de figuras irregulares contando cuántos puntos aleatorios caen dentro de la figura. También sirve para las dos integrales anteriores.

## Características

- Paralelización con MPI: reparto cíclico de las simulaciones entre procesos y una única reducción final (`MPI_Reduce`).
- Semillas independientes por proceso: la semilla base se reparte con `MPI_Bcast` y cada proceso la desplaza según su rank.
- Tiempo medido con `MPI_Wtime` entre dos `MPI_Barrier` (tiempo del proceso más lento).

## Requisitos

- Compilador de C y una implementación de MPI con `mpicc` y `mpirun` (Open MPI o MPICH).

En Ubuntu/Debian:

```bash
sudo apt install build-essential openmpi-bin libopenmpi-dev
pip install numpy pandas matplotlib openpyxl
```

## Compilación

```bash
mpicc valor_medio.c -o valor_medio -lm
mpicc acierto_error.c -o acierto_error -lm
```

## Ejecución

```bash
mpirun -np <P> ./valor_medio <N> [semilla]
mpirun -np <P> ./acierto_error <N> [semilla]
```

- `P`: cantidad de procesos.
- `N`: cantidad de simulaciones (por defecto, 50 000 000).
- `semilla`: entero opcional; si se omite, se usa la hora del sistema. Usa una semilla distinta en cada corrida.

Ejemplo y salida (los valores varían con la semilla):

```text
$ mpirun -np 2 ./valor_medio 1000000 42
--- FASE 1: MONTE CARLO VALOR MEDIO (2 procesos) ---
exp(-x^2)  | Integral en [0, 2] | N = 1000000 | Area: 0.8823921894 | Tiempo: 0.014543252 s
sin(x^2)   | Integral en [0, 2] | N = 1000000 | Area: 0.8057887451 | Tiempo: 0.024559357 s
```

Si `mpirun` se queja de que no hay suficientes slots (más procesos que núcleos), con Open MPI agregá `--oversubscribe`.


## Autores

- RIVERA OCTTAVIANO, Ramiro Tomas - Ingeniería en Informática  
- NIEVA OVEJERO, Joel Esteban  - Licenciatura en Informática
- NOTA, José Ignacio - Licenciatura en Informática
