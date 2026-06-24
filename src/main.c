#include <stdio.h>
#include "matrizStruct.c"
#include "imprimir.c"
#include "sistema.c"
#include "parse.c"

int escolhaLeitura(int esc, SistemaLinear sis);
int main() {
    char linha[TAMEQ];
    char variaveis[20];
    Linha lin[10];

    
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
                sistema.qtdLinhas = escolhaLeitura(esc, sistema);

                Matriz matrizAumentada = aumentarMatriz(sistema);
                escalonamento(&matrizAumentada);

                //continuar com prints da resolucao e informacoes que o professor quer

            break;
            case 2:
                printf("Transformação Linear\n");
                SistemaLinear sistema;
                sistema.qtdColunas = 0;
                int esc = escolhaEntrada();
                sistema.qtdLinhas = escolhaLeitura(esc, sistema);

                // funcoes de TL

            break;
        }   

    }
    return 0;
}

int escolhaLeitura(int esc, SistemaLinear sis){
    if(esc == 1){
        return lerArquivo(&sis);
    }else if(esc == 2){
        return lerTerminal(&sis);
    }else{
        printf("Opção invalida\n");
        return -1;
    }
}