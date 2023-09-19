#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;
 
// Numero maximo de vertices
#define V 6
 
//busca em largura
bool search(int rGraph[V][V], int origin, int destiny, int parent[])
{
    
    //Vetor de vértices visitados, marcado com true ou false se existe um caminho do vetor s para o t.    
    
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    //q = fila para percorrer todos os vertices
    
    queue<int> q;
    q.push(origin);
    visited[origin] = true;
    parent[origin] = -1;
 
    // Loop busca em largura
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                // caso encontre um caminho para o nó destino, retorne true
                if (v == destiny) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // caso não encontre um caminho para o nó destino, retorne falso
    return false;
}
 
// retorna o fluxo maximo entre o nó origem e o nó destino
int fordFulkerson(int graph[V][V], int origin, int destiny)
{
    int u, v;

    // criação de um grafo residual a partir do grafo original
    int rGraph[V][V];

    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];
 
    int parent[V]; // vetor usado na busca em largura para armazenar o caminho 
 
    int max_flow = 0; // inicializa o flow com 0
 
    // Aumenta o flow enquanto há caminho da origem a destino
    while (search(rGraph, origin, destiny, parent)) {

        // encontra a menor capacidade entre as arestas do caminho encontrado pela busca 
        int path_flow = INT_MAX;

        for (v = destiny; v != origin; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and
        // reverse edges along the path

        // atualiza as capacidades das arestas e inverte as arestas no caminho
        for (v = destiny; v != origin; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // soma ao flow total
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}
 
// Driver program to test above functions
int main()
{
    // Let us create a graph shown in the above example
    int graph[V][V]
        = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
            { 0, 4, 0, 0, 14, 0 },  { 0, 0, 9, 0, 0, 20 },
            { 0, 0, 0, 7, 0, 4 },   { 0, 0, 0, 0, 0, 0 } };
 
    cout << "The maximum possible flow is "
         << fordFulkerson(graph, 0, 5);
 
    return 0;
}