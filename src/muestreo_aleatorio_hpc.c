/* Versión paralela (MPI) del muestreo aleatorio: integra f_exponencial y f_seno
   promediando f en puntos elegidos al azar en [a, b], igual que
   muestreo_aleatorio_serial.c pero repartiendo los puntos entre procesos.

   CORRECCIÓN: reemplaza al muestreo_aleatorio_hpc.c anterior, que no compilaba
   (línea 10: "loasdng long hits_totales") y además calculaba pi tirando dardos
   en lugar de integrar estas funciones, así que no era la versión paralela del
   serial. Este código es valor_medio_hpc_2.c de la rama mediciones-ignacio
   (commit bd3f518), traído sin cambios: allí se llamaba "valor medio", pero es
   Monte Carlo (muestreo aleatorio).

   Pendiente (ver docs/sugerencias-codigo.md §3): usa rand() con semilla
   time(NULL) + rank, por lo que los resultados no son reproducibles y es más
   lento que el generador xorshift de la versión serial. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

// Definición de las funciones a integrar
double f_exponencial(double x) {
    return exp(-(x * x));
}

double f_seno(double x) {
    return sin(x * x);
}

double monte_carlo_mpi(double (*f)(double), double a, double b, long long n, int rank, int size) {
    srand(time(NULL) + rank);
    
    double suma_local = 0.0;
    double suma_total = 0.0;
    
    // distribucion ciclica 
    for (long long i = rank; i < n; i += size) {
        double x = a + (b - a) * ((double)rand() / RAND_MAX);
        suma_local += f(x);
    }
    
    MPI_Reduce(&suma_local, &suma_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // el rank 0 aplica la formula final 
    if (rank == 0) {
        double altura_promedio = suma_total / (double)n;
        return (b - a) * altura_promedio;
    }
    return 0.0;
}

static void calcular(const char *nombre, double (*f)(double), double a, double b, long long n, int rank, int size) {
    
    MPI_Barrier(MPI_COMM_WORLD); //para sincronizar relojes de todos los procesos
    double t0 = MPI_Wtime();
    
    double resultado = monte_carlo_mpi(f, a, b, n, rank, size);
    
    MPI_Barrier(MPI_COMM_WORLD);
    double t1 = MPI_Wtime();
    
    if (rank == 0) {
        printf("%-10s | Integral en [%g, %g] | N = %lld | Area: %.10f | Tiempo: %.6f s\n",
               nombre, a, b, n, resultado, t1 - t0);
    }
}

int main(int argc, char **argv) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long n = (argc > 1) ? atoll(argv[1]) : 50000000LL;
    double a = 0.0, b = 2.0;

    if (rank == 0) {
        printf("--- FASE 1: MONTE CARLO VALOR MEDIO (%d procesos) ---\n", size);
    }

    calcular("exp(-x^2)", f_exponencial, a, b, n, rank, size);
    calcular("sin(x^2)",  f_seno,        a, b, n, rank, size);

    MPI_Finalize();
    return 0;
}