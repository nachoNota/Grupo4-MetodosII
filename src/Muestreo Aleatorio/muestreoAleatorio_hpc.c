#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

double f_exponencial(double x) {
    return exp(-(x * x));
}

double f_seno(double x) {
    return sin(x * x);
}

double monte_carlo_acierto_error_mpi(double (*f)(double), double x_min, double x_max, double y_min, double y_max, long long n, int rank, int size) {
    
    long long aciertos_locales = 0;
    long long aciertos_totales = 0;
    
    // Distribucion ciclica
    for (long long i = rank; i < n; i += size) {
        double x = x_min + (x_max - x_min) * ((double)rand() / RAND_MAX);
        double y = y_min + (y_max - y_min) * ((double)rand() / RAND_MAX);
        
        double fx = f(x);
        
        // Verifica si cae dentro del area positiva
        if (fx >= 0.0 && y >= 0.0 && y <= fx) {
            aciertos_locales++;
        }
        // Verifica si cae dentro del area negativa (resta al total)
        else if (fx < 0.0 && y < 0.0 && y >= fx) {
            aciertos_locales--; 
        }
    }
    
    MPI_Reduce(&aciertos_locales, &aciertos_totales, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        double area_caja = (x_max - x_min) * (y_max - y_min);
        double proporcion = (double)aciertos_totales / (double)n;
        return area_caja * proporcion;
    }
    return 0.0;
}

static void calcular(const char *nombre, double (*f)(double), double x_min, double x_max, double y_min, double y_max, long long n, int rank, int size) {
    
    double t0 = MPI_Wtime();
    double resultado = monte_carlo_acierto_error_mpi(f, x_min, x_max, y_min, y_max, n, rank, size);
    double t1 = MPI_Wtime();
    
    if (rank == 0) {
        printf("%-10s | Integral en [%g, %g] | N = %lld | Area: %.10f | Tiempo: %.9f s\n",
               nombre, x_min, x_max, n, resultado, t1 - t0);
    }
}

int main(int argc, char **argv) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long n = (argc > 1) ? atoll(argv[1]) : 50000000LL;

    // Semilla independiente por proceso
    unsigned int semilla = (argc > 2) ? (unsigned int)atoi(argv[2]) : (unsigned int)time(NULL);
    MPI_Bcast(&semilla, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    srand(semilla + 7919 * rank);

    if (rank == 0) {
        printf("--- FASE 2: MONTE CARLO ACIERTO Y ERROR (%d procesos) ---\n", size);
    }

    // Warmup
    monte_carlo_acierto_error_mpi(f_exponencial, 0.0, 2.0, 0.0, 1.0, 100000, rank, size);

    calcular("exp(-x^2)", f_exponencial, 0.0, 2.0, 0.0, 1.0, n, rank, size);
    calcular("sin(x^2)",  f_seno,        0.0, 2.0, -1.0, 1.0, n, rank, size);

    MPI_Finalize();
    return 0;
}