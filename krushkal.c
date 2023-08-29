#include <stdio.h>
#include <stdlib.h>
struct Edge {
    int src, dest, weight;
};
struct Subset {
    int parent, rank;
};
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
void kruskalMST(struct Edge edges[], int numEdges, int numVertices) {
    struct Edge result[numVertices]; 
    int resultIndex = 0;
    qsort(edges, numEdges, sizeof(edges[0]), compareEdges);
    struct Subset subsets[numVertices];
    int i;
    for (i = 0; i < numVertices; ++i) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
   }
    for (i= 0; i < numEdges && resultIndex < numVertices - 1; ++i) {
        int srcRoot = find(subsets, edges[i].src);
        int destRoot = find(subsets, edges[i].dest);
        if (srcRoot != destRoot) {
            result[resultIndex++] = edges[i];
            unionSets(subsets, srcRoot, destRoot);
        }
    }
    printf("Minimum Spanning Tree:\n");
    for (i = 0; i < resultIndex; ++i) {
        printf("(%d, %d) -> %d\n", result[i].src, result[i].dest, result[i].weight);
    }
}
int main() {
    int numVertices = 4;
    int numEdges = 5;
    struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };
    kruskalMST(edges, numEdges, numVertices);
    return 0;
}

