#include <iostream>
#include <sstream>
#include <limits>

#include "../include/printGraph.h";
#include "../include/euler.h";
#include "../include/hamilton.h";

void actions(graph *L, std::string type, int nodes) { //jakas reprezentacje trzeba wybrac
    std::cout << "Actions\n";
    std::string message = "Help\t\tShow this message.\nPrint\t\tPrint the graph (_ representation).\nFindEuler\t\t\nFindHamilton\t\t"; //dopisac helpa
    std::string action;
    while (std::cin) {
        std::cin >> action;
        if (action != "") {
            std::cout << "action> " << action << "\n";
        }
        else if (action == "Print") {
            printGraph(L, nodes);
        }
        else if (action == "FindEuler" and type == "--hamilton") {
            findEuler(L, nodes);
        }
        else if (action == "FindHamilton") {
            findHamilton(L, nodes);
        }
        else if (action == "Exit") {
            std::cout << "Exiting the program...\n";
            break;
        }
        else if (action == "") {
            std::cout << "End of file.\nExiting the program...\n";
            break;
        }
        else
            std::cout << "\nWrong command\n";
        /*w*/
        action = "";
    }
}