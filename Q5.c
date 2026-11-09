
#include <stdio.h>
#include <stdlib.h>

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
arbolBinario crearArbolBinarioPreorden();
nodo crearEnPreorden();
void preorden(arbolBinario);
void recorridoPreorden(nodo);
void liberarNodos(nodo);
void eliminarArbol(arbolBinario);

int main(void) {
    arbolBinario arbol = crearArbolBinarioPreorden();
    
    printf("Recorrido preorden: ");
    preorden(arbol);
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

arbolBinario crearArbolBinarioPreorden() {
    arbolBinario tree = crearArbolBinario();
    tree->root = crearEnPreorden();
    return tree;
}

nodo crearEnPreorden() {
    int valor;
    scanf("%d", &valor);
    if (valor == 0) {
        return NULL;
    }
    nodo nuevoNodo = crearNodo(valor);
    nuevoNodo->left = crearEnPreorden();
    nuevoNodo->right = crearEnPreorden();
    return nuevoNodo;
}

void recorridoPreorden(nodo raiz) {
    if (raiz != NULL){
        printf("%d ", raiz->data);
        recorridoPreorden(raiz->left);
        recorridoPreorden(raiz->right);
    }
}

void preorden(arbolBinario tree) {
    if (tree->root != NULL) {
        recorridoPreorden(tree->root);
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

