#include <iostream>
#include <sstream>
#include <limits>

#include "../include/generate.h"
#include "../include/actions.h"

void ifCorrectArgs(int argc, std::string type) {
    if (argc <= 1) {
        std::cout << "No arguments given\n";
        exit(0);
    }

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

    std::string type = std::string(argv[1]);
    ifCorrectArgs(argc, type);

    std::string line;
    int to;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int nodes, saturation;
    getline(std::cin, line);
    std::stringstream inputStream(line);
    ifCorrectInput(line);
    if (type == "--hamilton") {
        inputStream >> nodes >> saturation;
        if (saturation != 30 || saturation != 70) {
            std::cout << "Error: Saturation must be 30 or 70.\nExiting the program...\n";
        }
        if (nodes < 10) {
            std::cout << "Error: Number of nodes must be greater than 10.\nExiting the program...\n";
        }
        generateHamilton(nodes, saturation);
    }
    else {
        inputStream >> nodes;
        generateNonHamilton(nodes, 50);
    }

    actions();
    return 0;
}