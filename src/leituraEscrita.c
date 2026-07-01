#include <stdio.h>

void inicializarMaiorMenorSL(SistemaLinear *sis);
void inicializarColunasSL(SistemaLinear *sis);
void informacoesLeitura();

int lerArquivo(SistemaLinear *sis){
    FILE *arq = fopen("Equacoes.txt", "r"); 

    if (arq == NULL){
        printf("Arquivo nao encontrado \n");
        return 0;
    }

    inicializarMaiorMenorSL(sis);

    char linhaLida[TAMEQ];
    int i = 0;
    while(fscanf(arq, "%[^\n]", linhaLida) == 1){
        fgetc(arq); //Pega o \n que ficou no arquivo
        strcpy(linhasPrint[i], linhaLida);
        sis->linhas[i++] = parser(linhaLida, sis); //salva a linha parseada no sistema e incrementa i
    }
    fclose(arq);

    inicializarColunasSL(sis);
    return i;
}

int escreverArquivoBases(){
    FILE *arq = fopen("Equacoes.txt", "w");

    if(arq == NULL){
        printf("Arquivo nao encontrado\n");
        return 1;
    }

    int dimensao;
    printf("Informe a dimensao do espaco:\n");
    scanf("%d", &dimensao);
    getchar();
 
    int qtdVet;
    printf("informe quantos vetores (linhas) voce quer colocar no arquivo:\n");
    scanf("%d", &qtdVet);
    getchar();

    double valores;
    informacoesLeituraBases();
    
    for(int i = 0; i < qtdVet; i++){
        for(int j = 0; j < dimensao; j++){
            scanf("%lf", &valores);
            getchar();
            fprintf(arq, "%.2f ", valores);
        }
        fprintf(arq, "\n");
    } 
    fclose(arq);
}
    

int escreverArquivo(){
    FILE *arq = fopen("Equacoes.txt", "w");

    if(arq == NULL){
        printf("Arquivo nao encontrado\n");
        return 1;
    }
    char linha[100];
    
    while(1){
        scanf("%[^\n]s", linha);
        getchar();
        
        if(strcasecmp(linha, "FIM") == 0) break;

        fprintf(arq, "%s\n", linha);
    }
    
    fclose(arq);
}

int lerTerminal(SistemaLinear *sis){
    int numeroLinhas = 0;
    char linhaEntrada[TAMEQ];

    inicializarMaiorMenorSL(sis);
    int i = 0;
    while(1){
        scanf("%[^\n]", linhaEntrada);
        getchar();        
        if(strcasecmp(linhaEntrada, "FIM") == 0) break; //Compara independente se é minuscula ou maiuscula
        strcpy(linhasPrint[i], linhaEntrada); //Guarda pra printar pro usuario
        Linha linha = parser(linhaEntrada, sis); //limpa e faz o parse da linha
        sis->linhas[i++] = linha; //salva a linha parseada no sistema linear
        numeroLinhas++;
    }

    inicializarColunasSL(sis);
    return numeroLinhas;
}

int lerArquivoNumeros(Matriz *mat){
    FILE *arq = fopen("Equacoes.txt", "r");

    if (arq == NULL){
        printf("Arquivo nao encontrado \n");
        return 0;
    }

    for(int i = 0; i < mat->linhas; i++){
        for(int j = 0; j < mat->colunas; j++){ 
            double numero;
            fscanf(arq, "%lf", &numero);
            mat->dados[i][j] = numero;
        }
    }
    fgetc(arq);

    fclose(arq);
}

void lerTerminalNumeros(Matriz *mat) {
    printf("Escreva abaixo os %d vetores (com %d numeros cada):\n", mat->linhas, mat->colunas);
    informacoesLeituraBases();
    for(int i = 0; i < mat->linhas; i++){
        for(int j = 0; j < mat->colunas; j++){ 
            double numero;
            scanf("%lf", &numero);
            getchar();
            mat->dados[i][j] = numero;
        }
    }
}