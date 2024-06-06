#include <iostream>
#include <sstream>
#include <limits>
#include <random>
#include <bits/stdc++.h>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

#include "../include/structList.h"

bool Hamiltonian(graph *L, int nodes, std::vector<int> &visited, std::vector<int> &path, int vertex, int &count_visited, int start)
{
    visited[vertex] = 1;
    count_visited++;
    path.push_back(vertex);
    
    std::list<int> successors_copy(L[vertex].next);

    while(!successors_copy.empty()){
        int next = successors_copy.front();
        successors_copy.pop_front();
        if (next == start && count_visited == nodes)
        {
            path.push_back(start); // complete the cycle
            return true;
        }
        if (!visited[next]){
            if (Hamiltonian(L, nodes, visited, path, next, count_visited, start)){
                return true;
            }
        }
    }
    visited[vertex] = 0;
    count_visited--;
    path.pop_back();  // Remove the vertex if backtracking
    return false;
}

void findHamilton(graph *L, int nodes)
{
    int start = 0, count_visited = 0;
    std::vector<int> visited(nodes, 0), path;

    bool result = Hamiltonian(L, nodes, visited, path, start, count_visited, start);

    if (result){
        for (int i = 0; i < path.size(); i++){
            std::cout << path[i] << " ";
        }
        std::cout << "\n";
        std::cout << "\nThe hamiltonian cycle found successfully.\n";
    }
    else{
        std::cout << "\nHamiltonian cycle not found.\n";
    }
}