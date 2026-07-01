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