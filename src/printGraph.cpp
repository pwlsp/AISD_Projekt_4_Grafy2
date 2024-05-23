#include <iostream>
#include <sstream>
#include <limits>

#include "../include/structList.h"

void printGraph(graph *L, int nodes) {//skopiowac z poprzedniego projektu ez
    for(int i = 0; i < nodes; i++){
        std::cout << i << ": ";
        for(std::list<int>::iterator it = L[i].next.begin(); it != L[i].next.end(); it++) std::cout << *it << " ";
        std::cout << "\n";
    }
}