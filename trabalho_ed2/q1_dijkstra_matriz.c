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

#define N 10 // numero de vertices
#define INF INT_MAX // valor infinito para inicializacao das distancias

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

// imprime o estado atual dos vetores de distancias, predecessores e visitados a cada iteracao
void imprimeEstado(int dist[N], int pred[N], int visitado[N], int iteracao) {
    printf("\n--- Iteracao %d ---\n", iteracao);
    printf("%-8s", "Vertice:");
    for (int i = 0; i < N; i++) printf("%4c", nomes[i]);// imprime os nomes dos vertices
    printf("\n%-8s", "Dist:");
    for (int i = 0; i < N; i++) {// imprime as distancias atuais dos vertices
        if (dist[i] == INF) printf("%4s", "inf");// se a distancia for infinita, imprime "inf"
        else printf("%4d", dist[i]);// caso contrario, imprime a distancia atual
    }
    printf("\n%-8s", "Pred:");
    for (int i = 0; i < N; i++) {// imprime os predecessores atuais dos vertices
        if (pred[i] == -1) printf("%4s", "-");// se o predecessor for -1, imprime "-"
        else printf("%4c", nomes[pred[i]]);// caso contrario, imprime o nome do predecessor atual
    }
    printf("\n%-8s", "Visit:");
    for (int i = 0; i < N; i++) printf("%4c", visitado[i] ? 'S' : 'N');// imprime se o vertice foi visitado (S) ou nao (N)
    printf("\n");
}

// retorna o indice do vertice com menor distancia nao visitado
int menorDistanciaNaoVisitado(int dist[N], int visitado[N]) {
    int min = INF, idx = -1;// inicializa a menor distancia como infinita e o indice como -1
    for (int i = 0; i < N; i++) {// percorre todos os vertices do grafo
        if (!visitado[i] && dist[i] < min) {// se o vertice nao foi visitado e sua distancia for menor que a menor distancia atual
            min = dist[i];
            idx = i;
        }
    }
    return idx;// retorna o indice do vertice com menor distancia nao visitado (ou -1 se todos foram visitados)
}

// imprime o caminho minimo de A ate J usando o vetor de predecessores
void imprimeCaminho(int pred[N], int destino) {
    if (pred[destino] == -1) {// se o vertice destino nao tem predecessor, significa que nao ha caminho
        printf("%c", nomes[destino]);// imprime o vertice destino e retorna
        return;
    }
    imprimeCaminho(pred, pred[destino]);// chama recursivamente a funcao para imprimir o caminho do predecessor do vertice destino
    printf(" -> %c", nomes[destino]);
}

// funcao principal do programa
int main(void) {
    int dist[N], pred[N], visitado[N];// vetores de distancias, predecessores e visitados
    int origem = 0;      /* A */
    int destino = 9;      /* J */

    for (int i = 0; i < N; i++) {// inicializa os vetores de distancias, predecessores e visitados
        dist[i] = INF;
        pred[i] = -1;
        visitado[i] = 0;
    }
    dist[origem] = 0;

    printf("=========================================================\n");
    printf(" Algoritmo de Dijkstra - Caminho Minimo de A ate J\n");
    printf("=========================================================\n");

    int iteracao = 0;
    for (int cont = 0; cont < N; cont++) {// loop principal do algoritmo de Dijkstra, executa N vezes (uma para cada vertice)
        int u = menorDistanciaNaoVisitado(dist, visitado);// encontra o vertice com menor distancia nao visitado
        if (u == -1) break; // se nao houver mais vertices nao visitados, sai do loop
        visitado[u] = 1;
        iteracao++;

        printf("\n>> Vertice extraido (menor distancia nao visitada): %c (dist=%d)\n",
               nomes[u], dist[u]);

        for (int v = 0; v < N; v++) {// percorre todos os vertices do grafo para relaxar as arestas do vertice u
            if (grafo[u][v] != 0 && !visitado[v]) {// se ha aresta de u para v e v nao foi visitado
                int novaDist = dist[u] + grafo[u][v];// calcula a nova distancia de v atraves de u
                if (novaDist < dist[v]) {// se a nova distancia for menor que a distancia atual de v, atualiza a distancia e o predecessor
                    printf("   relaxamento: dist[%c] = min(%s, %d+%d) -> atualizado para %d (pred=%c)\n",// imprime informacoes sobre o relaxamento da aresta
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
    if (dist[destino] == INF) {// se a distancia do vertice destino for infinita, significa que nao ha caminho de A ate J
        printf("Nao existe caminho de %c ate %c.\n", nomes[origem], nomes[destino]);
    } else {// caso contrario, imprime o custo total do caminho minimo e o caminho em si
        printf("Custo total do caminho minimo A -> J: %d\n", dist[destino]);
        printf("Caminho: ");
        imprimeCaminho(pred, destino);
        printf("\n");
    }

    return 0;
}