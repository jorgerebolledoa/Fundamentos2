#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gmp.h>
  

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
    if(stack->top == NULL){
        return 1;
    } else {
        return 0;
    }
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
    while (mpz_cmp_ui(b, 0) != 0) {//Aplicamos derechamente el algoritmo
        mpz_mod(r, a, b);
        mpz_set(a, b);
        mpz_set(b, r);
    }
    printf("El maximo comun divisor de p y q es: ");
    gmp_printf("%Zd\n", a);
    mpz_clear(r);
    return;
}



void algoritmo_modular(mpz_t a , mpz_t b){
    struct Stack pila;
    pila.top = NULL;

    unsigned int aux2;

    mpz_t resto;
    mpz_init(resto);
    mpz_t r_0;
    mpz_init(r_0);

    mpz_t aux;
    mpz_init_set_ui(aux, 2);
    unsigned int auxiliar;

    while (mpz_cmp_ui(b, 0) > 0) {//Primero pasar el entero entregado a binario
        mpz_fdiv_qr(b, resto, b, aux);
        auxiliar = mpz_get_ui(resto);
        push(&pila, auxiliar);//almacenar en una pila ya que es lo más comodo
    }

    mpz_init_set_ui(r_0, 1);//aplicamos exponenciacion modular
    while(empty(&pila)==0){
        mpz_pow_ui(r_0, r_0, 2);
        aux2 = pop(&pila);
        if(aux2 == 1){
            mpz_mul(r_0, r_0, a);
        }
    }
    gmp_printf("Exponenciacon modular: %Zd\n", r_0);
    mpz_clear(r_0);
    mpz_clear(resto);
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
    // Declarar variables de tipo mpz_t para números grandes
    mpz_t p, q, result, aux, p2, q2, p3, q3;
    unsigned int opcion;
    // Inicializar las variables
    mpz_init(p);
    mpz_init(q);
    mpz_init(p2);
    mpz_init(q2);
    mpz_init(p3);
    mpz_init(q3);
    mpz_init(result);

    opcion = 0;

    printf("0 para multiplicar numeros grandes, 1 para calcular el gcd euclideano, 2 para calcular la exponenciacion modular, 3 Trial Division con sieve of Eratothenes, o 4 para salir\n");
    scanf("%d", &opcion);
    switch(opcion){
        case 0:
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
            mpz_clear(p);
            mpz_clear(q);
            mpz_clear(result);
            break;
        case 1:
            printf("Introduce el primer número: ");
            gmp_scanf("%Zd", &p2);
            printf("Introduce el segundo número: ");
            gmp_scanf("%Zd", &q2);

            algoritmo_euclideano(p2, q2);
            mpz_clear(p2);
            mpz_clear(q2);
            break;
        case 2:
            printf("Introduce la base(debe ser un numero natural): ");
            gmp_scanf("%Zd", &p3);
            printf("Introduce el exponente(debe ser un numero natural): ");
            gmp_scanf("%Zd", &q3);
            algoritmo_modular(p3, q3);
            mpz_clear(p3);
            mpz_clear(q3);
            break;
        case 3:
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
            mpz_clear(n);
    }
    return 0;
}
