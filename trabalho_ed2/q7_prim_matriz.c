/*
 * Questao 7 - Algoritmo de Prim (Arvore Geradora Minima)
 * Estrutura de Dados II - Trabalho Final
 *
 * Rede de 10 predios comerciais interligados por fibra optica.
 * Aplica o Algoritmo de Prim com raiz A, mostrando passo a passo
 * a selecao das arestas e o custo total acumulado.
 */

#include <stdio.h>
#include <limits.h>

#define N 10
#define INF INT_MAX

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

int custo[N][N] = {
    /*    A   B   C   D   E   F   G   H   I   J */
    /*A*/{0,  5,  4,  0,  0,  0,  0,  0,  0,  0},
    /*B*/{5,  0,  2,  3,  8,  0,  0,  0,  0,  0},
    /*C*/{4,  2,  0,  0,  6,  0,  0,  0,  0,  0},
    /*D*/{0,  3,  0,  0,  1,  7,  4,  0,  0,  0},
    /*E*/{0,  8,  6,  1,  0,  0,  5,  0,  0,  0},
    /*F*/{0,  0,  0,  7,  0,  0,  2,  3,  0,  0},
    /*G*/{0,  0,  0,  4,  5,  2,  0,  6,  1,  0},
    /*H*/{0,  0,  0,  0,  0,  3,  6,  0,  2,  5},
    /*I*/{0,  0,  0,  0,  0,  0,  1,  2,  0,  4},
    /*J*/{0,  0,  0,  0,  0,  0,  0,  5,  4,  0}
};

int idx(char c) { return c - 'A'; }

int main(void) {
    int naAGM[N] = {0};
    int chave[N], pred[N];
    for (int i = 0; i < N; i++) { chave[i] = INF; pred[i] = -1; }

    int raiz = idx('A');
    chave[raiz] = 0;

    printf("=========================================================\n");
    printf(" Algoritmo de Prim - AGM, raiz = A\n");
    printf("=========================================================\n\n");

    int custoTotal = 0;
    for (int cont = 0; cont < N; cont++) {
        /* escolhe vertice fora da AGM com menor chave */
        int min = INF, u = -1;
        for (int v = 0; v < N; v++)
            if (!naAGM[v] && chave[v] < min) { min = chave[v]; u = v; }

        naAGM[u] = 1;
        printf("--- Iteracao %d: adiciona %c a AGM ", cont + 1, nomes[u]);
        if (pred[u] != -1) {
            printf("(aresta escolhida: %c-%c, peso %d)\n", nomes[pred[u]], nomes[u], chave[u]);
            custoTotal += chave[u];
        } else {
            printf("(raiz inicial)\n");
        }

        for (int v = 0; v < N; v++) {
            if (custo[u][v] != 0 && !naAGM[v] && custo[u][v] < chave[v]) {
                printf("   atualiza chave[%c]: %d -> %d (pred=%c)\n",
                       nomes[v], chave[v] == INF ? -1 : chave[v], custo[u][v], nomes[u]);
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

    printf("\nCusto total acumulado da rede: %d\n", custoTotal);

    return 0;
}
