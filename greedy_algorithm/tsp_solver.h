// File: tsp_solver.h
#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <vector>
#include <string>

/**
 * @class TSPSolver
 * @brief Решает задачу коммивояжера с помощью жадного алгоритма
 */
class TSPSolver {
private:
    std::vector<std::vector<int>> distance_matrix;
    std::vector<int> route;
    int total_distance;

public:
    /**
     * @brief Загружает матрицу расстояний из файла
     * @param filename Имя входного файла
     * @return true если успешно, false в противном случае
     */
    bool LoadMatrixFromFile(const std::string& filename);
    
    /**
     * @brief Решает задачу коммивояжера жадным алгоритмом
     */
    void SolveGreedyTSP();
    
    /**
     * @brief Сохраняет решение в виде файла Graphviz
     * @param filename Имя выходного файла
     * @return true если успешно, false в противном случае
     */
    bool SaveGraphToFile(const std::string& filename) const;
    
    /**
     * @brief Выводит решение в консоль
     */
    void PrintSolution() const;

private:
    /**
     * @brief Преобразует индекс города в название
     * @param index Индекс города
     * @return Название города в виде строки
     */
    std::string GetCityName(int index) const;
};

#endif