#include <iostream>
#include <sstream>
#include <limits>

#include "../include/structList.h"

void printGraph(graph *L, int nodes) {
    for (int i = 0; i < nodes; i++) {
        std::cout << i << ": ";
        for (std::list<int>::iterator it = L[i].next.begin(); it != L[i].next.end(); it++) {
            std::cout << *it << " ";
            if (*it == i || *it >= nodes) {std::cout << "\nThe graph is corrupted.\n"; exit(0);}
        }
        std::cout << "\n";
    }
}