#include <iostream>
#include <vector>
#include "graph.h"

#define INT_MAX 1000000

int** createMatrix(Graph* graph){

    int **graphMatrix = (int **)malloc(graph->numOfVertices * sizeof(int *));

    for(int row = 0; row < graph->numOfVertices; row++)
        graphMatrix[row] = (int *)malloc(graph->numOfVertices * sizeof(int));

    for(int i = 0; i < graph->numOfVertices; i++){
        for(int j = 0; j< graph->numOfVertices; j++){
            if(graph->vertices[i].edge[j].height){
                graphMatrix[i][j] = graph->vertices[i].edge[j].height;
            }else{
                graphMatrix[i][j] = 0;
            }
        }
    }

    return graphMatrix;
}

int minDistance(int dist[], bool sptSet[], int numOfVertices){
    int min = INT_MAX;
    int min_index;

    for(int i = 0; i < numOfVertices; i++)
        if(sptSet[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;

    return min_index;
}

int dijikstra(Graph* graph, int src){

    int **graphMatrix = createMatrix(graph);

    int dist[graph->numOfVertices]; //vector with distances

    bool sptSet[graph->numOfVertices]; //

    for(int i = 0; i < graph->numOfVertices; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    
    dist[0] = 0;

    for(int count = 0; count < graph->numOfVertices - 1; count++){

        int u = minDistance(dist, sptSet, graph->numOfVertices);

        sptSet[u] = true; 

        for(int i = 0; i < graph->numOfVertices; i++)
            if(!sptSet[i] && graphMatrix[u][i] && dist[u] != INT_MAX && dist[u] + graphMatrix[u][i] < dist[i])
                dist[i] = dist[u] + graphMatrix[u][i];
    }

    return dist[src - 1];    
}