// File: main.cpp
#include "tsp_solver.h"
#include <iostream>

/**
 * @brief Главная функция для решения задачи коммивояжера
 * @param argc Количество аргументов
 * @param argv Значения аргументов
 * @return Статус выхода из программы
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <входной_файл> <выходной_файл>" << std::endl;
        std::cerr << "Пример: " << argv[0] << " input.txt output.dot" << std::endl;
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
    
    std::cout << "Граф сохранен в файл " << output_file << std::endl;
    
    return 0;
}