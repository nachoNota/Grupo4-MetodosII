#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

double f_exponencial(double x){
  return exp(-x * x);
}

double f_seno(double x){
  return sin(x*x);
}

/* Generador xorshift64*: rápido y de calidad suficiente para Monte Carlo. */
static uint64_t estado;

static double uniforme01(void){
  estado ^= estado >> 12;
  estado ^= estado << 25;
  estado ^= estado >> 27;
  uint64_t r = estado * 2685821657736338717ULL;
  return (r >> 11) * (1.0 / 9007199254740992.0);   /* [0, 1) con 53 bits */
}

/* Muestreo aleatorio (Monte Carlo): x_i ~ U(a, b),
   I ≈ (b - a) / n * sum f(x_i).
   Devuelve también el error estándar estimado en *error. */
double muestreo_aleatorio(double (*f)(double), double a, double b, long n, double *error){
  double suma = 0.0, suma2 = 0.0;
  for (long i = 0; i < n; i++){
    double fx = f(a + (b - a) * uniforme01());
    suma += fx;
    suma2 += fx * fx;
  }
  double media = suma / n;
  double varianza = suma2 / n - media * media;
  *error = (b - a) * sqrt(varianza / n);
  return (b - a) * media;
}

static double tiempo_actual(void){
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1e-9;
}

static void calcular(const char *nombre, double (*f)(double), double a, double b, long n){
  double error;
  double t0 = tiempo_actual();
  double resultado = muestreo_aleatorio(f, a, b, n, &error);
  double t1 = tiempo_actual();
  printf("%-14s integral en [%g, %g] con n=%ld: %.12f (error est. %.2e) | tiempo (serial): %.6f s\n",
         nombre, a, b, n, resultado, error, t1 - t0);
}

int main(int argc, char **argv){
  long n = (argc > 1) ? atol(argv[1]) : 100000000L;
  double a = 0.0, b = 1.0;
  if (n <= 0){
    fprintf(stderr, "Uso: %s [n > 0]\n", argv[0]);
    return 1;
  }

  estado = 88172645463325252ULL;   /* semilla fija: resultados reproducibles */

  calcular("exp(-x^2)", f_exponencial, a, b, n);
  calcular("sin(x^2)", f_seno, a, b, n);
  return 0;
}
