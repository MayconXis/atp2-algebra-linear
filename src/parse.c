#include <stdio.h>
#include <string.h>
#include <strings.h>
#define TAMEQ 60


Linha parser(char equacao[], SistemaLinear *sis);
void limparLixoLinha(Linha *e);
int lerArquivo(SistemaLinear *sis);
int lerTerminal(SistemaLinear *sis);

char linhasPrint[10][TAMEQ];

void printarEntrada(int numeroLinhas){
    printf("Entrada:\n");
    for(int i = 0; i < numeroLinhas; i++){
        printf("\t%s\n", linhasPrint[i]);
    }
    printf("\n");
}

Linha parser(char linha[], SistemaLinear *sis){
    Linha e; // expressão ou equação

    limparLixoLinha(&e); //Limpar lixo de memoria gerado por int
    double coeficiente = 0;
    int igualdadeApareceu = FALSE;
    int isNumero = TRUE;
    int isLetra = TRUE;
    int sinal = 1;
    int linhaTam = strlen(linha);

    int barraApareceu = FALSE;
    int coefDepoisBarra = 0;

    
    for(int j = 0; j < linhaTam; j++){
        int caractere = (int) linha[j];

        if(caractere == ' ') continue;

        if(caractere >= 'a' && caractere <= 'z') isLetra = TRUE;
            else isLetra = FALSE;

        if(caractere >= '0' && caractere <= '9') isNumero = TRUE;
            else isNumero = FALSE;

        if(caractere == '/'){
            barraApareceu = TRUE;
            continue;
        }

        if(coeficiente == 0 && (isLetra)){ //Quando o digito for oculto ex: -z
            coeficiente = 1;
        }

        if(barraApareceu && isNumero){
            coefDepoisBarra *= 10;
            coefDepoisBarra += (int) caractere - '0';
        }
        else if(isNumero){
            coeficiente *= 10; // ganhar uma casa decimal, para numeros > 1 digito
            coeficiente += (int) caractere - '0'; // char = numero - '0' = numero real
        }else if(caractere == '-'){
            sinal = -1;
        }else if(caractere == '+'){
            sinal = 1;
        }

        else if(isLetra){ 
            if(barraApareceu && coefDepoisBarra != 0){ //evitar divisao por 0
                coeficiente = (double) coeficiente / coefDepoisBarra;
                barraApareceu = FALSE;
                coefDepoisBarra = 0;
            }
            e.coef[caractere - 'a'] = coeficiente * sinal;
            coeficiente = 0;
            sinal = 1;
            if(caractere - 'a' < sis->menorVariavel) sis->menorVariavel = caractere - 'a';
            if(caractere - 'a' > sis->maiorVariavel) sis->maiorVariavel = caractere - 'a';
        }
            
        else if(caractere == '='){
            igualdadeApareceu = TRUE;
            coeficiente = 0;
            sinal = 1; // reseta sinal
        } 
    }

    if(igualdadeApareceu) {
        if(barraApareceu && coefDepoisBarra != 0){ // fazer a divisao depois da igualde, no outro caso espera por letra
            coeficiente = (double) coeficiente / coefDepoisBarra;
        }
        e.igualdade = coeficiente * sinal;
    }
    return e; //retorna a linha pra salvar no sistema
}


void inicializarMaiorMenorSL(SistemaLinear *sis){
    sis->maiorVariavel = -1000;
    sis->menorVariavel = 1000;
}
void inicializarColunasSL(SistemaLinear *sis){
    sis->maiorVariavel = sis->maiorVariavel + 1; //+1 pra subtracao dar o numero certo de colunas
    sis->qtdColunas = sis->maiorVariavel - sis->menorVariavel; // numero total de colunas da matriz
}

void limparLixoLinha(Linha *l){
    for(int i = 0; i < qtdCoef; i++){
        l->coef[i] = 0;
    }
    l->igualdade = 0;
}











