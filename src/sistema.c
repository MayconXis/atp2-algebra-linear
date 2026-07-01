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

void escalonamentoVerifBase(Matriz *matriz) {
    double multiplicador;
    // O escalonamento normal sempre buscava o pivo na diagonal.
    // mas quando uma coluna inteira era zero abaixo da diagonal, ele pula com continue e
    // linhas dependentes nunca era eliminadas.
    // a ideia foi controlar a linha do pivo separado da coluna.
    // e o pivo avanca so quando encontra um valor valido.
    int linhaPivo = 0;

    for (int coluna = 0; coluna < (*matriz).colunas; coluna++) {
        if (linhaPivo >= (*matriz).linhas) break;

        // procura linha com valor != 0, a partir do pivo atual
        int encontrou = FALSE;
        for (int busca = linhaPivo; busca < (*matriz).linhas; busca++) {
            if ((*matriz).dados[busca][coluna] != 0) {
                // troca a linha com a linha do pivo atual
                double temp[10];
                for (int k = 0; k < (*matriz).colunas; k++) {
                    temp[k] = (*matriz).dados[linhaPivo][k];
                }
                for (int k = 0; k < (*matriz).colunas; k++) {
                    (*matriz).dados[linhaPivo][k] = (*matriz).dados[busca][k];
                }
                for (int k = 0; k < (*matriz).colunas; k++) {
                    (*matriz).dados[busca][k] = temp[k];
                }
                encontrou = TRUE;
                break;
            }
        }

        if (encontrou == FALSE) continue;

        // elimina todas as linhas abaixo do pivo atual
        for (int linha = linhaPivo + 1; linha < (*matriz).linhas; linha++) {
            multiplicador = (*matriz).dados[linha][coluna] / (*matriz).dados[linhaPivo][coluna];
            for (int k = 0; k < (*matriz).colunas; k++) {
                (*matriz).dados[linha][k] = (*matriz).dados[linha][k] - multiplicador * (*matriz).dados[linhaPivo][k];
            }
            if (multiplicador != 0) {
                printf("Operacao: L%d = L%d - (%.2f * L%d)\n", linha + 1, linha + 1, multiplicador, linhaPivo + 1);
                imprimir_matriz(*matriz);
            }
        }
        linhaPivo++;
    }
}

int verificarBase(Matriz matriz, int dimensao) {
    if (dimensao != matriz.linhas) {
        printf("Nao e base: o conjunto tem %d vetores mas o espaco tem dimensao %d.\n", matriz.linhas, dimensao);
        return FALSE;
    }

    escalonamentoVerifBase(&matriz);
    int posto = linhasUteis(matriz);

    if (posto == dimensao) {
        printf("E base: os %d vetores sao linearmente independentes e geram o espaco.\n", dimensao);
        return TRUE;
    } else {
        printf("Nao e base: apos escalonamento, posto = %d mas dimensao = %d.\n", posto, dimensao);
        printf("Os vetores sao linearmente dependentes.\n");
        return FALSE;
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

Matriz igualarZero(Matriz mat){
    Matriz aumentada;
    aumentada.linhas = mat.linhas;
    aumentada.colunas = mat.colunas + 1;
    int colunaAumentada = aumentada.colunas;

    for(int i = 0; i < mat.linhas; i++){
        for(int j = 0; j < mat.colunas; j++){
            aumentada.dados[i][j] = mat.dados[i][j];
        }
        aumentada.dados[i][colunaAumentada - 1] = 0;
    }

    return aumentada;
}

void autoVetor(Matriz matrizOriginal, double lambda){
    Matriz autoVetor = matrizOriginal;

    int lin = autoVetor.linhas;
    int col = autoVetor.colunas;

    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(i == j){
                autoVetor.dados[i][j] -= lambda;
            }
        }
    }
    printf("Matriz - Lambda %.2f:\n", lambda);
    imprimir_matriz(autoVetor);

    
    autoVetor = igualarZero(autoVetor);
    printf("Matriz igualada a zero:\n");
    imprimir_matriz(autoVetor);
    printf("\n");
    escalonamento(&autoVetor);
    printf("Matriz após o escalonamento:\n");
    imprimir_matriz(autoVetor);

    // ex: ax - by = 0
    double elementoA = autoVetor.dados[0][0];
    double elementoB = autoVetor.dados[0][1];

    double x, y;
    
    
    if(elementoA != 0){ //Evitar divisao por zero
        y = 1.0; //
        printf("Variavel livre Y assumida como 1\n");
        x = (-elementoB * y) / elementoA;
    }else{
        printf("Coeficiente da primeira variavel da primeira linha = 0.\n");
        printf("Resultaria em uma divisão por 0.\n");
        printf("x -> Livre, assumido como 1.\n");
        printf("y -> 0\n");
        x = 1;
        y = 0;
    }

    printf("Autovetor V = (%.2f, %.2f)\n", x, y);
}

