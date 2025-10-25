g++ -std=c++11 -o tsp_solver main.cpp tsp_solver.cpp

./tsp_solver test1.txt result1.dot
./tsp_solver test2.txt result2.dot  
./tsp_solver test3.txt result3.dot

dot -Tpng result1.dot -o graph1.png
dot -Tpng result2.dot -o graph2.png
dot -Tpng result3.dot -o graph3.png
