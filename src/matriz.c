#include <stdio.h>
#include "matrix.c"


void imprimir_matriz(Matriz m) {
    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            printf("%8.2f ", m.dados[i][j]);
        }
        printf("\n");
    }
}
