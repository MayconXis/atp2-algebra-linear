#include <stdio.h>
#include <string.h>

#define qtdCoef 3
#define TAMEQ 60

char variaveisChar[] = "xyz";

typedef enum{
    X,
    Y,
    Z
}Variaveis;

typedef struct{
    double coef[qtdCoef];
    double igualdade;
}Equacao;

typedef enum{
    FALSE, TRUE
}booleano;

Equacao parser(char equacao[]);
int descobrirCoef(char c);
void limparLixoEquacoes(Equacao *e);
void aberturaPrograma();
int lerArquivo(Equacao e[]);
int lerTerminal(Equacao e[]);
void continuar();
void printarEqs(Equacao e[], int tam);

int main(){
    char equacao[TAMEQ];
    Equacao eq[20];
    int quantidade;

    while(TRUE){
        aberturaPrograma();
        int opcao;
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 1:
                quantidade = lerArquivo(eq);
                printarEqs(eq, quantidade);
                break;
            case 2:
                quantidade = lerTerminal(eq);
                printarEqs(eq, quantidade);
                break;
            default:
                printf("Opcão invalida\n");
                continuar();
                continue;
        }

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

int lerArquivo(Equacao e[]){
    FILE *arq = fopen("Equacoes.txt", "r");
    if (arq == NULL){
        printf("Arquivo não encontrado \n");
        return 0;
    }

    char equacao[TAMEQ];
    int i = 0;
    while(fscanf(arq, "%[^\n]s", equacao) != EOF){
        fgetc(arq);
        e[i++] = parser(equacao);
    }
    fclose(arq);
    return i;
}

int lerTerminal(Equacao e[]){
    int numeroLinhas;
    char equacao[TAMEQ];
    printf("informe quantas linhas de equações haverá: \n");
    scanf("%d", &numeroLinhas);
    getchar();

    for(int i = 0; i < numeroLinhas; i++){
        scanf("%[^\n]s", equacao);
        getchar();
        Equacao linha = parser(equacao);
        e[i] = linha;
    }

    return numeroLinhas;
}

Equacao parser(char equacao[]){
    Equacao eq;

    limparLixoEquacoes(&eq); //Limpar lixo de memoria gerado por int
    double coeficiente = 0;
    int igualdadeApareceu = FALSE;
    int isNumero = TRUE;
    int sinal = 1;
    int equacaoTam = strlen(equacao);

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
            eq.coef[letraCoef] = coeficiente * sinal; // x = 0, y = 1, z = 2
            coeficiente = 0;
            sinal = 1;
        }
            
        else if(caractere == '='){
            igualdadeApareceu = TRUE;
            coeficiente = 0;
            sinal = 1; // reseta sinal
        }
    }
    if(igualdadeApareceu) eq.igualdade = coeficiente * sinal;

    return eq;
}


void limparLixoEquacoes(Equacao *e){
    for(int i = 0; i < qtdCoef; i++){
        e->coef[i] = 0;
    }
    e->igualdade = 0;
}

int descobrirLinhasArq(){
    FILE *arq = fopen("Equacoes.txt", "r");

    if (arq == NULL){
        printf("Arquivo não encontrado \n");
        return 0;
    }

    char a[TAMEQ];

    int linhas = 0;
    while(fscanf(arq, "%[^\n]s", a)){
        fgetc(arq);
        linhas++;
    }

    fclose(arq);

    return linhas;
}

void aberturaPrograma(){
    printf("PROGRAMA DE MATRIZES\n");
    printf("Escolha uma opção: \n");
    printf("[1] - Ler por arquivo\n");
    printf("[2] - Ler por terminal\n");
}


void continuar(){
    printf("Pressione enter para continuar...");
    while (getchar() != '\n');
}

void printarEqs(Equacao e[], int tam){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < qtdCoef; j++){
            if(j == qtdCoef - 1){
                printf("%d%c = %d\n", e[i].coef[j], variaveisChar[j], e[i].igualdade);
            }else{
                printf("%d%c ", e[i].coef[j], variaveisChar[j]);
            }
        }
    }
}