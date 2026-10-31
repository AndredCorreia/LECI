#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Função Bellman-Ford para determinar os vértices alcançáveis a partir de um dado vértice
void bellmanFord(int **graph, int V, int start, int *reachable) {
    int *dist = (int *)malloc(V * sizeof(int));

    // Inicializar distâncias para infinito e definir a distância inicial como 0
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    // Relaxar as arestas (V-1) vezes
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != 0 && dist[u] != INF && dist[u] + 1 < dist[v]) {
                    dist[v] = dist[u] + 1;
                }
            }
        }
    }

    // Determinar os vértices alcançáveis
    for (int i = 0; i < V; i++) {
        if (dist[i] != INF) {
            reachable[i] = 1;
        }
    }

    free(dist);
}

// Função para calcular o transitive closure
int **transitiveClosure(int **graph, int V) {
    // Alocar memória para o grafo do transitive closure
    int **closure = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        closure[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            closure[i][j] = graph[i][j]; // Copiar o grafo original
        }
    }

    // Determinar os vértices alcançáveis usando Bellman-Ford
    for (int u = 0; u < V; u++) {
        int *reachable = (int *)calloc(V, sizeof(int));
        bellmanFord(graph, V, u, reachable);
        for (int v = 0; v < V; v++) {
            if (reachable[v]) {
                closure[u][v] = 1; // Adicionar ligação direta
            }
        }
        free(reachable);
    }

    return closure;
}

// Função para imprimir as arestas no formato "vértice -> vértice"
void printEdges(int **graph, int V) {
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] == 1) {
                printf("%d -> %d;\n", u, v);
            }
        }
    }
}

int main() {
    int V;
    printf("Digite o número de vértices: ");
    scanf("%d", &V);

    // Alocar e ler o grafo original
    int **graph = (int **)malloc(V * sizeof(int *));
    printf("Escreva a matriz de adjacência do grafo original:\n");
    for (int i = 0; i < V; i++) {
        graph[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Calcula o transitive closure
    int **closure = transitiveClosure(graph, V);

    // Imprime as arestas no formato desejado
    printf("\nArestas do Transitive Closure:\n");
    printEdges(closure, V);

    // Liberta memória
    for (int i = 0; i < V; i++) {
        free(graph[i]);
        free(closure[i]);
    }
    free(graph);
    free(closure);

    return 0;
}
