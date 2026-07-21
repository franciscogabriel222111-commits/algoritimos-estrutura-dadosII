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

#define N 10       /* quantidade de vertices: A ate J */
#define VAZIO -1   /* usado para indicar "sem predecessor" (vertice raiz) */

/* traduz indice (0..9) para o nome do vertice (A..J) */
char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

/*
 * Lista de adjacencia do grafo NAO-DIRECIONADO.
 * adj[i] guarda, como string, todos os vizinhos do vertice i.
 * Como o grafo nao e direcionado, cada aresta aparece duas vezes
 * (ex: "B" esta em adj[A] e "A" esta em adj[B]).
 */
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

/* converte a letra do vertice (ex: 'C') para o indice correspondente (2) */
int idx(char c) { return c - 'A'; }

int main(void) {
    /*
     * fila[] implementa a fila FIFO da BFS.
     * ini = indice do proximo elemento a ser retirado (inicio da fila)
     * fimf = indice da proxima posicao livre (fim da fila)
     * Enquanto ini < fimf, ainda ha elementos pendentes na fila.
     */
    int fila[N], ini = 0, fimf = 0;

    int visitado[N] = {0};  /* marca quem ja entrou na fila alguma vez */
    int dist[N], pred[N];   /* dist[v] = numero de saltos ate v; pred[v] = quem descobriu v */
    int ordemVisita[N], nOrdem = 0; /* guarda a ordem em que os vertices sao processados */

    /* inicializa distancias como "nao alcancado" e predecessores como vazio */
    for (int i = 0; i < N; i++) { dist[i] = -1; pred[i] = VAZIO; }

    /* vertice de origem da busca: E */
    int origem = idx('E');
    visitado[origem] = 1;
    dist[origem] = 0;        /* distancia da origem para ela mesma e 0 */
    fila[fimf++] = origem;   /* coloca a origem na fila para comecar */

    printf("=========================================================\n");
    printf(" BFS - grafo nao-direcionado, inicio em E\n");
    printf("=========================================================\n\n");
    printf("Fila inicial: [ E ]\n\n");

    int passo = 0;
    /* processa a fila ate esvaziar: essa e a essencia da BFS */
    while (ini < fimf) {
        int u = fila[ini++];         /* retira o vertice da frente da fila */
        ordemVisita[nOrdem++] = u;   /* registra a ordem de processamento */
        passo++;
        printf("--- Passo %d: retira da fila %c ---\n", passo, nomes[u]);

        int qtd = strlen(adj[u]);    /* quantidade de vizinhos de u */

        /* examina cada vizinho v de u */
        for (int i = 0; i < qtd; i++) {
            int v = idx(adj[u][i]);
            if (!visitado[v]) {
                /*
                 * v ainda nao foi descoberto: marca como visitado,
                 * define a distancia (um salto a mais que u) e o
                 * predecessor, e enfileira para ser processado depois.
                 * Como a BFS avanca "camada por camada", a primeira
                 * vez que um vertice e alcancado ja e o caminho mais
                 * curto (em numero de arestas) ate ele.
                 */
                visitado[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                fila[fimf++] = v;
                printf("   descobre %c (via %c): nivel %d -> enfileira\n", nomes[v], nomes[u], dist[v]);
            }
        }

        /* mostra o estado atual da fila apos processar u */
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
    /*
     * Como a BFS visita o grafo em ondas (nivel 0, depois nivel 1,
     * depois nivel 2...), podemos agrupar os vertices por dist[i]
     * para obter as camadas de distancia a partir da origem.
     */
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