#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

double f_exponencial(double x){
  return exp(-x * x);
}

double f_seno(double x){
  return sin(x*x);
}

/* Método del valor medio (punto medio) con n subintervalos, en paralelo con MPI.
   Cada proceso suma los índices i = rank, rank+size, ... (reparto cíclico, que
   balancea la carga aunque n no sea divisible entre size) y luego se reducen
   las sumas parciales en el rango 0.
   I ≈ h * sum f(a + (i + 0.5) h),  h = (b - a) / n */
double valor_medio_mpi(double (*f)(double), double a, double b, long n, int rank, int size){
  double h = (b - a) / n;
  double suma_local = 0.0, suma_total = 0.0;
  for (long i = rank; i < n; i += size){
    suma_local += f(a + (i + 0.5) * h);
  }
  MPI_Reduce(&suma_local, &suma_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  return h * suma_total;   /* solo válido en rank 0 */
}

static void calcular(const char *nombre, double (*f)(double), double a, double b,
                     long n, int rank, int size){
  MPI_Barrier(MPI_COMM_WORLD);
  double t0 = MPI_Wtime();
  double resultado = valor_medio_mpi(f, a, b, n, rank, size);
  MPI_Barrier(MPI_COMM_WORLD);
  double t1 = MPI_Wtime();
  if (rank == 0){
    printf("%-14s integral en [%g, %g] con n=%ld: %.12f | procesos: %d | tiempo (MPI): %.6f s\n",
           nombre, a, b, n, resultado, size, t1 - t0);
  }
}

int main(int argc, char **argv){
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long n = (argc > 1) ? atol(argv[1]) : 100000000L;
  double a = 0.0, b = 1.0;
  if (n <= 0){
    if (rank == 0) fprintf(stderr, "Uso: mpirun -np P %s [n > 0]\n", argv[0]);
    MPI_Finalize();
    return 1;
  }

  calcular("exp(-x^2)", f_exponencial, a, b, n, rank, size);
  calcular("sin(x^2)", f_seno, a, b, n, rank, size);

  MPI_Finalize();
  return 0;
}
