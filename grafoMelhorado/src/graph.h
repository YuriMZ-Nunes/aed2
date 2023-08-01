#ifndef MAKE_GRAPH
#define MAKE_GRAPH

using namespace std;

const int MAX_VERTICES = 20;

typedef struct Vertices Vertices;

typedef struct Edges{
    int height;
    Vertices* originVertex;
    Vertices* destinationVertex;
}Edges;

struct Vertices{
    string name;
    Edges edge[MAX_VERTICES];
    int numOfEdges;
};


typedef struct Graph{
    Vertices vertices[MAX_VERTICES];
    int numOfVertices;
}Graph;

void makeGraph(Graph* graph);
void listGraph(Graph* graph);
void listOptions(Graph* graph);
int **createMatrix(Graph* graph);

#endif