#include <stdio.h>
#include <string.h>

typedef enum{
    X,
    Y,
    Z
}coeficientes;

typedef struct{
    int coef[3];
    int igualdade;
}Equacao;

typedef enum{
    FALSE, TRUE
}booleano;

int descobrirCoef(char c);

int main(){
    int numerosLinhas = 0;
    int numerosColunas = 0;
    char equacao[50];
    
    while(TRUE){
        
        printf("informe quantas linhas de equações haverá: \n");
        scanf("%d", &numerosLinhas);
        getchar();

        Equacao eq[numerosLinhas];
        for(int i = 0; i < numerosLinhas; i++){
            scanf("%[^\n]s", equacao);
            getchar();
            int equacaoTam = strlen(equacao);

            int coeficiente = 0;
            int igualdadeApareceu = FALSE;
            int isNumero = TRUE;
            int sinal = 1;

            for(int j = 0; j < equacaoTam; j++){
                int caractere = (int) equacao[j];

                if(caractere == ' ') continue;

                if(!(caractere >= '0' && caractere <= '9')) isNumero = FALSE;
                    else isNumero = TRUE; 
                
                if(coeficiente == 0 && (caractere == 'x' || caractere == 'y' || caractere == 'z')){ //Quando o digito for oculto ex: -z
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

                else if(caractere == 'x' || caractere == 'y' || caractere == 'z'){ 
                    int letraCoef = descobrirCoef(caractere); //retorna posicao do coef pra salvar o numero
                    eq[i].coef[letraCoef] = coeficiente * sinal; // x = 0, y = 1, z = 2
                    coeficiente = 0;
                    sinal = 1;
                }
            
                else if(caractere == '='){
                    igualdadeApareceu = TRUE;
                    sinal = 1;
                }
            }
            if(igualdadeApareceu) eq[i].igualdade = coeficiente;
        }
        printf("X = %d\n", eq[0].coef[X]);
        printf("Y = %d\n", eq[0].coef[Y]);
        printf("Z = %d\n", eq[0].coef[Z]);
        printf("Igualdade = %d\n", eq[0].igualdade);
    }
}

int descobrirCoef(char c){
    switch(c){
        case 'x': case 'X':
            return X; // i = 0
            break;
        case 'y': case 'Y':
            return Y; // i = 1
            break;
        case 'z': case 'Z':
            return Z; // i = 2
            break;
        default:
        break;
    }
}