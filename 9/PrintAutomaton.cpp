#include <iostream>
#include <string>

#include "KMPStringMatcher.h"

int main() {
  KMPStringMatcher kmp;
  std::string pattern = "HEHSEHE";
  std::string text = "HSEHSEHSEHSEHSE";
  auto automaton = kmp.BuildKmpAutomaton(pattern);
  kmp.PrintAutomaton(automaton);
  return 0;
}