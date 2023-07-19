#include <iostream>
#include <vector>
#include "graph.h"

#define INT_MAX 1000000 // equivale ao infinito no calculo de distancias

// cria a matriz de adjacencia do grafo pois assim é mais fácil de rodar o algoritmo de Dijikstra
int** createMatrix(Graph* graph){
    int **graphMatrix = (int **)malloc(graph->numOfVertices * sizeof(int *)); // aloca espaço para a matriz

    for(int row = 0; row < graph->numOfVertices; row++) //aloca espaço para cada linha da matriz
        graphMatrix[row] = (int *)malloc(graph->numOfVertices * sizeof(int));

    //preenche a matriz com os valores da lista de adjacencia 
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

// retorna o index do vertice com a menor distancia 
int minDistance(int dist[], bool sptSet[], int numOfVertices){
    int min = INT_MAX;
    int min_index;

    // percorre o vertices e verifica qual é o index do vertice com menor distancia 
    for(int i = 0; i < numOfVertices; i++)
        if(sptSet[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;

    return min_index;
}

int dijikstra(Graph* graph, int origin, int target){

    int **graphMatrix = createMatrix(graph); // chama a função para criar a matris

    int dist[graph->numOfVertices]; //vetor usado pra armazenar as distancias pra cada vertice do grafo

    bool sptSet[graph->numOfVertices]; //vetor booleano usado para armazenar quais vertices foram ou não visitados

    // preenche todas as distancias com infinito (INT_MAX) e o vetor de visitados com False
    for(int i = 0; i < graph->numOfVertices; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    
    dist[origin - 1] = 0; // o vertice origem é configurado com 0

    // percorre calculando a menor distancia pra cada vertice
    for(int count = 0; count < graph->numOfVertices - 1; count++){

        int u = minDistance(dist, sptSet, graph->numOfVertices); // pega o retorno do index do vertice com menor distancia

        sptSet[u] = true; // marca esse index como ja visitado

        // preenche o vetor de distancias com a menor distancia encontrada na função minDistance pra cada vertice
        for(int i = 0; i < graph->numOfVertices; i++)
            /*  vai somar o peso da aresta com a menor distancia de cada vertice caso o vertice ainda
                não tenha sido visitado, se o peso é diferente de 0 e diferente de indinito e caso essa soma
                seja menor que a distancia ja calculada anteriormente

                esse vetor de distancias então será preechido com a menor distancia da origem escolhida
                pra cada vertice 
            */
            if(!sptSet[i] && graphMatrix[u][i] && dist[u] != INT_MAX && dist[u] + graphMatrix[u][i] < dist[i])
                dist[i] = dist[u] + graphMatrix[u][i];
    }

    return dist[target - 1]; // retorna a distancia pro vertice alvo
}