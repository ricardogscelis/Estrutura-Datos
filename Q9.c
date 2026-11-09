#include <stdio.h>

#define MAX 100

int heap[MAX];
int tamaño = 0;

void intercambiar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int padre(int i)
{
    return (i - 1) / 2;
}

void insertar(int valor)
{
    int i = tamaño;

    heap[tamaño] = valor;
    tamaño++;

    while(i > 0 && heap[i] < heap[padre(i)])
    {
        intercambiar(&heap[i], &heap[padre(i)]);
        i = padre(i);
    }
}

void imprimirHeap()
{
    for(int i = 0; i < tamaño; i++)
    {
        printf("%d ", heap[i]);
    }

    printf("\n");
}

int main()
{
    int n;
    int valor;

    printf("Cantidad de numeros: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &valor);
        insertar(valor);
    }

    printf("Monticulo minimo:\n");
    imprimirHeap();

    return 0;
}
