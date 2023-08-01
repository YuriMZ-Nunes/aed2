#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
// algoritmos
#include "graph.h"
#include "dijikstra.h"
#include "kruskal.h"
#include "prim.h"

using namespace std;

int main(){
    int choice; // armazena a escolha do menu
    int origin; // armazena a escolha do vertice origem
    int target; // armazena a escolha do vertice destino
    Graph* graph = new Graph; // cria um novo grafo

    int minPath;


    makeGraph(graph);   // cria o grafo com base nos inputs
    cout << "\n--Graph created--" << endl;

    //algoritmo de kruskal
    Graph* kruskalGraph = new Graph;
    memcpy(&kruskalGraph, &graph, sizeof(graph));
    vector<Edges> mstKruskal;
    int mstKruskalCount = 0;

    //algoritmo de Prim
    vector<Edges> mstPrim;
    int mstPrimCount = 0;
    

    while(1){
        // display menu
        cout << "\n1. Show graph" << endl;
        cout << "2. Dijikstra Algorithm" << endl;
        cout << "3. Kruskal Algorithm" << endl;
        cout << "4. Prim Algorithm" << endl;
        cout << "5. Exit" << endl;
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
                minPath = dijikstra(graph, origin, target); // recebe da função Dijikstra o menor caminho
                cout << "The min path to " << graph->vertices[target - 1].name << " is " << minPath << "." << endl;
                break;
            case 3:
                mstKruskal = kruskal(kruskalGraph);
                cout << "The MST using the Kruskal Algorithm is: " << endl;
                for(int i = 0; i < (int)mstKruskal.size(); i++){
                    mstKruskalCount += mstKruskal[i].height;
                    cout << mstKruskal[i].originVertex->name << " -> " << mstKruskal[i].destinationVertex->name << endl;
                }
                cout << "MST Cost: " << mstKruskalCount << endl;
                break;
            case 4:
                mstPrim = prim(graph);
                cout << "The MST using the Prim Algorithm is: " << endl;
                for(int i = 0; i < (int)mstPrim.size(); i++){
                    cout << mstPrim[i].originVertex->name << " -> " << mstPrim[i].destinationVertex->name << endl;
                    mstPrimCount += mstPrim[i].height;
                }
                cout << "MST Cost: " << mstPrimCount << endl;
                break;
            case 5:
                exit(1);
            default:
                cout << "Invalid option." << endl;
        }
    }
}
