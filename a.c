#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// Función para cribar números primos hasta √n usando el método de Eratóstenes
void sieve_of_eratosthenes(int n, int *primes, int *prime_count) {
    // Límite superior para la criba: la raíz cuadrada de n
    int limit = (int)sqrt(n);

    // Crear un arreglo booleano para marcar números como primos o no
    bool *is_prime = (bool *)malloc((limit + 1) * sizeof(bool));
    for (int i = 0; i <= limit; i++) 
        is_prime[i] = true;  // Inicialmente asumimos que todos son primos

    // Criba de Eratóstenes
    for (int p = 2; p * p <= limit; p++) {
        if (is_prime[p]) {  // Si el número p es primo
            // Marcar todos los múltiplos de p como no primos
            for (int k = p * p; k <= limit; k += p) {
                is_prime[k] = false;
            }
        }
    }

    // Llenar la lista de primos con los números marcados como verdaderos
    *prime_count = 0;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes[(*prime_count)++] = i;  // Guardar el número primo y aumentar el contador
        }
    }

    // Liberar memoria asignada para la criba
    free(is_prime);
}

// Función para factorizar n usando Trial Division con los primos generados
void trial_division_factorization(int n) {
    // Crear un arreglo para almacenar los primos generados
    int *primes = (int *)malloc(((int)sqrt(n) + 1) * sizeof(int));
    int prime_count;

    // Generar números primos hasta √n
    sieve_of_eratosthenes(n, primes, &prime_count);

    printf("Factores primos de %d:\n", n);

    // Variable para iterar sobre los primos y el número original
    int i = 0, original_n = n;

    // Iterar sobre los primos generados
    while (n > 1 && i < prime_count) {
        int p = primes[i];  // Tomar el primo actual
        int e = 0;          // Exponente del primo actual

        // Dividir n repetidamente por p mientras sea divisible
        while (n % p == 0) {
            n /= p;  // Reducir n dividiéndolo por p
            e++;     // Incrementar el exponente del factor primo
        }

        // Si el primo p divide a n al menos una vez, imprimir el factor
        if (e > 0) {
            printf("%d^%d\n", p, e);
        }

        i++;  // Pasar al siguiente primo
    }

    // Si queda un factor primo mayor que √n (solo puede ocurrir al final)
    if (n > 1) {
        printf("%d^1\n", n);  // Este factor es primo y aparece una vez
    }

    // Liberar memoria asignada para la lista de primos
    free(primes);
}

int main() {
    int n;

    // Pedir al usuario un número para factorizar
    printf("Ingresa un número para factorizar: ");
    scanf("%d", &n);

    // Validar que el número sea válido
    if (n < 2) {
        printf("El número debe ser mayor o igual a 2.\n");
        return 1;  // Salir del programa si la entrada no es válida
    }

    // Llamar a la función para factorizar el número
    trial_division_factorization(n);

    return 0;
}
