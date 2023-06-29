#include <iostream>
#include <fstream>
//#include <ctype.h>
#include <string>

using namespace std;

const int MAX_VERTICES = 20;

typedef struct Vertices Vertices;

typedef struct{
    int height;
    Vertices* destinationVertex;
}Edges;

struct Vertices{
    string name;
    Edges aresta[MAX_VERTICES];
    int numOfEdges;
};

typedef struct{
    Vertices vertices[MAX_VERTICES];
    int numOfVertices;
}Graph;

Graph createGraph(){
    Graph graph;
    if(!(&graph)){
        cout << "Can't create graph" << endl;
        exit(1);
    }
    graph.numOfVertices = 0;
    return graph;
}

void createVertex(Graph* graph, string name){
    Vertices vertex;
    
    vertex.name = name;
    vertex.numOfEdges = 0;

    graph->vertices[graph->numOfVertices] = vertex;
    graph->numOfVertices += 1;
}

void createEdge(Vertices* vertexOrigin, Vertices* destinationVertex, int height){
    Edges originEdge;
    Edges destinationEdge;

    originEdge.height = height;
    destinationEdge.height = height;
    originEdge.destinationVertex = destinationVertex;
    destinationEdge.destinationVertex = vertexOrigin;
    vertexOrigin->aresta[vertexOrigin->numOfEdges] = originEdge;
    vertexOrigin->numOfEdges += 1;

    destinationVertex->aresta[destinationVertex->numOfEdges] = destinationEdge;
    destinationVertex->numOfEdges += 1;
}

void listGraph(Graph* graph){
    Vertices vertex;
    for(int i = 0; i < graph->numOfVertices; i++){
        vertex = graph->vertices[i];
        cout << vertex.name << " -> ";
        for(int j = 0; j < vertex.numOfEdges; j++){
            cout << "[" << vertex.aresta[j].destinationVertex->name << ", height " << vertex.aresta[j].height << "] ";
        }
        cout << "\n";
    }
}

void menuOptionVerify(char getChoise){
    int choise = getChoise - '0';
        if(!isdigit(getChoise) || choise > 4 || choise < 1){
            cout << "ERRO: Insert syntax error in input menu option." << endl;
            exit(1); 
        }
}

void limitVerticesVerify(Graph* graph){
    if(graph->numOfVertices == MAX_VERTICES){
        cout << "ERRO: Number of vertices exceeded the limit (20)" << endl;
        exit(1);
    }
}

void limitEdgesVerify(Graph* graph, int chosenVertexInt){
    if(graph->vertices[chosenVertexInt - 1].numOfEdges >= 19){
        cout << "ERRO: Number of edges in vertex "<< graph->vertices[chosenVertexInt - 1].name << "exceeded the limit (19)" << endl;
        exit(1);
    }
}

void vertexOptionVerify(char chosenVertex){
    if(!isdigit(chosenVertex)){
        cout << "ERRO: Insert syntax error in input vertex option." << endl;
        exit(1); 
    }
}

int heightVerifyAndConvert(string line){
    int height;
    
    for(int i = 0; i < (int)line.length(); i++){
        if(!isdigit(line[i])){
            cout << "ERRO: Insert syntax error in input height value." << endl;
            exit(1);
        }
    }

    height = atoi(line.c_str());
    return height;
}

int main(){
    Graph graph = createGraph();

    char getChoise;
    int choise;

    string name;

    ifstream inputFile("src/input.txt");
    string line;

    int height;
    char chosenVertex;
    int chosenVertexInt;
    Vertices* vertexOrigin;
    Vertices* destinationVertex;

    while(1){
        cout << "\n1. Add vertex" << endl;
        cout << "2. Add edge" << endl;
        cout << "3. List graph" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter the number: \n" << endl;
        getline(inputFile, line);
        getChoise = line[0];

        menuOptionVerify(getChoise);

        choise = getChoise - '0';

        switch(choise){
            case 1:
                limitVerticesVerify(&graph);

                cout << "Name of vertex: " << endl;
                getline(inputFile, line);
                name = line;
                createVertex(&graph, name);
                break;
            case 2:
                cout << "Choose the origin vertex(enter the number): " << endl;
                for(int i = 0; i < graph.numOfVertices; i++){
                    cout << i+1 << ". " << graph.vertices[i].name << "\n";
                }
                getline(inputFile, line);
                chosenVertex = line[0];

                vertexOptionVerify(chosenVertex);

                chosenVertexInt = chosenVertex - '0';
                
                limitEdgesVerify(&graph, chosenVertexInt);

                vertexOrigin = &(graph.vertices[chosenVertexInt - 1]);

                cout << "Choose the destination vertex(enter the number): " << endl;
                for(int i = 0; i < graph.numOfVertices; i++){
                    cout << i+1 << ". " << graph.vertices[i].name << "\n";
                }

                getline(inputFile, line);
                chosenVertex = line[0];
                
                vertexOptionVerify(chosenVertex);

                chosenVertexInt = chosenVertex - '0';
                
                limitEdgesVerify(&graph, chosenVertexInt);

                destinationVertex = &(graph.vertices[chosenVertexInt - 1]);
                
                cout << "New edge weight? (integer): " << endl;
                getline(inputFile, line);
                
                height = heightVerifyAndConvert(line);

                createEdge(vertexOrigin, destinationVertex, height);
                break;
            case 3:
                listGraph(&graph);
                break;
            case 4:
                exit(1);
        }
    }

}
