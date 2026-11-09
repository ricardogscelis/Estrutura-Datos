#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *siguiente;
} tipoNodo, *nodo;

void insertarOrdenado(nodo *cabeza, int valor) {
    nodo nuevo = (nodo) malloc(sizeof(tipoNodo));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    if (*cabeza == NULL || (*cabeza)->dato >= valor) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
    } else {
        nodo actual = *cabeza;
        while (actual->siguiente != NULL && actual->siguiente->dato < valor) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
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
    nodo lista = NULL;
    int val;

    while (scanf("%d", &val) == 1 && val != 0) {
        insertarOrdenado(&lista, val);
    }

    imprimirLista(lista);
    destruirLista(lista);

    return 0;
}