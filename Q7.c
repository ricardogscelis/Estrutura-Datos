#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
    int dato;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

Nodo* crearNodo(int valor)
{
    Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));

    nuevo->dato = valor;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

Nodo* insertar(Nodo *raiz, int valor)
{
    if(raiz == NULL)
    {
        return crearNodo(valor);
    }

    if(valor < raiz->dato)
    {
        raiz->izq = insertar(raiz->izq, valor);
    }
    else
    {
        raiz->der = insertar(raiz->der, valor);
    }

    return raiz;
}

void inorden(Nodo *raiz)
{
    if(raiz != NULL)
    {
        inorden(raiz->izq);
        printf("%d ", raiz->dato);
        inorden(raiz->der);
    }
}

int main()
{
    Nodo *raiz = NULL;

    int n;
    int valor;

    printf("Cantidad de numeros: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &valor);
        raiz = insertar(raiz, valor);
    }

    printf("Numeros ordenados:\n");
    inorden(raiz);

    return 0;
}