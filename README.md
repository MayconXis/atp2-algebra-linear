# Calculadora de Álgebra Linear em C99

Projeto Final Interdisciplinar — ATP2 (Algoritmos e Técnicas de Programação 2) + Álgebra Linear  
Instituto Federal de Goiás — Campus Inhumas]

---

## Sumário

1. [Visão Geral](#visão-geral)
2. [Estrutura de Arquivos](#estrutura-de-arquivos)
3. [Como Compilar e Executar](#como-compilar-e-executar)
4. [Decisões de Projeto](#decisoes-de-projeto-e-curiosidades-de-implementacao)
5. [Estruturas de Dados](#estruturas-de-dados)
6. [Funcionalidades](#funcionalidades)
7. [Formatos de Entrada](#formatos-de-entrada)
8. [Exemplos de Uso](#exemplos-de-uso)
9. [Limitações Conhecidas](#limitações-conhecidas)
10. [Desenvolvedores](#desenvolvedores)

---

## Visão Geral

Este programa é uma calculadora interativa de Álgebra Linear que opera via terminal. Ele é capaz de:

- Resolver sistemas lineares (solução única, infinitas soluções ou sem solução)
- Analisar transformações lineares (injetividade, sobrejetividade e bijetividade)
- Verificar se um conjunto de vetores forma uma base de um espaço vetorial
- Calcular autovalores e autovetores de matrizes 2x2
- Diagonalizar matrizes 2x2

O programa aceita entrada tanto pelo terminal quanto por arquivo de texto, e exibe o passo a passo de cada operação para fins didáticos.

---

## Estrutura de Arquivos

```
Atp2_Algebra/
├── main.c            → ponto de entrada, menu principal e chamada dos módulos
├── matrizStruct.c    → definição de todas as structs e enums do projeto
├── imprimir.c        → funções de impressão, interface visual e menus
├── parse.c           → parser de equações (leitura e interpretação de strings)
├── leituraEscrita.c  → leitura do terminal/arquivo e escrita no arquivo
├── sistema.c         → escalonamento, verificação de solução, substituição reversa
├── transformacaoL.c  → análise de transformações lineares (núcleo, imagem, posto)
├── Bases.c           → verificação de base e escalonamento robusto
├── Autovetores.c     → cálculo de autovalores, autovetores e diagonalização
└── Equacoes.txt      → arquivo de entrada (criado/editado pelo próprio programa)
```

### Dependência de inclusão (ordem obrigatória no `main.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrizStruct.c"   // structs — base de tudo
#include "imprimir.c"       // funções de UI
#include "sistema.c"        // operações matriciais
#include "parse.c"          // parser de strings
#include "transformacaoL.c" // análise de transformações
#include "Autovetores.c"    // autovalores e autovetores
#include "Bases.c"          // verificação de base
#include "leituraEscrita.c" // leitura e escrita de arquivos
```

## Como Compilar e Executar

### Pré-requisitos

- Compilador GCC com suporte a C99
- Sistema operacional: Windows, Linux ou macOS

### Compilação via terminal

```bash
gcc -std=c99 -o algebra main.c -lm
```

A flag `-lm` é necessária para a biblioteca matemática (`sqrt` usada no cálculo de autovalores).

### Compilação via CMake (CLion)

O projeto já inclui um `CMakeLists.txt`. Basta abrir a pasta no CLion e compilar normalmente pelo botão de play.

### Execução

```bash
./algebra
```

No Windows:
```bash
algebra.exe
```

O executável deve estar na mesma pasta que o arquivo `Equacoes.txt`.

---

## Decisoes de Projeto e Curiosidades de Implementacao

### Desenvolvimento em dupla e divisão de responsabilidades

O projeto foi desenvolvido em programação colaborativa, com dois desenvolvedores trabalhando em paralelo sobre os mesmos arquivos base. Para evitar conflitos, a divisão foi feita por módulo: um desenvolvedor ficou responsável pelos módulos matemáticos (escalonamento, verificação de solução, bases, autovalores e diagonalização) e o outro pela entrada de dados (parser de equações, leitura de arquivo e terminal, interface visual), porém ao mesmo tempo fazendo a mixagem.

Essa separação permitiu que ambos trabalhassem simultaneamente sem sobrescrever o trabalho um do outro, já que cada módulo é um arquivo `.c` independente.

---

### Como o parser interpreta equações

O parser em `parse.c` lê cada equação como uma string caractere por caractere, sem usar nenhuma biblioteca de expressões regulares ou de parsing. Todo o processo é feito manualmente:

- **Números**: quando o parser encontra um dígito, ele acumula o valor com `coeficiente = coeficiente * 10 + digito`. Isso permite ler números com mais de um dígito (`10x`, `23y`) sem precisar saber antecipadamente o tamanho.

- **Frações**: quando encontra `/`, ativa uma flag `barraApareceu`. Os dígitos seguintes vão para `coefDepoisBarra`. Quando finalmente encontra a variável, divide: `coeficiente = coeficiente / coefDepoisBarra`. Isso permite `1/2x`, `3/4y`, etc.

- **Coeficiente implícito**: se o parser chega numa letra sem ter acumulado nenhum número antes (ex: `x`, `-z`, `+y`), ele assume coeficiente 1. Isso evita que o usuário precise escrever `1x` explicitamente.

- **Ordenação automática das variáveis**: cada variável é mapeada pelo índice `caractere - 'a'` (sendo que `a` = 0, `b` = 1, ..., `x` = 23, `y` = 24, `z` = 25). O parser rastreia a menor e maior variável encontrada (`menorVariavel` e `maiorVariavel` na struct `SistemaLinear`). Com isso, mesmo que o usuário escreva `y + 2x = 4`, o programa monta a matriz corretamente com `x` na coluna 0 e `y` na coluna 1, porque sabe que `x` vem antes de `y` no alfabeto.

- **Limpeza entre usos**: o array `linhasPrint` (que guarda as linhas digitadas para exibir na tela) é um array global. No início de cada nova leitura, a função `limparLinhasPrint()` zera esse array para evitar que linhas de operações anteriores apareçam misturadas com a entrada atual — bug que foi identificado e corrigido durante o desenvolvimento.

---

### Leitura de arquivo e terminal unificada

O programa usa o mesmo arquivo `Equacoes.txt` para todas as operações de leitura e escrita. A opção `[6] - Escrever no Arquivo` do menu permite que o usuário popule esse arquivo pelo próprio programa, antes de usá-lo como entrada nas outras opções.

A leitura por arquivo e por terminal produzem exatamente o mesmo resultado: ambas alimentam a mesma struct `SistemaLinear`. A diferença é só a origem dos dados. Isso foi uma decisão de design deliberada para simplificar os módulos matemáticos, que nunca precisam saber como os dados chegaram.

Para o terminal, a leitura termina quando o usuário digita `FIM` (aceita maiúsculo ou minúsculo, usando `strcasecmp`). Para arquivo, termina quando `fscanf` retorna `EOF`.

---

### Passagem por ponteiro vs. por valor

Funções que modificam a matriz recebem `Matriz *matriz` (ponteiro). Sem o ponteiro, a função receberia uma cópia local e todas as modificações se perderiam ao retornar. O acesso é feito com `(*matriz).dados[i][j]` em vez do operador `->` (seta), que não foi ministrado na disciplina.

Funções que apenas leem (como `imprimir_matriz`) recebem `Matriz m` por valor, já que não precisam modificar o original e a cópia é suficiente.

---

### Por que dois escalonamentos diferentes?

O `escalonamento` simples assume que o pivô está sempre na diagonal principal (`dados[coluna][coluna]`). Quando esse elemento é zero, pula com `continue`. Isso funciona para resolver sistemas lineares comuns.

Porém, para verificar bases, esse comportamento causava falsos positivos: quando uma coluna inteira tinha zeros abaixo da diagonal (situação comum em conjuntos com vetores LD), o programa pulava a coluna e deixava linhas dependentes sem eliminar. O resultado era que um conjunto linearmente dependente passava na verificação como se fosse base.

A solução foi criar o `escalonamentoVerifBase`, que controla a linha do pivô com uma variável separada (`linhaPivo`). Quando o pivô natural é zero, ele busca em linhas abaixo e realiza a troca (pivoteamento parcial). O `linhaPivo` só avança quando efetivamente encontra e usa um pivô válido, garantindo que todas as dependências sejam detectadas.

Esse segundo escalonamento também é usado no cálculo de autovetores, onde a matriz `A - λI` frequentemente tem zeros na diagonal.

---

### Verificações

- **Sistemas com variáveis fora de ordem**: o programa deve reorganizar automaticamente. Ex: `y + 2x = 4` deve ser tratado como `2x + y = 4`.
- **Sistemas com frações**: ex: `1/2x + 3y = 7` deve funcionar corretamente.
- **Sistema impossível**: uma linha de zeros com resultado diferente de zero deve ser detectada mesmo que apareça no meio do sistema, não só no final.
- **Conjunto LD na verificação de base**: como o `V5 = {(1,2,0), (2,4,1), (3,6,1)}`, onde a dependência só aparece após pivoteamento.
- **Matriz sem autovalores reais**: como `T(x,y) = (-y, x)`, que representa uma rotação e não tem autovalores reais.
- **Raiz dupla não diagonalizável**: como `T(x,y) = (3x + y, 3y)`, que tem autovalor duplo λ=3 mas não é diagonalizável.


## Estruturas de Dados

Todas definidas em `matrizStruct.c`:

### `Linha`
Representa uma equação linear parseada.
```c
typedef struct {
    double coef[26];   // coeficientes de cada variável (índice = letra - 'a')
    double igualdade;  // valor após o sinal de igual
} Linha;
```

### `Matriz`
Representa uma matriz numérica genérica.
```c
typedef struct {
    double dados[10][10]; // dados em layout linha x coluna
    int linhas;           // número de linhas ativas
    int colunas;          // número de colunas ativas
} Matriz;
```

### `SistemaLinear`
Agrupa as linhas de um sistema com metadados sobre as variáveis.
```c
typedef struct {
    Linha linhas[10];   // equações do sistema
    int qtdLinhas;      // número de equações
    int qtdColunas;     // número de variáveis detectadas
    int menorVariavel;  // índice da menor variável (ex: 'x' = 23)
    int maiorVariavel;  // índice da maior variável (ex: 'z' = 25)
} SistemaLinear;
```

### `Autovetor`
Armazena as componentes de um autovetor 2D.
```c
typedef struct {
    double x;
    double y;
} Autovetor;
```

### Enums

```c
typedef enum { FALSE, TRUE } booleano;

typedef enum {
    SOLUCAO_UNICA,
    INFINITAS_SOLUCOES,
    SEM_SOLUCAO
} TipoSolucao;
```

---

## Funcionalidades

### 1. Resolver Sistema Linear

Recebe um sistema de equações lineares e:

1. Monta a matriz aumentada `[A | b]`
2. Aplica Eliminação de Gauss com exibição de cada passo
3. Detecta o tipo de solução:
   - **Solução única**: número de equações válidas = número de variáveis
   - **Infinitas soluções**: restam menos equações válidas que variáveis
   - **Sem solução**: linha com todos coeficientes zero mas resultado ≠ 0
4. Se solução única: aplica substituição reversa e exibe os valores

**Algoritmo de Eliminação de Gauss:**
Para cada coluna pivô, calcula o multiplicador `m = linha[coluna] / pivô` e aplica `Li = Li - m * Lpivô` em todas as linhas abaixo, zerando a coluna progressivamente até obter a forma triangular superior.

### 2. Analisar Transformação Linear

Recebe a matriz da transformação e as dimensões do domínio e contradomínio, e determina:

- **Dimensão da Imagem**: número de linhas não nulas após escalonamento (posto da matriz)
- **Dimensão do Núcleo**: dimensão do domínio - dimensão da imagem (Teorema do Núcleo e da Imagem)
- **Injetora**: núcleo = {0}, ou seja, dimensão do núcleo = 0
- **Sobrejetora**: imagem = contradomínio, ou seja, dimensão da imagem = dimensão de destino
- **Bijetora**: injetora E sobrejetora simultaneamente

### 3. Verificar Base

Recebe um conjunto de vetores e a dimensão do espaço, e verifica:

1. **Quantidade**: o conjunto precisa ter exatamente `n` vetores para ser base de Rⁿ
2. **Independência Linear**: após escalonamento robusto, conta o posto. Se posto = n, os vetores são LI e formam uma base. Se posto < n, são LD e não formam base.

Usa o `escalonamentoVerifBase` (com pivoteamento parcial) para garantir que linhas dependentes sejam sempre detectadas.

### 4. Autovalores e Autovetores

Implementado apenas para matrizes 2x2. O processo é:

1. Calcula o **traço** (soma da diagonal principal) e o **determinante**
2. Monta o **polinômio característico**: `λ² - traço·λ + det = 0`
3. Aplica **Bhaskara** para encontrar os autovalores λ1 e λ2
4. Para cada autovalor, resolve `(A - λI)v = 0` para encontrar o autovetor

**Casos:**
- `Delta < 0`: sem autovalores reais
- `Delta = 0`: autovalor único (raiz dupla)
- `Delta > 0`: dois autovalores reais distintos

### 5. Diagonalização

Para uma matriz 2x2, determina se é diagonalizável em R e exibe as matrizes P e D tais que `A = P·D·P⁻¹`:

- **D**: matriz diagonal com os autovalores na diagonal principal
- **P**: matriz cujas **colunas** são os autovetores correspondentes

Os autovetores ficam nas colunas (não nas linhas) porque a relação `A·P = P·D` exige que cada coluna de P seja um autovetor de A. Se estivessem nas linhas, a multiplicação matricial não produziria a relação correta.

**Não é diagonalizável quando:**
- Delta < 0 (sem autovalores reais)
- Delta = 0 e a matriz não é múltipla da identidade (raiz dupla sem 2 autovetores LI)

---

## Formatos de Entrada

### Regras gerais para equações (opções 1, 2, 4 e 5)

O parser interpreta strings de equações caractere por caractere. As regras são:

**Variáveis:**
- Apenas letras minúsculas (`a` a `z`)
- Devem ser sequenciais no alfabeto (ex: `x, y, z` ou `a, b, c`)
- Não pule letras (evite `a, m, z`)
- O programa organiza automaticamente em ordem alfabética, independente da ordem de digitação

**Coeficientes:**
- Números inteiros antes da variável: `3x`, `10y`
- Coeficiente 1 pode ser omitido: `x` equivale a `1x`, `-z` equivale a `-1z`
- Frações no formato `numerador/denominador` ANTES da variável: `1/2x` representa `0.5x`
- Não use decimais diretamente (ex: `0.5x` pode não funcionar)
- Não use o formato `x/2` (fração depois da variável não é suportada)

**Sinais:**
- Use `+` e `-` para separar termos
- O sinal negativo antes do primeiro termo é aceito: `-2x + y = 3`

**Igualdade:**
- Sempre terminar com `= valor`: `2x + y = 5`
- O valor após `=` também aceita frações: `x + y = 1/2`

**Exemplos válidos:**
```
4x + 2y + z - 2t = 3
y + 2x = 4
-z + 3x - y = 0
1/2x + 3y = 7
2x - 1/3y = 1/4
```

**Exemplos inválidos:**
```
0.5x + y = 3      → decimal não suportado
X + Y = 5         → maiúsculas não suportadas
x/2 + y = 3       → fração depois da variável
a + z = 5         → pulou letras (b, c, ..., y)
```

### Leitura pelo terminal (opção 2 no menu de entrada)

Digite cada equação em uma linha separada. Quando terminar, digite `FIM` (maiúsculo ou minúsculo):

```
Entrada:
2x + y = 5
-x + 3y = 1
FIM
```

### Leitura por arquivo (opção 1 no menu de entrada)

O arquivo `Equacoes.txt` deve estar na mesma pasta do executável. Uma equação por linha, sem linha em branco no final:

```
2x + y = 5
-x + 3y = 1
```

Para criar/editar o arquivo pelo próprio programa, use a opção `[6] - Escrever no Arquivo` do menu.

### Formato para Bases (opção 3)

Para verificar bases, os vetores são inseridos como números separados por espaço, um vetor por linha. O programa pede primeiro a dimensão do espaço e a quantidade de vetores.

**Pelo terminal:**
```
Dimensao do espaco: 3
Quantidade de vetores: 3
1 0 1
0 1 -1
2 1 0
```

**Por arquivo (`Equacoes.txt`):**
```
1.00 0.00 1.00
0.00 1.00 -1.00
2.00 1.00 0.00
```

### Formato para Transformações Lineares (opção 2)

Cada linha da matriz de transformação é uma equação sem o `= valor`. O programa pede as dimensões do domínio e contradomínio antes da entrada.

**Exemplo para T: R² → R², T(x,y) = (2x + y, 3x + 5y):**
```
R(Entrada): 2
R(Destino): 2
---
2x + y
3x + 5y
FIM
```

### Formato para Autovalores e Diagonalização (opções 4 e 5)

Igual às transformações lineares: cada linha da matriz como uma equação sem o `= valor`.

**Exemplo para a matriz:**
```
| 3  1 |
| 0  3 |
```
```
3x + y
3y
FIM
```

---

## Exemplos de Uso

### Exemplo 1 — Sistema com solução única

**Entrada:**
```
2x + y = 5
-x + 3y = 1
```

**Saída esperada:**
```
Operacao: L2 = L2 - (-0.50 * L1)
   2.00  1.00  5.00
   0.00  3.50  3.50

Nao ha contradicoes no sistema
O numero de equacoes validas (2) = numero de variaveis (2)
Portanto -> Sistema Possivel e Determinado (Solucao Unica)

Solucao do sistema:
x = 2.00
y = 0.43
```

### Exemplo 2 — Sistema com infinitas soluções

**Entrada:**
```
2x - z + y = 3
4x - 2z + 2y = 6
```

**Saída esperada:**
```
Operacao: L2 = L2 - (2.00 * L1)
   2.00  1.00  -1.00  3.00
   0.00  0.00   0.00  0.00

Nao ha contradicoes no sistema
Restaram apenas 1 equacoes validas para 3 variaveis apos o escalonamento
Existem variaveis livres, pois numero de equacoes < incognitas
Portanto -> Sistema possui infinitas solucoes.
```

### Exemplo 3 — Sistema sem solução

**Entrada:**
```
y + x = 1
2x + 2y = 2
3y + 3x = 5
```

**Saída esperada:**
```
...escalonamento...

Apos o escalonamento restaram linhas zeradas com o resultado diferente de zero.
Isso e uma contradicao matematica.
Sistema sem solucao (SI).
```

### Exemplo 4 — Verificação de base

**Entrada (R³, 3 vetores):**
```
1 0 1
0 1 -1
2 1 0
```

**Saída esperada:**
```
E base: os 3 vetores sao linearmente independentes e geram o espaco.
Forma uma base do R3!
```

### Exemplo 5 — Autovalores e Autovetores

**Entrada (matriz 2x2):**
```
3x + y
3y
FIM
```

**Saída esperada:**
```
Traco = 3.00 + 3.00 = 6.00
Determinante = 9.00 - 0.00 = 9.00
Delta = 0.00

Delta = 0. Existe apenas um autovalor real (raiz dupla).
Lambda = 3.00

Como tem raiz dupla mas nao e multipla da identidade, nao gera 2 autovetores LI.
Portanto -> Nao e diagonalizavel.
```

### Exemplo 6 — Diagonalização

**Entrada (matriz 2x2):**
```
3x
2y
FIM
```

**Saída esperada:**
```
Autovalores encontrados: L1 = 3.00, L2 = 2.00

Matriz D (Autovalores na diagonal):
     3.00      0.00
     0.00      2.00

Matriz P (Autovetores nas colunas):
     1.00      0.00
     0.00      1.00
```

---

## Como Funciona o Parser (Manipulação de Strings)

O parser em `parse.c` lê uma string caractere por caractere e extrai os coeficientes de cada variável. O processo é:

1. **Identificação do caractere**: verifica se é letra (`a-z`), número (`0-9`), sinal (`+`, `-`), fração (`/`) ou igualdade (`=`)

2. **Acumulação do coeficiente**: quando encontra dígitos, acumula o valor: `coeficiente = coeficiente * 10 + digito`. Isso permite números com mais de um dígito (ex: `10x`).

3. **Tratamento de frações**: quando encontra `/`, ativa a flag `barraApareceu`. O próximo número lido vai para `coefDepoisBarra`. Quando encontra a variável, divide: `coeficiente = coeficiente / coefDepoisBarra`.

4. **Coeficiente implícito**: se encontra uma letra sem número antes (ex: `x` ou `-z`), assume coeficiente 1 (ou -1 se havia sinal negativo).

5. **Ordenação automática**: cada variável é mapeada pelo índice `caractere - 'a'` (ex: `x` = índice 23, `y` = 24, `z` = 25). O parser rastreia a menor e maior variável encontrada para saber o intervalo de colunas da matriz, garantindo ordenação alfabética independente da ordem de digitação.

6. **Parte após o `=`**: quando encontra `=`, ativa `igualdadeApareceu` e o próximo número lido vai para `e.igualdade` (incluindo suporte a frações).

---

## Limitações Conhecidas

- **Tamanho máximo**: matrizes até 10x10 e sistemas com até 10 equações
- **Autovalores e diagonalização**: implementados apenas para matrizes 2x2
- **Decimais**: não suportados diretamente na entrada de equações; use frações (`1/2x` em vez de `0.5x`)
- **Variáveis**: devem ser letras minúsculas sequenciais no alfabeto
- **Arquivo único**: todas as operações de arquivo usam o mesmo arquivo `Equacoes.txt`
- **Encoding**: caracteres especiais (ã, ç, é) podem aparecer incorretamente em terminais Windows dependendo da configuração de codificação
- **Variáveis com letras não sequenciais**: o sistema pode gerar resultados incorretos se as variáveis pularem letras do alfabeto (ex: usar `a` e `z` sem as letras intermediárias)


## Desenvolvedores
👨‍💻 Desenvolvido por: **Maycon Douglas da Silva** e   **Felype de Moura Lino e Silva** 

📧 Contato: [mayconcontacts@gmail.com]  
📧 Contato: [srpsecontact@gmail.com]  

🌐 Linkedin:[https://www.linkedin.com/in/maycon-douglas-da-silva-9a791a2aa/]
🌐 Linkedin:[https://www.linkedin.com/in/felypemoura/]

🌐 GitHub: [https://github.com/MayconXis]  
🌐 GitHub: [https://github.com/surpriseone] 
