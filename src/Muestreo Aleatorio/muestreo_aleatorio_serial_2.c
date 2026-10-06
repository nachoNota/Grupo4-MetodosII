#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

double monte_carlo_2d_serial(int (*figura)(double, double), double x_min, double x_max, double y_min, double y_max, long long n) {
    
    long long aciertos_totales = 0;
    
    for (long long i = 0; i < n; i++) {
        double x = x_min + (x_max - x_min) * ((double)rand() / RAND_MAX);
        double y = y_min + (y_max - y_min) * ((double)rand() / RAND_MAX);
        
        aciertos_totales += figura(x, y);
    }
    
    double area_caja = (x_max - x_min) * (y_max - y_min);
    double proporcion = (double)aciertos_totales / (double)n;
    return area_caja * proporcion;
}

static void calcular_2d(const char *nombre, int (*figura)(double, double), double x_min, double x_max, double y_min, double y_max, long long n) {
    
    clock_t t0 = clock();
    
    double resultado = monte_carlo_2d_serial(figura, x_min, x_max, y_min, y_max, n);
    
    clock_t t1 = clock();
    double tiempo_ejecucion = (double)(t1 - t0) / CLOCKS_PER_SEC;
    
    printf("%-15s | N = %lld | Area: %.10f | Tiempo: %.6f s\n",
           nombre, n, resultado, tiempo_ejecucion);
}

int main(int argc, char **argv) {
    long long n = (argc > 1) ? atoll(argv[1]) : 50000000LL;

    double x_min = -1.0, x_max = 1.0;
    double y_min = -1.0, y_max = 1.0;

    if (n <= 0) {
        printf("Uso: %s [n > 0]\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    printf("--- FASE 2: MONTE CARLO ACIERTO Y ERROR (SERIAL) ---\n");
    printf("Area de la caja (Bounding Box) = %.2f\n", (x_max - x_min) * (y_max - y_min));

    calcular_2d("Circulo r=1", f_circulo, x_min, x_max, y_min, y_max, n);
    calcular_2d("Elipse",      f_elipse,  x_min, x_max, y_min, y_max, n);

    return 0;
}