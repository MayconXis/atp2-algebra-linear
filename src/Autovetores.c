void imprimir_matriz(Matriz m);
void escalonamentoVerifBase(Matriz *matriz);


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

Autovetor autoVetor(Matriz matrizOriginal, double lambda){
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
    printf("Matriz (Diagonal Principal) - Lambda %.2f:\n", lambda);
    imprimir_matriz(autoVetor);
    printf("\n");

    autoVetor = igualarZero(autoVetor);
    printf("Matriz igualada a zero:\n");
    imprimir_matriz(autoVetor);
    printf("\n");
    escalonamentoVerifBase(&autoVetor);
    printf("\n");
    printf("Matriz apos o escalonamento:\n");
    imprimir_matriz(autoVetor);
    printf("\n");

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

    Autovetor av; //retornar pra diagonalizacao
    av.x = x;
    av.y = y;
    return av;
}

void autoValores(Matriz matriz){
    if (matriz.linhas != 2 || matriz.colunas != 2) {
        printf("\n Os autovalores estão implementada apenas para matrizes 2x2.\n");
        return;
    }

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
    printf("No polinomio, o traco inverte o sinal pela distributiva da equacao: portanto -> -(%.2f)\n", traco);
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
        printf("Portanto -> Nao existem autovalores reais.\n");
    }
    else if(delta == 0){
        double lambda = -coefB / (2 * coefA);
        printf("Delta = 0.\n");
        printf("Portanto -> existe apenas um autovalor real (raiz dupla).\n");
        printf("Lambda = %.2f\n", lambda);
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

void diagonalizarMatriz(Matriz matriz) {
    if (matriz.linhas != 2 || matriz.colunas != 2) {
        printf("\n A diagonalizacao automatica esta implementada apenas para matrizes 2x2.\n");
        return;
    }

    double traco = matriz.dados[0][0] + matriz.dados[1][1];
    double det = (matriz.dados[0][0] * matriz.dados[1][1]) - (matriz.dados[0][1] * matriz.dados[1][0]);

    double coefA = 1.0;
    double coefB = -traco;
    double coefC = det;

    double delta = (coefB * coefB) - (4 * coefA * coefC);

    if (delta < 0) {
        printf("Delta = %.2f (Negativo).\n", delta);
        printf("A matriz nao possui autovalores reais.\n");
        printf("Portanto -> nao e diagonalizavel em  R.\n");
        return;
    }

    if (delta == 0) {
        double lambda = -coefB / (2 * coefA);
        printf("Matriz possui raiz dupla (L = %.2f).\n", lambda);

        if (matriz.dados[0][1] == 0 && matriz.dados[1][0] == 0) {
            printf("A matriz ja e diagonal (multipla da identidade).\n");
            printf("Portanto, P = Identidade e D = Matriz Original.\n");
        } else {
            printf("Como tem raiz dupla mas nao e multipla da identidade, nao gera 2 autovetores LI.\n");
            printf("Portanto -> Nao e diagonalizavel.\n");
        }
        return;
    }

    double lambda1 = (-coefB + sqrt(delta)) / (2 * coefA);
    double lambda2 = (-coefB - sqrt(delta)) / (2 * coefA);

    printf("Autovalores encontrados: L1 = %.2f, L2 = %.2f\n\n", lambda1, lambda2);

    printf("----- Autovetor L1: -----\n\n");

    Autovetor v1 = autoVetor(matriz, lambda1);
    printf("\n");
    printf("----- Autovetor L2: -----\n\n");
    Autovetor v2 = autoVetor(matriz, lambda2);
    printf("\n");
    printf("Matriz D (Autovalores na diagonal):\n");
    printf("   %6.2f    %6.2f\n", lambda1, 0.0);
    printf("   %6.2f    %6.2f\n\n", 0.0, lambda2);

    printf("Matriz P (Autovetores nas colunas):\n");
    printf("   %6.2f    %6.2f\n", v1.x, v2.x);
    printf("   %6.2f    %6.2f\n\n", v1.y, v2.y);
}
