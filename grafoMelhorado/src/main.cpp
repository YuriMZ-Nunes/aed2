#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"

using namespace std;

int main(){
    int choice;
    Graph* graph = new Graph;

    while(1){
        cout << "\n1. Generate graph" << endl;
        cout << "2. Show graph" << endl;
        cout << "3. Dijikstra Algorithm" << endl;
        cout << "Enter option: ";
        cin >> choice;

        switch(choice){
            case 1:
                makeGraph(graph);
                cout << "\n--Graph created--" << endl;
                break;
            case 2:
                listGraph(graph);
        }
    }
}
