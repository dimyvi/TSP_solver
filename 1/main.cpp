// File: main.cpp
#include "tsp_solver.h"
#include <iostream>

/**
 * @brief Main function for TSP solver
 * @param argc Argument count
 * @param argv Argument values
 * @return Program exit status
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        std::cerr << "Example: " << argv[0] << " input.txt output.dot" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    TSPSolver solver;
    
    if (!solver.LoadMatrixFromFile(input_file)) {
        return 1;
    }
    
    solver.SolveGreedyTSP();
    solver.PrintSolution();
    
    if (!solver.SaveGraphToFile(output_file)) {
        return 1;
    }
    
    std::cout << "Граф сохранен " << output_file << std::endl;
    
    return 0;
}