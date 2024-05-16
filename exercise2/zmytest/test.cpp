
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

// Iterator
#include "../iterator/iterator.hpp"

// BinaryTree
#include "../binarytree/binarytree.hpp"

// BinaryTreeVec
#include "../binarytree/vec/binarytreevec.hpp"

// BinaryTreeLnk
#include "../binarytree/lnk/binarytreelnk.hpp"

// BST
#include "../bst/bst.hpp"

// Useful functions from zlasdtest
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/traversable.hpp"


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

// Resizes a vector with a random size and random integers
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
void RandomIntList(lasd::List<int> &lc, uint size) {
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
void RandomIntNSizeList(lasd::List<int> &lc) {
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

// Resizes a stack with a random size stack with random integers
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
  std::chrono::steady_clock::time_point begin = std::chrono::_V2::steady_clock::now();
  for (uint i = 0; i < size; i++) {
    queue.Enqueue(dist(gen));
  }
  std::chrono::steady_clock::time_point end = std::chrono::_V2::steady_clock::now();
  std::cout << "Queue populated randomly in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << endl;
}

// Clears and resizes a queue with a random size and random integers
void RandomIntNSizeQueue(lasd::Queue<int> &queue) {
  default_random_engine gen(random_device{}());
  uniform_int_distribution<uint> dist(1, 10000);
  uint size = dist(gen);
  std::cout << "Clearing and resizing the queue... " << endl;
  queue.Clear();
  RandomIntQueue(queue, size);
  std::cout << "Queue cleared and resized with size " << size << endl;
}

// Checks if the vector is sorted
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

// EXERCISE 1 TESTS

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

// Checks if the container is empty
void EmptyTest(uint &testnum, uint &testerr, lasd::Container &con) {
  bool tst = false;
  con.Empty() ? tst = true, testerr++, testnum++ : tst = false, testnum++;
  std::cout << "#Test "  << testnum << ": Is the container empty? " << (tst ? "Yes, error!" : "No, correct!") << endl;
}

void Ex1Tests(uint &loctestnum, uint &loctesterr) {
  std::cout << endl << "----------~*~#~*~ Ex1Tests ~*~#~*~----------" << endl;

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
}

/* ************************************************************************** */

// EXERCISE 2 TESTS

// Tests an empty tree
void TestEmptyTree(uint &loctest, uint &testerr) {
  bool tst = false;
  loctest++;
  lasd::BST<int> bst;

  try {
    // test 1
    bst.Min();
    testerr++; // should not be executed
  } catch (const std::length_error& e) { tst = true; }
  try {
    // test 2
    bst.Max();
    testerr++; // should not be executed
  } catch (const std::length_error& e) { tst = true; }
  
  // test 3
  bst.Remove(10) ? tst = false, testerr++ : tst = true;
  
  if (tst) { std::cout << "#Test " << loctest << ": Empty tree test passed" << std::endl; }
  else { std::cout << "#Test " << loctest << ": Empty tree test failed" << std::endl; }
}

// Tests duplicates in a binary tree
 void TestDuplicateInsertion(uint &loctest, uint &testerr) {
  bool tst = false;
  loctest++;

  lasd::List<int> lst;
  lst.InsertAtBack(10);
  lst.InsertAtBack(10);
  
  lasd::BST<int> bst(lst);
  
  short count = 0;
  bst.Traverse([&count](const int& data) { data == 10 ? count++ : count; } );
  
  count == 1 ? tst = true : testerr++; // Only one 10 should exist

  if (testerr == 0) { std::cout << "#Test " << loctest << ": Duplicate insertion test passed" << std::endl; }
  else { std::cout << "#Test " << loctest << ": Duplicate insertion test failed" << std::endl; }
}


// Tests a tree with 1 node
void TestSingleElementTree(uint &loctest, uint &testerr) {
  bool tst = false;
  loctest++;
  
  lasd::List<int> lst;
  lst.InsertAtBack(10);

  lasd::BST<int> bst(lst);
  
  bst.Min() == 10 ? tst = true : testerr++;
  bst.Max() == 10 ? tst = true : testerr++;
  bst.Exists(10) ? tst = true : testerr++;
  
  bst.Remove(10);

  bst.Exists(10) ? testerr++ : tst = true;

  if (testerr == 0) { std::cout << "#Test " << loctest << ": Single element test passed" << std::endl; }
  else { std::cout << "#Test " << loctest << ": Single element test failed" << std::endl; }
}

// Tests the removal of the root
void TestRootRemoval(uint &loctest, uint &testerr) {
  bool tst = false;
  loctest++;

  // Case 1: Root without children
  lasd::List<int> lst;
  lst.InsertAtBack(10);

  lasd::BST<int> bst1(lst);
  bst1.Remove(10);
  (bst1.Exists(10) == false) ? tst = true : testerr++;

  // Case 2: Root with one child
  lasd::List<int> lst2;
  lst2.InsertAtBack(10);
  lst2.InsertAtBack(5);

  lasd::BST<int> bst2(lst2);
  bst2.Remove(10);
  (bst2.Exists(10) == false) ? tst = true : testerr++;
  (bst2.Exists(5) == true) ? tst = true : testerr++;

  // Case 3: Root with two children
  lasd::List<int> lst3;
  lst3.InsertAtBack(10);
  lst3.InsertAtBack(5);
  lst3.InsertAtBack(15);

  lasd::BST<int> bst3(lst3);
  bst3.Remove(10);
  (bst3.Exists(10) == false) ? tst = true : testerr++;
  (bst3.Exists(5) == true) ? tst = true : testerr++;
  (bst3.Exists(15) == true) ? tst = true : testerr++;

  if (testerr == 0) { std::cout << "#Test " << loctest << ": Root removal test passed" << std::endl; }
  else { std::cout << "#Test " << loctest << ": Root removal test failed" << std::endl; }
}

void TestDescendingInsertion(uint &loctest, uint &testerr) {
  bool tst = true;
  loctest++;
    
  lasd::List<int> lst;
  const int numElements = 100;
  for (int i = numElements - 1; i >= 0; --i) {
    lst.InsertAtBack(i);
  }

  lasd::BST<int> bst(lst);

  if (bst.Size() != numElements) {
    tst = false;
    testerr++;
  }
    
  if (tst) { std::cout << "#Test " << loctest << ": Descending insertion test passed" << std::endl; }
  else { std::cout << "#Test " << loctest << ": Descending insertion test failed" << std::endl; }
}

void TestSuccessorPredecessor(uint &loctest, uint &testerr) {
  bool tst = true;
  loctest++;
    
  lasd::List<int> lst;
  lst.InsertAtBack(20);
  lst.InsertAtBack(10);
  lst.InsertAtBack(30);
  lst.InsertAtBack(5);
  lst.InsertAtBack(15);
  lst.InsertAtBack(25);
  lst.InsertAtBack(35);

  lasd::BST<int> bst(lst);
    
  try {
    (bst.Successor(10) == 15) ? tst = true : testerr++;
    (bst.Predecessor(35) == 30) ? tst = true : testerr++;
    bst.InOrderTraverse(&TraversePrint<int>);
    std::cout << std::endl;
  } catch (std::length_error&) { tst = false; }
    
  if (tst) { std::cout << "#Test " << loctest << ": Successor and Predecessor test passed" << std::endl; }
  else { std::cout << "#Test " << loctest << ": Successor and Predecessor test failed" << std::endl; }
}

void TestLargeInsertion(uint &loctest, uint &testerr) {
  bool tst = true;
  loctest++;  

  lasd::List<int> lst;
  
  const int numElements = 20000;
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  for (int i = 0; i < numElements; ++i) {
    lst.InsertAtBack(i);  
  }

  try {
    lasd::BST<int> bst(lst);
    if (bst.Size() != numElements) {
      tst = false;
    }
  } catch (std::length_error& e) { tst = false; }
  
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "BST of " << numElements << " elements created in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
    
  if (tst) { std::cout << "#Test " << loctest << ": Large insertion test passed" << std::endl; }
  else { std::cout << "#Test " << loctest << ": Large insertion test failed" << std::endl; testerr++; }
}


void Ex2Tests(uint& loctestnum, uint& loctesterr) {
  std::cout << endl << "----------~*~#~*~ Ex2Tests ~*~#~*~----------" << endl;

  TestEmptyTree(loctestnum, loctesterr);
  TestDuplicateInsertion(loctestnum, loctesterr);
  TestSingleElementTree(loctestnum, loctesterr);
  TestRootRemoval(loctestnum, loctesterr);
  TestDescendingInsertion(loctestnum, loctesterr);
  TestSuccessorPredecessor(loctestnum, loctesterr);
  TestLargeInsertion(loctestnum, loctesterr);

  std::cout << "----------End of Ex2Tests!---------- " << "Errors/Tests: " << "(" << loctesterr << "/" << loctestnum << ") " << endl;
  std::cout << endl;
}

/* ************************************************************************** */

void mytest() {
  std::cout << endl << "~*~#~*~ mytestSuite ~*~#~*~ " << endl;
  uint loctestnum = 0, loctesterr = 0;

  Ex1Tests(loctestnum, loctesterr);
  Ex2Tests(loctestnum, loctesterr);

  std::cout << "----------End of Tests!----------" << endl;
}
