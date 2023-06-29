#include <iostream>
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

void criarVertice(Grafo* grafo){
    Vertices vertice;
    cout << "Qual o nome do vertice a ser criado? ";
    cin >> vertice.nome;
    vertice.numArestas = 0;

    grafo->vertices[grafo->numVertices] = vertice;
    grafo->numVertices += 1;
}

void criarAresta(Vertices* verticeOrigem, Vertices* verticeDestino){
    int peso;

    Arestas arestaOrigem;
    Arestas arestaDestino;

    cout << "Qual o peso da aresta? (num inteiro) ";
    cin >> peso;

    arestaOrigem.peso = peso;
    arestaDestino.peso = peso;
    arestaOrigem.verticeDestino = verticeOrigem;
    arestaDestino.verticeDestino = verticeDestino;
    verticeOrigem->aresta[verticeOrigem->numArestas] = arestaDestino;
    verticeOrigem->numArestas += 1;

    verticeDestino->aresta[verticeDestino->numArestas] = arestaOrigem;
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
    int escolha;

    int escolhaVertice;
    Vertices* verticeOrigem;
    Vertices* verticeDestino;

    while(1){
        cout << "\n1. Adicionar Vertice\n";
        cout << "2. Adicionar Aresta\n";
        cout << "3. Listar grafo\n";
        cout << "4. Sair\n";

        cin >> escolha;

        switch(escolha){
            case 1:
                if(grafo.numVertices == MAX_VERTICES){
                    cout << "Não é possivel adicionar mais vertices.\n";
                    break;
                }else{
                    criarVertice(&grafo);
                }
                break;
            case 2:
                cout << "Escolha o vertice origem da aresta (Digite o numero correspondente):\n";
                for(int i = 0; i < grafo.numVertices; i++){
                    cout << i+1 << ". " << grafo.vertices[i].nome << "\n";
                }
                cin >> escolhaVertice;
                verticeOrigem = &(grafo.vertices[escolhaVertice - 1]);

                cout << "Escolha o vertice destino da aresta (Digite o numero correspondente):\n";
                for(int i = 0; i < grafo.numVertices; i++){
                    cout << i+1 << ". " << grafo.vertices[i].nome << "\n";
                }
                cin >> escolhaVertice;
                verticeDestino = &(grafo.vertices[escolhaVertice - 1]);

                criarAresta(verticeOrigem, verticeDestino);
                break;
            case 3:
                listarGrafo(&grafo);
            case 4:
                exit(1);
        }
    }

}
