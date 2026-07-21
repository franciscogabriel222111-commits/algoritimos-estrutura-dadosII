/*
 * Questao 8 - Algoritmo de Prim (Expansao de Subrede)
 * Estrutura de Dados II - Trabalho Final
 *
 * Grafo com 10 vertices dado por lista de arestas ponderadas.
 * Executa o Algoritmo de Prim a partir de E, descrevendo a cada
 * iteracao o corte considerado (conjunto na AGM x fora da AGM) e a
 * aresta de menor peso que cruza o corte.
 */

#include <stdio.h>
#include <limits.h>

#define N 10
#define INF INT_MAX

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

typedef struct { char de, para; int peso; } Aresta;

Aresta arestas[] = {// Grafo ponderado
    {'A','B',4}, {'A','H',8},
    {'B','C',8}, {'B','H',11},
    {'C','D',7}, {'C','F',4}, {'C','I',2},
    {'D','E',9}, {'D','F',14},
    {'E','F',10},
    {'F','G',2},
    {'G','H',1}, {'G','I',6},
    {'H','I',7}, {'H','J',5},
    {'I','J',3}
};
int numArestas = sizeof(arestas) / sizeof(Aresta);// 16 arestas

int custo[N][N];// matriz de adjacencia para armazenar os pesos das arestas
int idx(char c) { return c - 'A'; }// funcao para converter o caractere do vertice em indice da matriz

// funcao principal
int main(void) {
    for (int i = 0; i < N; i++)// inicializa a matriz de adjacencia com 0 (sem aresta)
        for (int j = 0; j < N; j++)// percorre todos os vertices
            custo[i][j] = 0;
    for (int i = 0; i < numArestas; i++) {// percorre todas as arestas para preencher a matriz de adjacencia
        int u = idx(arestas[i].de), v = idx(arestas[i].para);// converte os caracteres dos vertices em indices da matriz
        custo[u][v] = arestas[i].peso;
        custo[v][u] = arestas[i].peso;
    }

    int naAGM[N] = {0};
    int chave[N], pred[N];
    for (int i = 0; i < N; i++) { chave[i] = INF; pred[i] = -1; }// inicializa chaves como infinito e predecessores como -1

    int raiz = idx('E');
    chave[raiz] = 0;

    printf("=========================================================\n");
    printf(" Algoritmo de Prim - AGM, raiz = E\n");
    printf("=========================================================\n\n");

    int custoTotal = 0;
    for (int cont = 0; cont < N; cont++) {// percorre todos os vertices para construir a AGM
        int min = INF, u = -1;
        for (int v = 0; v < N; v++)// percorre todos os vertices para encontrar o vertice com menor chave fora da AGM
            if (!naAGM[v] && chave[v] < min) { min = chave[v]; u = v; }// atualiza o vertice com menor chave

        naAGM[u] = 1;

        printf("--- Iteracao %d ---\n", cont + 1);
        printf("   Corte: AGM = { ");
        for (int i = 0; i < N; i++) if (naAGM[i]) printf("%c ", nomes[i]);// imprime os vertices na AGM
        printf("}  x  Fora = { ");
        for (int i = 0; i < N; i++) if (!naAGM[i]) printf("%c ", nomes[i]);// imprime os vertices fora da AGM
        printf("}\n");

        if (pred[u] != -1) {// se nao for a raiz, mostra a aresta escolhida e o peso
            printf("   Aresta de menor peso cruzando o corte: %c-%c (peso %d) -> adiciona %c\n",
                   nomes[pred[u]], nomes[u], chave[u], nomes[u]);
            custoTotal += chave[u];
        } else {// se for a raiz, apenas indica que e a raiz inicial
            printf("   Vertice raiz adicionado: %c\n", nomes[u]);
        }

        for (int v = 0; v < N; v++) {// percorre todos os vertices para atualizar as chaves dos vizinhos de u
            if (custo[u][v] != 0 && !naAGM[v] && custo[u][v] < chave[v]) {// se v e vizinho de u, nao esta na AGM e o peso da aresta e menor que a chave atual de v
                chave[v] = custo[u][v];
                pred[v] = u;
            }
        }
        printf("\n");
    }

    printf("=========================================================\n");
    printf(" ARESTAS DA ARVORE GERADORA MINIMA\n");
    printf("=========================================================\n");
    for (int i = 0; i < N; i++)// percorre todos os vertices para imprimir as arestas da AGM
        if (pred[i] != -1)// se o vertice nao for a raiz, imprime a aresta e o peso
            printf("   %c - %c   (peso %d)\n", nomes[pred[i]], nomes[i], chave[i]);

    printf("\nCusto total acumulado: %d\n", custoTotal);

    return 0;
}
