#include <iostream>
#include <sstream>
#include <limits>
#include <chrono>

#include "../include/printGraph.h"
#include "../include/euler.h"
#include "../include/hamilton.h"

void actions(graph *L, std::string type, int nodes)
{
    std::cout << "\nActions\nEnter the action:";
    std::string message = "Help\t\tShow this message.\nPrint\t\tPrint the graph (_ representation).\nFindEuler\t\t\nFindHamilton\t\t"; // dopisac helpa
    std::string action;
    while (std::cin)
    {
        std::cout << "\n";
        std::cin >> action;
        if (action != "")
        {
            std::cout << "\naction> " << action << "\n";
        }
        if (action == "Help")
        {
            std::cout << message;
        }
        else if (action == "Print")
        {
            printGraph(L, nodes);
        }
        else if (action == "FindEuler")
        {
            findEuler(L, nodes);
        }
        else if (action == "FindHamilton")
        {
            findHamilton(L, nodes);
        }
        else if (action == "Exit")
        {
            std::cout << "Exiting the program...\n";
            break;
        }
        else if (action == "")
        {
            std::cout << "End of file.\nExiting the program...\n";
            break;
        }
        else
            std::cout << "\nWrong command\n";

        action = "";
        std::cout << "\nEnter the action:";
    }
}