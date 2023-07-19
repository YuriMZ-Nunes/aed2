#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "dijikstra.h"

using namespace std;

int main(){
    int choice;
    int origin;
    int target;
    Graph* graph = new Graph;

    makeGraph(graph);
    cout << "\n--Graph created--" << endl;

    while(1){
        cout << "\n1. Show graph" << endl;
        cout << "2. Dijikstra Algorithm" << endl;
        cout << "Enter option: ";
        cout << endl;
        cin >> choice;

        switch(choice){
            case 1:
                listGraph(graph);
                break;
            case 2:
                listOptions(graph);
                cout << "Select the origin: ";
                cout << endl;
                cin >> origin;
                listOptions(graph);
                cout << "Select the target: ";
                cout << endl;
                cin >> target;
                int minPath = dijikstra(graph, origin, target);
                cout << "The min path to " << graph->vertices[target - 1].name << " is " << minPath << "." << endl;
        }
    }
}
