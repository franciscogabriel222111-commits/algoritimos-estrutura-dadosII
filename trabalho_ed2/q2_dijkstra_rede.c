/*
 * Questao 2 - Algoritmo de Dijkstra (Rede de Roteamento)
 * Estrutura de Dados II - Trabalho Final
 *
 * Rede de 10 roteadores (A..J) com custos de latencia (grafo nao
 * direcionado). Encontra a rota de menor latencia de A ate J,
 * exibindo a tabela de iteracoes (nos visitados, distancias
 * atualizadas e predecessores).
 */

#include <stdio.h>
#include <limits.h>

#define N 10
#define INF INT_MAX

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

int grafo[N][N]; /* preenchido em main a partir da lista de arestas */

typedef struct { char de, para; int peso; } Aresta;

Aresta arestas[] = {
    {'A','B',3}, {'A','C',5}, {'A','D',9},
    {'B','C',2}, {'B','E',4}, {'B','F',7},
    {'C','D',2}, {'C','F',6}, {'C','G',8},
    {'D','G',5}, {'D','H',4},
    {'E','F',1}, {'E','I',6},
    {'F','G',3}, {'F','I',5}, {'F','J',8},
    {'G','H',1}, {'G','J',6},
    {'H','J',9},
    {'I','J',2}
};
int numArestas = sizeof(arestas) / sizeof(Aresta);

int idx(char c) { return c - 'A'; }

int menorDistanciaNaoVisitado(int dist[N], int visitado[N]) {
    int min = INF, sel = -1;
    for (int i = 0; i < N; i++)
        if (!visitado[i] && dist[i] < min) { min = dist[i]; sel = i; }
    return sel;
}

void imprimeCaminho(int pred[N], int destino) {
    if (pred[destino] == -1) { printf("%c", nomes[destino]); return; }
    imprimeCaminho(pred, pred[destino]);
    printf(" -> %c", nomes[destino]);
}

int main(void) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grafo[i][j] = 0;

    for (int i = 0; i < numArestas; i++) {
        int u = idx(arestas[i].de), v = idx(arestas[i].para);
        grafo[u][v] = arestas[i].peso;
        grafo[v][u] = arestas[i].peso; /* nao-direcionado */
    }

    int dist[N], pred[N], visitado[N];
    int origem = idx('A'), destino = idx('J');
    for (int i = 0; i < N; i++) { dist[i] = INF; pred[i] = -1; visitado[i] = 0; }
    dist[origem] = 0;

    printf("=========================================================\n");
    printf(" Dijkstra - Rota de menor latencia do roteador A ao J\n");
    printf("=========================================================\n");
    printf("\n%-4s | %-30s | %-10s\n", "It.", "Distancias (A..J)", "Visitado");
    printf("---------------------------------------------------------------\n");

    for (int cont = 0; cont < N; cont++) {
        int u = menorDistanciaNaoVisitado(dist, visitado);
        if (u == -1) break;
        visitado[u] = 1;

        printf("\n>> Iteracao %d: no visitado = %c (distancia = %d)\n", cont + 1, nomes[u], dist[u]);
        for (int v = 0; v < N; v++) {
            if (grafo[u][v] != 0 && !visitado[v]) {
                int nova = dist[u] + grafo[u][v];
                if (nova < dist[v]) {
                    printf("   dist[%c] atualizada: %s -> %d (predecessor = %c)\n",
                           nomes[v], dist[v] == INF ? "inf" : "valor anterior", nova, nomes[u]);
                    dist[v] = nova;
                    pred[v] = u;
                }
            }
        }
        printf("   Estado: ");
        for (int i = 0; i < N; i++) {
            if (dist[i] == INF) printf("%c=inf ", nomes[i]);
            else printf("%c=%d(%c) ", nomes[i], dist[i], pred[i] == -1 ? '-' : nomes[pred[i]]);
        }
        printf("\n");
    }

    printf("\n=========================================================\n");
    printf(" RESULTADO FINAL\n");
    printf("=========================================================\n");
    printf("Latencia total minima de A ate J: %d\n", dist[destino]);
    printf("Rota: ");
    imprimeCaminho(pred, destino);
    printf("\n");

    return 0;
}
