#include <iostream>
#include <sstream>
#include <limits>

#include "../include/generate.h"
#include "../include/actions.h"
#include "../include/structList.h"

void ifCorrectArgs(int argc, char *argv[], std::string &type) {
    if (argc <= 1) {
        std::cout << "No arguments given.\n";
        exit(0);
    }
    type = std::string(argv[1]);

    if (type != "--hamilton" && type != "--non-hamilton") {
        std::cout << "Wrong arguments\n";
        exit(0);
    }
}

void ifCorrectInput(std::string line) {
    for (int j = 0; j < line.size(); j++) {
            if (line[j] != ' ') {
                if (!((line[j] >= '0' && line[j] <= '9') || line[j] == ' ')) {
                    std::cout << "Wrong type of data.\nExiting the program...\n";
                    exit(0);
                }
            }
        }
}

int main(int argc, char *argv[]) {

    std::string type;
    ifCorrectArgs(argc, argv, type);
    std::cout << "type:" << type << "\n";
    std::string line;
    int to;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    graph *L;
    int nodes, saturation;
    getline(std::cin, line);
    ifCorrectInput(line);
    std::stringstream inputStream(line);
    if (type == "--hamilton") {
        inputStream >> nodes >> saturation;
        if (saturation != 30 && saturation != 70) {
            std::cout << "Error: Saturation must be 30 or 70.\nExiting the program...\n";
            exit(0);
        }
        if (nodes < 11) {
            std::cout << "Error: Number of nodes must be greater than 10.\nExiting the program...\n";
            exit(0);
        }
        std::cout << "nodes>" << nodes << "\n" << "saturation>" << saturation << "\n";
        L = new graph[nodes];
        generateHamilton(L, nodes, saturation);
    }
    else {
        inputStream >> nodes;
        std::cout << "nodes>" << nodes << "\n";
        L = new graph[nodes];
        generateNonHamilton(L, nodes);
    }

    actions(L, type, nodes);
    delete[] L;
    return 0;
}