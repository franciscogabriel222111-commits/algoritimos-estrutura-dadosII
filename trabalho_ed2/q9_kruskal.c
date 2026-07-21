/*
 * Questao 9 - Algoritmo de Kruskal (Florestas e Conjuntos Disjuntos)
 * Estrutura de Dados II - Trabalho Final
 *
 * Mesmo grafo da Questao 7 (rede de 10 predios comerciais).
 * Executa o Algoritmo de Kruskal: ordena as arestas por peso
 * crescente e usa Union-Find para decidir, a cada rodada, se a
 * aresta e incluida (nao forma ciclo) ou rejeitada (forma ciclo).
 */

#include <stdio.h>

#define N 10
#define M 17

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

typedef struct { char de, para; int peso; } Aresta;

/* arestas extraidas da matriz de custos da Questao 7 (uma vez cada) */
Aresta arestas[M] = {
    {'A','B',5}, {'A','C',4},
    {'B','C',2}, {'B','D',3}, {'B','E',8},
    {'C','E',6},
    {'D','E',1}, {'D','F',7}, {'D','G',4},
    {'E','G',5},
    {'F','G',2}, {'F','H',3},
    {'G','H',6}, {'G','I',1},
    {'H','I',2}, {'H','J',5},
    {'I','J',4}
};

int idx(char c) { return c - 'A'; }

int pai[N];

int encontrar(int x) {// encontra o representante do conjunto de x
    while (pai[x] != x) x = pai[x];// encontra o representante do conjunto de x
    return x;
}

int unir(int x, int y) {// une os conjuntos de x e y, se forem diferentes
    int rx = encontrar(x), ry = encontrar(y);
    if (rx == ry) return 0; // se ja estao no mesmo conjunto, nao faz nada
    pai[rx] = ry;// une os conjuntos de x e y, fazendo o representante de x apontar para o representante de y
    return 1;
}

void ordenar(Aresta v[], int n) {// ordena as arestas por peso crescente usando bubble sort
    for (int i = 0; i < n - 1; i++)// percorre todas as arestas
        for (int j = 0; j < n - 1 - i; j++)// percorre as arestas restantes
            if (v[j].peso > v[j + 1].peso) {// se a aresta atual tem peso maior que a proxima, troca de posicao
                Aresta tmp = v[j]; v[j] = v[j + 1]; v[j + 1] = tmp;// troca de posicao
            }
}

// funcao principal
int main(void) {
    for (int i = 0; i < N; i++) pai[i] = i;// inicializa o vetor de pais, cada vertice e seu proprio representante

    ordenar(arestas, M);

    printf("=========================================================\n");
    printf(" Algoritmo de Kruskal - AGM (mesmo grafo da Questao 7)\n");
    printf("=========================================================\n\n");

    printf("Arestas ordenadas crescentemente por peso:\n   ");
    for (int i = 0; i < M; i++)// percorre todas as arestas para imprimir as arestas ordenadas
        printf("%c-%c(%d) ", arestas[i].de, arestas[i].para, arestas[i].peso);
    printf("\n\n");

    int custoTotal = 0, arestasAGM = 0;
    for (int i = 0; i < M; i++) {// percorre todas as arestas para decidir se inclui ou rejeita cada aresta
        int u = idx(arestas[i].de), v = idx(arestas[i].para);
        printf("Rodada %2d: analisa aresta %c-%c (peso %d) ... ", i + 1, arestas[i].de, arestas[i].para, arestas[i].peso);

        if (unir(u, v)) {// se os representantes de u e v sao diferentes, inclui a aresta na AGM
            printf("INCLUIDA (conjuntos de %c e %c eram diferentes -> uniao realizada)\n",
                   arestas[i].de, arestas[i].para);
            custoTotal += arestas[i].peso;
            arestasAGM++;
        } else {// se os representantes de u e v sao iguais, rejeita a aresta (formaria ciclo)
            printf("REJEITADA (%c e %c ja pertencem ao mesmo conjunto -> formaria ciclo)\n",
                   arestas[i].de, arestas[i].para);
        }

        if (arestasAGM == N - 1) {// se ja foram incluídas N-1 arestas, a AGM esta completa
            printf("\n(AGM completa: %d arestas selecionadas para %d vertices)\n", arestasAGM, N);
            break;
        }
    }

    printf("\n=========================================================\n");
    printf(" GRAFO FINAL (AGM) E CUSTO TOTAL\n");
    printf("=========================================================\n");
    for (int i = 0; i < N; i++) pai[i] = i; /* apenas para reexibir nao usado */

    /* reconstroi lista de arestas incluidas */
    for (int i = 0; i < N; i++) pai[i] = i;
    printf("Arestas selecionadas:\n");
    int c2 = 0, custo2 = 0;
    for (int i = 0; i < M && c2 < N - 1; i++) {// percorre todas as arestas para reconstituir a AGM e calcular o custo total
        int u = idx(arestas[i].de), v = idx(arestas[i].para);
        if (unir(u, v)) {// se os representantes de u e v sao diferentes, inclui a aresta na AGM
            printf("   %c - %c   (peso %d)\n", arestas[i].de, arestas[i].para, arestas[i].peso);
            custo2 += arestas[i].peso;
            c2++;
        }
    }
    printf("\nCusto total da AGM: %d\n", custo2);

    return 0;
}
