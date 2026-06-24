

Matriz aumentarMatriz(SistemaLinear sis){
    Matriz aumentada;
    int linha = sis.qtdLinhas;
    int colunaAumentada = sis.qtdColunas + 1;

    aumentada.linhas = linha;
    aumentada.colunas = colunaAumentada;

    for(int i = 0; i < linha; i++){
        for(int j = 0; j < colunaAumentada - 1; j++){
            aumentada.dados[i][j] = sis.linhas[i].coef[j];
        }
        aumentada.dados[i][colunaAumentada-1] = sis.linhas[i].igualdade;     
    }
    return aumentada;
}

void escalonamento(Matriz *matriz) {
    double multiplicador;

    for (int coluna = 0; coluna < (*matriz).colunas; coluna++) {

        // // Começa em coluna + 1 para não mexer na linha do pivô
        // Desce nas linhas abaixo do pivô pra zerar

        for (int linha = coluna + 1; linha < (*matriz).linhas; linha++) {

            // Descobre o número pra zerar a posição atual
            // Divide o número pelo pivô para zerar
            multiplicador = (*matriz).dados[linha][coluna] / (*matriz).dados[coluna][coluna];

            for (int k = 0; k < (*matriz).colunas; k++) {
                //Atualiza a linha inteira
               (*matriz).dados[linha][k] = (*matriz).dados[linha][k] - multiplicador * (*matriz).dados[coluna][k];
            }
        }
    }
}
