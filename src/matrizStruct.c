#define qtdCoef 26
typedef struct{
    double coef[qtdCoef];
    double igualdade;
}Linha;

typedef struct{
    double dados[10][10];
    int linhas;
    int colunas;
}Matriz;

typedef struct{
    Linha linhas[10];
    int qtdLinhas;
    int qtdColunas;
    int menorVariavel;
    int maiorVariavel;
}SistemaLinear;

typedef enum{
    FALSE, TRUE
}booleano;

typedef enum {
    SOLUCAO_UNICA,
    INFINITAS_SOLUCOES,
    SEM_SOLUCAO
} TipoSolucao;


typedef struct{
    double x;
    double y;
}Autovetor;






