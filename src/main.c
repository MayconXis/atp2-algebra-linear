#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrizStruct.c"
#include "imprimir.c"
#include "sistema.c"
#include "parse.c"
#include "transformacaoL.c"
#include "Autovetores.c"
#include "Bases.c"
#include "leituraEscrita.c"

int main() {
    char linha[TAMEQ];
    char variaveis[20];
    Linha lin[10];
    instrucoes();
    enterPraContinuar();
    limparTela();


    while (TRUE) {
        aberturaPrograma();
        int opcao;
        scanf("%d", &opcao);
        getchar();
        limparTela();

        int continuar;
        switch (opcao) {
            case 1: {
                do{
                cabecalho("Sistema Linear", 85);
                SistemaLinear sistema;
                int esc = escolhaEntrada();
                sistema.qtdLinhas = escolhaLeitura(esc, &sistema);
                limparTela();
                cabecalho("Sistema Linear", 85);
                printarEntrada(sistema.qtdLinhas);
                printf("\n");
                printf("Sistema Linear -> Matriz Aumentada:\n");
                printarSistemaLinear(sistema);
                printf("\n");
                resolverSistema(sistema);
                enterPraContinuar();
                limparTela();
                continuar = continuarNoBloco("Sistema Linear");
                }while(continuar == 1);
                limparTela();
            }
            break;

            case 2: {
                do{
                    limparTela();
                    int bijetora = 0, injetora = 0, sobrejetora = 0, nucleo;
                    int DimE; // dimensao entrada
                    int DimS; // dimensao saida
                    cabecalho("Transformação Linear", 90);
                    printf("Digite a R(Entrada) -> R(Destino) respectivamente: \n");
                    scanf("%d %d", &DimE, &DimS);
                    getchar();
                    SistemaLinear tl;
                    int escolha = escolhaEntrada();
                    tl.qtdLinhas = escolhaLeitura(escolha, &tl);
                    limparTela();
                    Matriz mat = tranformarEmMatriz(tl);

                    cabecalho("Transformação Linear", 90);

                    printarEntrada(tl.qtdColunas);

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
                    continuar = continuarNoBloco("Transformacoes Lineares");
                }while(continuar == 1);
                limparTela();
                
            }break;
            case 3: {
                do{
                    limparTela();
                    cabecalho("Verificar bases", 80);

                    int dimensao;
                    printf(" - Informe a dimensao do espaco (ex: 2 para R2, 3 para R3):\n");
                    scanf("%d", &dimensao);
                    getchar();

                    Matriz vetores;
                    vetores.colunas = dimensao;

                    int qtdVetores;
                    printf(" - Informe quantos vetores (linhas) entraram?\n");
                    scanf("%d", &qtdVetores);
                    getchar();

                    vetores.linhas = qtdVetores;

                    int escBases = escolhaEntrada();
                    if (escBases == 1) {
                        lerArquivoNumeros(&vetores);
                    } else if (escBases == 2) {
                        lerTerminalNumeros(&vetores);
                    } else {
                        printf("Opcao invalida!\n");
                        enterPraContinuar();
                        break; 
                    }
                    enterPraContinuar();
                    limparTela();
                    printf("Matriz formada pelos vetores do R%d:\n", dimensao);
                    printarMatriz(vetores);
                    printf("\n");

                    printf("--- Iniciando Testes de Base ---\n");
                    
                
                    int resultado = verificarBase(vetores, dimensao);

                    printf("\n");
                    moldura(50);
                    if (resultado == TRUE) {
                        printf(" RESULTADO FINAL: FORMA UMA BASE DO R%d!\n", dimensao);
                    } else {
                        printf(" RESULTADO FINAL: NAO FORMA UMA BASE DO R%d!\n", dimensao);
                    }
                    moldura(50);
                    
                    enterPraContinuar();
                    limparTela();
                    continuar = continuarNoBloco("Bases");
                }while(continuar == 1);
                limparTela();
            } break;
            case 4: {
                do{
                    cabecalho("Autovalores e Autovetores", 85);
                    SistemaLinear av;
                    int e = escolhaEntrada(); //escolha
                    av.qtdLinhas = escolhaLeitura(e, &av);
                    limparTela();
                    cabecalho("Autovalores e Autovetores", 85);
                    printarEntrada(av.qtdLinhas);
                    printf("Formato de matriz:\n");
                    Matriz matrizAutov = tranformarEmMatriz(av);
                    printarMatriz(matrizAutov);
                    printf("\n");
                    autoValores(matrizAutov);
                    enterPraContinuar();
                    limparTela();
                    continuar = continuarNoBloco("Autovetores");
                }while(continuar == 1);
                limparTela();
            } break;

            case 5: {//
                do{
                    limparTela();
                    moldura(50);
                    printf("Diagonalizacao de Matriz 2x2\n");
                    moldura(50);

                    SistemaLinear av;
                    int e = escolhaEntrada();
                    av.qtdLinhas = escolhaLeitura(e, &av);

                    if (av.qtdLinhas > 0) {
                        limparTela();
                        cabecalho("Diagonalizacao de Matriz 2x2", 60);
                        printarEntrada(av.qtdLinhas);

                        Matriz matrizAutov = tranformarEmMatriz(av);

                        printf("Matriz de Entrada:\n");
                        printarMatriz(matrizAutov);
                        printf("\n");

                        printf("Resumo dos Autovalores e Autovetores \n");
                        // autoValores(matrizAutov); 
                        diagonalizarMatriz(matrizAutov);
                    } else {
                        printf("\nNenhuma matriz valida foi carregada.\n");
                    }

                    enterPraContinuar();
                    limparTela();
                    continuar = continuarNoBloco("Diagonalizacao de Matriz 2x2");
                }while(continuar == 1);
                limparTela();
            } break;
            case 6:{
                moldura(80);
                int opcao;
                printf("[1] - Entrada para Sistemas, Transformacoes e Autovetores\n");
                printf("[2] - Bases\n");
                scanf("%d",  &opcao);
                getchar();
                if(opcao == 1){
                    informacoesLeitura();
                    moldura(80);
                    escreverArquivo();
                }else if(opcao == 2){
                    escreverArquivoBases();
                }
                enterPraContinuar();
                limparTela();
            }break;
            case 0:
                return 0;
            default:
                printf("opcão invalida.\n");
                enterPraContinuar();
                limparTela();
                break;
        }
    }
    return 0;
}



