#include <iostream>

int main(){
    int nodeAmount;
    int weightValue;

    std::cout << "How many nodes we will have: ";
    std::cin >> nodeAmount;

    double graph[nodeAmount][nodeAmount];

    for(int i = 0; i < nodeAmount; i++){
        for(int j = i; j < nodeAmount; j++){
            if(i == j){
                graph[i][j] = 0;
                graph[j][i] = 0;
            }else{
                std::cout << "What's the edge weight from node " << i + 1 << " to node " << j + 1 << " : ";
                std::cin >> weightValue;
                graph[i][j] = weightValue;
            }
        }
    }

    int edgeQtd = (nodeAmount * (nodeAmount - 1)) / 2;

    for(int i = 0; i < edgeQtd - 1; i++){
        for(int j = i + 1; j < edgeQtd; j++){
            std::cout << "Weight between node " << i + 1 << " and node " << j + 1 << " is " << graph[i][j] << ".\n";
        }
    }


}
