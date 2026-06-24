
void imprimir_matriz(Matriz m) {
    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            printf("%8.2f ", m.dados[i][j]);
        }
        printf("\n");
    }
}

void imprimir_sistemaLienar(SistemaLinear sistema) {
    for (int i = 0; i < sistema.A.linhas; i++) {
        for (int j = 0; j < sistema.A.colunas; j++) {

            printf("%8.2f ", sistema.A.dados[i][j]);
        }
        printf("= %8.2f",sistema.b.vetor[i]);

        printf("\n");
    }
}