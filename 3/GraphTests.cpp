#define CATCH_CONFIG_MAIN
#include <vector>

#include "Graph.h"
#include "catch.hpp"

TEST_CASE("DFS") {
  Graph g(8);
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  g.AddEdge(1, 2);
  g.AddEdge(2, 3);
  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(4, 7);
  g.AddEdge(5, 6);
  g.AddEdge(6, 4);
  g.AddEdge(7, 6);

  g.DFS(2);
  REQUIRE(g.path == std::vector<int>{2, 0, 1, 3, 4, 5, 6, 7});
}

TEST_CASE("IsConnected") {

  SECTION("CONNECTED") {
    Graph g(8);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);
    g.AddEdge(4, 7);
    g.AddEdge(5, 6);
    g.AddEdge(6, 4);
    g.AddEdge(7, 6);

    REQUIRE(g.IsConnected());
  }

  SECTION("DISCONNECTED") {
    Graph g(8);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    // g.AddEdge(3, 4);  Разорвем связь между 3 и 4
    g.AddEdge(4, 5);
    g.AddEdge(4, 7);
    g.AddEdge(5, 6);
    g.AddEdge(6, 4);
    g.AddEdge(7, 6);

    REQUIRE(!g.IsConnected());
  }
}

TEST_CASE("CountOddDegrees") {
  Graph g(8);
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  g.AddEdge(1, 2);
  g.AddEdge(2, 3);
  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(4, 7);
  g.AddEdge(5, 6);
  g.AddEdge(6, 4);
  g.AddEdge(7, 6);

  REQUIRE(g.CountOddDegrees() == 2);
}

TEST_CASE("IsEulerian") {
  SECTION("EULERIAN (TWO VERTICES WITH ODD DEGREE)") {
    Graph g(8);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);
    g.AddEdge(4, 7);
    g.AddEdge(5, 6);
    g.AddEdge(6, 4);
    g.AddEdge(7, 6);

    REQUIRE(g.IsEulerian());
  }

  SECTION("EULERIAN (NO VERTICES WITH ODD DEGREE)") {
    Graph g(3);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(1, 2);

    REQUIRE(g.IsEulerian());
  }

  SECTION("NOT EULERIAN (DISCONNECTED)") {
    Graph g(8);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    // g.AddEdge(3, 4);  Разорвем связь между 3 и 4
    g.AddEdge(4, 5);
    g.AddEdge(4, 7);
    g.AddEdge(5, 6);
    g.AddEdge(6, 4);
    g.AddEdge(7, 6);

    REQUIRE(!g.IsEulerian());
  }

  SECTION("NOT EULERIAN") {
    Graph g(8);
    g.AddEdge(0, 1);
    // g.AddEdge(0, 2); Разорвем связь между 0 и 2
    g.AddEdge(1, 2);
    g.AddEdge(2, 3);
    // g.AddEdge(3, 4);  Разорвем связь между 3 и 4
    g.AddEdge(4, 5);
    g.AddEdge(4, 7);
    g.AddEdge(5, 6);
    g.AddEdge(6, 4);
    g.AddEdge(7, 6);

    REQUIRE(!g.IsEulerian());
  }
}