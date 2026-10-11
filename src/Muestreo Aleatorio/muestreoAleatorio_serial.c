#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double f_exponencial(double x) {
    return exp(-(x * x));
}

double f_seno(double x) {
    return sin(x * x);
}

double monte_carlo_acierto_error_serial(double (*f)(double), double x_min, double x_max, double y_min, double y_max, long long n) {
    long long aciertos_totales = 0;
    
    for (long long i = 0; i < n; i++) {
        double x = x_min + (x_max - x_min) * ((double)rand() / RAND_MAX);
        double y = y_min + (y_max - y_min) * ((double)rand() / RAND_MAX);
        
        double fx = f(x);
        
        if (fx >= 0.0 && y >= 0.0 && y <= fx) {
            aciertos_totales++;
        }
        else if (fx < 0.0 && y < 0.0 && y >= fx) {
            aciertos_totales--;
        }
    }
    
    double area_caja = (x_max - x_min) * (y_max - y_min);
    double proporcion = (double)aciertos_totales / (double)n;
    return area_caja * proporcion;
}

static void calcular(const char *nombre, double (*f)(double), double x_min, double x_max, double y_min, double y_max, long long n) {
    
    clock_t t0 = clock();
    double resultado = monte_carlo_acierto_error_serial(f, x_min, x_max, y_min, y_max, n);
    clock_t t1 = clock();
    
    double tiempo_ejecucion = (double)(t1 - t0) / CLOCKS_PER_SEC;
    
    printf("%-10s | Integral en [%g, %g] | N = %lld | Area: %.10f | Tiempo: %.6f s\n",
           nombre, x_min, x_max, n, resultado, tiempo_ejecucion);
}

int main(int argc, char **argv) {
    long long n = (argc > 1) ? atoll(argv[1]) : 50000000LL;

    srand(time(NULL));

    printf("--- FASE 2: MONTE CARLO ACIERTO Y ERROR (SERIAL) ---\n");

    calcular("exp(-x^2)", f_exponencial, 0.0, 2.0, 0.0, 1.0, n);
    calcular("sin(x^2)",  f_seno,        0.0, 2.0, -1.0, 1.0, n);

    return 0;
}