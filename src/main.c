#include <stdio.h>
#include <stdlib.h>
#include "matrizStruct.c"
#include "imprimir.c"
#include "sistema.c"
#include "parse.c"
#include "transformacaoL.c"

int main() {
    char linha[TAMEQ];
    char variaveis[20];
    Linha lin[10];


    while (TRUE) {
        aberturaPrograma();
        int opcao;
        scanf("%d", &opcao);
        getchar();
        limparTela();
        switch (opcao) {
            case 1: {
                cabecalho("Sistema Linear", 85);
                SistemaLinear sistema;
                sistema.qtdColunas = 0;
                int esc = escolhaEntrada();
                sistema.qtdLinhas = escolhaLeitura(esc, &sistema);
                limparTela();
                cabecalho("Sistema Linear", 85);

                printf("\n");
                printf("Sistema Linear -> Matriz Aumentada:\n");
                printarSistemaLinear(sistema);
                printf("\n");
                resolverSistema(sistema);
                enterPraContinuar();
                limparTela();
            }
            break;

            case 2: {
                int bijetora = 0, injetora = 0, sobrejetora = 0, nucleo;
                int DimE; // dimensao entrada
                int DimS; // dimensao saida
                cabecalho("Transformação Linear", 90);
                printf("Digite a R(Entrada) -> R(Destino) respectivamente: \n");
                scanf("%d %d", &DimE, &DimS);
                getchar();
                SistemaLinear tl;
                tl.qtdColunas = 0;
                int escolha = escolhaEntrada();
                tl.qtdLinhas = escolhaLeitura(escolha, &tl);

                limparTela();
                Matriz mat = tranformarEmMatriz(tl);
                cabecalho("Transformação Linear", 90);

                printf("Formato de Matriz Tranformacão Linear R%d -> R%d:\n", DimE, DimS);
                printarMatriz(mat);
                printf("\n");

                escalonamento(&mat);
                int imagem = linhasUteis(mat); //retorna numero de linhas nao nulas -> Dimensão imagem
                printf("\n");

                printf("Após o escalonamento sobrou %d linhas não nulas\n", imagem);
                printf("Portanto -> Dimensão da imagem -> %d\n", imagem);
                printf(" \n");

                printf("Informações sobre a Transformação Linear R(%d) -> R(%d):\n", DimE, DimS);
                sobrejetora = isSobrejetora(imagem, DimS); //verifica se a imagem é igual dimensao destino
                if(sobrejetora){
                    printf("Dimensão da imagem (%d) = Dimensão de destino (%d)\n", imagem, DimS);
                    printf("Portanto -> Sobrejetora\n");
                }else{
                    printf("Dimensão da imagem (%d) != Dimensão de destino (%d)\n", imagem, DimS);
                    printf("Portanto -> não é Sobrejetora\n");
                }
                printf("\n");

                nucleo = dimensaoNucleo(DimE, imagem);
                printf("Dimensão do nucleo = Dimensão de entrada - Dimensão da imagem\n");
                printf("Dimensão do nucleo = %d - %d | Resultado = %d\n", DimE, imagem, DimE-imagem);

                if(nucleo == 0){
                    printf("Dimensão núcleo = 0\n");
                    printf("Portanto -> Injetora\n");
                    injetora = 1;
                }else{
                    printf("Dimensão núcleo > 0\n");
                    printf("Portanto -> Não é Injetora\n");
                }

                printf("\n");
                if(sobrejetora && injetora){
                    printf("Transformação Linear é Sobrejetora e Injetora\n");
                    printf("Portanto -> Bijetora\n");
                }else{
                    printf("Transformação Linear não é Sobrejetora e/ou Injetora\n");
                    printf("Portanto -> não é Bijetora\n");
                }
                enterPraContinuar();
                limparTela();
            }
            break;
            case 3: {
                printf("=== TESTE V1: {(2,1), (1,3)} - base de R2? SIM ===\n");
                Matriz v1;
                v1.linhas = 2; v1.colunas = 2;
                v1.dados[0][0] = 2; v1.dados[0][1] = 1;
                v1.dados[1][0] = 1; v1.dados[1][1] = 3;
                verificarBase(v1, 2);

                printf("\n=== TESTE V2: {(1,1), (2,2), (1,0)} - base de R2? NAO ===\n");
                Matriz v2;
                v2.linhas = 3; v2.colunas = 2;
                v2.dados[0][0] = 1; v2.dados[0][1] = 1;
                v2.dados[1][0] = 2; v2.dados[1][1] = 2;
                v2.dados[2][0] = 1; v2.dados[2][1] = 0;
                verificarBase(v2, 2);

                printf("\n=== TESTE V4: {(1,0,1), (0,1,-1), (2,1,0)} - base de R3? SIM ===\n");
                Matriz v4;
                v4.linhas = 3; v4.colunas = 3;
                v4.dados[0][0] = 1; v4.dados[0][1] = 0; v4.dados[0][2] = 1;
                v4.dados[1][0] = 0; v4.dados[1][1] = 1; v4.dados[1][2] = -1;
                v4.dados[2][0] = 2; v4.dados[2][1] = 1; v4.dados[2][2] = 0;
                verificarBase(v4, 3);

                printf("\n=== TESTE V5: {(1,2,0), (2,4,1), (3,6,1)} - base de R3? NAO ===\n");
                Matriz v5;
                v5.linhas = 3; v5.colunas = 3;
                v5.dados[0][0] = 1; v5.dados[0][1] = 2; v5.dados[0][2] = 0;
                v5.dados[1][0] = 2; v5.dados[1][1] = 4; v5.dados[1][2] = 1;
                v5.dados[2][0] = 3; v5.dados[2][1] = 6; v5.dados[2][2] = 1;
                verificarBase(v5, 3);
            } break;

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

            case 6:
            moldura(80);
            informacoesLeitura();
            moldura(80);
            escreverArquivo();
            enterPraContinuar();
            limparTela();
            break;

            case 0: return 0;
        }
    }
    return 0;
}



