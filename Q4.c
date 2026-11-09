#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *siguiente;
} Nodo;

typedef struct {
    Nodo *cabeza;
} Lista;

Lista* crearLista() {
    Lista *l = (Lista *)malloc(sizeof(Lista));
    if (l != NULL) {
        l->cabeza = NULL;
    }
    return l;
}

void insertarFinal(Lista *l, int valor) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    
    if (l->cabeza == NULL) {
        l->cabeza = nuevo;
    } else {
        Nodo *actual = l->cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

int contarFrecuencia(int arr[], int n, int valor) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == valor) {
            contador++;
        }
    }
    return contador;
}

void imprimirLista(Lista *l) {
    Nodo *actual = l->cabeza;
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

void destruirLista(Lista *l) {
    if (l == NULL) return;
    Nodo *actual = l->cabeza;
    while (actual != NULL) {
        Nodo *temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    free(l);
}

int main(void) {
    int arr[100];
    int n = 0;
    int val;

    while (n < 100 && scanf("%d", &val) == 1) {
        arr[n++] = val;
    }

    Lista *listaUnicos = crearLista();

    for (int i = 0; i < n; i++) {
        int numero = arr[i];
        
        if (contarFrecuencia(arr, n, numero) == 1) {
            insertarFinal(listaUnicos, numero); 
        }
    }

    imprimirLista(listaUnicos);
    destruirLista(listaUnicos);

    return 0;
}