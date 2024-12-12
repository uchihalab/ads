#include <stdio.h>
#include <stdlib.h>


struct Edge {
    int src, dest, weight;
};


struct Graph {
    int V, E; 
    struct Edge* edge;
};


struct Subset {
    int parent;
    int rank;
};


struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(E * sizeof(struct Edge));
    return graph;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}


void Union(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}


int compareEdges(const void* a, const void* b) {
    struct Edge* edgeA = (struct Edge*) a;
    struct Edge* edgeB = (struct Edge*) b;
    return edgeA->weight > edgeB->weight;
}


void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V]; 
    int e = 0; 
    int i = 0; 

    
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);


    struct Subset* subsets = (struct Subset*) malloc(V * sizeof(struct Subset));

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    
    while (e < V - 1 && i < graph->E) {
        struct Edge nextEdge = graph->edge[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) { 
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
    }


    printf("Edge \tWeight\n");
    for (int j = 0; j < e; j++) {
        printf("%d - %d \t%d\n", result[j].src, result[j].dest, result[j].weight);
    }

    free(subsets);
}

int main() {
    int V, E;

    
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    
    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    printf("\nMinimum Spanning Tree (MST) using Kruskal's Algorithm:\n");
    kruskalMST(graph);

    free(graph->edge);
    free(graph);

    return 0;
}
