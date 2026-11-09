#include <stdio.h>
#include <stdlib.h>


typedef struct Nodo {
    int dato;
    struct Nodo *siguiente;
} tipoNodo, *nodo;

void insertarFinal(nodo *cabeza, int valor) {
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

void separarParesImpares(nodo original, nodo *pares, nodo *impares) {
    nodo actual = original;
    while (actual != NULL) {
        if (actual->dato != 0) {
            if (actual->dato % 2 == 0) {
                insertarFinal(pares, actual->dato);
            } else {
                insertarFinal(impares, actual->dato);
            }
        }
        actual = actual->siguiente;
    }
}

void imprimirLista(nodo cabeza) {
    nodo actual = cabeza;
    while (actual != NULL) {
        printf("%d ", actual->dato);
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
    nodo listaOriginal = NULL;
    int val;
    while (scanf("%d", &val) == 1 && val != 0) {
        insertarFinal(&listaOriginal, val);
    }

    nodo listaPares = NULL;
    nodo listaImpares = NULL;

    separarParesImpares(listaOriginal, &listaPares, &listaImpares);

    printf("Pares: ");
    imprimirLista(listaPares);

    printf("Impares: ");
    imprimirLista(listaImpares);
    destruirLista(listaOriginal);
    destruirLista(listaPares);
    destruirLista(listaImpares);

    return 0;
}