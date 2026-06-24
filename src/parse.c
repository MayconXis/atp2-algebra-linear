#include <stdio.h>
#include <string.h>

#define qtdCoef 3
#define TAMEQ 60

typedef struct{
    double coef[qtdCoef];
    double igualdade;
}Linha;

typedef struct{
    double matriz[10][10];
    int linhas;
    int colunas;
}Matriz;


typedef struct{
    Linha linhas[10];
    int qtdLinhas;
    int qtdColunas;
}SistemaLinear;

typedef enum{
    FALSE, TRUE
}booleano;

Linha parser(char equacao[], SistemaLinear *sis);
int descobrirCoef(char c);
void limparLixoLinha(Linha *e);
void aberturaPrograma();
int lerArquivo(SistemaLinear *sis);
int lerTerminal(SistemaLinear *sis);
void continuar();
void printarEqs(Linha l[], int tam);



int main(){
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
}

Matriz aumentarMatriz(SistemaLinear sis){
    Matriz aumentada;
    int linha = sis.qtdLinhas;
    int colunaAumentada = sis.qtdColunas + 1;

    aumentada.linhas = linha;
    aumentada.colunas = colunaAumentada;

    for(int i = 0; i < linha; i++){
        for(int j = 0; j < colunaAumentada - 1; j++){
            aumentada.matriz[i][j] = sis.linhas[i].coef[j];
        }
        aumentada.matriz[i][colunaAumentada-1] = sis.linhas[i].igualdade;     
    }
    return aumentada;
}


int escolhaEntrada(){
    int o;
    printf("Escolha uma opção: \n");
    printf("[1] - Ler de Arquivo\n");
    printf("[2] - Ler do Terminal\n");
    scanf("%d", &o);
    getchar();
    return o;
}

int descobrirCoef(char c){
    char variaveisXYZ[] = "xyz";
    char variaviesUVW[] = "uvw";

    for(int i = 0; i < 3; i++){
        if(c == variaveisXYZ[i] || c == variaviesUVW[i]){
            return i;
        }
    }

    return -1;
}

int lerArquivo(SistemaLinear *sis){
    FILE *arq = fopen("Equacoes.txt", "r"); 

    if (arq == NULL){
        printf("Arquivo não encontrado \n");
        return 0;
    }

    char linhaLida[TAMEQ];
    int i = 0;
    while(fscanf(arq, "%[^\n]s", linhaLida) != EOF){
        fgetc(arq); //Pega o \n que ficou no arquivo
        sis->linhas[i++] = parser(linhaLida, sis); //salva a linha parseada no sistema e incrementa i
    }
    fclose(arq);
    return i;
}

int lerTerminal(SistemaLinear *sis){
    int numeroLinhas;
    char equacao[TAMEQ];
    printf("informe quantas linhas haverá: \n"); 
    scanf("%d", &numeroLinhas);
    getchar();

    for(int i = 0; i < numeroLinhas; i++){
        scanf("%[^\n]s", equacao);
        getchar();
        Linha linha = parser(equacao, sis);
        sis->linhas[i] = linha;
    }

    return numeroLinhas;
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
            int letraCoef = descobrirCoef(caractere); //retorna posicao do coef pra salvar o numero
            e.coef[letraCoef] = coeficiente * sinal; // x/u = 0, y/v = 1, z/w = 2
            coeficiente = 0;
            sinal = 1;

            if(letraCoef + 1 > sis->qtdColunas){
                sis->qtdColunas = letraCoef + 1; // guarda quantas variaveis
            }
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
    printf("[1] - Resolver Sistema Linear\n");
    printf("[2] - Analisar Transformação Linear\n");
    printf("[3] - Verificar Base de um Espaço Vetorial\n");
    printf("[4] - Calcular Autovalores e Autovetores\n");
    printf("[0] - Sair\n");
}


void continuar(){
    printf("Pressione enter para continuar...");
    while (getchar() != '\n');
}