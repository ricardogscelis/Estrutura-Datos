#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    short digito;
    struct Nodo *siguiente;
} tipoNodo, *nodo;

void insertarAdelante(nodo *cabeza, short val) {
    nodo nuevo = (nodo) malloc(sizeof(tipoNodo));
    nuevo->digito = val;
    nuevo->siguiente = *cabeza;
    *cabeza = nuevo;
}

void insertarFinal(nodo *cabeza, nodo *cola, short val) {
    nodo nuevo = (nodo) malloc(sizeof(tipoNodo));
    nuevo->digito = val;
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
    int acarreo = 0;

    while (p1 != NULL || p2 != NULL || acarreo > 0) {
        int suma = acarreo;
        if (p1 != NULL) {
            suma += p1->digito;
            p1 = p1->siguiente;
        }
        if (p2 != NULL) {
            suma += p2->digito;
            p2 = p2->siguiente;
        }

        acarreo = suma / 10;
        int digitoActual = suma % 10;

        insertarFinal(&resultado, &colaResultado, (short)digitoActual);
    }

    return resultado;
}

void imprimirNumero(nodo cabeza) {
    if (cabeza == NULL) return;
    imprimirNumero(cabeza->siguiente);
    printf("%d", cabeza->digito);
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
    char str1[1005], str2[1005];

    if (scanf("%s %s", str1, str2) != 2) {
        return 0;
    }

    nodo lista1 = NULL;
    nodo lista2 = NULL;

    int len1 = strlen(str1);
    for (int i = 0; i < len1; i++) {
        if (str1[i] >= '0' && str1[i] <= '9') {
            insertarAdelante(&lista1, (short)(str1[i] - '0'));
        }
    }

    int len2 = strlen(str2);
    for (int i = 0; i < len2; i++) {
        if (str2[i] >= '0' && str2[i] <= '9') {
            insertarAdelante(&lista2, (short)(str2[i] - '0'));
        }
    }

    nodo listaResultado = sumarListas(lista1, lista2);

    imprimirNumero(listaResultado);
    printf("\n");

    destruirLista(lista1);
    destruirLista(lista2);
    destruirLista(listaResultado);

    return 0;
}