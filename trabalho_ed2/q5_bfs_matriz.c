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

int idx(char c) { return c - 'A'; } // converte caractere para indice (0..N-1)

int main(void) { // BFS - busca em largura (menor numero de arestas)
    int fila[N], ini = 0, fimf = 0; // fila de vertices a visitar
    int visitado[N] = {0}; // vetor de vertices visitados
    int dist[N], pred[N];// vetor de distancias e predecessores
    for (int i = 0; i < N; i++) { dist[i] = -1; pred[i] = VAZIO; }// inicializa distancias e predecessores

    int origem = idx('A');// vertice de origem (A)
    visitado[origem] = 1;// marca origem como visitado
    dist[origem] = 0;// distancia da origem para si mesma = 0
    fila[fimf++] = origem;// enfileira origem

    printf("=========================================================\n");
    printf(" BFS - rede academica, inicio em A\n");
    printf("=========================================================\n\n");

    printf("Fila inicial: [ A ]\n\n");

    int passo = 0;// contador de passos (iteracoes)
    while (ini < fimf) {// enquanto a fila nao estiver vazia
        int u = fila[ini++];// retira o primeiro vertice da fila
        passo++;// incrementa contador de passos
        printf("--- Passo %d: retira da fila o vertice %c ---\n", passo, nomes[u]);

        for (int v = 0; v < N; v++) {// percorre todos os vertices do grafo
            if (grafo[u][v] && !visitado[v]) {// se ha aresta e v nao foi visitado
                visitado[v] = 1;// marca v como visitado
                dist[v] = dist[u] + 1;// atualiza distancia de v (dist[u]+1)
                pred[v] = u;// atualiza predecessor de v (u)
                fila[fimf++] = v;// enfileira v
                printf("   descobre %c (via %c): d[%c]=%d, pred[%c]=%c -> enfileira %c\n",
                       nomes[v], nomes[u], nomes[v], dist[v], nomes[v], nomes[u], nomes[v]);// imprime informacoes sobre o vertice descoberto
            }
        }

        printf("   Fila atual: [ ");
        for (int i = ini; i < fimf; i++) printf("%c ", nomes[fila[i]]);// imprime a fila atual
        printf("]\n\n");
    }

    printf("=========================================================\n");
    printf(" TABELA FINAL: distancias (saltos) e predecessores\n");
    printf("=========================================================\n");
    printf("%-8s%-8s%-10s\n", "Vertice", "d[v]", "Pred");// imprime cabecalho da tabela
    for (int i = 0; i < N; i++)
        printf("%-8c%-8d%-10c\n", nomes[i], dist[i], pred[i] == VAZIO ? '-' : nomes[pred[i]]);// imprime cada linha da tabela com o vertice, distancia e predecessor

    printf("\n=========================================================\n");
    printf(" ARVORE DE BUSCA (BFS Tree) - representacao textual\n");
    printf("=========================================================\n");
    for (int niv = 0; niv <= 4; niv++) {// imprime os vertices de cada nivel da arvore de busca
        int algum = 0;// flag para verificar se ha vertices no nivel atual
        printf("Nivel %d: ", niv);// imprime o nivel atual
        for (int i = 0; i < N; i++) {// percorre todos os vertices do grafo
            if (dist[i] == niv) { printf("%c ", nomes[i]); algum = 1; }// se a distancia do vertice i for igual ao nivel atual, imprime o vertice e marca a flag como verdadeira
        }
        if (!algum) continue;// se nao houver vertices no nivel atual, continua para o proximo nivel
        printf("\n");
    }
    printf("\nLigacoes da arvore (pai -> filho):\n");// imprime as ligacoes da arvore de busca (predecessor -> vertice)
    for (int i = 0; i < N; i++)// percorre todos os vertices do grafo
        if (pred[i] != VAZIO)// se o vertice i tiver um predecessor, imprime a ligacao (predecessor -> vertice)
            printf("   %c -> %c\n", nomes[pred[i]], nomes[i]);// imprime a ligacao (predecessor -> vertice)

    return 0;
}
