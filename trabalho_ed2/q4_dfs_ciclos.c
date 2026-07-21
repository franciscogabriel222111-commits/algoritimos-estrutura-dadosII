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

#define N 10  /* quantidade de vertices do grafo: A ate J */

/* vetor que traduz indice (0..9) para o nome do vertice (A..J) */
char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

/*
 * Lista de adjacencia do grafo DIRECIONADO.
 * adj[i] guarda, como string, os vertices para os quais o vertice i
 * possui aresta de saida. Ex.: adj[0] = "BC" significa que A -> B e A -> C.
 */
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

/* converte a letra do vertice (ex: 'C') para o indice correspondente (2) */
int idx(char c) { return c - 'A'; }

/*
 * Estado de cada vertice durante a DFS:
 *   0 = branco  -> ainda nao foi visitado
 *   1 = cinza   -> esta sendo visitado agora (esta na pilha de recursao)
 *   2 = preto   -> ja foi totalmente processado (finalizado)
 * Essa e a base do algoritmo classico de deteccao de ciclo em grafo
 * direcionado: se durante a DFS encontramos uma aresta para um vertice
 * CINZA, significa que existe um caminho voltando para um ancestral
 * ainda ativo na recursao -> ou seja, um ciclo.
 */
int cor[N];

/* pilha usada apenas para IMPRIMIR visualmente a pilha de recursao atual */
int pilha[N], topo = -1;

/* flag que indica se algum ciclo foi encontrado durante a busca */
int cicloEncontrado = 0;

/* imprime o conteudo atual da pilha de recursao, do fundo ao topo */
void imprimePilha(void) {
    printf("      pilha de recursao atual: [ ");
    for (int i = 0; i <= topo; i++) printf("%c ", nomes[pilha[i]]);
    printf("]\n");
}

/*
 * DFS recursiva a partir do vertice u.
 * A cada chamada, o vertice atual e "empilhado" (entra na pilha de
 * recursao) e, ao final da funcao, e "desempilhado" (a recursao volta).
 */
void dfsVisita(int u) {
    cor[u] = 1;              /* marca u como cinza: comecou a ser visitado */
    pilha[++topo] = u;       /* empilha u para fins de visualizacao */
    printf("-> Empilha %c (visitando)\n", nomes[u]);
    imprimePilha();

    int qtd = strlen(adj[u]); /* quantidade de vizinhos (arestas de saida) de u */

    /* percorre cada vizinho v de u, na ordem em que aparece em adj[u] */
    for (int i = 0; i < qtd; i++) {
        int v = idx(adj[u][i]);

        if (cor[v] == 0) {
            /* v ainda nao foi visitado: e uma aresta de arvore, avanca a recursao */
            printf("   aresta %c->%c : vertice branco, avanca recursao\n", nomes[u], nomes[v]);
            dfsVisita(v);
        } else if (cor[v] == 1) {
            /*
             * v esta cinza, ou seja, ainda esta na pilha de recursao.
             * Isso significa que existe um caminho de v ate u (pois v
             * e ancestral de u na arvore de DFS) e agora u->v fecha um
             * ciclo. Esta e a condicao classica de deteccao de ciclo.
             */
            printf("   aresta %c->%c : ATENCAO! %c esta CINZA (ja na pilha) => ARESTA DE RETORNO => CICLO!\n",
                   nomes[u], nomes[v], nomes[v]);
            cicloEncontrado = 1;
        } else {
            /*
             * v esta preto (ja finalizado). A aresta u->v pode ser de
             * avanco (para um descendente ja processado) ou de
             * cruzamento (para outro ramo da arvore ja visitado).
             * Nenhum dos dois casos indica ciclo.
             */
            printf("   aresta %c->%c : vertice preto (ja finalizado), aresta de avanco/cruzamento, sem ciclo\n",
                   nomes[u], nomes[v]);
        }
    }

    cor[u] = 2; /* todos os vizinhos de u ja foram tratados: u esta finalizado (preto) */
    printf("<- Desempilha %c (finalizado)\n", nomes[u]);
    topo--;     /* remove u da pilha de recursao (visualizacao) */
    imprimePilha();
}

int main(void) {
    /* inicializa todos os vertices como brancos (nao visitados) */
    for (int i = 0; i < N; i++) cor[i] = 0;

    printf("=========================================================\n");
    printf(" DFS - deteccao de ciclos (grafo direcionado), inicio em A\n");
    printf("=========================================================\n\n");

    /* inicia a DFS a partir do vertice A (indice 0) */
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