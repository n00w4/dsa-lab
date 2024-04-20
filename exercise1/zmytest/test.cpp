
#include "exercise1/vector/vector.hpp"
#include "exercise1/stack/stack.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

void StackFactorial(uint &loctest, uint &testerr, const uint N, uint val, lasd::Stack<int> &s) {
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

bool IsSortedInt(lasd::SortableVector<int> &sv) {
  bool tst = true;
  for(uint i = 0; i < sv.Size() - 1; i++) {
    if(sv[i] > sv[i + 1]) {
      tst = false;
      break;
    }
  }
  return tst;
}

void SortVector(uint &loctest, uint &testerr, lasd::SortableVector<int> &sv) {
  bool tst;
  loctest++;
  std::cout << "Test " << loctest << ": Sorting the vector... ";
  sv.Sort();
  std::cout << "The vector is sorted: ";
  tst = IsSortedInt(sv);
  std::cout << ((tst) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

void mytest() {
  // ...
}
