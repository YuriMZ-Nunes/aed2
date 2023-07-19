#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"

using namespace std;

// verifica se o grafo foi criado, caso não seja, saia do programa
void verifyCreateGraph(Graph* graph){
    if(!(&graph)){
        cout << "Can't create graph" << endl;
        exit(1);
    }
    graph->numOfVertices = 0;
}

// cria um vertice no grafo com o nome dado no arquivo texto de input
void createVertex(Graph* graph, string name){
    graph->vertices[graph->numOfVertices].name = name;
    graph->numOfVertices += 1;
}

// cria uma aresta entre o vertice origem e vertice destino
void createEdge(Vertices* vertexOrigin, int origin, Vertices* destinationVertex, int destination, int height){
    vertexOrigin->edge[destination].height = height;
    destinationVertex->edge[origin].height = height;

    vertexOrigin->edge[destination].destinationVertex = destinationVertex;
    destinationVertex->edge[origin].destinationVertex = vertexOrigin;

    vertexOrigin->numOfEdges += 1;
    destinationVertex->numOfEdges += 1;
}

// mostra na tela as opções de vertices disponiveis para escolha
void listOptions(Graph* graph){
    for(int i = 0; i < graph->numOfVertices; i++)
        cout << i+1 << ". " << graph->vertices[i].name << endl;
}

// mostra na tela a lista de adjacencia do grafo
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

//  VERIFICAÇÕES DE ERROS NO INPUT

// verifica se houve erro no input de seleção de opção
void menuOptionVerify(char getChoice){
    int choice = getChoice - '0';
        if(!isdigit(getChoice) || choice > 5 || choice < 1){
            cout << "ERRO: Insert syntax error in input menu option." << endl;
            exit(1); 
        }
}

// verifica se a quantidade de verticeis foi excedida
void limitVerticesVerify(Graph* graph){
    if(graph->numOfVertices == MAX_VERTICES){
        cout << "ERRO: Number of vertices exceeded the limit (20)" << endl;
        exit(1);
    }
}

// verifica se a quantidade de arestas em um vertice foi excedida
void limitEdgesVerify(Graph* graph, int chosenVertexInt){
    if(graph->vertices[chosenVertexInt - 1].numOfEdges >= 19){
        cout << "ERRO: Number of edges in vertex "<< graph->vertices[chosenVertexInt - 1].name << "exceeded the limit (19)" << endl;
        exit(1);
    }
}
//TODO: verificação se o vertice escolhido existe

// verifica se digitou corretamente o valor do vertice desejado
void vertexOptionVerify(char chosenVertex){
    if(!isdigit(chosenVertex)){
        cout << "ERRO: Insert syntax error in input vertex option." << endl;
        exit(1); 
    }
}

// verifica se o peso digitado no input é um numero e caso seja, converte para inteiro
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


// criação do grafo
void makeGraph(Graph* graph){
    verifyCreateGraph(graph);

    char getChoice;
    int choice;

    ifstream inputFile("src/input.txt");
    string line;

    int height;
    int chosenVertexInt1;
    int chosenVertexInt2;
    Vertices* vertexOrigin;
    Vertices* destinationVertex;

    while(inputFile.is_open()){
        getline(inputFile, line);// pega a linha com a opção do menu desejada
        getChoice = line[0]; 

        menuOptionVerify(getChoice); //verifica se o input esta correto

        choice = getChoice - '0';

        //verifica do arquivo texto do input a opçao desejada
        switch(choice){
            case 1: // opção 1: criar vertice; pega a linha do input, que deverá conter um nome
                limitVerticesVerify(graph);// verifica o limite de vertices

                getline(inputFile, line); // pega a linha com o nome do vertice

                createVertex(graph, line); // chama a função para criar o vertice com o nome encontrado
                break;
            case 2: // opção 2: criar aresta, pega os vertices origem e destino e o peso em ordem com o getLine
                getline(inputFile, line); // pega a linha que deverá conter o index do vertice origem
                chosenVertexInt1 = atoi(line.c_str());
                
                limitEdgesVerify(graph, chosenVertexInt1); //chama a função de verificação de limite de arestas

                vertexOrigin = &(graph->vertices[chosenVertexInt1 - 1]);

                getline(inputFile, line); // pega a linha que deverá conter o index do vertice destino
                chosenVertexInt2 = atoi(line.c_str());
                
                limitEdgesVerify(graph, chosenVertexInt2);

                destinationVertex = &(graph->vertices[chosenVertexInt2 - 1]);
                
                getline(inputFile, line); // pega a linha que deverá conter o peso da aresta
                
                height = heightVerifyAndConvert(line);

                createEdge(vertexOrigin, chosenVertexInt1 - 1, destinationVertex, chosenVertexInt2 - 1, height); // cria a aresta
                break;
            case 3: // mostra o grafo na tela
                listGraph(graph);
                break;
            case 4: // encerra o arquivo texto de input
                inputFile.close();
                break; 
        }
    }
}
