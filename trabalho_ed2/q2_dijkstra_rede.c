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

// retorna o indice do no nao visitado com menor distancia
int menorDistanciaNaoVisitado(int dist[N], int visitado[N]) {
    int min = INF, sel = -1;
    for (int i = 0; i < N; i++)// percorre todos os nos do grafo
        if (!visitado[i] && dist[i] < min) { min = dist[i]; sel = i; }// se o no nao foi visitado e sua distancia for menor que a menor distancia atual, atualiza a menor distancia e o indice do no selecionado
    return sel;// retorna o indice do no nao visitado com menor distancia (ou -1 se todos foram visitados)
}

void imprimeCaminho(int pred[N], int destino) {// imprime o caminho minimo de A ate J usando o vetor de predecessores
    if (pred[destino] == -1) { printf("%c", nomes[destino]); return; }// se o no destino nao tem predecessor, imprime o no destino e retorna
    imprimeCaminho(pred, pred[destino]);
    printf(" -> %c", nomes[destino]);
}

// inicializa o grafo com 0 (sem arestas) e preenche com as arestas da lista
int main(void) {
    for (int i = 0; i < N; i++)// percorre todos os nos do grafo
        for (int j = 0; j < N; j++)
            grafo[i][j] = 0;// inicializa o grafo com 0 (sem arestas)

    for (int i = 0; i < numArestas; i++) {// percorre todas as arestas da lista
        int u = idx(arestas[i].de), v = idx(arestas[i].para);// obtem os indices dos nos da aresta
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

    for (int cont = 0; cont < N; cont++) {// percorre todos os nos do grafo
        int u = menorDistanciaNaoVisitado(dist, visitado);// obtem o indice do no nao visitado com menor distancia
        if (u == -1) break;// se todos os nos foram visitados, sai do loop
        visitado[u] = 1;

        printf("\n>> Iteracao %d: no visitado = %c (distancia = %d)\n", cont + 1, nomes[u], dist[u]);// imprime o no visitado e sua distancia
        for (int v = 0; v < N; v++) {// percorre todos os nos do grafo
            if (grafo[u][v] != 0 && !visitado[v]) {// se existe uma aresta entre u e v e v nao foi visitado
                int nova = dist[u] + grafo[u][v];
                if (nova < dist[v]) {// se a nova distancia for menor que a distancia atual, atualiza a distancia e o predecessor
                    printf("   dist[%c] atualizada: %s -> %d (predecessor = %c)\n",
                           nomes[v], dist[v] == INF ? "inf" : "valor anterior", nova, nomes[u]);
                    dist[v] = nova;
                    pred[v] = u;
                }
            }
        }
        printf("   Estado: ");
        for (int i = 0; i < N; i++) {// percorre todos os nos do grafo
            if (dist[i] == INF) printf("%c=inf ", nomes[i]);// se a distancia for infinita, imprime "inf"
            else printf("%c=%d(%c) ", nomes[i], dist[i], pred[i] == -1 ? '-' : nomes[pred[i]]);// imprime a distancia e o predecessor do no
        }
        printf("\n");
    }

    printf("\n=========================================================\n");
    printf(" RESULTADO FINAL\n");
    printf("=========================================================\n");
    printf("Latencia total minima de A ate J: %d\n", dist[destino]);
    printf("Rota: ");
    imprimeCaminho(pred, destino);// imprime o caminho minimo de A ate J usando o vetor de predecessores
    printf("\n");

    return 0;
}