#include <stdio.h>
#include "matrizStruct.c"
#include "imprimir.c"
#include "sistema.c"
#include "parse.c"

int main() {
    char linha[TAMEQ];
    char variaveis[20];
    Linha lin[10];

    int quantidadeLinhas;
    
    while(TRUE){
        aberturaPrograma();
        int opcao;
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 1:
                printf("Sistema Linear: \n");
                SistemaLinear sistema;
                sistema.qtdColunas = 0;
                int esc = escolhaEntrada();

                if(esc == 1){
                    sistema.qtdLinhas = lerArquivo(&sistema);
                }else{
                    sistema.qtdLinhas = lerTerminal(&sistema);
                } 
        }

    }
    return 0;
}