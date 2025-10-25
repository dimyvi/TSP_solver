/**
 * @file main.cpp
 * @brief Главный файл программы для решения задачи коммивояжера
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "tsp_solver.h"

/**
 * @brief Читает матрицу расстояний из файла
 */
std::vector<std::vector<int>> readDistanceMatrix(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> matrix;
    
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return matrix;
    }
    
    // Читаем размерность матрицы
    int n;
    if (!(file >> n)) {
        std::cerr << "Ошибка: не удалось прочитать размерность матрицы" << std::endl;
        return matrix;
    }
    
    // Читаем саму матрицу
    for (int i = 0; i < n; i++) {
        std::vector<int> row;
        for (int j = 0; j < n; j++) {
            int value;
            if (!(file >> value)) {
                std::cerr << "Ошибка: не удалось прочитать элемент матрицы [" << i << "][" << j << "]" << std::endl;
                return matrix;
            }
            row.push_back(value);
        }
        matrix.push_back(row);
    }
    
    file.close();
    return matrix;
}

/**
 * @brief Сохраняет граф решения в файл DOT
 */
void saveSolutionToDot(const std::vector<int>& path, const std::vector<std::vector<int>>& matrix, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
        return;
    }
    
    file << "digraph TSP_Solution {" << std::endl;
    file << "    rankdir=LR;" << std::endl;
    file << "    node [shape=circle, style=filled, fillcolor=white];" << std::endl;
    file << "    edge [fontsize=10];" << std::endl;
    
    int n = matrix.size();
    
    // Добавляем узлы (города)
    for (int i = 0; i < n; i++) {
        file << "    " << i << " [label=\"" << char('A' + i) << "\"];" << std::endl;
    }
    
    // Добавляем рёбра оптимального маршрута
    for (size_t i = 0; i < path.size() - 1; i++) {
        int from = path[i];
        int to = path[i + 1];
        file << "    " << from << " -> " << to 
             << " [label=\"" << matrix[from][to] << "\", color=red, penwidth=2];" << std::endl;
    }
    
    file << "}" << std::endl;
    file.close();
}

/**
 * @brief Основная функция программы
 */
int main(int argc, char* argv[]) {
    // Проверяем аргументы командной строки
    if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <input_file> <output_file>" << std::endl;
        std::cerr << "Пример: " << argv[0] << " test1.txt result1.dot" << std::endl;
        return 1;
    }
    
    std::string input_filename = argv[1];
    std::string output_filename = argv[2];
    
    // Чтение матрицы расстояний из файла
    std::vector<std::vector<int>> distance_matrix = readDistanceMatrix(input_filename);
    
    if (distance_matrix.empty()) {
        std::cerr << "Не удалось загрузить матрицу расстояний" << std::endl;
        return 1;
    }
    
    // Создаем решатель задачи коммивояжера
    TSPSolver tsp_solver(distance_matrix);
    
    // Решаем задачу и получаем результат
    auto result = tsp_solver.solve();
    std::vector<int> path = result.first;
    int cost = result.second;
    
    // Выводим результат
    std::cout << "Рекомендуемый маршрут: ";
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << static_cast<char>('A' + path[i]);
        if (i < path.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Длинна маршрута: " << cost << std::endl;
    
    // Сохраняем граф решения в файл
    saveSolutionToDot(path, distance_matrix, output_filename);
    std::cout << "Маршрут сохранен " << output_filename << std::endl;
    
    return 0;
}