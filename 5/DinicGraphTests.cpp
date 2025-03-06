#define CATCH_CONFIG_MAIN
#include "DinicGraph.h"
#include "catch.hpp"

TEST_CASE("DinicGraph") {
  DinicGraph g(11);
  g.AddEdge(0, 1, 5);
  g.AddEdge(0, 2, 10);
  g.AddEdge(0, 3, 15);
  g.AddEdge(1, 4, 10);
  g.AddEdge(2, 1, 15);
  g.AddEdge(2, 5, 20);
  g.AddEdge(3, 6, 25);
  g.AddEdge(4, 7, 10);
  g.AddEdge(4, 5, 25);
  g.AddEdge(5, 8, 30);
  g.AddEdge(5, 3, 5);
  g.AddEdge(6, 8, 20);
  g.AddEdge(6, 9, 10);
  g.AddEdge(7, 10, 5);
  g.AddEdge(8, 10, 15);
  g.AddEdge(8, 9, 15);
  g.AddEdge(9, 10, 10);

  REQUIRE(g.DinicMaxFlow(0, 10) == 30);
}