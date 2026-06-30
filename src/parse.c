#include <stdio.h>
#include <string.h>
#include <strings.h>
#define TAMEQ 60


Linha parser(char equacao[], SistemaLinear *sis);
int descobrirCoef(char c);
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

    
    for(int j = 0; j < linhaTam; j++){
        int caractere = (int) linha[j];

        if(caractere == ' ') continue;

        if(caractere >= 'a' && caractere <= 'z') isLetra = TRUE;
            else isLetra = FALSE;

        if(caractere >= '0' && caractere <= '9') isNumero = TRUE;
            else isNumero = FALSE;
                
        if(coeficiente == 0 && (isLetra)){ //Quando o digito for oculto ex: -z
            coeficiente = 1;
        }

        if(isNumero){
            coeficiente *= 10; // ganhar uma casa decimal, para numeros > 1 digito
            coeficiente += (int) caractere - '0'; // char = numero - '0' = numero real
        }else if(caractere == '-'){
            sinal = -1;
        }else if(caractere == '+'){
            sinal = 1;
        }

        else if(isLetra){ 
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
    if(igualdadeApareceu) e.igualdade = coeficiente * sinal;

    return e; //retorna a linha pra salvar no sistema
}


void limparLixoLinha(Linha *l){
    for(int i = 0; i < qtdCoef; i++){
        l->coef[i] = 0;
    }
    l->igualdade = 0;
}

int lerTerminal(SistemaLinear *sis){
    int numeroLinhas = 0;
    char linhaEntrada[TAMEQ];

    inicializarMaiorMenorSL(sis);
    int i = 0;
    while(1){
        scanf("%[^\n]", linhaEntrada);
        getchar();        
        if(strcasecmp(linhaEntrada, "FIM") == 0) break; //Compara independente se é minuscula ou maiuscula
        strcpy(linhasPrint[i], linhaEntrada); //Guarda pra printar pro usuario
        Linha linha = parser(linhaEntrada, sis); //limpa e faz o parse da linha
        sis->linhas[i++] = linha; //salva a linha parseada no sistema linear
        numeroLinhas++;
    }

    sis->maiorVariavel = sis->maiorVariavel + 1;

    return numeroLinhas;
}

// Arquivo
int lerArquivo(SistemaLinear *sis){
    FILE *arq = fopen("Equacoes.txt", "r"); 

    if (arq == NULL){
        printf("Arquivo não encontrado \n");
        return 0;
    }

    inicializarMaiorMenorSL(sis);
    char linhaLida[TAMEQ];
    int i = 0;
    while(fscanf(arq, "%[^\n]", linhaLida) == 1){
        fgetc(arq); //Pega o \n que ficou no arquivo
        strcpy(linhasPrint[i], linhaLida);
        sis->linhas[i++] = parser(linhaLida, sis); //salva a linha parseada no sistema e incrementa i
    }
    fclose(arq);

    sis->maiorVariavel = sis->maiorVariavel + 1;
    return i;
}

int escreverArquivo(){
    FILE *arq = fopen("Equacoes.txt", "w");

    if(arq == NULL){
        printf("Arquivo não encontrado\n");
        return 1;
    }
    char linha[100];
    
    while(1){
        scanf("%[^\n]s", linha);
        getchar();
        
        if(strcasecmp(linha, "FIM") == 0) break;

        fprintf(arq, "%s\n", linha);
    }
    
    fclose(arq);
}

void inicializarMaiorMenorSL(SistemaLinear *sis){
    sis->maiorVariavel = -1000;
    sis->menorVariavel = 1000;
}



