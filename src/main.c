#include <stdio.h>
#include "matrizStruct.c"
#include "imprimir.c"
#include "sistema.c"
#include "parse.c"

int escolhaLeitura(int esc, SistemaLinear *sis);

int main() {
    char linha[TAMEQ];
    char variaveis[20];
    Linha lin[10];


    while (TRUE) {
        aberturaPrograma();
        int opcao;
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1: {
                printf("Sistema Linear: \n");
                SistemaLinear sistema;
                sistema.qtdColunas = 0;
                int esc = escolhaEntrada();
                sistema.qtdLinhas = escolhaLeitura(esc, &sistema);

                Matriz matrizAumentada = aumentarMatriz(sistema);
                escalonamento(&matrizAumentada);
                substituicaoReversa(&matrizAumentada); // Adicionado aqui também
            }
            break;

            case 2: {
                printf("Transformacao Linear\n");
            }
            break;

            case 5: {
                printf("=== TESTE 1: Solucao Unica ===\n");
                SistemaLinear s1;
                s1.qtdLinhas = 2;
                s1.qtdColunas = 2;
                s1.linhas[0].coef[0] = 1; s1.linhas[0].coef[1] = 1; s1.linhas[0].igualdade = 5;
                s1.linhas[1].coef[0] = 2; s1.linhas[1].coef[1] = -1; s1.linhas[1].igualdade = 1;
                resolverSistema(s1);

                printf("\n=== TESTE 2: Infinitas Solucoes ===\n");
                SistemaLinear s2;
                s2.qtdLinhas = 2;
                s2.qtdColunas = 3;
                s2.linhas[0].coef[0] = 2; s2.linhas[0].coef[1] = -1; s2.linhas[0].coef[2] = 1; s2.linhas[0].igualdade = 3;
                s2.linhas[1].coef[0] = 4; s2.linhas[1].coef[1] = -2; s2.linhas[1].coef[2] = 2; s2.linhas[1].igualdade = 6;
                resolverSistema(s2);

                printf("\n=== TESTE 3: Sem Solucao ===\n");
                SistemaLinear s3;
                s3.qtdLinhas = 3;
                s3.qtdColunas = 2;
                s3.linhas[0].coef[0] = 1; s3.linhas[0].coef[1] = 1; s3.linhas[0].igualdade = 2;
                s3.linhas[1].coef[0] = 2; s3.linhas[1].coef[1] = 2; s3.linhas[1].igualdade = 4;
                s3.linhas[2].coef[0] = 3; s3.linhas[2].coef[1] = 3; s3.linhas[2].igualdade = 7;
                resolverSistema(s3);
            } break;

            case 0: return 0;
        }
    }
    return 0;
}

int escolhaLeitura(int esc, SistemaLinear *sis) {
    if (esc == 1) {
        return lerArquivo(sis);
    } else if (esc == 2) {
        return lerTerminal(sis);
    } else {
        printf("Opção invalida\n");
        return -1;
    }
}