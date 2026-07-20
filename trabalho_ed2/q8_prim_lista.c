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

Aresta arestas[] = {
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
int numArestas = sizeof(arestas) / sizeof(Aresta);

int custo[N][N];
int idx(char c) { return c - 'A'; }

int main(void) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            custo[i][j] = 0;
    for (int i = 0; i < numArestas; i++) {
        int u = idx(arestas[i].de), v = idx(arestas[i].para);
        custo[u][v] = arestas[i].peso;
        custo[v][u] = arestas[i].peso;
    }

    int naAGM[N] = {0};
    int chave[N], pred[N];
    for (int i = 0; i < N; i++) { chave[i] = INF; pred[i] = -1; }

    int raiz = idx('E');
    chave[raiz] = 0;

    printf("=========================================================\n");
    printf(" Algoritmo de Prim - AGM, raiz = E\n");
    printf("=========================================================\n\n");

    int custoTotal = 0;
    for (int cont = 0; cont < N; cont++) {
        int min = INF, u = -1;
        for (int v = 0; v < N; v++)
            if (!naAGM[v] && chave[v] < min) { min = chave[v]; u = v; }

        naAGM[u] = 1;

        printf("--- Iteracao %d ---\n", cont + 1);
        printf("   Corte: AGM = { ");
        for (int i = 0; i < N; i++) if (naAGM[i]) printf("%c ", nomes[i]);
        printf("}  x  Fora = { ");
        for (int i = 0; i < N; i++) if (!naAGM[i]) printf("%c ", nomes[i]);
        printf("}\n");

        if (pred[u] != -1) {
            printf("   Aresta de menor peso cruzando o corte: %c-%c (peso %d) -> adiciona %c\n",
                   nomes[pred[u]], nomes[u], chave[u], nomes[u]);
            custoTotal += chave[u];
        } else {
            printf("   Vertice raiz adicionado: %c\n", nomes[u]);
        }

        for (int v = 0; v < N; v++) {
            if (custo[u][v] != 0 && !naAGM[v] && custo[u][v] < chave[v]) {
                chave[v] = custo[u][v];
                pred[v] = u;
            }
        }
        printf("\n");
    }

    printf("=========================================================\n");
    printf(" ARESTAS DA ARVORE GERADORA MINIMA\n");
    printf("=========================================================\n");
    for (int i = 0; i < N; i++)
        if (pred[i] != -1)
            printf("   %c - %c   (peso %d)\n", nomes[pred[i]], nomes[i], chave[i]);

    printf("\nCusto total acumulado: %d\n", custoTotal);

    return 0;
}
