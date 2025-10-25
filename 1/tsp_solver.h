// File: tsp_solver.h
#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <vector>
#include <string>

/**
 * @class TSPSolver
 * @brief Solves Traveling Salesman Problem using greedy algorithm
 */
class TSPSolver {
private:
    std::vector<std::vector<int>> distance_matrix;
    std::vector<int> route;
    int total_distance;

public:
    /**
     * @brief Load distance matrix from file
     * @param filename Input file name
     * @return true if successful, false otherwise
     */
    bool LoadMatrixFromFile(const std::string& filename);
    
    /**
     * @brief Solve TSP using greedy algorithm
     */
    void SolveGreedyTSP();
    
    /**
     * @brief Save solution as Graphviz file
     * @param filename Output file name
     * @return true if successful, false otherwise
     */
    bool SaveGraphToFile(const std::string& filename) const;
    
    /**
     * @brief Print solution to console
     */
    void PrintSolution() const;

private:
    /**
     * @brief Convert city index to name
     * @param index City index
     * @return City name as string
     */
    std::string GetCityName(int index) const;
};

#endif