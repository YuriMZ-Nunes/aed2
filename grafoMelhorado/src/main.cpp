#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_VERTICES = 20;

typedef struct Vertices Vertices;

typedef struct{
    int peso;
    Vertices* verticeDestino;
}Arestas;

struct Vertices{
    string nome;
    Arestas aresta[MAX_VERTICES];
    int numArestas;
};

typedef struct{
    Vertices vertices[MAX_VERTICES];
    int numVertices;
}Grafo;

Grafo criarGrafo(){
    Grafo grafo;
    grafo.numVertices = 0;
    return grafo;
}

void criarVertice(Grafo* grafo, string nome){
    Vertices vertice;
    
    vertice.nome = nome;
    vertice.numArestas = 0;

    grafo->vertices[grafo->numVertices] = vertice;
    grafo->numVertices += 1;
}

void criarAresta(Vertices* verticeOrigem, Vertices* verticeDestino, int peso){
    Arestas arestaOrigem;
    Arestas arestaDestino;

    arestaOrigem.peso = peso;
    arestaDestino.peso = peso;
    arestaOrigem.verticeDestino = verticeDestino;
    arestaDestino.verticeDestino = verticeOrigem;
    verticeOrigem->aresta[verticeOrigem->numArestas] = arestaOrigem;
    verticeOrigem->numArestas += 1;

    verticeDestino->aresta[verticeDestino->numArestas] = arestaDestino;
    verticeDestino->numArestas += 1;
}

void listarGrafo(Grafo* grafo){
    Vertices vertice;
    for(int i = 0; i < grafo->numVertices; i++){
        vertice = grafo->vertices[i];
        cout << vertice.nome << " -> ";
        for(int j = 0; j < vertice.numArestas; j++){
            cout << "[" << vertice.aresta[j].verticeDestino->nome << ", peso " << vertice.aresta[j].peso << "] ";
        }
        cout << "\n";
    }
}

int main(){
    Grafo grafo = criarGrafo();
    char escolha;

    string nome;

    ifstream inputFile("src/input.txt");
    string line;

    int peso;
    char escolhaVertice;
    int escolhaVerticeInt;
    Vertices* verticeOrigem;
    Vertices* verticeDestino;

    while(1){
        cout << "\n1. Adicionar Vertice\n";
        cout << "2. Adicionar Aresta\n";
        cout << "3. Listar grafo\n";
        cout << "4. Sair\n";

        getline(inputFile, line);

        escolha = line[0];

        switch(escolha){
            case '1':
                if(grafo.numVertices == MAX_VERTICES){
                    cout << "Não é possivel adicionar mais vertices.\n";
                    break;
                }else{
                    cout << "Qual o nome do vertice a ser criado? ";
                    getline(inputFile, line);
                    nome = line;
                    criarVertice(&grafo, nome);
                }
                break;
            case '2':
                cout << "Escolha o vertice origem da aresta (Digite o numero correspondente):\n";
                for(int i = 0; i < grafo.numVertices; i++){
                    cout << i+1 << ". " << grafo.vertices[i].nome << "\n";
                }
                getline(inputFile, line);
                escolhaVertice = line[0];
                escolhaVerticeInt = escolhaVertice - '0';
                verticeOrigem = &(grafo.vertices[escolhaVerticeInt - 1]);

                cout << "Escolha o vertice destino da aresta (Digite o numero correspondente):\n";
                for(int i = 0; i < grafo.numVertices; i++){
                    cout << i+1 << ". " << grafo.vertices[i].nome << "\n";
                }
                getline(inputFile, line);
                escolhaVertice = line[0];
                escolhaVerticeInt = escolhaVertice - '0';
                verticeDestino = &(grafo.vertices[escolhaVerticeInt - 1]);
                
                cout << "Qual o peso da aresta? (num inteiro) ";
                getline(inputFile, line);
                peso = atoi(line.c_str());

                criarAresta(verticeOrigem, verticeDestino, peso);
                break;
            case '3':
                listarGrafo(&grafo);
                break;
            case '4':
                exit(1);
        }
    }

}
