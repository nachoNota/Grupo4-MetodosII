#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Definición de las funciones a integrar
double f_exponencial(double x) {
    return exp(-(x * x));
}

double f_seno(double x) {
    return sin(x * x);
}

double monte_carlo_serial(double (*f)(double), double a, double b, long long n) {
    double suma_total = 0.0;
    
    for (long long i = 0; i < n; i++) {
        double x = a + (b - a) * ((double)rand() / RAND_MAX);
        suma_total += f(x);
    }
    
    double altura_promedio = suma_total / (double)n;
    return (b - a) * altura_promedio;
}

static void calcular(const char *nombre, double (*f)(double), double a, double b, long long n) {
    
    clock_t t0 = clock();
    
    double resultado = monte_carlo_serial(f, a, b, n);
    
    clock_t t1 = clock();
    double tiempo_ejecucion = (double)(t1 - t0) / CLOCKS_PER_SEC;
    
    printf("%-10s | Integral en [%g, %g] | N = %lld | Area: %.10f | Tiempo: %.6f s\n",
           nombre, a, b, n, resultado, tiempo_ejecucion);
}

int main(int argc, char **argv) {
    long long n = (argc > 1) ? atoll(argv[1]) : 50000000LL;
    double a = 0.0, b = 2.0;

    srand(time(NULL));

    printf("--- FASE 1: MONTE CARLO VALOR MEDIO (SERIAL) ---\n");

    calcular("exp(-x^2)", f_exponencial, a, b, n);
    calcular("sin(x^2)",  f_seno,        a, b, n);

    return 0;
}