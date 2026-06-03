
#ifndef ATP2_ALGEBRA_MATRIX_H
#define ATP2_ALGEBRA_MATRIX_H


// parar guardar os dados da matriz
typedef struct {
    double dados[100][100];
    int linhas;
    int colunas;
}Matriz;

//termo independentes
typedef struct {
    double vetor[100];
    int tam;
}Vetor;

// struct utilizando os dados da matriz e os termos independentes juntos
typedef struct {
    Matriz A;
    Vetor b;
    int num_variaveis;
    int num_equacoes;
}SistemaLinear;


#endif





