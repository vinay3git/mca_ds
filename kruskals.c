#include <stdio.h>

int parent[10], n, cost[10][10];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

int union_set(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
    return 0;
}

void main() {
    int i, j, a, b, u, v, ne = 1, min, mincost = 0;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = 999;
        }
    }


    for (i = 0; i < n; i++)
        parent[i] = i;

    printf("\nEdges in the Minimum Spanning Tree:\n");
    while (ne < n) {
        for (i = 0, min = 999; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (cost[i][j] < min) {
                    min = cost[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }

        u = find(u);
        v = find(v);


        if (u != v) {
            printf("Edge %d: (%d, %d) cost: %d\n", ne++, a, b, min);
            mincost += min;
            union_set(u, v);
        }


    cost[a][b] = cost[b][a] = 999;
    }

    printf("\nMinimum cost: %d\n", mincost);
}
