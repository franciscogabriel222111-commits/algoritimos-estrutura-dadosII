/*
 * Questao 10 - Algoritmo de Kruskal (Ordenacao Global de Pesos)
 * Estrutura de Dados II - Trabalho Final
 *
 * Grafo ponderado conexo com 10 nos. Ordena todas as arestas por
 * peso crescente e analisa passo a passo as 12 primeiras arestas
 * da lista ordenada, mostrando a fusao das componentes conexas via
 * Union-Find ate obter a AGM completa.
 */

#include <stdio.h>

#define N 10
#define M 18

char nomes[N] = {'A','B','C','D','E','F','G','H','I','J'};

typedef struct { char de, para; int peso; } Aresta;

Aresta arestas[M] = {
    {'A','B',6}, {'A','C',3}, {'A','D',8},
    {'B','C',1}, {'B','E',5},
    {'C','D',2}, {'C','E',7}, {'C','F',11},
    {'D','F',4},
    {'E','F',3}, {'E','G',8},
    {'F','G',7}, {'F','H',6},
    {'G','H',9}, {'G','I',2},
    {'H','I',12}, {'H','J',4},
    {'I','J',5}
};

int idx(char c) { return c - 'A'; }

int pai[N];
int encontrar(int x) { while (pai[x] != x) x = pai[x]; return x; }// encontra o representante do conjunto de x
int unir(int x, int y) {// une os conjuntos de x e y, se forem diferentes
    int rx = encontrar(x), ry = encontrar(y);
    if (rx == ry) return 0;// se ja estao no mesmo conjunto, nao faz nada
    pai[rx] = ry;
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
    ordenar(arestas, M);

    printf("=========================================================\n");
    printf(" Algoritmo de Kruskal - Ordenacao global de pesos\n");
    printf("=========================================================\n\n");

    printf("Lista de arestas ordenada (crescente por peso):\n   ");
    for (int i = 0; i < M; i++)// percorre todas as arestas para imprimir as arestas ordenadas
        printf("%c-%c(%d) ", arestas[i].de, arestas[i].para, arestas[i].peso);
    printf("\n\n");

    for (int i = 0; i < N; i++) pai[i] = i;// inicializa o vetor de pais, cada vertice e seu proprio representante

    printf("Analise das primeiras 12 arestas da lista ordenada:\n\n");
    int custoTotal = 0, arestasAGM = 0;
    int limite = 12;
    for (int i = 0; i < limite; i++) {// percorre as 12 primeiras arestas para decidir se inclui ou rejeita cada aresta
        int u = idx(arestas[i].de), v = idx(arestas[i].para);
        printf("Rodada %2d: aresta %c-%c (peso %d)\n", i + 1, arestas[i].de, arestas[i].para, arestas[i].peso);
        printf("           componente(%c) = %c , componente(%c) = %c => ",
               arestas[i].de, nomes[encontrar(u)], arestas[i].para, nomes[encontrar(v)]);

        if (unir(u, v)) {// se os representantes de u e v sao diferentes, inclui a aresta na AGM
            printf("componentes distintas: FUNDE os conjuntos (aresta INCLUIDA)\n");
            custoTotal += arestas[i].peso;
            arestasAGM++;
        } else {// se os representantes de u e v sao iguais, rejeita a aresta (formaria ciclo)
            printf("mesma componente: aresta REJEITADA (formaria ciclo)\n");
        }
        printf("\n");
    }

    printf("=========================================================\n");
    printf(" ESTADO APOS ANALISAR AS 12 PRIMEIRAS ARESTAS\n");
    printf("=========================================================\n");
    printf("Arestas incluidas ate agora: %d de %d necessarias\n", arestasAGM, N - 1);
    printf("Custo parcial acumulado: %d\n\n", custoTotal);

    if (arestasAGM < N - 1) {// se ainda nao foram incluídas N-1 arestas, a AGM nao esta completa
        printf("A AGM ainda nao esta completa; continuando com as arestas restantes\n");
        printf("da lista ordenada (posicoes 13 a %d) ate fechar %d arestas:\n\n", M, N - 1);
        for (int i = limite; i < M && arestasAGM < N - 1; i++) {// percorre as arestas restantes para decidir se inclui ou rejeita cada aresta
            int u = idx(arestas[i].de), v = idx(arestas[i].para);
            printf("Rodada %2d: aresta %c-%c (peso %d) ... ", i + 1, arestas[i].de, arestas[i].para, arestas[i].peso);
            if (unir(u, v)) {// se os representantes de u e v sao diferentes, inclui a aresta na AGM
                printf("INCLUIDA\n");
                custoTotal += arestas[i].peso;
                arestasAGM++;
            } else {// se os representantes de u e v sao iguais, rejeita a aresta (formaria ciclo)
                printf("REJEITADA (ciclo)\n");
            }
        }
    }

    printf("\n=========================================================\n");
    printf(" RESULTADO FINAL\n");
    printf("=========================================================\n");
    printf("AGM completa com %d arestas.\n", arestasAGM);
    printf("Somatorio final dos pesos da AGM: %d\n", custoTotal);

    return 0;
}
