#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

// Figura 1: Círculo de radio 1 (x^2 + y^2 <= 1)
int f_circulo(double x, double y) {
    if ((x * x) + (y * y) <= 1.0) {
        return 1;
    }
    return 0;
}

// Figura 2: Una elipse irregular (x^2 + 4*y^2 <= 1)
int f_elipse(double x, double y) {
    if ((x * x) + 4.0 * (y * y) <= 1.0) {
        return 1;
    }
    return 0;
}

double monte_carlo_2d_mpi(int (*figura)(double, double), double x_min, double x_max, double y_min, double y_max, long long n, int rank, int size) {
    
    srand(time(NULL) + (rank * 100));
    
    long long aciertos_locales = 0;
    long long aciertos_totales = 0;
    
    // distribucion ciclica
    for (long long i = rank; i < n; i += size) {
        double x = x_min + (x_max - x_min) * ((double)rand() / RAND_MAX);
        double y = y_min + (y_max - y_min) * ((double)rand() / RAND_MAX);
        
        aciertos_locales += figura(x, y);
    }
    
    MPI_Reduce(&aciertos_locales, &aciertos_totales, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        double area_caja = (x_max - x_min) * (y_max - y_min);
        double proporcion = (double)aciertos_totales / (double)n;
        return area_caja * proporcion;
    }
    return 0.0;
}

static void calcular_2d(const char *nombre, int (*figura)(double, double), double x_min, double x_max, double y_min, double y_max, long long n, int rank, int size) {
    
    MPI_Barrier(MPI_COMM_WORLD);
    double t0 = MPI_Wtime();
    
    double resultado = monte_carlo_2d_mpi(figura, x_min, x_max, y_min, y_max, n, rank, size);
    
    MPI_Barrier(MPI_COMM_WORLD);
    double t1 = MPI_Wtime();
    
    if (rank == 0) {
        printf("%-15s | N = %lld | Area: %.10f | Tiempo: %.6f s\n",
               nombre, n, resultado, t1 - t0);
    }
}

int main(int argc, char **argv) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long n = (argc > 1) ? atoll(argv[1]) : 50000000LL;

    double x_min = -1.0, x_max = 1.0;
    double y_min = -1.0, y_max = 1.0;

    if (n <= 0) {
        if (rank == 0) printf("Uso: mpirun -np P %s [n > 0]\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        printf("--- FASE 2: MONTE CARLO ACIERTO Y ERROR (%d procesos) ---\n", size);
        printf("Area de la caja (Bounding Box) = %.2f\n", (x_max - x_min) * (y_max - y_min));
    }

    calcular_2d("Circulo r=1", f_circulo, x_min, x_max, y_min, y_max, n, rank, size);
    calcular_2d("Elipse",      f_elipse,  x_min, x_max, y_min, y_max, n, rank, size);

    MPI_Finalize();
    return 0;
}