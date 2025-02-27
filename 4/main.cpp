#include <cmath>
#include <iostream>
#include <vector>

#include "Graph.h"

void PrintPath(const std::vector<int>& path) {
  for (int node : path)
    std::cout << node << " ";
  std::cout << "\n";
}

int main() {
  Graph g(8);

  g.heuristic[0][7] = 17;
  g.heuristic[1][7] = 10;
  g.heuristic[2][7] = 13;
  g.heuristic[3][7] = 4;
  g.heuristic[4][7] = 4;
  g.heuristic[5][7] = 2;
  g.heuristic[6][7] = 1;

  g.AddEdge(0, 1, 6);
  g.AddEdge(0, 2, 5);
  g.AddEdge(0, 3, 10);
  g.AddEdge(1, 4, 6);
  g.AddEdge(2, 4, 6);
  g.AddEdge(2, 5, 7);
  g.AddEdge(3, 5, 6);
  g.AddEdge(4, 6, 4);
  g.AddEdge(5, 6, 6);
  g.AddEdge(6, 7, 3);

  int ch_d = 0;
  int ch_a = 0;
  std::vector<int> path_dijkstra = g.Dijkstra(0, 7, ch_d);
  std::vector<int> path_A_Star = g.AStar(0, 7, ch_a);

  std::cout << "Dijkstra path: ";
  PrintPath(path_dijkstra);
  std::cout << "Nodes checked: " << ch_d << "\n";

  std::cout << "A* path: ";
  PrintPath(path_A_Star);
  std::cout << "Nodes checked: " << ch_a << "\n";

  // second
  std::cout << "\n----------------\n\n";

  g = Graph(10);

  g.heuristic[0][9] = 9;
  g.heuristic[1][9] = 60;
  g.heuristic[2][9] = 60;
  g.heuristic[3][9] = 4;
  g.heuristic[4][9] = 60;
  g.heuristic[5][9] = 60;
  g.heuristic[6][9] = 3;
  g.heuristic[7][9] = 50;
  g.heuristic[8][9] = 20;
  g.heuristic[9][9] = 0;

  // Плохие ветки:
  g.AddEdge(0, 1, 1);
  g.AddEdge(1, 7, 50);

  g.AddEdge(0, 2, 1);
  g.AddEdge(2, 7, 50);

  g.AddEdge(0, 4, 1);
  g.AddEdge(4, 7, 50);

  g.AddEdge(0, 5, 1);
  g.AddEdge(5, 7, 50);

  // Альтернативный путь:
  g.AddEdge(0, 8, 10);
  g.AddEdge(8, 9, 10);

  // Оптимальный путь:
  g.AddEdge(0, 3, 3);
  g.AddEdge(3, 6, 3);
  g.AddEdge(6, 9, 3);

  ch_d = 0;
  ch_a = 0;
  path_dijkstra = g.Dijkstra(0, 9, ch_d);
  path_A_Star = g.AStar(0, 9, ch_a);

  std::cout << "Dijkstra path: ";
  PrintPath(path_dijkstra);
  std::cout << "Nodes checked (Dijkstra): " << ch_d << "\n";

  std::cout << "A* path: ";
  PrintPath(path_A_Star);
  std::cout << "Nodes checked (A*): " << ch_a << "\n";
}