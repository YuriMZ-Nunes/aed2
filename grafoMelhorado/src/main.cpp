#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"

using namespace std;

int main(){
    int choice;
    Graph* graph = new Graph;

    makeGraph(graph);
    cout << "\n--Graph created--" << endl;

    while(1){
        cout << "\n1. Show graph" << endl;
        cout << "2. Dijikstra Algorithm" << endl;
        cout << "Enter option: ";
        cin >> choice;

        switch(choice){
            case 1:
                listGraph(graph);
                break;
        }
    }
}
