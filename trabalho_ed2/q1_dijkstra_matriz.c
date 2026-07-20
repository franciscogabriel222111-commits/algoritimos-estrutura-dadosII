/*
 * Questao 1 - Algoritmo de Dijkstra (Caminho Minimo)
 * Estrutura de Dados II - Trabalho Final
 *
 * Grafo direcionado e ponderado com 10 vertices (A..J), representado
 * por matriz de adjacencia. Calcula o caminho minimo de A ate J,
 * exibindo passo a passo o vetor de distancias e de predecessores
 * a cada iteracao (extracao do vertice de menor distancia).
 */

#include <stdio.h>
#include <limits.h>

#define N 10
#define INF INT_MAX

/* 0=A 1=B 2=C 3=D 4=E 5=F 6=G 7=H 8=I 9=J */
char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

/* matriz de adjacencia (0 = sem aresta) conforme enunciado */
int grafo[N][N] = {
    /*      A  B  C  D  E  F  G  H  I  J */
    /*A*/ { 0, 4, 2, 0, 0, 0, 0, 0, 0, 0 },
    /*B*/ { 0, 0, 1, 5, 0, 0, 0, 0, 0, 0 },
    /*C*/ { 0, 0, 0, 8,10, 0, 0, 0, 0, 0 },
    /*D*/ { 0, 0, 0, 0, 2, 6, 0, 0, 0, 0 },
    /*E*/ { 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
    /*F*/ { 0, 0, 0, 0, 0, 0, 0, 5, 1, 0 },
    /*G*/ { 0, 0, 0, 0, 0, 0, 0, 0, 4, 0 },
    /*H*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
    /*I*/ { 0, 0, 0, 0, 0, 0, 0, 1, 0, 7 },
    /*J*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void imprimeEstado(int dist[N], int pred[N], int visitado[N], int iteracao) {
    printf("\n--- Iteracao %d ---\n", iteracao);
    printf("%-8s", "Vertice:");
    for (int i = 0; i < N; i++) printf("%4c", nomes[i]);
    printf("\n%-8s", "Dist:");
    for (int i = 0; i < N; i++) {
        if (dist[i] == INF) printf("%4s", "inf");
        else printf("%4d", dist[i]);
    }
    printf("\n%-8s", "Pred:");
    for (int i = 0; i < N; i++) {
        if (pred[i] == -1) printf("%4s", "-");
        else printf("%4c", nomes[pred[i]]);
    }
    printf("\n%-8s", "Visit:");
    for (int i = 0; i < N; i++) printf("%4c", visitado[i] ? 'S' : 'N');
    printf("\n");
}

int menorDistanciaNaoVisitado(int dist[N], int visitado[N]) {
    int min = INF, idx = -1;
    for (int i = 0; i < N; i++) {
        if (!visitado[i] && dist[i] < min) {
            min = dist[i];
            idx = i;
        }
    }
    return idx;
}

void imprimeCaminho(int pred[N], int destino) {
    if (pred[destino] == -1) {
        printf("%c", nomes[destino]);
        return;
    }
    imprimeCaminho(pred, pred[destino]);
    printf(" -> %c", nomes[destino]);
}

int main(void) {
    int dist[N], pred[N], visitado[N];
    int origem = 0;      /* A */
    int destino = 9;      /* J */

    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        pred[i] = -1;
        visitado[i] = 0;
    }
    dist[origem] = 0;

    printf("=========================================================\n");
    printf(" Algoritmo de Dijkstra - Caminho Minimo de A ate J\n");
    printf("=========================================================\n");

    int iteracao = 0;
    for (int cont = 0; cont < N; cont++) {
        int u = menorDistanciaNaoVisitado(dist, visitado);
        if (u == -1) break; /* restante inalcancavel */
        visitado[u] = 1;
        iteracao++;

        printf("\n>> Vertice extraido (menor distancia nao visitada): %c (dist=%d)\n",
               nomes[u], dist[u]);

        for (int v = 0; v < N; v++) {
            if (grafo[u][v] != 0 && !visitado[v]) {
                int novaDist = dist[u] + grafo[u][v];
                if (novaDist < dist[v]) {
                    printf("   relaxamento: dist[%c] = min(%s, %d+%d) -> atualizado para %d (pred=%c)\n",
                           nomes[v],
                           dist[v] == INF ? "inf" : "?",
                           dist[u], grafo[u][v], novaDist, nomes[u]);
                    dist[v] = novaDist;
                    pred[v] = u;
                }
            }
        }
        imprimeEstado(dist, pred, visitado, iteracao);
    }

    printf("\n=========================================================\n");
    printf(" RESULTADO FINAL\n");
    printf("=========================================================\n");
    if (dist[destino] == INF) {
        printf("Nao existe caminho de %c ate %c.\n", nomes[origem], nomes[destino]);
    } else {
        printf("Custo total do caminho minimo A -> J: %d\n", dist[destino]);
        printf("Caminho: ");
        imprimeCaminho(pred, destino);
        printf("\n");
    }

    return 0;
}
