#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include "graph.h"

using namespace std;

bool compare(Edges a, Edges b){
    return a.height > b.height;
}

vector<Edges> prim(Graph* graph){
    vector<Edges> result;
    unordered_map<Vertices*, bool> visited;
    priority_queue<Edges, vector<Edges>, decltype(&compare)> minEdges(&compare);

    Vertices* startVertex = &graph->vertices[0];

    visited[startVertex] = true;

    for(int i = 0; i < startVertex->numOfEdges; i++)
        minEdges.push(startVertex->edge[i]);

    while(!minEdges.empty()){
        Edges current = minEdges.top();
        minEdges.pop();

        Vertices* originVertex = current.originVertex;
        Vertices* destVertex = current.destinationVertex;

        if(!visited[destVertex]){
            result.push_back(current);
            visited[destVertex] = true;

            for(int i = 0; i < destVertex->numOfEdges; i++)
                if(!visited[destVertex->edge[i].destinationVertex])
                    minEdges.push(destVertex->edge[i]);

        }
    }
    return result;
}

