#include <stdio.h>
#include <string.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    char cadenas[10][25];
    for (int i = 0; i < n; i++) {
        scanf("%s", cadenas[i]);
    }

    char prefijo[25];
    strcpy(prefijo, cadenas[0]);

    for (int i = 1; i < n; i++) {
        int j = 0;
        while (prefijo[j] != '\0' && cadenas[i][j] != '\0' && prefijo[j] == cadenas[i][j]) {
            j++;
        }
        prefijo[j] = '\0'; 
    }

    if (strlen(prefijo) == 0) {
        printf("-\n");
    } else {
        printf("%s\n", prefijo);
    }

    return 0;
}