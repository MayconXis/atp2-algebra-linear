
void imprimir_matriz(Matriz m) {
    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            printf("%8.2f ", m.dados[i][j]);
        }
        printf("\n");
    }
}

void imprimir_sistemaLienar(SistemaLinear sistema) {
    for (int i = 0; i < sistema.qtdLinhas; i++) {
        for (int j = 0; j < sistema.qtdColunas; j++) {

            printf("%8.2f ", sistema.linhas[i].coef[j]);
        }
        printf("= %8.2f",sistema.linhas[i].igualdade);

        printf("\n");
    }
}

void aberturaPrograma(){
    printf("PROGRAMA DE MATRIZES\n");
    printf("Escolha uma opção: \n");
    printf("[1] - Resolver Sistema Linear\n");
    printf("[2] - Analisar Transformação Linear\n");
    printf("[3] - Verificar Base de um Espaço Vetorial\n");
    printf("[4] - Calcular Autovalores e Autovetores\n");
    printf("[0] - Sair\n");
}


int escolhaEntrada(){
    int o;
    printf("Escolha uma opção: \n");
    printf("[1] - Ler de Arquivo\n");
    printf("[2] - Ler do Terminal\n");
    scanf("%d", &o);
    getchar();
    return o;
}