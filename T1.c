#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 205
typedef struct {
    char datos[MAX_SIZE];
    int tope;
} Pilachar;

void inipilachar(Pilachar *p) {
    p->tope = -1;
}

int isemptychar(Pilachar *p) {
    return p->tope == -1;
}

void pushchar(Pilachar *p, char c) {
    if (p->tope < MAX_SIZE - 1) {
        p->tope++;
        p->datos[p->tope] = c;
    }
}

char popchar(Pilachar *p) {
    if (!isemptychar(p)) {
        char c = p->datos[p->tope];
        p->tope--;
        return c;
    }
    return '\0'; 
}

char topchar(Pilachar *p) {
    if (!isemptychar(p)) {
        return p->datos[p->tope];
    }
    return '\0'; 
}

int obtenerprecedencia(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; 
}

int esasociativoderecha(char op) {
    if (op == '^') return 1; 
    return 0;               
}

void infijoAPosfijo(char *infijo, char *posfijo) {
    Pilachar pila;
    inipilachar(&pila);
    
    posfijo[0] = '\0'; 
    
    char copiaInfijo[MAX_SIZE];
    strcpy(copiaInfijo, infijo);

    char *token = strtok(copiaInfijo, " \n\r");
    
    while (token != NULL) {

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            strcat(posfijo, token);
            strcat(posfijo, " ");
        }

        else if (strcmp(token, "(") == 0) {
            pushchar(&pila, '(');
        }

        else if (strcmp(token, ")") == 0) {
            while (!isemptychar(&pila) && topchar(&pila) != '(') {
                char op[2] = {popchar(&pila), '\0'};
                strcat(posfijo, op);
                strcat(posfijo, " ");
            }
            if (!isemptychar(&pila) && topchar(&pila) == '(') {
                popchar(&pila); 
            }
        }

        else {
            char opActual = token[0];
            
            while (!isemptychar(&pila) && topchar(&pila) != '(') {
                char opTope = topchar(&pila);
                int precActual = obtenerprecedencia(opActual);
                int precTope = obtenerprecedencia(opTope);
                
                if ((!esasociativoderecha(opActual) && precActual <= precTope) ||
                    (esasociativoderecha(opActual) && precActual < precTope)) {
                    char op[2] = {popchar(&pila), '\0'};
                    strcat(posfijo, op);
                    strcat(posfijo, " ");
                } else {
                    break;
                }
            }
            pushchar(&pila, opActual);
        }
        
        token = strtok(NULL, " \n\r");
    }
    
    while (!isemptychar(&pila)) {
        char op[2] = {popchar(&pila), '\0'};
        strcat(posfijo, op);
        strcat(posfijo, " ");
    }
    
    int len = strlen(posfijo);
    if (len > 0 && posfijo[len - 1] == ' ') {
        posfijo[len - 1] = '\0';
    }
}

typedef struct {
    double datos[MAX_SIZE];
    int tope;
} PilaDouble;

void initPilaDouble(PilaDouble *p) {
    p->tope = -1;
}

int isEmptyDouble(PilaDouble *p) {
    return p->tope == -1;
}

void pushDouble(PilaDouble *p, double val) {
    if (p->tope < MAX_SIZE - 1) {
        p->tope++;
        p->datos[p->tope] = val;
    }
}

double popDouble(PilaDouble *p) {
    if (!isEmptyDouble(p)) {
        double val = p->datos[p->tope];
        p->tope--;
        return val;
    }
    return 0.0;
}

double evaluarPosfijo(char *posfijo) {
    PilaDouble pila;
    initPilaDouble(&pila);

    char copiaPosfijo[MAX_SIZE];
    strcpy(copiaPosfijo, posfijo);

    char *token = strtok(copiaPosfijo, " \n\r");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            double num = atof(token); 
            pushDouble(&pila, num);
        } else {
            double val2 = popDouble(&pila); 
            double val1 = popDouble(&pila); 
            double res = 0.0;
            
            switch (token[0]) {
                case '+': res = val1 + val2; break;
                case '-': res = val1 - val2; break;
                case '*': res = val1 * val2; break;
                case '/': res = val1 / val2; break;
                case '^': res = pow(val1, val2); break; 
            }

            pushDouble(&pila, res);
        }
        
        token = strtok(NULL, " \n\r");
    }
    
    return popDouble(&pila);
}

int main() {
    char entrada[MAX_SIZE];
    char posfijo[MAX_SIZE];

    if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        infijoAPosfijo(entrada, posfijo);
        double resultado = evaluarPosfijo(posfijo);
        
        printf("%s\n", posfijo);
        printf("%g\n", resultado);
    }
    
    return 0;
}