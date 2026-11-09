
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} tipoNodo, *nodo;

typedef struct {
    nodo root;
} tipoArbol, *arbolBinario;

nodo crearNodo(int);
arbolBinario crearArbolBinario();
nodo construirDesdePostordenRec(int arr[], int *idx);
arbolBinario crearArbolBinarioPostorden();
void recorridoInorden(nodo);
void inorden(arbolBinario);
void liberarNodos(nodo);
void eliminarArbol(arbolBinario);

int main(void) {
    arbolBinario arbol = crearArbolBinarioPostorden();
    
    inorden(arbol);
    printf("\n");
    
    eliminarArbol(arbol);
    
    return 0;
}

nodo crearNodo(int valor) {
    nodo nuevoNodo = (nodo) malloc(sizeof(tipoNodo));
    nuevoNodo->data = valor;
    nuevoNodo->left = NULL;
    nuevoNodo->right = NULL;
    return nuevoNodo;
}

arbolBinario crearArbolBinario() {
    arbolBinario nuevoArbol = (arbolBinario) malloc(sizeof(tipoArbol));
    nuevoArbol->root = NULL;
    return nuevoArbol;
}

nodo construirDesdePostordenRec(int arr[], int *idx) {
    if (*idx < 0) {
        return NULL;
    }
    
    int valor = arr[*idx];
    (*idx)--;

    if (valor == 0) {
        return NULL;
    }

    nodo nuevoNodo = crearNodo(valor);
    
    nuevoNodo->right = construirDesdePostordenRec(arr, idx);
    nuevoNodo->left = construirDesdePostordenRec(arr, idx);

    return nuevoNodo;
}

arbolBinario crearArbolBinarioPostorden() {
    int arr[MAX_NODES];
    int n = 0;
    int val;

    while (scanf("%d", &val) == 1) {
        arr[n++] = val;
    }

    arbolBinario tree = crearArbolBinario();
    int idx = n - 1; 
    tree->root = construirDesdePostordenRec(arr, &idx);
    return tree;
}

void recorridoInorden(nodo raiz) {
    if (raiz != NULL) {
        recorridoInorden(raiz->left);
        printf("%d ", raiz->data);
        recorridoInorden(raiz->right);
    }
}

void inorden(arbolBinario tree) {
    if (tree->root != NULL) {
        recorridoInorden(tree->root);
    }
}

void liberarNodos(nodo raiz) {
    if (raiz != NULL) {
        liberarNodos(raiz->left);
        liberarNodos(raiz->right);
        free(raiz);
    }
}

void eliminarArbol(arbolBinario tree) {
    if (tree != NULL) {
        if (tree->root != NULL) {
            liberarNodos(tree->root);
            tree->root = NULL;
        }
        free(tree);
    }
}
