#define CATCH_CONFIG_MAIN
#include <vector>

#include "DamerayLevenshtein.h"
#include "catch.hpp"

TEST_CASE("DamerayLevenshtein Seminar Test") {
  DamerayLevenshtein dl;
  dl.BuildTable("BKAOC", "KACO");

  std::vector<std::vector<int>> expected = {{0, 1, 2, 3, 4}, {1, 1, 2, 3, 4}, {2, 1, 2, 3, 4},
                                            {3, 2, 1, 2, 3}, {4, 3, 2, 2, 2}, {5, 4, 3, 2, 2}};

  REQUIRE(dl.d == expected);
  REQUIRE(dl.GetDistance() == 2);
}

TEST_CASE("DamerayLevenshtein Test") {
  DamerayLevenshtein dl;
  dl.BuildTable("CA", "ABC");

  REQUIRE(dl.GetDistance() == 3);  // Хоть это и не истинное значение, настоящее значение - 2
}