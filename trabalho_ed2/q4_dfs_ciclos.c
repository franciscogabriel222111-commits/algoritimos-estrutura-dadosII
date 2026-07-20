/*
 * Questao 4 - Busca em Profundidade (DFS - Deteccao de Ciclos)
 * Estrutura de Dados II - Trabalho Final
 *
 * Grafo direcionado representando dependencias de modulos.
 * Executa DFS a partir de A mostrando a pilha de recursao e
 * detecta ciclos (aresta de retorno para um vertice cinza/ativo
 * na pilha).
 */

#include <stdio.h>
#include <string.h>

#define N 10

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

/* listas de adjacencia (ordem alfabetica) conforme as conexoes do enunciado */
char *adj[N] = {
    "BC",   /* A -> B, C */
    "DE",   /* B -> D, E */
    "F",    /* C -> F */
    "G",    /* D -> G */
    "FH",   /* E -> F, H */
    "I",    /* F -> I */
    "J",    /* G -> J */
    "I",    /* H -> I */
    "B",    /* I -> B  (fecha ciclo) */
    "H"     /* J -> H */
};

int idx(char c) { return c - 'A'; }

int cor[N]; /* 0=branco 1=cinza(na pilha) 2=preto(finalizado) */
int pilha[N], topo = -1;
int cicloEncontrado = 0;

void imprimePilha(void) {
    printf("      pilha de recursao atual: [ ");
    for (int i = 0; i <= topo; i++) printf("%c ", nomes[pilha[i]]);
    printf("]\n");
}

void dfsVisita(int u) {
    cor[u] = 1;
    pilha[++topo] = u;
    printf("-> Empilha %c (visitando)\n", nomes[u]);
    imprimePilha();

    int qtd = strlen(adj[u]);
    for (int i = 0; i < qtd; i++) {
        int v = idx(adj[u][i]);
        if (cor[v] == 0) {
            printf("   aresta %c->%c : vertice branco, avanca recursao\n", nomes[u], nomes[v]);
            dfsVisita(v);
        } else if (cor[v] == 1) {
            printf("   aresta %c->%c : ATENCAO! %c esta CINZA (ja na pilha) => ARESTA DE RETORNO => CICLO!\n",
                   nomes[u], nomes[v], nomes[v]);
            cicloEncontrado = 1;
        } else {
            printf("   aresta %c->%c : vertice preto (ja finalizado), aresta de avanco/cruzamento, sem ciclo\n",
                   nomes[u], nomes[v]);
        }
    }

    cor[u] = 2;
    printf("<- Desempilha %c (finalizado)\n", nomes[u]);
    topo--;
    imprimePilha();
}

int main(void) {
    for (int i = 0; i < N; i++) cor[i] = 0;

    printf("=========================================================\n");
    printf(" DFS - deteccao de ciclos (grafo direcionado), inicio em A\n");
    printf("=========================================================\n\n");

    dfsVisita(idx('A'));

    printf("\n=========================================================\n");
    printf(" RESULTADO\n");
    printf("=========================================================\n");
    if (cicloEncontrado) {
        printf("O grafo POSSUI ciclo.\n");
        printf("Aresta que fecha o ciclo: I -> B\n");
        printf("(quando I e processado, B ainda esta na pilha de recursao,\n");
        printf(" pois o caminho A->B->E->H->I ainda nao finalizou B)\n");
    } else {
        printf("O grafo NAO possui ciclos.\n");
    }

    return 0;
}
