#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double f_exponencial(double x){
  return exp(-x * x);
}

double f_seno(double x){
  return sin(x*x);
}

/* Método del valor medio (punto medio) con n subintervalos:
   I ≈ h * sum f(a + (i + 0.5) h),  h = (b - a) / n */
double valor_medio(double (*f)(double), double a, double b, long n){
  double h = (b - a) / n;
  double suma = 0.0;
  for (long i = 0; i < n; i++){
    suma += f(a + (i + 0.5) * h);
  }
  return h * suma;
}

static double tiempo_actual(void){
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1e-9;
}

static void calcular(const char *nombre, double (*f)(double), double a, double b, long n){
  double t0 = tiempo_actual();
  double resultado = valor_medio(f, a, b, n);
  double t1 = tiempo_actual();
  printf("%-14s integral en [%g, %g] con n=%ld: %.12f | tiempo (serial): %.6f s\n",
         nombre, a, b, n, resultado, t1 - t0);
}

int main(int argc, char **argv){
  long n = (argc > 1) ? atol(argv[1]) : 100000000L;
  double a = 0.0, b = 1.0;
  if (n <= 0){
    fprintf(stderr, "Uso: %s [n > 0]\n", argv[0]);
    return 1;
  }

  calcular("exp(-x^2)", f_exponencial, a, b, n);
  calcular("sin(x^2)", f_seno, a, b, n);
  return 0;
}
