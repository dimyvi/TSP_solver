/**
 * @file tsp_solver.cpp
 * @brief Реализация алгоритма решения задачи коммивояжера методом ветвей и границ
 */

#include "tsp_solver.h"
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

TSPSolver::TSPSolver(const std::vector<std::vector<int>>& dist_matrix) 
    : matrix(dist_matrix), n(dist_matrix.size()) {}

int TSPSolver::computeBound(const std::vector<int>& path, const std::vector<bool>& visited) const {
    int bound = 0;
    
    for (size_t i = 0; i < path.size() - 1; i++) {
        bound += matrix[path[i]][path[i + 1]];
    }

    if (!path.empty()) {
        int current_city = path.back();
        int min_edge = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && matrix[current_city][i] < min_edge) {
                min_edge = matrix[current_city][i];
            }
        }
        if (min_edge != INT_MAX) {
            bound += min_edge;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int min_out = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (j == 0 || !visited[j] || j == path[0]) {
                    if (matrix[i][j] < min_out) {
                        min_out = matrix[i][j];
                    }
                }
            }
            if (min_out != INT_MAX) {
                bound += min_out;
            }
        }
    }
    
    return bound;
}

int TSPSolver::computePathCost(const std::vector<int>& path) const {
    int cost = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path.back()][path[0]];
    return cost;
}

std::pair<std::vector<int>, int> TSPSolver::solve() {
    std::vector<int> best_path;
    int best_cost = INT_MAX;

    auto cmp = [](const Node& a, const Node& b) { return a.bound > b.bound; };
    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> active_nodes(cmp);

    std::vector<int> start_path = {0};
    std::vector<bool> visited(n, false);
    visited[0] = true;
    int start_bound = computeBound(start_path, visited);
    
    active_nodes.push(Node(0, start_path, visited, start_bound));

    while (!active_nodes.empty()) {
        Node current_node = active_nodes.top();
        active_nodes.pop();

        if (current_node.bound >= best_cost) {
            continue;
        }

        if (current_node.level == n - 1) {
            std::vector<int> complete_path = current_node.path;
            complete_path.push_back(complete_path[0]);
            int path_cost = computePathCost(complete_path);
            
            if (path_cost < best_cost) {
                best_cost = path_cost;
                best_path = complete_path;
            }
            continue;
        }

        for (int i = 0; i < n; i++) {
            if (!current_node.visited[i]) {
                std::vector<int> new_path = current_node.path;
                new_path.push_back(i);
                
                std::vector<bool> new_visited = current_node.visited;
                new_visited[i] = true;
                
                int new_level = current_node.level + 1;
                int new_bound = computeBound(new_path, new_visited);

                if (new_bound < best_cost) {
                    active_nodes.push(Node(new_level, new_path, new_visited, new_bound));
                }
            }
        }
    }
    
    return std::make_pair(best_path, best_cost);
}