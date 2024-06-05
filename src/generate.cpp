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
#include "../include/printGraph.h"

int randomNumber(int x, int y)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(x, y);
    return distribution(gen);
}

void doGenerateHamilton(graph *L, int nodes, int saturation, int &cur_vertices, int &max_vertices){
    std::vector<int> cycle(nodes);
    for (int i = 0; i < nodes; ++i)
    {
        cycle[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cycle.begin(), cycle.end(), g);

    for (int i = 0; i < nodes - 1; i++)
    {
        L[cycle[i]].next.push_back(cycle[i + 1]);
        L[cycle[i + 1]].next.push_back(cycle[i]);
    }
    L[cycle[nodes - 1]].next.push_back(cycle[0]);
    L[cycle[0]].next.push_back(cycle[nodes - 1]);

    // std::cout << "\nbase cycle:\n";
    // for(int i = 0; i < nodes; i++){
    //     std::cout << cycle[i] << " ";
    // }
    // std::cout << "\n";    

    while (cur_vertices <= max_vertices - 3)
    {
        int a, b, c;
        std::vector<int> availableA, availableB, availableC;

        for (int i = 0; i < nodes; i++)
        {
            if (L[i].next.size() <= nodes - 3)
            {
                availableA.push_back(i);
            }
        }
        std::shuffle(availableA.begin(), availableA.end(), g);

        bool success = false;
        while (availableA.size() >= 3)
        {
            a = availableA[0];
            availableA.erase(availableA.begin());

            for (int i = 0; i < nodes; i++)
            {
                if ((i != a) && (std::find(L[a].next.begin(), L[a].next.end(), i) == L[a].next.end()))
                {
                    availableB.push_back(i);
                }
            }
            if (availableB.size() > 0)
            {
                std::shuffle(availableB.begin(), availableB.end(), g);
                b = availableB[0];
                for (int j = 0; j < nodes; j++)
                {
                    if ((j != a) && (j != b) && (std::find(L[a].next.begin(), L[a].next.end(), j) == L[a].next.end()) && (std::find(L[b].next.begin(), L[b].next.end(), j) == L[b].next.end()))
                    {
                        availableC.push_back(j);
                    }
                }
                if (availableC.size() > 0)
                {
                    std::shuffle(availableC.begin(), availableC.end(), g);
                    c = availableC[0];
                    success = true;
                }
            }
            if (success)
            {
                L[a].next.push_back(b);
                L[b].next.push_back(a);
                L[b].next.push_back(c);
                L[c].next.push_back(b);
                L[c].next.push_back(a);
                L[a].next.push_back(c);
                cur_vertices += 3;
                // std::cout << "\nadded small cycle:" << a << " " << b << " " << c << "\n";
                // printGraph(L, nodes);
                break;
            }
        }
        if (!success)
            break;
    }

    
}

void generateHamilton(graph *L, int nodes, int saturation)
{
    std::cout << "\nautomatic> Hamiltionian graph generation\n";

    int cur_vertices = nodes;
    int max_vertices = (((nodes * nodes) - nodes) / 2) * saturation / 100;

    doGenerateHamilton(L, nodes, saturation, cur_vertices, max_vertices);

    std::cout << "The hamiltonian graph has been generated.\n";
    std::cout << "100\% = " << (((nodes * nodes) - nodes) / 2) << "\n";
    std::cout << "max_vertices = " << max_vertices << "\n";
    std::cout << "end_vertices = " << cur_vertices << "\n";
}

void generateNonHamilton(graph *L, int nodes)
{
    int saturation = 50;
    std::cout << "\nautomatic> Non-hamiltionian graph generation\n";

    int cur_vertices = nodes;
    int max_vertices = (((nodes * nodes) - nodes) / 2) * saturation / 100;

    doGenerateHamilton(L, nodes, saturation, cur_vertices, max_vertices);

    int removed = randomNumber(0, nodes-1);

    while (L[removed].next.size() > 0){
        L[L[removed].next.front()].next.remove(removed);
        L[removed].next.pop_front();
        cur_vertices--;
    }

    std::cout << "The non-hamiltonian graph has been generated.\n";
    std::cout << "100\% = " << (((nodes * nodes) - nodes) / 2) << "\n";
    std::cout << "max_vertices = " << max_vertices << "\n";
    std::cout << "end_vertices = " << cur_vertices << "\n";
}