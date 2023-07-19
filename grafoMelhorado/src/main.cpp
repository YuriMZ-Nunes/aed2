#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "dijikstra.h"

using namespace std;

int main(){
    int choice; // armazena a escolha do menu
    int origin; // armazena a escolha do vertice origem
    int target; // armazena a escolha do vertice destino
    Graph* graph = new Graph; // cria um novo grafo

    makeGraph(graph);   // cria o grafo com base nos inputs
    cout << "\n--Graph created--" << endl;

    while(1){
        // display menu
        cout << "\n1. Show graph" << endl;
        cout << "2. Dijikstra Algorithm" << endl;
        cout << "Enter option: ";
        cout << endl;
        cin >> choice;

        // verificação da escolha
        switch(choice){
            case 1: // listará o grafo
                listGraph(graph);
                break;
            case 2: // pedirá o vertice origem e o destino para rodar o algoritmo de Dijikstra
                listOptions(graph);
                cout << "Select the origin: ";
                cout << endl;
                cin >> origin;
                listOptions(graph);
                cout << "Select the target: ";
                cout << endl;
                cin >> target;
                int minPath = dijikstra(graph, origin, target); // recebe da função Dijikstra o menor caminho
                cout << "The min path to " << graph->vertices[target - 1].name << " is " << minPath << "." << endl;
        }
    }
}