void autoValores(Matriz matriz){
    double traco = 0;
    double determinante;
    double diagPrincipal = 1;
    double diagSecundaria = 1;
    int tamanhoMatriz = matriz.linhas;

    int lin = matriz.linhas;
    int col = matriz.colunas;

    for(int i = 0; i < lin; i++){ //soma diagonal principaç
        for(int j = 0; j < col; j++){
            if(i == j){
                traco += matriz.dados[i][j];
                diagPrincipal *= matriz.dados[i][j];
            }
            if(i + j == tamanhoMatriz-1){ //regra diagonal secundaria
                diagSecundaria *= matriz.dados[i][j];
            }
        }
    }

    
    double coefA = 1.0;
    double coefB = -traco; //Seria o jogo de sinal pra isolar o lambda -(a + d) . Lambda
    determinante = diagPrincipal - diagSecundaria; //coef C

    printf("Soma da diagonal principal: (TRAÇO)\n");
    printf("Traço = %.2f + %.2f = %.2f\n", matriz.dados[0][0], matriz.dados[1][1], traco);
    printf("\n");

    printf("Calculo do Determinante (Diagonal Principal - Secundaria)\n");
    printf("Determinante = (%.2f * %.2f) - (%.2f * %.2f)\n", 
        matriz.dados[0][0], matriz.dados[1][1], matriz.dados[0][1], matriz.dados[1][0]);
    printf("Determinante = %.2f - %.2f = %.2f\n\n", diagPrincipal, diagSecundaria, determinante);
    
    //Delta = b² - 4.a.c
    double delta = (coefB * coefB) - (4 * coefA * determinante);
    printf("Calculando Delta (B² - 4*A*C) -> (%.2f)² - 4 * (1.00) * (%.2f)\n\n", coefB, determinante);

    if(delta < 0){
        printf("Delta = %.2f\n", delta);
        printf("Delta resultou em um valor negativo.\n");
        printf("Portanto -> Não existem autovalores reais.\n");
    }
    else if(delta == 0){
        double lambda = -coefB / (2 * coefA);
        printf("Delta = 0.\n");
        printf("Portanto -> existe apenas um autovalor real (raiz dupla).\n");
        printf("Lambda = %.2f/n", lambda);
        printf("Lambda:\n");
        autoVetor(matriz, lambda);
    }
    else{
        //x = -b +- Raiz(Delta)/2a
        double lambda1 = (-coefB + sqrt(delta)) / (2 * coefA); //x1 formula de bhaslara
        double lambda2 = (-coefB - sqrt(delta)) / (2 * coefA); //x2
        printf("Delta = %.2f. Sendo > 0.\n", delta);
        printf("Portanto -> existe apenas dois autovalor reais.\n");
        printf("Lambda x¹ = %.2f\n", lambda1);
        printf("Lambda x² = %.2f\n", lambda2);
        printf("\n");
        printf("Lambda x¹:\n");
        autoVetor(matriz, lambda1);
        printf("\n");
        printf("Lambda x²:\n");
        autoVetor(matriz, lambda2);
    }
}
