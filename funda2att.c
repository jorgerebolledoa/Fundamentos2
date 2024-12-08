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
    while (mpz_cmp_ui(b, 0) != 0) {
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
    int q_digitos_bin = 0, j = 0;
    int log2 = 0;
    unsigned long auxiliar= 0, aux2 = 0;
    mpz_t resto;
    mpz_init(resto);
    unsigned long int a22 = mpz_get_ui(b);
    unsigned long int a32 = mpz_get_ui(a);
    mpz_t r_0;
    mpz_init(r_0);

    if (mpz_get_ui(b)==0){
        q_digitos_bin = 1;
        printf("Cantidad de digitos binarioS: %d\n", q_digitos_bin);
    } else{
        q_digitos_bin = mpz_get_ui(b);
        q_digitos_bin = floor((log(q_digitos_bin) / log(2)) +1);
        printf("Cantidad de digitos binarios: %d\n", q_digitos_bin);
    }

    mpz_t aux;
    mpz_init_set_ui(aux, 2);
;

    for(int i = 0; i < q_digitos_bin-1; i = i + 1){
        mpz_fdiv_qr(b, resto, b, aux);
        auxiliar = mpz_get_ui(resto);
        push(&pila, auxiliar);
    }

    mpz_set(r_0, a);
    for(j = q_digitos_bin-2; j>=0; j = j - 1){
        mpz_pow_ui(r_0, r_0, 2);
        aux2 = pop(&pila);
        if(aux2 == 1){
            mpz_mul(r_0, r_0, a);
        }
    }
    gmp_printf("Exponenciacon modular: %Zd\n", r_0);
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
    }
    return 0;
}
