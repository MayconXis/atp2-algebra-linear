#include <stdio.h>
#include "matrizStruct.c"
#include "imprimir.c"
#include "sistema.c"



int main() {
    SistemaLinear sistema;
    sistema.num_equacoes = 2;
    sistema.num_variaveis = 2;
    sistema.A.dados[0][0] = 1;
    sistema.A.dados[0][1] = 1;
    sistema.A.dados[1][0] = 2;
    sistema.A.dados[1][1] = -1;
    sistema.b.vetor[0] = 5;
    sistema.b.vetor[1] = 1;

    SistemaLinear meu_sistema = lerTerminal();
    Matriz aumentada = criarMatrizAumentada(meu_sistema);
    escalonamento(&aumentada);
    imprimir_matriz(aumentada);



    Matriz aumentada = criarMatrizAumentada(sistema);
    imprimir_matriz(aumentada);
    return 0;
}