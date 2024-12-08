#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

int is_prime(mpz_t n);

struct node {
    unsigned int resto;
    struct node *next;
};

struct Stack {
    struct node *top;
};

void push(struct Stack *stack, unsigned int valor) {
    struct node *nuevoNodo = (struct node *)calloc(1, sizeof(struct node));

    nuevoNodo->resto = valor;       
    nuevoNodo->next = stack->top;  
    stack->top = nuevoNodo;        
}

unsigned int pop(struct Stack *stack) {
    unsigned int valor = 0;
    if (stack->top == NULL) {
        printf("Error: La pila está vacía.\n");
        return 555;
    }
    struct node *aux = stack->top;
    valor = aux->resto;
    stack->top = aux->next;
    free(aux);
    return valor;
}

unsigned int empty(struct Stack *stack) {
    return stack->top == NULL ? 1 : 0;
}

void mostrar_pila(struct Stack *stack) {
    if (stack->top == NULL) {
        printf("La pila está vacía.\n");
        return;
    }

    struct node *aux = stack->top;
    printf("Contenido de la pila:\n");
    while (aux != NULL) {
        printf("%u\n", aux->resto);
        aux = aux->next;
    }
}

void algoritmo_euclideano(mpz_t a, mpz_t b) {
    mpz_t r;
    mpz_init(r);
    while (mpz_cmp_ui(b, 0) != 0) {
        mpz_mod(r, a, b);
        mpz_set(a, b);
        mpz_set(b, r);
    }
    printf("El máximo común divisor es: ");
    gmp_printf("%Zd\n", a);
    mpz_clear(r);
}

void algoritmo_modular(mpz_t a , mpz_t b) {
    struct Stack pila = { .top = NULL };
    unsigned int aux2;

    mpz_t resto, r_0, aux;
    mpz_inits(resto, r_0, aux, NULL);
    mpz_init_set_ui(aux, 2);
    unsigned int auxiliar;

    while (mpz_cmp_ui(b, 0) > 0) {
        mpz_fdiv_qr(b, resto, b, aux);
        auxiliar = mpz_get_ui(resto);
        push(&pila, auxiliar);
    }

    mpz_init_set_ui(r_0, 1);
    while (!empty(&pila)) {
        mpz_pow_ui(r_0, r_0, 2);
        aux2 = pop(&pila);
        if (aux2 == 1) {
            mpz_mul(r_0, r_0, a);
        }
    }
    gmp_printf("Exponenciación modular: %Zd\n", r_0);
    mpz_clears(r_0, resto, aux, NULL);
}

void trial_division_factorization(mpz_t n) {
    printf("Factores primos:\n");

    mpz_t factor, exp, remainder, sqrt_n;
    mpz_inits(factor, exp, remainder, sqrt_n, NULL);
    mpz_sqrt(sqrt_n, n);

    for (mpz_set_ui(factor, 2); mpz_cmp(factor, sqrt_n) <= 0; mpz_add_ui(factor, factor, 1)) {
        if (!is_prime(factor)) continue;

        mpz_set_ui(exp, 0);
        while (1) {
            mpz_mod(remainder, n, factor);
            if (mpz_cmp_ui(remainder, 0) != 0) break;

            mpz_divexact(n, n, factor);
            mpz_add_ui(exp, exp, 1);
        }

        if (mpz_cmp_ui(exp, 0) > 0) {
            gmp_printf("%Zd^%Zd\n", factor, exp);
        }

        mpz_sqrt(sqrt_n, n);
    }

    if (mpz_cmp_ui(n, 1) > 0) {
        gmp_printf("%Zd^1\n", n);
    }

    mpz_clears(factor, exp, remainder, sqrt_n, NULL);
}
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

// Generar números aleatorios de tamaño n
void generate_random_number(mpz_t number, unsigned int n) {
    mpz_t max_value;
    mpz_init(max_value);

    mpz_ui_pow_ui(max_value, 10, n); // Máximo valor basado en el tamaño
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_urandomm(number, state, max_value); // Generar número aleatorio
    mpz_clear(max_value);
    gmp_randclear(state);
}

void iterar_funciones(int k, unsigned int n) {
    mpz_t a, b;
    mpz_inits(a, b, NULL);

    for (int i = 0; i < k; i++) {
        generate_random_number(a, n);
        generate_random_number(b, n);

        printf("\nIteración %d:\n", i + 1);
        printf("Número aleatorio 1: ");
        gmp_printf("%Zd\n", a);
        printf("Número aleatorio 2: ");
        gmp_printf("%Zd\n", b);

        algoritmo_euclideano(a, b);
        algoritmo_modular(a, b);
        trial_division_factorization(a);
    }

    mpz_clears(a, b, NULL);
}

int main() {
    unsigned int n, k;
    printf("Ingrese el tamaño de los números aleatorios (n): ");
    scanf("%u", &n);
    printf("Ingrese el número de iteraciones (k): ");
    scanf("%u", &k);

    iterar_funciones(k, n);

    return 0;
}
