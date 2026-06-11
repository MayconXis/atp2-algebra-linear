#include <stdio.h>
#include "matrix.c"


void imprimir_sistemaLienar(SistemaLinear sistema) {
    for (int i = 0; i < sistema.A.linhas; i++) {
        for (int j = 0; j < sistema.A.colunas; j++) {

            printf("%8.2f ", sistema.A.dados[i][j]);
        }
            printf("= %8.2f",sistema.b.vetor[i]);

        printf("\n");
    }
}
