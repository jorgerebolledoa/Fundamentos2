#include <stdio.h>
#include <gmp.h>

int main() {
    // Declarar variables de tipo mpz_t para números grandes
    mpz_t p, q, result;

    // Inicializar las variables
    mpz_init(p);
    mpz_init(q);
    mpz_init(result);

    // Leer los números grandes desde el usuario
    printf("Introduce el primer número primo grande (p): ");
    gmp_scanf("%Zd", &p);

    printf("Introduce el segundo número primo grande (q): ");
    gmp_scanf("%Zd", &q);

    // Multiplicar los números grandes
    mpz_mul(result, p, q);

    // Mostrar el resultado
    printf("El resultado de p * q es: ");
    gmp_printf("%Zd\n", result);

    // Liberar la memoria usada por las variables
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(result);

    return 0;
}
