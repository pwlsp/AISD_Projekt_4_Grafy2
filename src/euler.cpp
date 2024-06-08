#include <iostream>
#include <sstream>
#include <limits>
#include <stack>
#include <chrono>

#include "../include/structList.h"

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

void eulerGo(graph *L_copy, int V, int *visited, std::stack<int> &resultStack, bool **visitedEdges) {
    int U;
    visited[V] = 1;
    std::list<int>::iterator i;
    for (i = L_copy[V].next.begin(); i != L_copy[V].next.end(); i++) {
        if (!visitedEdges[V][*i]) {
            visitedEdges[V][*i] = 1;
            eulerGo(L_copy, *i, visited, resultStack, visitedEdges);
        }
    }
    resultStack.push(V);
}

void displayResult(std::stack<int> &resultStack) {
    while (!resultStack.empty()) {
        std::cout << resultStack.top() << " ";
        resultStack.pop();
    }
    std::cout << "\nThe eulerian cycle found successfully\n";
}

void eulerAlgorithm(graph *L, int nodes) {
    bool **visitedEdges;
    visitedEdges = new bool *[nodes];
    for (int i = 0; i < nodes; i++) {
        visitedEdges[i] = new bool[nodes];
    }
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            visitedEdges[i][j] = 0;
        }
    }
    int *visited;
    visited = new int[nodes];
    for (int i = 0; i < nodes; i++) {
        visited[i] = 0;
    }
    graph *L_copy;
    L_copy = new graph[nodes];
    for (int i = 0; i < nodes; i++) {
        for (std::list<int>::iterator it = L[i].next.begin(); it != L[i].next.end(); it++) {
            L_copy[i].next.push_back(*it);
        }
    }

    std::stack<int> resultStack;
    for (int i = 0; i < nodes; i++) {
        if (visited[i] != 1) {
            eulerGo(L_copy, i, visited, resultStack, visitedEdges);
        }
    }

    displayResult(resultStack);

    for (int i = 0; i < nodes; i++) 
        delete[] visitedEdges[i];
    delete[] visitedEdges; 
}

void findEuler(graph *L, int nodes) {
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, stopTime;
    startTime = std::chrono::high_resolution_clock::now();

    if (ifEuler(L, nodes)) {
        eulerAlgorithm(L, nodes);
    }
    else {
        std::cout << "The graph is not an eulerian graph. The eulerian cycle doesn't exist.\n";
    }

    stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);
    std::cout << "Time: " << duration.count() << "\n";
}