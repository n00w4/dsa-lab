
#include "../../stack/stack.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */


void StackFactorial(uint &loctest, uint &testerr, const uint N, uint val, lasd::Stack<int> &s){
  bool tst;
  loctest++;
  std::cout << "Test " << loctest << ": Checking the factorial of " << N << "... ";
  s.Clear();
  uint result = 1;
  uint tstval = N;
  while(tstval > 0 || !(s.Empty())) {
     if(tstval > 0) {
         s.Push(tstval);
         tstval--;
      } else {
         result *= s.Top();
         s.Pop();
      }
  }
  std::cout << "The factorial of " << N << " is " << result << ": ";
  tst = (result == val);
  std::cout << ((tst) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

void mytest() {
  // ...
}
