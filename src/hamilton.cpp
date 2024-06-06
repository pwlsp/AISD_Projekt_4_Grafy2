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
    std::list successors_copy(L[vertex].next);
    std::list successors_copy2(L[vertex].next);
    std::cout << "\nvertex: " << vertex << "\nsuccessors: ";
    while(successors_copy2.size() > 0){
        int next = successors_copy2.front();
        successors_copy2.pop_front();
        std::cout << next << " ";
    }
    std::cout<<"\nvisited: "<< count_visited <<"\n\n";
    while(successors_copy.size() > 0){
        int next = successors_copy.front();
        successors_copy.pop_front();
        if (next == start && count_visited == nodes)
            return 1;
        if (!visited[next]){
            if (Hamiltonian(L, nodes, visited, path, next, count_visited, start)){
                path.push_back(vertex);
                return 1;
            }
        }
    }
    visited[vertex] = 0;
    count_visited--;
    return 0;
}
void findHamilton(graph *L, int nodes)
{
    int start = 5, count_visited = 0;
    std::vector<int> visited(nodes, 0), path{start};

    bool result = Hamiltonian(L, nodes, visited, path, start, count_visited, start);

    if (result){
        std::cout << "\nThe graph contains a hamiltonian cycle:\n";
        for (int i = 0; i < path.size(); i++){
            std::cout << path[i] << " ";
        }
        std::cout << "\n";
    }

    else{
        std::cout << "\nHamiltonian cycle not found.\nLast path that has been searched:\n";
        for (int i = 0; i < path.size(); i++){
            std::cout << path[i] << " ";
        }
        std::cout << "\n";
    }
}