#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    long long N_total = 10000000; // 10 millones de simulaciones totales
    long long hits_locales = 0;   // Aciertos de este proceso
    loasdng long hits_totales = 0;   // Aciertos sumados de todos los procesos

    // 1. Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double t_inicio = MPI_Wtime(); // Iniciar medición de tiempo

    // 2. Semilla aleatoria (¡CRÍTICO en Monte Carlo paralelo!)
    // Cada proceso DEBE tener una semilla distinta, por eso sumamos el 'rank'
    srand(time(NULL) + rank * 1999); 

    // 3. Dividir el trabajo equitativamente
    long long N_local = N_total / size;

    // 4. Bucle principal de Monte Carlo (Lanzar los dardos)
    for (long long i = 0; i < N_local; i++) {
        // Generar coordenadas aleatorias (x, y) entre 0.0 y 1.0
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        
        // Evaluar si el punto cayó dentro de la figura (Ecuación del círculo: x^2 + y^2 <= 1)
        if ((x * x) + (y * y) <= 1.0) {
            hits_locales++; // ¡Acierto!
        }
    }

    // 5. Juntar los resultados de todos los procesos en el Rango 0
    MPI_Reduce(&hits_locales, &hits_totales, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // 6. Procesar el resultado final (Solo el Rango 0)
    if (rank == 0) {
        // Multiplicamos por 4 porque simulamos solo en un cuadrante (1/4 del círculo)
        double area_calculada = 4.0 * ((double)hits_totales / (double)N_total);
        double t_fin = MPI_Wtime();
        
        printf("Simulaciones (N): %lld\n", N_total);
        printf("Area / Valor de Pi: %f\n", area_calculada);
        printf("Tiempo de ejecucion: %f segundos\n", t_fin - t_inicio);
    }

    MPI_Finalize();
    return 0;
}