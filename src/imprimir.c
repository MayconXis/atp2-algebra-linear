int lerArquivo(SistemaLinear *sis);
int lerTerminal(SistemaLinear *sis);


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
    printf("[5] - Diagonalização\n");
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

void informacoesLeitura(){
    printf("\t- Digite cada LINHA DE ENTRADA uma abaixo da outra -\n");
    printf("\t- ESCREVA 'FIM' PARA TERMINAR A LEITURA -\n");
}

void informacoesLeituraBases(){
    printf("\t- Digite cada VETOR uma abaixo da outro -\n");
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



void cabecalho(char texto[], int tamMoldura){
    moldura(tamMoldura);
    printf("\t\t\t%s\n", texto);
    moldura(tamMoldura);
}

void instrucoes(){
    moldura(150);
    printf("\t\t\t\t\tBEM VINDOS AO PROGRAMA DE ALGEBRA LINEAR\n");
    moldura(150);
    printf("Abaixo se encontram algumas instruções de uso do programa!\n");
    printf("Siga essas instruções para que o sistema funcione corretamente:\n");
    printf("\n");
    printf("1. UTILIZE VARIAVEIS SEQUENCIAIS: O sistema aceita todas as letras do alfabeto. Use letras que sejam vizinhas no alfabeto como variaveis.\n");
    printf("\t- (Ex: 'a, b, c' ou 't, u, v, w, x') Não pule letras. Evite: 'a, x, m'\n\n");
    printf("2. ORDEM ALFABETICA: O sistema organizara as matrizes por ordem alfabetica, independente de como você digitar.\n");
    printf("\t- (Ex: 'y - 2x = 3' sera lido como '-2x + y = 3')\n\n");
    printf("3. SOBRE FRAÇÕES: O sistema tranforma frações em números decimais.\n");
    printf("\t- Para isso use frações no formato: '1/2'\n");
    printf("\t- Evite 'x/2', utilize o padrão '1/2x', fração depois variável.\n");
    printf("\n");
    printf("4. BASES: para conjuntos entre com valores diretos.\n");
    printf("\t- Evite: {(2, 1), (1,3)}.\n");
    printf("\t- Utilize: 2 1 separados por espaço, e 1 3 na linha debaixo.\n");
    moldura(150);
}

int continuarNoBloco(char texto[]){
    int continuar;
    printf("deseja fazer outra operação em %s\n", texto);
    printf("[1] - Sim\n");
    printf("Digite qualquer outro numero pra sair!\n");
    
    scanf ("%d", &continuar);
    getchar();
    return continuar;
}


