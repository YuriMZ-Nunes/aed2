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

void createEdge(Vertices* vertexOrigin, int origin, Vertices* destinationVertex, int destination, int height){
    vertexOrigin->edge[destination].height = height;
    destinationVertex->edge[origin].height = height;

    vertexOrigin->edge[destination].destinationVertex = destinationVertex;
    destinationVertex->edge[origin].destinationVertex = vertexOrigin;

    vertexOrigin->numOfEdges += 1;
    destinationVertex->numOfEdges += 1;
}

void listOptions(Graph* graph){
    for(int i = 0; i < graph->numOfVertices; i++)
        cout << i+1 << ". " << graph->vertices[i].name << endl;
}

void listGraph(Graph* graph){
    cout << "\n";
    for(int i = 0; i < graph->numOfVertices; i++){
        cout << graph->vertices[i].name << " -> ";
        for(int j = 0; j < graph->numOfVertices; j++){
            if(graph->vertices[i].edge[j].height != 0)
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
    //char chosenVertex;
    int chosenVertexInt1;
    int chosenVertexInt2;
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
                chosenVertexInt1 = atoi(line.c_str());

                //vertexOptionVerify(chosenVertex);

                //chosenVertexInt = chosenVertex - '0';
                
                limitEdgesVerify(graph, chosenVertexInt1);

                vertexOrigin = &(graph->vertices[chosenVertexInt1 - 1]);

                getline(inputFile, line);
                //chosenVertex = line[0];
                chosenVertexInt2 = atoi(line.c_str());
                
                //vertexOptionVerify(chosenVertex);

                //chosenVertexInt = chosenVertex - '0';
                
                limitEdgesVerify(graph, chosenVertexInt2);

                destinationVertex = &(graph->vertices[chosenVertexInt2 - 1]);
                
                getline(inputFile, line);
                
                height = heightVerifyAndConvert(line);

                createEdge(vertexOrigin, chosenVertexInt1 - 1, destinationVertex, chosenVertexInt2 - 1, height);
                break;
            case 3:
                listGraph(graph);
                break;
            case 4:
                inputFile.close();
                break; 
        }
    }
}
