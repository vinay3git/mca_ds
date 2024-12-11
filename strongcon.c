#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Graph structure
struct Graph {
    int V;
    int adj[MAX_VERTICES][MAX_VERTICES];
};

// Stack structure for the DFS order
struct Stack {
    int items[MAX_VERTICES];
    int top;
};

// Functions for Stack operations
void push(struct Stack* stack, int v) {
    stack->items[++(stack->top)] = v;
}

int pop(struct Stack* stack) {
    return stack->items[(stack->top)--];
}

bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// DFS function to fill the stack based on finish time
void dfs(struct Graph* graph, int v, bool visited[], struct Stack* stack) {
    visited[v] = true;
    for (int i = 0; i < graph->V; i++) {
        if (graph->adj[v][i] && !visited[i]) {
            dfs(graph, i, visited, stack);
        }
    }
    push(stack, v);
}

// Transpose the graph (reverse the edges)
void transposeGraph(struct Graph* graph, struct Graph* transposedGraph) {
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            transposedGraph->adj[j][i] = graph->adj[i][j];
        }
    }
}

// DFS on transposed graph to print SCC
void dfsOnTransposed(struct Graph* transposedGraph, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);
    for (int i = 0; i < transposedGraph->V; i++) {
        if (transposedGraph->adj[v][i] && !visited[i]) {
            dfsOnTransposed(transposedGraph, i, visited);
        }
    }
}

// Kosaraju's algorithm to find SCCs
void kosaraju(struct Graph* graph) {
    struct Stack stack = { .top = -1 };
    bool visited[MAX_VERTICES] = { false };

    // Step 1: Perform DFS on original graph to get finish time order
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            dfs(graph, i, visited, &stack);
        }
    }

    // Step 2: Transpose the graph
    struct Graph transposedGraph = { .V = graph->V };
    transposeGraph(graph, &transposedGraph);

    // Step 3: DFS on transposed graph in reverse finish time order
    for (int i = 0; i < graph->V; i++) {
        visited[i] = false; // Reset visited array
    }

    while (!isEmpty(&stack)) {
        int v = pop(&stack);
        if (!visited[v]) {
            printf("SCC: ");
            dfsOnTransposed(&transposedGraph, v, visited);
            printf("\n");
        }
    }
}

int main() {
    struct Graph graph;
    
    // Input number of vertices and edges
    printf("Enter number of vertices: ");
    scanf("%d", &graph.V);

    // Initialize adjacency matrix to 0
    for (int i = 0; i < graph.V; i++) {
        for (int j = 0; j < graph.V; j++) {
            graph.adj[i][j] = 0;
        }
    }

    // Input edges
    int E;
    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Enter edges (u v) where u -> v:\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph.adj[u][v] = 1;
    }

    // Run Kosaraju's algorithm to find SCCs
    printf("Strongly Connected Components (SCCs):\n");
    kosaraju(&graph);

    return 0;
}
