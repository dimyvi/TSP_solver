// File: tsp_solver.cpp
#include "tsp_solver.h"
#include <iostream>
#include <fstream>
#include <climits>

bool TSPSolver::LoadMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Невозможно открыть файл " << filename << std::endl;
        return false;
    }

    int n;
    file >> n;
    
    distance_matrix.resize(n, std::vector<int>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> distance_matrix[i][j];
        }
    }
    
    file.close();
    return true;
}

void TSPSolver::SolveGreedyTSP() {
    int n = distance_matrix.size();
    std::vector<bool> visited(n, false);
    route.clear();
    total_distance = 0;
    
    int current = 0;
    visited[current] = true;
    route.push_back(current);

    for (int i = 1; i < n; ++i) {
        int nearest = -1;
        int min_dist = INT_MAX;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && distance_matrix[current][j] < min_dist) {
                min_dist = distance_matrix[current][j];
                nearest = j;
            }
        }

        route.push_back(nearest);
        visited[nearest] = true;
        total_distance += min_dist;
        current = nearest;
    }

    total_distance += distance_matrix[current][route[0]];
    route.push_back(route[0]);
}

bool TSPSolver::SaveGraphToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Невозможно создать файл " << filename << std::endl;
        return false;
    }

    file << "digraph TravelingSalesman {" << std::endl;
    file << "    rankdir=LR;" << std::endl;
    file << "    node [shape=circle];" << std::endl;
    
    for (size_t i = 0; i < route.size() - 1; ++i) {
        int from = route[i];
        int to = route[i + 1];
        int dist = distance_matrix[from][to];
        
        file << "    " << GetCityName(from) << " -> " << GetCityName(to);
        file << " [label=\"" << dist << "\", color=red, penwidth=2.0];" << std::endl;
    }
    
    file << "}" << std::endl;
    file.close();
    return true;
}

void TSPSolver::PrintSolution() const {
    std::cout << "Рекомендуемый маршрут: ";
    for (int city : route) {
        std::cout << GetCityName(city) << " ";
    }
    std::cout << std::endl;
    std::cout << "Общяя дистанция: " << total_distance << std::endl;
}

std::string TSPSolver::GetCityName(int index) const {
    return std::string(1, 'A' + index);
}