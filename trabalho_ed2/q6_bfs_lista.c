/*
 * Questao 6 - Busca em Largura (BFS - Conectividade e Niveis)
 * Estrutura de Dados II - Trabalho Final
 *
 * Grafo nao-direcionado com 10 vertices (lista de adjacencia).
 * BFS a partir de E: mostra o estado da fila a cada iteracao e a
 * particao do grafo em camadas/niveis de distancia, alem da ordem
 * completa de visitacao.
 */

#include <stdio.h>
#include <string.h>

#define N 10
#define VAZIO -1

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

char *adj[N] = {
    "BE",    /* A */
    "ACF",   /* B */
    "BDG",   /* C */
    "CH",    /* D */
    "AFI",   /* E */
    "BEGJ",  /* F */
    "CFHJ",  /* G */
    "DG",    /* H */
    "EJ",    /* I */
    "FGI"    /* J */
};

int idx(char c) { return c - 'A'; }

int main(void) {
    int fila[N], ini = 0, fimf = 0;
    int visitado[N] = {0};
    int dist[N], pred[N];
    int ordemVisita[N], nOrdem = 0;
    for (int i = 0; i < N; i++) { dist[i] = -1; pred[i] = VAZIO; }

    int origem = idx('E');
    visitado[origem] = 1;
    dist[origem] = 0;
    fila[fimf++] = origem;

    printf("=========================================================\n");
    printf(" BFS - grafo nao-direcionado, inicio em E\n");
    printf("=========================================================\n\n");
    printf("Fila inicial: [ E ]\n\n");

    int passo = 0;
    while (ini < fimf) {
        int u = fila[ini++];
        ordemVisita[nOrdem++] = u;
        passo++;
        printf("--- Passo %d: retira da fila %c ---\n", passo, nomes[u]);

        int qtd = strlen(adj[u]);
        for (int i = 0; i < qtd; i++) {
            int v = idx(adj[u][i]);
            if (!visitado[v]) {
                visitado[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                fila[fimf++] = v;
                printf("   descobre %c (via %c): nivel %d -> enfileira\n", nomes[v], nomes[u], dist[v]);
            }
        }
        printf("   Fila atual: [ ");
        for (int i = ini; i < fimf; i++) printf("%c ", nomes[fila[i]]);
        printf("]\n\n");
    }

    printf("=========================================================\n");
    printf(" ORDEM COMPLETA DE VISITACAO\n");
    printf("=========================================================\n");
    for (int i = 0; i < nOrdem; i++) printf("%c%s", nomes[ordemVisita[i]], i < nOrdem - 1 ? " -> " : "\n");

    printf("\n=========================================================\n");
    printf(" PARTICAO EM CAMADAS / NIVEIS DE DISTANCIA\n");
    printf("=========================================================\n");
    for (int niv = 0; niv <= 4; niv++) {
        printf("Nivel %d: { ", niv);
        for (int i = 0; i < N; i++)
            if (dist[i] == niv) printf("%c ", nomes[i]);
        printf("}\n");
    }

    printf("\nPredecessores:\n");
    for (int i = 0; i < N; i++)
        printf("   pred[%c] = %c   (d=%d)\n", nomes[i], pred[i] == VAZIO ? '-' : nomes[pred[i]], dist[i]);

    return 0;
}
