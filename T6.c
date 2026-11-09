#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

typedef struct{
    long cedula;
    int categoria;
    int llegada;
} Paciente;

Paciente heap[MAX];
int cantidad = 0;

int mayorPrioridad(Paciente a, Paciente b)
{
    if(a.categoria < b.categoria)
        return 1;

    if(a.categoria > b.categoria)
        return 0;

    return a.llegada < b.llegada;
}

void intercambiar(Paciente *a, Paciente *b)
{
    Paciente temp = *a;
    *a = *b;
    *b = temp;
}

int padre(int i)
{
    return (i - 1) / 2;
}

int hijoIzq(int i)
{
    return 2 * i + 1;
}

int hijoDer(int i)
{
    return 2 * i + 2;
}

void insertarPaciente(Paciente p)
{
    int i = cantidad;

    heap[cantidad] = p;
    cantidad++;

    while(i > 0 && mayorPrioridad(heap[i], heap[padre(i)]))
    {
        intercambiar(&heap[i], &heap[padre(i)]);
        i = padre(i);
    }
}

void heapifyDown(int i)
{
    int menor = i;
    int izq = hijoIzq(i);
    int der = hijoDer(i);

    if(izq < cantidad &&
       mayorPrioridad(heap[izq], heap[menor]))
    {
        menor = izq;
    }

    if(der < cantidad &&
       mayorPrioridad(heap[der], heap[menor]))
    {
        menor = der;
    }

    if(menor != i)
    {
        intercambiar(&heap[i], &heap[menor]);
        heapifyDown(menor);
    }
}

Paciente extraerMin()
{
    Paciente atendido = heap[0];

    heap[0] = heap[cantidad - 1];

    cantidad--;

    if(cantidad > 0)
    {
        heapifyDown(0);
    }

    return atendido;
}

int main()
{
    int llegada = 0;

    FILE *archivo;

    char linea[50];

    archivo = fopen("triage_data.txt", "r");

    if(archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    while(fgets(linea, sizeof(linea), archivo))
    {
        if(linea[0] == '0')
        {
            if(cantidad > 0)
            {
                Paciente atendido = extraerMin();

                printf("%ld\n", atendido.cedula);
            }
        }
        else
        {
            long cedula;
            int categoria;

            sscanf(linea, "%ld %d", &cedula, &categoria);

            if(categoria != 4)
            {
                Paciente nuevo;

                llegada++;

                nuevo.cedula = cedula;
                nuevo.categoria = categoria;
                nuevo.llegada = llegada;

                insertarPaciente(nuevo);
            }
        }
    }

    fclose(archivo);

    return 0;
}