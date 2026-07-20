# Trabalho Final — Estrutura de Dados II

Implementação em linguagem C dos 10 exercícios sobre Dijkstra, DFS, BFS,
Prim e Kruskal. Cada questão está em um arquivo `.c` independente, que
imprime no terminal a execução passo a passo do algoritmo (exatamente
o que cada enunciado pede: vetores de distância, predecessores, fila,
pilha, cortes, ordenação de arestas etc.).

## Como compilar e executar

Compilar tudo de uma vez:
```
make all
```

Compilar e já executar todos os programas em sequência:
```
make run
```

Compilar/executar um programa isolado:
```
gcc -Wall -o q1 q1_dijkstra_matriz.c
./q1
```

`make clean` remove os binários gerados.

## Arquivos e resultado final de cada questão

| Arquivo                     | Algoritmo                          | Resultado final                                   |
|------------------------------|-------------------------------------|----------------------------------------------------|
| q1_dijkstra_matriz.c         | Dijkstra (matriz, dirigido)         | Caminho A→B→D→F→I→H→J, custo total **19**          |
| q2_dijkstra_rede.c           | Dijkstra (lista de arestas)         | Rota A→B→E→I→J, latência total **15**              |
| q3_dfs_hierarquica.c         | DFS com d[v]/f[v] e classif. arestas| Árvore DFS + arestas de retorno (B-F, A-C, A-D)    |
| q4_dfs_ciclos.c              | DFS com pilha, detecção de ciclo    | Ciclo detectado; aresta que fecha o ciclo: **I→B** |
| q5_bfs_matriz.c               | BFS (matriz)                        | Distâncias e árvore de busca a partir de A          |
| q6_bfs_lista.c                | BFS (lista de adjacência)           | Camadas de 0 a 4 a partir de E                      |
| q7_prim_matriz.c              | Prim (raiz A)                       | AGM com custo total **23**                          |
| q8_prim_lista.c               | Prim (raiz E)                       | AGM com custo total **40**                           |
| q9_kruskal.c                  | Kruskal (mesmo grafo da Q7)         | AGM com custo total **23** (confere com o Prim)     |
| q10_kruskal_ordenacao.c       | Kruskal (ordenação global)          | AGM fechada dentro das 12 primeiras arestas, custo **30** |

## Observações de implementação

- Vértices A–J são mapeados internamente para os índices 0–9 (`'A'-'A'=0`, etc.).
- Nas questões de Dijkstra e Prim os grafos foram representados por
  **matriz de adjacência**; nas de DFS/BFS por **lista de adjacência**
  (vetor de strings, já em ordem alfabética); e nas de Kruskal por
  **lista de arestas** ordenada com um `sort` simples (bubble sort),
  seguida de **Union-Find** (find com compressão simples de caminho não
  implementada, apenas para manter o código didático e fácil de
  acompanhar).
- Todo o código é livre de bibliotecas externas (apenas `stdio.h`,
  `string.h`, `limits.h`), compila com `gcc -Wall` sem nenhum warning.
- A Questão 9 usa o mesmo grafo da Questão 7 propositalmente, o que
  permite comparar Prim x Kruskal: ambos chegam ao mesmo custo total
  (23), como esperado pela teoria (a AGM de um grafo com pesos
  distintos é única).
