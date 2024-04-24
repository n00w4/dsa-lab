
#include <iostream>

#include <random>
#include <chrono> // for time measurements

// Vector
#include "../vector/vector.hpp"

// List
#include "../list/list.hpp"

// Stack
#include "../stack/stack.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"

// Queue
#include "../queue/queue.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

// Useful functions from zlasdtest
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/dictionary.hpp"


/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

// Functions that can help

// Puts random integers in the vector
void RandomIntVector(lasd::LinearContainer<int> &lc) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<int> dist(-100000, 100000);
  std::cout << "Populating the vector... " << endl;
  std::chrono::steady_clock::time_point begin = std::chrono::_V2::steady_clock::now();
  for (uint i = 0; i < lc.Size(); i++) {
    lc[i] = dist(gen);
  }
  std::chrono::steady_clock::time_point end = std::chrono::_V2::steady_clock::now();
  std::cout << "Vector populated randomly in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << endl;
}

// Resizes a vector with a random size vector with random data
void RandomIntNSizeVector(lasd::Vector<int> &lc) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<uint> dist(1, 10000);
  uint size = dist(gen);
  std::cout << "Resizing the vector... " << endl;
  lc.Resize(size);
  std::cout << "Vector resized with size " << size << endl;
  RandomIntVector(lc);
}

// Puts random integers in the list
void RandomIntList (lasd::List<int> &lc, uint size) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<int> dist(-100000, 100000);
  std::cout << "Populating the list... " << endl;
  std::chrono::steady_clock::time_point begin = std::chrono::_V2::steady_clock::now();
  for (uint i = 0; i < size; i++) {
    lc.InsertAtBack(dist(gen));
  }
  std::chrono::steady_clock::time_point end = std::chrono::_V2::steady_clock::now();
  std::cout << "List populated randomly in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << endl;
}

// Clears and resizes a list with a random size and random integers
void RandomIntNSizeList (lasd::List<int> &lc) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<uint> dist(1, 10000);
  std::cout << "Clearing and resizing the list... " << endl;
  uint size = dist(gen);
  lc.Clear();
  RandomIntList(lc, size);
  std::cout << "List cleared and resized with size " << size << endl;
}

// Puts random integers in the stack
void RandomIntStack(lasd::Stack<int> &stack, uint stacksize) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<int> dist(-100000, 100000);
  std::cout << "Populating the stack... " << endl;
  std::chrono::steady_clock::time_point begin = std::chrono::_V2::steady_clock::now();
  for (uint i = 0; i < stacksize; i++) {
    stack.Push(dist(gen));
  }
  std::chrono::steady_clock::time_point end = std::chrono::_V2::steady_clock::now();
  std::cout << "Stack populated randomly in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << endl;
}

// Resizes a stack with a random size stack with random data
void RandomIntNSizeStack(lasd::Stack<int> &stack) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<uint> dist(1, 10000);
  uint size = dist(gen);
  std::cout << "Clearing and resizing the stack... " << endl;
  stack.Clear();
  RandomIntStack(stack, size);
  std::cout << "Stack resized with size " << size << endl;
}

// Puts random integers in the queue
void RandomIntQueue(lasd::Queue<int> &queue, uint size) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<int> dist(-100000, 100000);
  std::cout << "Populating the queue... " << endl;
  for (uint i = 0; i < size; i++) {
    queue.Enqueue(dist(gen));
  }
  std::cout << "Queue populated" << endl;
}

void RandomIntNSizeQueue(lasd::Queue<int> &queue) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<uint> dist(1, 10000);
  uint size = dist(gen);
  std::cout << "Clearing and resizing the queue... " << endl;
  queue.Clear();
  RandomIntQueue(queue, size);
  std::cout << "Queue cleared and resized with size " << size << endl;
}

template <typename Data>
bool IsSortedVector(lasd::SortableVector<Data> &sv) {
  bool tst = true;
  for(uint i = 0; i < sv.Size() - 1; i++) {
    if(sv[i] > sv[i + 1]) {
      tst = false;
      break;
    }
  }
  return tst;
}

/* ************************************************************************** */

// Tests

