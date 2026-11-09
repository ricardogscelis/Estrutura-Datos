#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 10000
#define DIGITS_PER_BLOCK 4

typedef struct Nodo {
    short valor;
    struct Nodo *siguiente;
} tipoNodo, *nodo;

void insertarFinal(nodo *cabeza, nodo *cola, short val) {
    nodo nuevo = (nodo) malloc(sizeof(tipoNodo));
    nuevo->valor = val;
    nuevo->siguiente = NULL;
    if (*cabeza == NULL) {
        *cabeza = nuevo;
        *cola = nuevo;
    } else {
        (*cola)->siguiente = nuevo;
        *cola = nuevo;
    }
}

nodo sumarListas(nodo l1, nodo l2) {
    nodo resultado = NULL;
    nodo colaResultado = NULL;
    nodo p1 = l1;
    nodo p2 = l2;
    long long acarreo = 0;

    while (p1 != NULL || p2 != NULL || acarreo > 0) {
        long long suma = acarreo;
        if (p1 != NULL) {
            suma += p1->valor;
            p1 = p1->siguiente;
        }
        if (p2 != NULL) {
            suma += p2->valor;
            p2 = p2->siguiente;
        }

        acarreo = suma / BASE;
        short valorActual = (short)(suma % BASE);

        insertarFinal(&resultado, &colaResultado, valorActual);
    }

    return resultado;
}

nodo invertirLista(nodo cabeza) {
    nodo previo = NULL;
    nodo actual = cabeza;
    nodo siguiente = NULL;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        actual->siguiente = previo;
        previo = actual;
        actual = siguiente;
    }
    return previo;
}

void imprimirResultado(nodo cabeza) {
    nodo invertida = invertirLista(cabeza);
    nodo actual = invertida;
    
    int primero = 1;
    while (actual != NULL) {
        if (primero) {
            printf("%d", actual->valor);
            primero = 0;
        } else {
            printf("%04d", actual->valor);
        }
        actual = actual->siguiente;
    }
    printf("\n");
}

void destruirLista(nodo cabeza) {
    nodo actual = cabeza;
    while (actual != NULL) {
        nodo temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}

int main() {
    char str1[5005], str2[5005];

    if (scanf("%s %s", str1, str2) != 2) {
        return 0;
    }

    nodo lista1 = NULL, cola1 = NULL;
    nodo lista2 = NULL, cola2 = NULL;

    int len1 = strlen(str1);
    for (int i = len1; i > 0; i -= DIGITS_PER_BLOCK) {
        int inicio = i - DIGITS_PER_BLOCK;
        if (inicio < 0) inicio = 0;
        
        char bloqueStr[10];
        int l = i - inicio;
        strncpy(bloqueStr, &str1[inicio], l);
        bloqueStr[l] = '\0';
        
        short val = (short)atoi(bloqueStr);
        insertarFinal(&lista1, &cola1, val);
    }

    int len2 = strlen(str2);
    for (int i = len2; i > 0; i -= DIGITS_PER_BLOCK) {
        int inicio = i - DIGITS_PER_BLOCK;
        if (inicio < 0) inicio = 0;
        
        char bloqueStr[10];
        int l = i - inicio;
        strncpy(bloqueStr, &str2[inicio], l);
        bloqueStr[l] = '\0';
        
        short val = (short)atoi(bloqueStr);
        insertarFinal(&lista2, &cola2, val);
    }

    nodo listaResultado = sumarListas(lista1, lista2);

    imprimirResultado(listaResultado);

    destruirLista(lista1);
    destruirLista(lista2);
    destruirLista(listaResultado);

    return 0;
}