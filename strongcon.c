#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Graph structure
struct Graph {
    int V;
    int adj[MAX_VERTICES][MAX_VERTICES]; // Adjacency matrix
};

// Stack structure for the DFS order
struct Stack {
    int items[MAX_VERTICES];
    int top;
};

// Functions for the Stack
void push(struct Stack* stack, int v) {
    stack->items[++(stack->top)] = v;
}

int pop(struct Stack* stack) {
    return stack->items[(stack->top)--];
}

bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// DFS function to fill the Stack with the finish time order
void dfs(struct Graph* graph, int v, bool visited[], struct Stack* stack) {
    visited[v] = true;
    for (int i = 0; i < graph->V; i++) {
        if (graph->adj[v][i] && !visited[i]) {
            dfs(graph, i, visited, stack);
        }
    }
    push(stack, v);
}

// Transpose (reverse) the graph
void transposeGraph(struct Graph* graph, struct Graph* transposedGraph) {
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            if (graph->adj[i][j]) {
                transposedGraph->adj[j][i] = 1;
            }
        }
    }
}

// DFS on the transposed graph to find SCCs
void dfsOnTransposed(struct Graph* transposedGraph, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);
    for (int i = 0; i < transposedGraph->V; i++) {
        if (transposedGraph->adj[v][i] && !visited[i]) {
            dfsOnTransposed(transposedGraph, i, visited);
        }
    }
}

// Kosaraju's Algorithm to find SCCs
void kosaraju(struct Graph* graph) {
    struct Stack stack;
    stack.top = -1;

    bool visited[MAX_VERTICES] = {false};

    // Step 1: Perform DFS to fill vertices in stack based on finish time
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            dfs(graph, i, visited, &stack);
        }
    }

    // Step 2: Reverse the graph
    struct Graph transposedGraph;
    transposedGraph.V = graph->V;
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            transposedGraph.adj[i][j] = 0;
        }
    }
    transposeGraph(graph, &transposedGraph);

    // Step 3: Perform DFS on the reversed graph using the finish time order
    for (int i = 0; i < graph->V; i++) {
        visited[i] = false; // Reset visited for the transposed graph
    }

    // Process vertices in decreasing order of finish time
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
    
    // Take number of vertices as input
    printf("Enter the number of vertices: ");
    scanf("%d", &graph.V);

    // Initialize adjacency matrix to 0
    for (int i = 0; i < graph.V; i++) {
        for (int j = 0; j < graph.V; j++) {
            graph.adj[i][j] = 0;
        }
    }

    // Take number of edges as input
    int E;
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    // Take edges as input
    printf("Enter the edges (u v) where there is a directed edge from u to v:\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph.adj[u][v] = 1;
    }

    printf("Strongly Connected Components (SCCs):\n");
    kosaraju(&graph);

    return 0;
}
