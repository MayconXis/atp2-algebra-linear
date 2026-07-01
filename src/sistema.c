#include <stdio.h>
#include <math.h>


int linhasUteis(Matriz m);
void imprimir_matriz(Matriz m);

Matriz aumentarMatriz(SistemaLinear sis) {
    Matriz aumentada;
    int primeiraVariavel = sis.menorVariavel; // indice da primeira variavel

    int linha = sis.qtdLinhas;
    int colunaAumentada = sis.qtdColunas + 1;

    aumentada.linhas = linha;
    aumentada.colunas = colunaAumentada;

    for (int i = 0; i < linha; i++) {
        int indiceVariavel = primeiraVariavel;
        for (int j = 0; j < colunaAumentada - 1; j++) { //roda exatamente o numero de colunas sem contar a igualdade
            //copia todos os coeficientes de A
            aumentada.dados[i][j] = sis.linhas[i].coef[indiceVariavel++]; //salva o valor da variavel na coluna e incrementa
        }
        //coloca na última coluna o valor de b (tudo depois do = )
        aumentada.dados[i][colunaAumentada - 1] = sis.linhas[i].igualdade; // acrescenta a parte aumentada
    }
    return aumentada;
}

void escalonamento(Matriz *matriz) {
    double multiplicador;

    for (int coluna = 0; coluna < (*matriz).colunas; coluna++) {
        // // Começa em coluna + 1 para não mexer na linha do pivô
        // Desce nas linhas abaixo do pivô pra zerar

        for (int linha = coluna + 1; linha < (*matriz).linhas; linha++) {

            if ((*matriz).dados[coluna][coluna] == 0) {
                continue; // Se o pivô for zero, pula a linha, tava dando nan quando fazia a divisao
            }

            // Descobre o número pra zerar a posição atual
            // Divide o número pelo pivô para zerar
            multiplicador = (*matriz).dados[linha][coluna] / (*matriz).dados[coluna][coluna];

            for (int k = 0; k < (*matriz).colunas; k++) {
                //Atualiza a linha inteira
                (*matriz).dados[linha][k] = (*matriz).dados[linha][k] - multiplicador * (*matriz).dados[coluna][k];
            }
            if (multiplicador != 0) {
                printf("Operacao: L%d = L%d - (%.2f * L%d)\n", linha + 1, linha + 1, multiplicador, coluna + 1);
                imprimir_matriz(*matriz);
            }
        }
    }
}

TipoSolucao verificarSolucao(Matriz *matriz) {
    int ultima_coluna = (*matriz).colunas - 1;
    int temLinhaNula = FALSE;

    for (int linha = 0; linha < (*matriz).linhas; linha++) {
        int todosZero = TRUE;

        for (int coluna = 0; coluna < ultima_coluna; coluna++) {
            if ((*matriz).dados[linha][coluna] != 0) {
                todosZero = FALSE;
            }
        }
        if (todosZero == TRUE) {
            if ((*matriz).dados[linha][ultima_coluna] == 0) {
                temLinhaNula = TRUE;  //estava retornando infinta solucoes imediatamente quando encontrava uma linha de zeros e para de verificar e se haver uma linha impossível depois nao tinha verificao.
            } else {
                return SEM_SOLUCAO;
            }
        }
    }
    if (temLinhaNula == TRUE) return INFINITAS_SOLUCOES;
    return SOLUCAO_UNICA;
}

void substituicaoReversa(Matriz *matriz, int menorVar) {
    double respostas[10];
    int ultima_coluna = (*matriz).colunas - 1;

    // começa na última linha e vai subindo
    for (int linha = (*matriz).linhas - 1; linha >= 0; linha--) {
        // Pega valor total no final da linha(depois do =)
        double soma = (*matriz).dados[linha][ultima_coluna];

        // Subtrai o valor das letras nas linhas de baixo
        for (int coluna = linha + 1; coluna < ultima_coluna; coluna++) {
            //vai pegar soma que sempre vai ser a ultima linha e fazer a soma com o ultimo resultado encontrado
            soma = soma - ((*matriz).dados[linha][coluna] * respostas[coluna]);
        }

        respostas[linha] = soma / ((*matriz).dados[linha][linha]);
    }
    printf("\nSolucao do sistema:\n");
    char variaveis[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
                         'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for(int i = 0; i < (*matriz).linhas; i++){
        printf("%c = %.2f\n", variaveis[menorVar++], respostas[i]);
    }
}


void resolverSistema(SistemaLinear sistema) {
    Matriz aumentada = aumentarMatriz(sistema);
    escalonamento(&aumentada);
    TipoSolucao solucao = verificarSolucao(&aumentada);

    int linhasU = linhasUteis(aumentada);
    if (solucao == SOLUCAO_UNICA) {
        printf("\n");
        printf("Não há contradições no sistema\n");
        printf("O número de equações validas (%d) = número de variáveis (%d)\n", linhasU, aumentada.colunas - 1);
        printf("Portanto -> Sistema Possivel e Determinado (Solução Única)\n");
        substituicaoReversa(&aumentada, sistema.menorVariavel);
    } else if (solucao == INFINITAS_SOLUCOES) {
        printf("\n");
        printf("Não há contradições no sistema\n");
        printf("Restaram apenas %d equações validas para %d variáveis após o escalonamento\n", linhasU, aumentada.colunas - 1);
        printf("Existem variaveis livres, pois número de equações < icógnitas \n");
        printf("Portanto -> Sistema possui infinitas soluções.\n");
    } else {
        printf("\nApós o escalonamento restaram linhas zeradas com o resultado diferente de zero.\n");
        printf("Isso é uma contradicao matematica.\n");
        printf("Sistema sem solucao (SI).\n");
    }
}

Matriz tranformarEmMatriz(SistemaLinear sistema){
    Matriz matriz;
    matriz.linhas = sistema.qtdLinhas;
    matriz.colunas = sistema.qtdColunas;
    for(int i = 0; i < matriz.linhas; i++){
        int primeiraVariavel = sistema.menorVariavel;
        for(int j = 0; j < matriz.colunas; j++){
            matriz.dados[i][j] = sistema.linhas[i].coef[primeiraVariavel++];
        }      
    }
    return matriz;
}

void printarMatriz(Matriz matriz){
    for(int i = 0; i < matriz.linhas; i++){
        printf("   ");
        for(int j = 0; j < matriz.colunas; j++){
            printf("%.2f ", matriz.dados[i][j]);
        }  
        printf("\n");   
    }
}


void printarSistemaLinear(SistemaLinear sistema){
    for(int i = 0; i < sistema.qtdLinhas; i++){
        int primeiraVariavel = sistema.menorVariavel;
        printf("\t");
        for(int j = 0; j < sistema.qtdColunas; j++){
            printf("%.2f ", sistema.linhas[i].coef[primeiraVariavel++]);
        }
        printf("| %.2f\n", sistema.linhas[i].igualdade);
    } 
}

