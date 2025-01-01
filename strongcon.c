#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

int adj[MAX_NODES][MAX_NODES], transposed[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int count[MAX_NODES] = {0}, count_transposed[MAX_NODES] = {0};
int stack[MAX_NODES], top = -1;

// Push onto stack
void push(int v) {
    stack[++top] = v;
}

// Pop from stack
int pop() {
    return stack[top--];
}

// DFS for the original graph
void DFS(int vertex) {
    visited[vertex] = 1;

    for (int i = 0; i < count[vertex]; i++) {
        int neighbor = adj[vertex][i];
        if (!visited[neighbor]) {
            DFS(neighbor);
        }
    }
    push(vertex); // Push to stack after finishing
}

// DFS for the transposed graph
void DFS_Transpose(int vertex) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < count_transposed[vertex]; i++) {
        int neighbor = transposed[vertex][i];
        if (!visited[neighbor]) {
            DFS_Transpose(neighbor);
        }
    }
}

int main() {
    int N, M;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &N, &M);

    // Initialize adjacency lists
    for (int i = 0; i < N; i++) {
        count[i] = 0;
        count_transposed[i] = 0;
        visited[i] = 0;
    }

    printf("Enter edges (u v):\n");
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][count[u]++] = v; // Original graph
        transposed[v][count_transposed[v]++] = u; // Transposed graph
    }

    // Step 1: Perform DFS on the original graph
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            DFS(i);
        }
    }

    // Step 2: Perform DFS on the transposed graph
    for (int i = 0; i < N; i++) {
        visited[i] = 0; // Reset visited array
    }

    printf("Strongly Connected Components:\n");
    while (top != -1) {
        int v = pop();
        if (!visited[v]) {
            DFS_Transpose(v); // Find one SCC
            printf("\n");
        }
    }

    return 0;
}
