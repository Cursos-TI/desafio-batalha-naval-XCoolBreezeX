#include <stdio.h>
#include <math.h>  // Inclui a biblioteca matemática para a função abs()

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.


    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    // Define o tamanho das matrizes de habilidade
#define TAMANHO_DA_HABILIDADE 5
// Define o tamanho do tabuleiro principal
#define TABULEIRO_TAMANHO 10

// Define os valores númericos para representação no tabuleiro
#define Agua 0 // Representa a água ou células vazias
#define Navio 3 // Representa as partes dos navios
#define Area_Afetada_Habilidade 5 // Representa as áreas afetadas pelas habilidades

int main(){
    // Array de caracteres para o cabeçalho das colunas do tabuleiro
    char letras[TABULEIRO_TAMANHO] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    // Tabuleiro principal (10x10)
    int tabuleiro[TABULEIRO_TAMANHO][TABULEIRO_TAMANHO];

    // Matrizes das habilidades (tamanho 5x5)
    // Serão preechidas dinamicamente com 0s e 1s
    int cone[TAMANHO_DA_HABILIDADE][TAMANHO_DA_HABILIDADE];
    int cruz[TAMANHO_DA_HABILIDADE][TAMANHO_DA_HABILIDADE];
    int octaedro[TAMANHO_DA_HABILIDADE][TAMANHO_DA_HABILIDADE];

    // --- Construção Dinâmica das Matrizes de habilidade ---

    // Habilidade: CONE (ponto de origem no topo, expandido para baixo)
    // O cone terá 3 linhas de efeito dentro da matriz 5x5.
    for (int i = 0; i < TAMANHO_DA_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_DA_HABILIDADE; j++) {
            if (i < 3 && abs(j - TAMANHO_DA_HABILIDADE / 2) <= i) {
                cone[i][j] = 1; // Parte do cone
            } else {
                cone[i][j] = 0; // Fora do cone
            }
        }
    }

    // Habilidade: CRUZ (ponto de orgiem no centro)
    // O centro da matriz 5x5 é na linha 2, coluna 2 (índice TAMANHO_DA_HABILIDADE / 2)
    for (int i = 0; i < TAMANHO_DA_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_DA_HABILIDADE; j++) {
            if (i == TAMANHO_DA_HABILIDADE / 2 || j == TAMANHO_DA_HABILIDADE / 2){
                cruz[i][j] = 1; //Parte da cruz            
            } else {
                cruz[i][j] = 0; //Fora da cruz
            }
        }
    }

    // Habilidade: OCTAEDRO (Losango, ponto de origem no centro)
    // O centro da matriz 5x5 é na linha 2, coluna 2.
    // A condição para um losango é a soma das distâncias absolutas ao centro.
    for (int i = 0; i < TAMANHO_DA_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_DA_HABILIDADE; j++) {
            if (abs(i - TAMANHO_DA_HABILIDADE / 2) + abs(j - TAMANHO_DA_HABILIDADE / 2) <= TAMANHO_DA_HABILIDADE / 2) {
                octaedro[i][j] = 1; // Parte do octaedro
            } else {
                octaedro[i][j] = 0; // Fora do octaedro
            }
        }
    }

    // --- Definição dos pontos de origem das habilidades no tabuleiro ---
    // Estes são os pontos no TABULEIRO principal onde o "centro" ou "pico"
    // de cada habilidade será ancorado.

    int cone_origem_x = 2; // Linha 2 do tabuleiro para o "pico" do cone
    int cone_origem_y = 2; // Coluna 2 do tabuleiro para o "pico" do cone

    int cruz_origem_x = 5; // Linha 5 do tabuleiro para o centro da cruz
    int cruz_origem_y = 5; // Coluna 5 do tabuleiro para o centro da cruz

    int octaedro_origem_x = 7; // Linha 7 do tabuleiro para o centro do octaedro
    int octaedro_origem_y = 7; // Coluna 7 do tabuleiro para o centro do octaedro

    // --- Inicialização do Tabuleiro Principal ---
    // Preenche todo o tabuleiro com o valor de Agua (0)
    for (int i = 0; i < TABULEIRO_TAMANHO; i++) {
        for (int j = 0; j < TABULEIRO_TAMANHO; j++) {
            tabuleiro[i][j] = Agua;
        }
    }

    // --- Posicionamento dos Navios no Tabuleiro ---

    // Navio na vertical: coluna 5, linhas 1, 2, 3
    for (int i = 1; i < 4; i++){
        tabuleiro[i][5] = Navio;
    }

    // Navio na horizontal: linha 9, colunas 1, 2, 3
    for (int j = 1; j < 4; j++) {
        tabuleiro[9][j] = Navio;
    }

    // Navio na diagonal principal: pontos (0,0), (1,1), (2,2)
    tabuleiro[0][0] = Navio;
    tabuleiro[1][1] = Navio;
    tabuleiro[2][2] = Navio;

    // Navio na diagonal secundária: pontos (0,9), (1,8), (2,7)
    tabuleiro[0][9] = Navio;
    tabuleiro[1][8] = Navio;
    tabuleiro[2][7] = Navio;

    // --- Lógica para sobrepor as habilidades no Tabuleiro ---

    // Sobrepondo a Habilidade: CONE
    // Itera sobre cada célula da matriz da habilidade (5x5)
    for (int i = 0; i < TAMANHO_DA_HABILIDADE; i++) {
        for (int j = 0; j <TAMANHO_DA_HABILIDADE; j++ ) {
            // Calcula a posição correspondente no tabuleiro principal.
            // O ajuste 'j - (TAMANHO_DA_HABILIDADE / 2)' centraliza a largura do cone 
            // em relação ao 'cone_origem_y'.
            int LINHA = cone_origem_x + i;
            int COLUNA = cone_origem_y + j - (TAMANHO_DA_HABILIDADE / 2);

            // Verifica se a célula da habilidade está ativa (valor 1)
            // E se a posição calculada no tabuleiro está dentro dos limites válidos (0 a 9)
            if (cone[i][j] == 1 &&
                LINHA >= 0 && LINHA < TABULEIRO_TAMANHO &&
                COLUNA >= 0 && COLUNA < TABULEIRO_TAMANHO) {

                    // Se a posição no tabuleiro NÃO for um navio (valor 3),
                    // então marca como área afetada pela habilidade (valor 5)
                    if (tabuleiro[LINHA][COLUNA] != Navio) {
                        tabuleiro[LINHA][COLUNA] = Area_Afetada_Habilidade;
                    }
                }
        }
    }

    // Sobrepondo a Habilidade: CRUZ
    // Itera sobre cada célula da matriz da habilidade (5x5)
    for (int i = 0; i < TAMANHO_DA_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_DA_HABILIDADE; j++) {
            // Calcula a posição no tabuleiro principal, centralizando a cruz.
            // '- (TAMANHO_DA_HABILIDADE / 2)' ajusta para que o centro da matriz da habilidade
            // (onde i e j seriam TAMANHO_DA_HABILIDADE / 2) coincida com o 'cruz_origem_x/y'.
            int LINHA = cruz_origem_x + i - (TAMANHO_DA_HABILIDADE / 2);
            int COLUNA = cruz_origem_y + j - (TAMANHO_DA_HABILIDADE / 2);

            // Verifica se a célula da habilidade está ativa (valor 1)
            // E se a posição calculada no tabuleiro está dentro dos limites válidos
            if (cruz[i][j] == 1 &&
                LINHA >= 0 && LINHA < TABULEIRO_TAMANHO &&
                COLUNA >= 0 && COLUNA < TABULEIRO_TAMANHO) {

                    // Se a posição no tabuleiro NÃO for um navio, marca como área de habilidade
                    if (tabuleiro[LINHA][COLUNA] != Navio) {
                        tabuleiro[COLUNA][COLUNA] = Area_Afetada_Habilidade;
                    }
                }
        }
    }

    // Sobrepondo a Habilidade: OCTAEDRO (Losango)
    // Itera sobre cada célula da matriz da habilidade (5x5)
    for (int i = 0; i < TAMANHO_DA_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_DA_HABILIDADE; j++) {
            //Calcula a posição no tabuleiro principal, centralizando o octaedro
            int LINHA = octaedro_origem_x + i - (TAMANHO_DA_HABILIDADE / 2);
            int COLUNA = octaedro_origem_y + j - (TAMANHO_DA_HABILIDADE / 2);

            // Verifica se a célula da habilidade está ativa (valor 1)
            // E se a posição calculada no tabuleiro está dentro dos limites válidos
            if (octaedro[i][j] == 1 &&
                LINHA >= 0 && LINHA < TABULEIRO_TAMANHO &&
                COLUNA >= 0 && COLUNA < TABULEIRO_TAMANHO) {

                    //Se a posição no tabuleiro NÃO for um navio, marca como área de habilidade
                    if (tabuleiro[LINHA][COLUNA] != Navio) {
                        tabuleiro[LINHA][COLUNA] = Area_Afetada_Habilidade;
                    }
                }
        }
    }

    // --- Exibição Final do Tabuleiro ---

    // Exibir o cabeçalho de letras das colunas
    printf("   "); // Espaço para alinhar com os números das linhas
    for (int j = 0; j < TABULEIRO_TAMANHO; j++) {
        printf("%c ", letras[j]); // Imprime a letra da coluna
    }
    printf("\n"); // Quebra de linha para a próxima linha de saída

    // Exibir o tabuleiro linha por linha
    for (int i = 0; i < TABULEIRO_TAMANHO; i++) {
        printf("%2d ", i ); // Imprime o número da linha (0 a 9) formatado para 2 dígitos
        for (int j = 0; j < TABULEIRO_TAMANHO; j++) {
            // Usa condicionais para imprimir caracteres diferentes com base no valor da célula
            if (tabuleiro[i][j] == Agua) {
                printf("0 "); // Representa Água (0)
            } else if (tabuleiro[i][j] == Navio) {
                printf("3 "); // Representa Navio (3)
            } else if (tabuleiro[i][j] == Area_Afetada_Habilidade) {
                printf("1 "); // Representa Área afetada pela habilidade (1)
            } else {
                // Caso haja valor inesperado (não deveria acontecer com esta lógica),
                // Imprime o próprio número para depuração.
                printf("%d ", tabuleiro[i][j]);                
            }
        }
        printf("\n"); // Quebra de linha após cada linha do tabuleiro
    }

    return 0;
}