// Calculates the factorial of N with a stack
void StackFactorial(uint &loctest, uint &testerr, const uint N, uint val, lasd::Stack<int> &stack) {
  bool tst;
  loctest++;
  std::cout << "#Test " << loctest << ": Checking the factorial of " << N << "... ";
  stack.Clear();
  uint result = 1;
  uint tstval = N;
  while (tstval > 0 || !(stack.Empty())) {
     if (tstval > 0) {
         stack.Push(tstval);
         tstval--;
      } else {
         result *= stack.Top();
         stack.Pop();
      }
  }
  std::cout << "The factorial of " << N << " is " << result << ": ";
  tst = (result == val);
  std::cout << ((tst) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

// Calculates the fibonacci of N terms with a queue
void QueueFibonacci(uint &loctest, uint &testerr, const uint N, uint val, lasd::Queue<int> &queue) {
  bool tst;
  loctest++;
  std::cout << "#Test " << loctest << ": Checking the fibonacci of " << N << " terms... ";
  queue.Clear();
  uint t1 = 0;
  uint t2 = 1;
  uint nextT = 0; 
  for (uint i = 0; i <= N; i++) {
    if (i == 1) { queue.Enqueue(t1); continue; }
    if (i == 2) { queue.Enqueue(t2); continue; }
    if (i > 2) {
      nextT = t1 + t2;
      queue.Enqueue(nextT);
      t1 = t2;
      t2 = nextT;
    }
  }
  std::cout << "The fibonacci of " << N << " terms is " << nextT << ": ";
  std::cout << "Printing the fibonacci sequence from the queue: " << endl;
  while (!queue.Empty()) {
    std::cout << queue.HeadNDequeue() << " ";
  }
  tst = (nextT == val);
  std::cout << ((tst) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

// Checks if the vector can perform a sort
template <typename Data>
void SortVectorTest(uint &loctest, uint &testerr, lasd::SortableVector<Data> &sv) {
  bool tst;
  loctest++;
  std::cout << "#Test " << loctest << ": Sorting the vector... ";
  std::chrono::steady_clock::time_point begin = std::chrono::_V2::steady_clock::now();
  sv.Sort();
  std::chrono::steady_clock::time_point end = std::chrono::_V2::steady_clock::now();
  std::cout << "The vector is sorted in: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << endl;
  tst = IsSortedVector(sv);
  std::cout << ((tst) ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint)tst);
}

void EmptyTest(uint &testnum, uint &testerr, lasd::Container &con) {
  bool tst = false;
  con.Empty() ? tst = true, testerr++, testnum++ : tst = false, testnum++;
  std::cout << "#Test "  << testnum << ": Is the container empty? " << (tst ? "Yes, error!" : "No, correct!") << endl;
}

/* ************************************************************************** */

void mytest() {
  std::cout << endl << "~*~#~*~ mytestSuite ~*~#~*~ " << endl;
  uint loctestnum = 0, loctesterr = 0;

  std::cout << "----------Testing SortableVector<int>----------" << endl;

  lasd::SortableVector<int> sv(5);
  RandomIntVector(sv);
  SortVectorTest(loctestnum, loctesterr, sv);

  std::cout << "Clearing the container for another test" << endl;
  sv.Clear();
  
  RandomIntNSizeVector(sv);
  SortVectorTest(loctestnum, loctesterr, sv);
  EmptyTest(loctestnum, loctesterr, sv);

  std::cout << "----------End of SortableVector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;

  /* ************************************************************************** */

  std::cout << "----------Testing List<int>----------" << endl;
  
  lasd::List<int> list;
  RandomIntNSizeList(list);
  EmptyTest(loctestnum, loctesterr, list);

  std::cout << "#Test " << loctestnum+1 << ": MapPostOrder using MapIncrement" << " --> ";
  MapPostOrder(loctestnum, loctesterr, list, true, &MapIncrement<int>);
  std::cout << "#Test " << loctestnum+1 << ": MapPostOrder using MapDecrement" << " --> ";
  MapPostOrder(loctestnum, loctesterr, list, true, &MapDecrement<int>);
  std::cout << "#Test " << loctestnum+1 << ": MapPostOrder using MapDouble" << " --> ";
  MapPostOrder(loctestnum, loctesterr, list, true, &MapDouble<int>);
  std::cout << "#Test " << loctestnum+1 << ": MapPostOrder using MapHalf" << " --> ";
  MapPostOrder(loctestnum, loctesterr, list, true, &MapHalf<int>);

  lasd::List<int> list2;
  std::cout << "#Test " << loctestnum+1 << ": InsertSome using copy" << " --> ";
  InsertSomeC(loctestnum, loctesterr, list2, true, list);

  std::cout << "----------End of List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;

  /* ************************************************************************** */

  std::cout << "----------Testing StackList<int>----------" << endl;

  lasd::StackLst<int> stacklst;
  StackFactorial(loctestnum, loctesterr, 5, 120, stacklst);

  std::cout << "Clearing the stack for another test" << endl;
  stacklst.Clear();

  RandomIntNSizeStack(stacklst);
  EmptyTest(loctestnum, loctesterr, stacklst);

  std::cout << "----------End of StackList<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;

  /* ************************************************************************** */

  std::cout << "----------Testing StackVec<int>----------" << endl;

  lasd::StackVec<int> stackvec;
  StackFactorial(loctestnum, loctesterr, 7, 5040, stackvec);

  std::cout << "Clearing the stack for another test" << endl;
  stackvec.Clear();

  RandomIntNSizeStack(stackvec);
  EmptyTest(loctestnum, loctesterr, stackvec);

  std::cout << "----------End of StackVec<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;

  /* ************************************************************************** */

  std::cout << "----------Testing QueueList<int>----------" << endl;
  
  lasd::QueueLst<int> queuelst;
  RandomIntNSizeQueue(queuelst);
  EmptyTest(loctestnum, loctesterr, queuelst);

  QueueFibonacci(loctestnum, loctesterr, 10, 34, queuelst);

  std::cout << "----------End of QueueList<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;

  /* ************************************************************************** */

  std::cout << "----------Testing QueueVec<int>----------" << endl;

  lasd::QueueVec<int> queuevec;
  RandomIntNSizeQueue(queuevec);
  EmptyTest(loctestnum, loctesterr, queuevec);

  QueueFibonacci(loctestnum, loctesterr, 16, 610, queuelst);

  std::cout << "----------End of QueueVec<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;

  std::cout << "----------End of Tests!----------" << endl;
}
