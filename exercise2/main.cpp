
#include "zlasdtest/test.hpp"

#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2024" << std::endl;
  std::cout << "Choose a test" << std::endl;
  std::cout << "[1] Prof Tests" << std::endl;
  std::cout << "[2] My Test" << std::endl;
  short choice = 0;
  std::cin >> choice;
  switch (choice) {
  case 1:
    lasdtest();
    break;
  
  case 2:
    mytest();
    break;
  
  default:
    break;
  }
  return 0;
}
