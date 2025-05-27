#define CATCH_CONFIG_MAIN
#include "Backpack.h"
#include "catch.hpp"

TEST_CASE("Basic knapsack test") {
  Backpack bp(10, 10);
  bp.Add(2, 3, 5);  // weight, volume, value
  bp.Add(4, 2, 7);
  bp.Add(3, 4, 10);
  bp.Add(5, 5, 15);

  REQUIRE(bp.Solve() == 25);

  std::vector<int> selected = bp.GetSelectedItems();
  REQUIRE(selected.size() == 2);
  REQUIRE(selected[0] == 2);
  REQUIRE(selected[1] == 3);
}

TEST_CASE("No items test") {
  Backpack bp(10, 10);
  REQUIRE(bp.Solve() == 0);

  std::vector<int> selected = bp.GetSelectedItems();
  REQUIRE(selected.empty());
}

TEST_CASE("Weight only") {
  Backpack bp(15, 0);

  bp.Add(3, 0, 3);
  bp.Add(3, 0, 3);
  bp.Add(4, 0, 5);
  bp.Add(5, 0, 2);
  bp.Add(3, 0, 2);
  bp.Add(2, 0, 4);
  bp.Add(3, 0, 5);

  REQUIRE(bp.Solve() == 20);

  std::vector<int> selected = bp.GetSelectedItems();
  REQUIRE(selected.size() == 5);
  REQUIRE(selected[0] == 0);
  REQUIRE(selected[1] == 1);
  REQUIRE(selected[2] == 2);
  REQUIRE(selected[3] == 5);
  REQUIRE(selected[4] == 6);
}

TEST_CASE("Volume only") {
  Backpack bp(0, 15);

  bp.Add(0, 3, 3);
  bp.Add(0, 3, 3);
  bp.Add(0, 4, 5);
  bp.Add(0, 5, 2);
  bp.Add(0, 3, 2);
  bp.Add(0, 2, 4);
  bp.Add(0, 3, 5);

  REQUIRE(bp.Solve() == 20);

  std::vector<int> selected = bp.GetSelectedItems();
  REQUIRE(selected.size() == 5);
  REQUIRE(selected[0] == 0);
  REQUIRE(selected[1] == 1);
  REQUIRE(selected[2] == 2);
  REQUIRE(selected[3] == 5);
  REQUIRE(selected[4] == 6);
}
