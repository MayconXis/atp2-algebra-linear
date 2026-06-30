
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
    printf("Escolha uma opcao: \n");
    printf("[1] - Resolver Sistema Linear\n");
    printf("[2] - Analisar Transformacao Linear\n");
    printf("[3] - Verificar Base de um Espaco Vetorial\n");
    printf("[4] - Calcular Autovalores e Autovetores\n");
    printf("[5] - Teste automatizado\n");
    printf("[6] - Escrever no Arquivo\n");
    printf("[0] - Sair\n");
}


int escolhaEntrada(){
    int o;
    printf("Escolha uma opção: \n");
    printf("[1] - Ler de Arquivo (Certifique-se que há dados no arquivo!)\n");
    printf("[2] - Ler do Terminal\n");
    scanf("%d", &o);
    getchar();
    return o;
}

void enterPraContinuar(){
    printf("\n");
    printf("Pressione enter pra continuar...\n");
    while(getchar() != '\n');
}

void limparTela(){
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif
}

void moldura(int qtd){
    for(int i = 0; i < qtd; i++){
        printf("=");
    }
    printf("\n");
}

int escolhaLeitura(int esc, SistemaLinear *sis) {
    if (esc == 1) {
        return lerArquivo(sis);
    } else if (esc == 2) {
        moldura(75);
        informacoesLeitura();
        moldura(75);
        return lerTerminal(sis);
    } else {
        printf("Opção invalida\n");
        return -1;
    }
}

void informacoesLeitura(){
    printf("\t- Digite cada LINHA DE ENTRADA uma abaixo da outra -\n");
    printf("\t- ESCREVA 'FIM' PARA TERMINAR A LEITURA -\n");
}

void cabecalho(char texto[], int tamMoldura){
    moldura(tamMoldura);
    printf("\t\t\t%s\n", texto);
    moldura(tamMoldura);
}

