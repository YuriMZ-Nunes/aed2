#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "kruskal.h"
#include "graph.h"

using namespace std;

Vertices* findRootHelper(Vertices* vertex, unordered_map<Vertices*, Vertices*> parent) {
    if (vertex != parent[vertex])
        parent[vertex] = findRootHelper(parent[vertex], parent);
    return parent[vertex];
}

Vertices* findRoot(Vertices* vertex, unordered_map<Vertices*, Vertices*> parent){
    return findRootHelper(vertex, parent);
}

void unionSet(Vertices* x, Vertices* y, unordered_map<Vertices*, Vertices*>& parent, unordered_map<Vertices*, int>& rank) {
    Vertices* xRoot = findRoot(x, parent);
    Vertices* yRoot = findRoot(y, parent);

    if (xRoot != yRoot) {
        if (rank[xRoot] < rank[yRoot])
            parent[xRoot] = yRoot;
        else if (rank[xRoot] > rank[yRoot])
            parent[yRoot] = xRoot;
        else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }
}

bool compareEdges(const Edges& a, const Edges& b) {
    return a.height < b.height;
}

vector<Edges> kruskal(Graph* graph) {
    vector<Edges> result;
    vector<Edges> allEdges;
    unordered_map<Vertices*, Vertices*> parent;
    unordered_map<Vertices*, int> rank;
    
    for (int i = 0; i < graph->numOfVertices; i++) {
        for (int j = 0; j < graph->vertices[i].numOfEdges; j++) {
            allEdges.push_back(graph->vertices[i].edge[j]);
        }
    }

    for (const Edges& edge : allEdges) {
        parent[edge.originVertex] = edge.originVertex;
        parent[edge.destinationVertex] = edge.destinationVertex;
        rank[edge.originVertex] = 0;
        rank[edge.destinationVertex] = 0;
    }

    sort(allEdges.begin(), allEdges.end(), compareEdges);

    for (const Edges& edge : allEdges) {
        Vertices* srcRoot = findRoot(edge.originVertex, parent);
        Vertices* destRoot = findRoot(edge.destinationVertex, parent);

        if (srcRoot != destRoot) {
            result.push_back(edge);
            unionSet(srcRoot, destRoot, parent, rank);
        }
    }
    int count = 0;
    for(int i = 0; i < result.size(); i++)
        count += result[i].height;

    return result;
}
