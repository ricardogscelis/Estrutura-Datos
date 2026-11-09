#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    float dato;
    struct Nodo *siguiente;
} tipoNodo, *nodo;

void insertarFinal(nodo *cabeza, float valor) {
    nodo nuevo = (nodo) malloc(sizeof(tipoNodo));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    if (*cabeza == NULL) {
        *cabeza = nuevo;
    } else {
        nodo actual = *cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void invertirLista(nodo *cabeza) {
    nodo previo = NULL;
    nodo actual = *cabeza;
    nodo siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        actual->siguiente = previo;
        previo = actual;
        actual = siguiente;
    }
    *cabeza = previo;
}

void imprimirLista(nodo cabeza) {
    nodo actual = cabeza;
    while (actual != NULL) {
        printf("%g ", actual->dato);
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
    nodo cabeza = NULL;
    float val;
    int contadorMenosUno = 0;

    while (scanf("%f", &val) == 1) {
        if (val == -1.0f) {
            contadorMenosUno++;
            insertarFinal(&cabeza, val);
            if (contadorMenosUno == 3) {
                break; 
            }
        } else {
            insertarFinal(&cabeza, val);
        }
    }
    invertirLista(&cabeza);
    imprimirLista(cabeza);
    destruirLista(cabeza);

    return 0;
}