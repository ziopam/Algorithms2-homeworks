#define CATCH_CONFIG_MAIN
#include "SkipList.h"
#include "catch.hpp"

TEST_CASE("SkipList") {
  SkipList<3> list;
  list.Insert(1);
  list.Insert(2);
  list.Insert(6);
  list.Insert(-5);
  list.Insert(3);
  list.Insert(4);
  list.Insert(5);
  list.Insert(-10);

  // Check that all elements are in the list
  REQUIRE(list.Search(1)->value == 1);
  REQUIRE(list.Search(2)->value == 2);
  REQUIRE(list.Search(6)->value == 6);
  REQUIRE(list.Search(-5)->value == -5);
  REQUIRE(list.Search(3)->value == 3);
  REQUIRE(list.Search(4)->value == 4);
  REQUIRE(list.Search(5)->value == 5);
  REQUIRE(list.Search(-10)->value == -10);

  // Check elements that are not in the list
  REQUIRE(list.Search(0) == nullptr);
  REQUIRE(list.Search(7) == nullptr);
  REQUIRE(list.Search(-11) == nullptr);
  REQUIRE(list.Search(100) == nullptr);
  REQUIRE(list.Search(-100) == nullptr);
  REQUIRE(list.Search(8) == nullptr);
  REQUIRE(list.Search(-9) == nullptr);
  REQUIRE(list.Search(10) == nullptr);
  REQUIRE(list.Search(-12) == nullptr);

  // Check removed elements
  list.Remove(4);
  REQUIRE(list.Search(4) == nullptr);

  // Check that the rest of the elements are still in the list
  REQUIRE(list.Search(1)->value == 1);
  REQUIRE(list.Search(2)->value == 2);
  REQUIRE(list.Search(6)->value == 6);
  REQUIRE(list.Search(-5)->value == -5);
  REQUIRE(list.Search(3)->value == 3);
  REQUIRE(list.Search(5)->value == 5);
  REQUIRE(list.Search(-10)->value == -10);
}