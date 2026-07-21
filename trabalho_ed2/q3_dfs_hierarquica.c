/*
 * Questao 3 - Busca em Profundidade (DFS - Visita Hierarquica)
 * Estrutura de Dados II - Trabalho Final
 *
 * Grafo nao-direcionado com 10 vertices. DFS a partir de A, com
 * desempate em ordem alfabetica. Exibe tempos de descoberta d[v] e
 * finalizacao f[v], alem da classificacao das arestas (arvore/retorno).
 */

#include <stdio.h>
#include <string.h>

#define N 10
#define MAXADJ 5

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

/* listas de adjacencia (ja em ordem alfabetica, conforme enunciado) */
char *adj[N] = {
    "BCD",   /* A */
    "AEF",   /* B */
    "AG",    /* C */
    "AH",    /* D */
    "BI",    /* E */
    "BIJ",   /* F */
    "CJ",    /* G */
    "DJ",    /* H */
    "EF",    /* I */
    "FGH"    /* J */
};

int idx(char c) { return c - 'A'; }

int cor[N];      /* 0=branco 1=cinza 2=preto */
int d[N], f[N];   /* tempos de descoberta e finalizacao */
int pai[N];
int tempo = 0;

void dfsVisita(int u) { /* u = indice do vertice a ser visitado */
    tempo++;
    d[u] = tempo;
    cor[u] = 1; /* cinza: em processamento (na pilha de recursao) */
    printf("Descoberta de %c: d[%c] = %d (pilha de recursao ativa)\n", nomes[u], nomes[u], tempo);

    int qtd = strlen(adj[u]);
    for (int i = 0; i < qtd; i++) {// percorre todos os vizinhos do vertice u
        int v = idx(adj[u][i]);
        if (cor[v] == 0) {// se o vizinho v ainda nao foi visitado (cor==0)
            printf("   aresta (%c, %c): ARESTA DE ARVORE -> visita %c\n", nomes[u], nomes[v], nomes[v]);
            pai[v] = u;
            dfsVisita(v);
        } else if (v != pai[u] && cor[v] == 1) {
            /* vizinho ja visitado, ainda na pilha (cinza) e nao e o pai direto */
            printf("   aresta (%c, %c): ARESTA DE RETORNO (back edge) -> %c ja esta na pilha (cinza)\n",
                   nomes[u], nomes[v], nomes[v]);
        } else if (v == pai[u]) {// vizinho ja visitado, ainda na pilha (cinza) e e o pai direto
            printf("   aresta (%c, %c): aresta de retorno trivial ao pai, ja contabilizada como arvore\n",
                   nomes[u], nomes[v]);
        }
        /* v preto (cor==2) nao ocorre em grafo nao-direcionado simples com DFS de raiz unica */
    }

    cor[u] = 2; /* preto: finalizado */
    tempo++;
    f[u] = tempo;
    printf("Finalizacao de %c: f[%c] = %d\n", nomes[u], nomes[u], tempo);// vertice u finalizado, sai da pilha de recursao
}

int main(void) {// inicializa as estruturas e chama a DFS a partir do vertice A
    for (int i = 0; i < N; i++) { cor[i] = 0; d[i] = f[i] = 0; pai[i] = -1; }// inicializa cor, d, f e pai para todos os vertices

    printf("=========================================================\n");
    printf(" DFS - grafo nao-direcionado, inicio em A (ordem alfabetica)\n");
    printf("=========================================================\n\n");

    dfsVisita(idx('A'));

    printf("\n=========================================================\n");
    printf(" TABELA FINAL: tempos de descoberta e finalizacao\n");
    printf("=========================================================\n");
    printf("%-8s%-8s%-8s%-10s\n", "Vertice", "d[v]", "f[v]", "Pai");
    for (int i = 0; i < N; i++) {// percorre todos os vertices do grafo
        printf("%-8c%-8d%-8d%-10c\n", nomes[i], d[i], f[i], pai[i] == -1 ? '-' : nomes[pai[i]]);// imprime o vertice, tempo de descoberta, tempo de finalizacao e pai do vertice i
    }

    return 0;
}
