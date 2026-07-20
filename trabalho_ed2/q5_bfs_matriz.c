/*
 * Questao 5 - Busca em Largura (BFS - Menor Numero de Arestas)
 * Estrutura de Dados II - Trabalho Final
 *
 * Rede social academica com 10 alunos (matriz de adjacencia).
 * BFS a partir de A, mostrando a evolucao da fila (FIFO), a
 * distancia (numero de saltos) e o predecessor de cada no, alem
 * da arvore de busca gerada (impressa em modo texto).
 */

#include <stdio.h>

#define N 10
#define VAZIO -1

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

int grafo[N][N] = {
    /*    A  B  C  D  E  F  G  H  I  J */
    /*A*/{0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    /*B*/{1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    /*C*/{1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    /*D*/{0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    /*E*/{0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
    /*F*/{0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    /*G*/{0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    /*H*/{0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
    /*I*/{0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
    /*J*/{0, 0, 0, 0, 0, 1, 1, 0, 1, 0}
};

int idx(char c) { return c - 'A'; }

int main(void) {
    int fila[N], ini = 0, fimf = 0;
    int visitado[N] = {0};
    int dist[N], pred[N];
    for (int i = 0; i < N; i++) { dist[i] = -1; pred[i] = VAZIO; }

    int origem = idx('A');
    visitado[origem] = 1;
    dist[origem] = 0;
    fila[fimf++] = origem;

    printf("=========================================================\n");
    printf(" BFS - rede academica, inicio em A\n");
    printf("=========================================================\n\n");

    printf("Fila inicial: [ A ]\n\n");

    int passo = 0;
    while (ini < fimf) {
        int u = fila[ini++];
        passo++;
        printf("--- Passo %d: retira da fila o vertice %c ---\n", passo, nomes[u]);

        for (int v = 0; v < N; v++) {
            if (grafo[u][v] && !visitado[v]) {
                visitado[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                fila[fimf++] = v;
                printf("   descobre %c (via %c): d[%c]=%d, pred[%c]=%c -> enfileira %c\n",
                       nomes[v], nomes[u], nomes[v], dist[v], nomes[v], nomes[u], nomes[v]);
            }
        }

        printf("   Fila atual: [ ");
        for (int i = ini; i < fimf; i++) printf("%c ", nomes[fila[i]]);
        printf("]\n\n");
    }

    printf("=========================================================\n");
    printf(" TABELA FINAL: distancias (saltos) e predecessores\n");
    printf("=========================================================\n");
    printf("%-8s%-8s%-10s\n", "Vertice", "d[v]", "Pred");
    for (int i = 0; i < N; i++)
        printf("%-8c%-8d%-10c\n", nomes[i], dist[i], pred[i] == VAZIO ? '-' : nomes[pred[i]]);

    printf("\n=========================================================\n");
    printf(" ARVORE DE BUSCA (BFS Tree) - representacao textual\n");
    printf("=========================================================\n");
    for (int niv = 0; niv <= 4; niv++) {
        int algum = 0;
        printf("Nivel %d: ", niv);
        for (int i = 0; i < N; i++) {
            if (dist[i] == niv) { printf("%c ", nomes[i]); algum = 1; }
        }
        if (!algum) continue;
        printf("\n");
    }
    printf("\nLigacoes da arvore (pai -> filho):\n");
    for (int i = 0; i < N; i++)
        if (pred[i] != VAZIO)
            printf("   %c -> %c\n", nomes[pred[i]], nomes[i]);

    return 0;
}
