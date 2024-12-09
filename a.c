#include <stdio.h>
#include <gmp.h> // Biblioteca para manejo de números grandes
#include <stdlib.h>
#include <time.h> // Biblioteca para medir el tiempo


// Función para determinar si un número es primo
int is_prime(mpz_t n) {
    if (mpz_cmp_ui(n, 2) < 0) return 0; // Números menores a 2 no son primos
    if (mpz_cmp_ui(n, 2) == 0) return 1; // 2 es primo

    mpz_t i, sqrt_n, remainder;
    mpz_inits(i, sqrt_n, remainder, NULL);

    // Calcular raíz cuadrada de n
    mpz_sqrt(sqrt_n, n);

    // Iterar desde 2 hasta √n
    for (mpz_set_ui(i, 2); mpz_cmp(i, sqrt_n) <= 0; mpz_add_ui(i, i, 1)) {
        mpz_mod(remainder, n, i);
        if (mpz_cmp_ui(remainder, 0) == 0) {
            mpz_clears(i, sqrt_n, remainder, NULL);
            return 0; // Divisible, no es primo
        }
    }

    mpz_clears(i, sqrt_n, remainder, NULL);
    return 1; // Es primo
}

// Función para factorizar un número usando Trial Division
void trial_division_factorization(mpz_t n) {
    printf("Factores primos:\n");

    mpz_t factor, exp, remainder, sqrt_n;
    mpz_inits(factor, exp, remainder, sqrt_n, NULL);

    // Calcular √n
    mpz_sqrt(sqrt_n, n);

    // Iterar desde 2 hasta √n
    for (mpz_set_ui(factor, 2); mpz_cmp(factor, sqrt_n) <= 0; mpz_add_ui(factor, factor, 1)) {
        if (!is_prime(factor)) continue; // Saltar números no primos

        // Inicializar exponente
        mpz_set_ui(exp, 0);

        // Dividir n por factor mientras sea divisible
        while (1) {
            mpz_mod(remainder, n, factor);
            if (mpz_cmp_ui(remainder, 0) != 0) break;

            mpz_divexact(n, n, factor); // n = n / factor
            mpz_add_ui(exp, exp, 1);    // Incrementar exponente
        }

        // Si el factor aparece al menos una vez, imprimirlo
        if (mpz_cmp_ui(exp, 0) > 0) {
            gmp_printf("%Zd^%Zd\n", factor, exp);
        }

        // Recalcular √n en cada iteración
        mpz_sqrt(sqrt_n, n);
    }

    // Si queda un factor mayor que √n
    if (mpz_cmp_ui(n, 1) > 0) {
        gmp_printf("%Zd^1\n", n);
    }

    // Liberar memoria
    mpz_clears(factor, exp, remainder, sqrt_n, NULL);
}

int main() {
      // Variables para medir el tiempo
    clock_t start, end;
    double cpu_time_used;

    // Iniciar la medición del tiempo
    start = clock();

    // Inicializar el número n
    mpz_t n;
    mpz_init(n);

    // Pedir al usuario el número a factorizar
    printf("Ingresa un número grande para factorizar: ");
    gmp_scanf("%Zd", n);

    // Validar que el número sea mayor o igual a 2
    if (mpz_cmp_ui(n, 2) < 0) {
        printf("El número debe ser mayor o igual a 2.\n");
        mpz_clear(n);
        return 1;
    }

    // Factorizar el número
    trial_division_factorization(n);

    // Liberar memoria
    mpz_clear(n);
     // Finalizar la medición del tiempo
    end = clock();

    // Calcular el tiempo de CPU usado
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Mostrar el tiempo de ejecución
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);

    return 0;
}