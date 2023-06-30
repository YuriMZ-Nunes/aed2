#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"

using namespace std;

void createGraph(Graph* graph){
    if(!(&graph)){
        cout << "Can't create graph" << endl;
        exit(1);
    }
    graph->numOfVertices = 0;
}

void createVertex(Graph* graph, string name){
    graph->vertices[graph->numOfVertices].name = name;
    graph->numOfVertices += 1;
}

void createEdge(Vertices* vertexOrigin, Vertices* destinationVertex, int height){
    vertexOrigin->edge[vertexOrigin->numOfEdges].height = height;
    destinationVertex->edge[destinationVertex->numOfEdges].height = height;

    vertexOrigin->edge[vertexOrigin->numOfEdges].destinationVertex = destinationVertex;
    destinationVertex->edge[destinationVertex->numOfEdges].destinationVertex = vertexOrigin;

    vertexOrigin->numOfEdges += 1;
    destinationVertex->numOfEdges += 1;
}

void listGraph(Graph* graph){
    cout << "\n";
    for(int i = 0; i < graph->numOfVertices; i++){
        cout << graph->vertices[i].name << " -> ";
        for(int j = 0; j < graph->vertices[i].numOfEdges; j++){
            cout << "[" << graph->vertices[i].edge[j].destinationVertex->name << ", height " << graph->vertices[i].edge[j].height << "] ";
        }
        cout << "\n";
    }
}

void menuOptionVerify(char getChoice){
    int choice = getChoice - '0';
        if(!isdigit(getChoice) || choice > 5 || choice < 1){
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

void makeGraph(Graph* graph){
    createGraph(graph);

    char getChoice;
    int choice;

    ifstream inputFile("src/input.txt");
    string line;

    int height;
    char chosenVertex;
    int chosenVertexInt;
    Vertices* vertexOrigin;
    Vertices* destinationVertex;

    while(inputFile.is_open()){
        getline(inputFile, line);
        getChoice = line[0];

        menuOptionVerify(getChoice);

        choice = getChoice - '0';

        switch(choice){
            case 1:
                limitVerticesVerify(graph);
                getline(inputFile, line);
                createVertex(graph, line);
                break;
            case 2:
                getline(inputFile, line);
                chosenVertex = line[0];

                vertexOptionVerify(chosenVertex);

                chosenVertexInt = chosenVertex - '0';
                
                limitEdgesVerify(graph, chosenVertexInt);

                vertexOrigin = &(graph->vertices[chosenVertexInt - 1]);

                getline(inputFile, line);
                chosenVertex = line[0];
                
                vertexOptionVerify(chosenVertex);

                chosenVertexInt = chosenVertex - '0';
                
                limitEdgesVerify(graph, chosenVertexInt);

                destinationVertex = &(graph->vertices[chosenVertexInt - 1]);
                
                getline(inputFile, line);
                
                height = heightVerifyAndConvert(line);

                createEdge(vertexOrigin, destinationVertex, height);
                break;
            case 3:
                listGraph(graph);
                break;
            case 4:
                exit(1);
            case 5: 
                inputFile.close();
                break;
        }
    }
}
