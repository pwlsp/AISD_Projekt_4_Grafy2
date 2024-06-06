#include <iostream>
#include <sstream>
#include <limits>
#include <stack>

#include "../include/structList.h"

bool vis[512][512];

bool ifEuler(graph *L, int nodes) {
    int count;
    for (int i = 0; i < nodes; i++) {
        count = 0;
        for (std::list<int>::iterator it = L[i].next.begin(); it != L[i].next.end(); it++) {
            count++;
        }
        if (count % 2 != 0) {
            return false;
        }
    }
    return true;
}

void eulerGo(graph *L_copy, int V, int *visited, std::stack <int> &resultStack) {
    int U;
    visited[V] = 1;
    std::cout << "spr:" << V << "\n";
    std::list<int>::iterator i;
    for(i = L_copy[V].next.begin(); i != L_copy[V].next.end(); i++){
        if(!vis[V][*i]){
            vis[V][*i] = 1;
            eulerGo(L_copy, *i, visited, resultStack);
        }
    }
    // while (!L_copy[V].next.empty()){
    //         U = L_copy[V].next.front();
    //         if(!vis[V][U]) vis[V][U]
            // L_copy[V].next.pop_front();
            // std::list<int>::iterator i;
            // for (i = L_copy[U].next.begin(); i != L_copy[U].next.end(); i++) {
            //     if (*i == V) {
            //         break;
            //     }
            // }
            // L_copy[U].next.erase(i);
            // eulerGo(L_copy, U, visited, resultStack);
    //}
    resultStack.push(V);
}

void displayResult(std::stack <int> &resultStack) {
    while (!resultStack.empty()) {
        std::cout << resultStack.top() << " ";
        resultStack.pop();
    }
    std::cout << "\nThe eulerian cycle found successfully\n";
}

void eulerAlgorithm(graph *L, int nodes) {
    for(int i = 0; i < 512; i++) for(int j = 0; j < 512; j++) vis[i][j] = 0;
    int *visited; visited = new int[nodes];
    for (int i = 0; i < nodes; i++) {
        visited[i] = 0;
    }
    graph *L_copy; L_copy = new graph[nodes];
    for (int i = 0; i < nodes; i++) {
        for (std::list<int>::iterator it = L[i].next.begin(); it != L[i].next.end(); it++) {
            L_copy[i].next.push_back(*it);
        }
    }
    
    std::stack <int> resultStack;
    for (int i = 0; i < nodes; i++) {
        if(visited[i] != 1) {
            eulerGo(L_copy, i, visited, resultStack);
        }
    }

    displayResult(resultStack);
}

void user_provided_list(graph *L, int vertices)
{
    std::string line;
    int to;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < vertices; i++)
    {
        getline(std::cin, line);
        //std::cout << "i: " << i << "\n";
        std::stringstream is(line);
        if (line != "")
        {
            for (int j = 0; j < line.size(); j++)
            {
                if (!((line[j] >= '0' && line[j] <= '9') || line[j] == ' '))
                {
                    
                    std::cout << "Wrong type of data.\nExiting the program...\n";
                    exit(0);
                }
            }
            while (is >> to){
                if(to >= vertices){
                    std::cout << "Given vertex \"" << to << "\" is out of range.\nExiting the program...\n";
                    exit(0);
                }
                L[i].next.push_back(to);
            }
        }
    }
}

void findEuler(graph *L, int nodes) {
    std::cout << nodes << "\n";
    //user_provided_list(L,nodes);

    if (ifEuler(L, nodes)) {
        eulerAlgorithm(L, nodes);
    }
    else {
        std::cout << "The graph is not an eulerian graph. The euler cycle doesn't exist.\n";
    }
}