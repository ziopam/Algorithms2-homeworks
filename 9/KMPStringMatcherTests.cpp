#define CATCH_CONFIG_MAIN
#include "KMPStringMatcher.h"
#include "catch.hpp"

TEST_CASE("CountPatternOccurrences correctly counts pattern occurrences") {
  KMPStringMatcher kmp;

  SECTION("Basic pattern matching") {
    REQUIRE(kmp.CountPatternOccurrences("HSE", "HSE") == 1);
    REQUIRE(kmp.CountPatternOccurrences("HSEHSE", "HSE") == 2);
    REQUIRE(kmp.CountPatternOccurrences("HSEHSEHSE", "HSE") == 3);
  }

  SECTION("Overlapping patterns") {
    REQUIRE(kmp.CountPatternOccurrences("HSEHSEH", "HSEH") == 2);
    REQUIRE(kmp.CountPatternOccurrences("SEHESE", "SEHE") == 1);
  }

  SECTION("Pattern not found") {
    REQUIRE(kmp.CountPatternOccurrences("HSE", "EHS") == 0);
    REQUIRE(kmp.CountPatternOccurrences("HHSSEE", "HSH") == 0);
    REQUIRE(kmp.CountPatternOccurrences("", "HSE") == 0);
  }

  SECTION("Complex patterns") {
    REQUIRE(kmp.CountPatternOccurrences("HSEHHSEHSEHS", "HSEH") == 3);
    REQUIRE(kmp.CountPatternOccurrences("HSEHHSEHSEHS", "HSEHS") == 2);
    REQUIRE(kmp.CountPatternOccurrences("ESHESHESHE", "SHE") == 3);
  }

  SECTION("Patterns with repetitions") {
    REQUIRE(kmp.CountPatternOccurrences("HHHSSS", "HS") == 1);
    REQUIRE(kmp.CountPatternOccurrences("HHHSSS", "HSS") == 1);
    REQUIRE(kmp.CountPatternOccurrences("HHHSSSEHSSEE", "HSSSE") == 1);
  }

  SECTION("Long text with multiple occurrences") {
    REQUIRE(kmp.CountPatternOccurrences("HSEHSEHSEHSEHSEHSEHSEHSEHSE", "HSE") == 9);
    REQUIRE(kmp.CountPatternOccurrences("HSEHSEHSEHSEHSEHSEHSEHSEHSE", "HSEHSE") == 8);
  }

  SECTION("Case with characters outside of HSE") {
    REQUIRE(kmp.CountPatternOccurrences("HSABCHSE", "HSE") == 1);
    REQUIRE(kmp.CountPatternOccurrences("HS123ESE", "HSE") == 0);
  }
}
