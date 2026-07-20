/*
 * Questao 9 - Algoritmo de Kruskal (Florestas e Conjuntos Disjuntos)
 * Estrutura de Dados II - Trabalho Final
 *
 * Mesmo grafo da Questao 7 (rede de 10 predios comerciais).
 * Executa o Algoritmo de Kruskal: ordena as arestas por peso
 * crescente e usa Union-Find para decidir, a cada rodada, se a
 * aresta e incluida (nao forma ciclo) ou rejeitada (forma ciclo).
 */

#include <stdio.h>

#define N 10
#define M 17

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

typedef struct { char de, para; int peso; } Aresta;

/* arestas extraidas da matriz de custos da Questao 7 (uma vez cada) */
Aresta arestas[M] = {
    {'A','B',5}, {'A','C',4},
    {'B','C',2}, {'B','D',3}, {'B','E',8},
    {'C','E',6},
    {'D','E',1}, {'D','F',7}, {'D','G',4},
    {'E','G',5},
    {'F','G',2}, {'F','H',3},
    {'G','H',6}, {'G','I',1},
    {'H','I',2}, {'H','J',5},
    {'I','J',4}
};

int idx(char c) { return c - 'A'; }

int pai[N];

int encontrar(int x) {
    while (pai[x] != x) x = pai[x];
    return x;
}

int unir(int x, int y) {
    int rx = encontrar(x), ry = encontrar(y);
    if (rx == ry) return 0; /* mesmo conjunto -> formaria ciclo */
    pai[rx] = ry;
    return 1;
}

void ordenar(Aresta v[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (v[j].peso > v[j + 1].peso) {
                Aresta tmp = v[j]; v[j] = v[j + 1]; v[j + 1] = tmp;
            }
}

int main(void) {
    for (int i = 0; i < N; i++) pai[i] = i;

    ordenar(arestas, M);

    printf("=========================================================\n");
    printf(" Algoritmo de Kruskal - AGM (mesmo grafo da Questao 7)\n");
    printf("=========================================================\n\n");

    printf("Arestas ordenadas crescentemente por peso:\n   ");
    for (int i = 0; i < M; i++)
        printf("%c-%c(%d) ", arestas[i].de, arestas[i].para, arestas[i].peso);
    printf("\n\n");

    int custoTotal = 0, arestasAGM = 0;
    for (int i = 0; i < M; i++) {
        int u = idx(arestas[i].de), v = idx(arestas[i].para);
        printf("Rodada %2d: analisa aresta %c-%c (peso %d) ... ", i + 1, arestas[i].de, arestas[i].para, arestas[i].peso);

        if (unir(u, v)) {
            printf("INCLUIDA (conjuntos de %c e %c eram diferentes -> uniao realizada)\n",
                   arestas[i].de, arestas[i].para);
            custoTotal += arestas[i].peso;
            arestasAGM++;
        } else {
            printf("REJEITADA (%c e %c ja pertencem ao mesmo conjunto -> formaria ciclo)\n",
                   arestas[i].de, arestas[i].para);
        }

        if (arestasAGM == N - 1) {
            printf("\n(AGM completa: %d arestas selecionadas para %d vertices)\n", arestasAGM, N);
            break;
        }
    }

    printf("\n=========================================================\n");
    printf(" GRAFO FINAL (AGM) E CUSTO TOTAL\n");
    printf("=========================================================\n");
    for (int i = 0; i < N; i++) pai[i] = i; /* apenas para reexibir nao usado */

    /* reconstroi lista de arestas incluidas */
    for (int i = 0; i < N; i++) pai[i] = i;
    printf("Arestas selecionadas:\n");
    int c2 = 0, custo2 = 0;
    for (int i = 0; i < M && c2 < N - 1; i++) {
        int u = idx(arestas[i].de), v = idx(arestas[i].para);
        if (unir(u, v)) {
            printf("   %c - %c   (peso %d)\n", arestas[i].de, arestas[i].para, arestas[i].peso);
            custo2 += arestas[i].peso;
            c2++;
        }
    }
    printf("\nCusto total da AGM: %d\n", custo2);

    return 0;
}
