/**
 * @file tsp_solver.h
 * @brief Заголовочный файл для решения задачи коммивояжера методом ветвей и границ
 */

#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <vector>

/**
 * @brief Структура узла дерева поиска
 */
struct Node {
    int level;                      ///< Уровень узла в дереве поиска
    std::vector<int> path;          ///< Текущий частичный маршрут
    std::vector<bool> visited;      ///< Массив посещенных городов
    int bound;                      ///< Нижняя оценка стоимости
    
    /**
     * @brief Конструктор узла
     */
    Node(int l, const std::vector<int>& p, const std::vector<bool>& v, int b)
        : level(l), path(p), visited(v), bound(b) {}
    
    /**
     * @brief Оператор сравнения для приоритетной очереди
     */
    bool operator>(const Node& other) const {
        return bound > other.bound;
    }
};

/**
 * @brief Класс для решения задачи коммивояжера методом ветвей и границ
 */
class TSPSolver {
private:
    std::vector<std::vector<int>> matrix;   ///< Матрица расстояний между городами
    int n;                                  ///< Количество городов
    
    /**
     * @brief Вычисляет нижнюю границу для узла
     */
    int computeBound(const std::vector<int>& path, const std::vector<bool>& visited) const;
    
    /**
     * @brief Вычисляет стоимость полного маршрута
     */
    int computePathCost(const std::vector<int>& path) const;

public:
    /**
     * @brief Конструктор класса
     */
    TSPSolver(const std::vector<std::vector<int>>& dist_matrix);
    
    /**
     * @brief Решает задачу коммивояжера
     */
    std::pair<std::vector<int>, int> solve();
};

#endif