#ifndef MAKE_GRAPH
#define MAKE_GRAPH

using namespace std;

const int MAX_VERTICES = 20;

typedef struct Vertices Vertices;

typedef struct{
    int height;
    Vertices* destinationVertex;
}Edges;

struct Vertices{
    string name;
    Edges edge[MAX_VERTICES];
    int numOfEdges;
};


typedef struct{
    Vertices vertices[MAX_VERTICES];
    int numOfVertices;
}Graph;

void makeGraph(Graph* graph);
void listGraph(Graph* graph);

#endif