
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

// HashTable
#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

// Useful functions from zlasdtest
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/traversable.hpp"


/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace ex1 {
  
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
}

void Ex1Tests(uint &loctestnum, uint &loctesterr) {
  std::cout << endl << "----------~*~#~*~ Ex1Tests ~*~#~*~----------" << endl;

  std::cout << "----------Testing SortableVector<int>----------" << endl;

  lasd::SortableVector<int> sv(5);
  ex1::RandomIntVector(sv);
  ex1::SortVectorTest(loctestnum, loctesterr, sv);

  std::cout << "Clearing the container for another test" << endl;
  sv.Clear();

  ex1::RandomIntNSizeVector(sv);
  ex1::SortVectorTest(loctestnum, loctesterr, sv);
  ex1::EmptyTest(loctestnum, loctesterr, sv);

  std::cout << "----------End of SortableVector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;
  
  std::cout << endl;

  /* ************************************************************************** */

  std::cout << "----------Testing List<int>----------" << endl;

  lasd::List<int> list;
  ex1::RandomIntNSizeList(list);
  ex1::EmptyTest(loctestnum, loctesterr, list);

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
  ex1::StackFactorial(loctestnum, loctesterr, 5, 120, stacklst);

  std::cout << "Clearing the stack for another test" << endl;
  stacklst.Clear();

  ex1::RandomIntNSizeStack(stacklst);
  ex1::EmptyTest(loctestnum, loctesterr, stacklst);

  std::cout << "----------End of StackList<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;

  /* ************************************************************************** */

  std::cout << "----------Testing StackVec<int>----------" << endl;

  lasd::StackVec<int> stackvec;
  ex1::StackFactorial(loctestnum, loctesterr, 7, 5040, stackvec);

  std::cout << "Clearing the stack for another test" << endl;
  stackvec.Clear();

  ex1::RandomIntNSizeStack(stackvec);
  ex1::EmptyTest(loctestnum, loctesterr, stackvec);

  std::cout << "----------End of StackVec<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;

  /* ************************************************************************** */

  std::cout << "----------Testing QueueList<int>----------" << endl;

  lasd::QueueLst<int> queuelst;
  ex1::RandomIntNSizeQueue(queuelst);
  ex1::EmptyTest(loctestnum, loctesterr, queuelst);

  ex1::QueueFibonacci(loctestnum, loctesterr, 10, 34, queuelst);

  std::cout << "----------End of QueueList<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;

  /* ************************************************************************** */

  std::cout << "----------Testing QueueVec<int>----------" << endl;

  lasd::QueueVec<int> queuevec;
  ex1::RandomIntNSizeQueue(queuevec);
  ex1::EmptyTest(loctestnum, loctesterr, queuevec);

  ex1::QueueFibonacci(loctestnum, loctesterr, 16, 610, queuelst);

  std::cout << "----------End of QueueVec<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")----------" << endl;

  std::cout << endl;
}

/* ************************************************************************** */

namespace ex2 {

  // EXERCISE 2 TESTS

  void TestConstructors(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::List<int> lst;
      for (int i = 0; i < 10; i++) { lst.InsertAtBack(i); }
      lasd::BinaryTreeVec<int> btv(lst);
      lasd::BinaryTreeLnk<int> btl(lst);
      lasd::BST<int> bst(lst);
      lasd::BTBreadthIterator<int> it(btl);
      lasd::BTInOrderIterator<int> it2(btl);
      lasd::BTPostOrderIterator<int> it3(btl);
      lasd::BTPreOrderIterator<int> it4(btl);
      lasd::BTBreadthMutableIterator<int> it5(btl);
      lasd::BTPostOrderMutableIterator<int> it6(btl);
      lasd::BTPreOrderMutableIterator<int> it7(btl);
      lasd::BTInOrderMutableIterator<int> it8(btl);
      
      tst = true;
    } catch (const std::bad_alloc& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::List<int> lst;
      lasd::BinaryTreeVec<int> btv(std::move(lst));
      lasd::BinaryTreeLnk<int> btl(std::move(lst));
      lasd::BST<int> bst(std::move(lst));
      lasd::BTBreadthIterator<int> it(std::move(btl));
      lasd::BTInOrderIterator<int> it2(std::move(btl));
      lasd::BTPostOrderIterator<int> it3(std::move(btl));
      lasd::BTPreOrderIterator<int> it4(std::move(btl));
      
      tst = true;
    } catch (const std::bad_alloc& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Constructor test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Constructor test failed" << std::endl; }
  }

  void TestAssignment(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::BinaryTreeLnk<int> btl1;
      lasd::BinaryTreeLnk<int> btl2;
      btl1 = btl2;
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeVec<int> btv1;
      lasd::BinaryTreeVec<int> btv2;
      btv1 = btv2;
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BST<int> bst1;
      lasd::BST<int> bst2;
      bst1 = bst2;
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeLnk<int> btl1;
      lasd::BTPreOrderIterator<int> it(btl1);
      lasd::BTPreOrderIterator<int> it2 = it;
      lasd::BTPreOrderMutableIterator<int> it3(btl1);
      lasd::BTPreOrderMutableIterator<int> it4 = it3;
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeVec<int> btv1;
      lasd::BTPostOrderIterator<int> it(btv1);
      lasd::BTPostOrderIterator<int> it2 = it;
      lasd::BTPostOrderMutableIterator<int> it3(btv1);
      lasd::BTPostOrderMutableIterator<int> it4 = it3;
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeLnk<int> btl;
      lasd::BTInOrderIterator<int> it(btl);
      lasd::BTInOrderIterator<int> it2 = it;
      lasd::BTInOrderMutableIterator<int> it3(btl);
      lasd::BTInOrderMutableIterator<int> it4 = it3;
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeLnk<int> btl1;
      lasd::BTBreadthIterator<int> it(btl1);
      lasd::BTBreadthIterator<int> it2 = it;
      lasd::BTBreadthMutableIterator<int> it3(btl1);
      lasd::BTBreadthMutableIterator<int> it4 = it3;
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeLnk<int> btl1;
      lasd::BinaryTreeLnk<int> btl2;
      btl1 = std::move(btl2);
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeVec<int> btv1;
      lasd::BinaryTreeVec<int> btv2;
      btv1 = std::move(btv2);
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BST<int> bst1;
      lasd::BST<int> bst2;
      bst1 = std::move(bst2);
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeLnk<int> btl1;
      lasd::BTPreOrderIterator<int> it(btl1);
      lasd::BTPreOrderIterator<int> it2 = std::move(it);
      lasd::BTPreOrderMutableIterator<int> it3(btl1);
      lasd::BTPreOrderMutableIterator<int> it4 = std::move(it3);
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeVec<int> btv1;
      lasd::BTPostOrderIterator<int> it(btv1);
      lasd::BTPostOrderIterator<int> it2 = std::move(it);
      lasd::BTPostOrderMutableIterator<int> it3(btv1);
      lasd::BTPostOrderMutableIterator<int> it4 = std::move(it3);
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeLnk<int> btl;
      lasd::BTInOrderIterator<int> it(btl);
      lasd::BTInOrderIterator<int> it2 = std::move(it);
      lasd::BTInOrderMutableIterator<int> it3(btl);
      lasd::BTInOrderMutableIterator<int> it4 = std::move(it3);
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::BinaryTreeLnk<int> btl1;
      lasd::BTBreadthIterator<int> it(btl1);
      lasd::BTBreadthIterator<int> it2 = std::move(it);
      lasd::BTBreadthMutableIterator<int> it3(btl1);
      lasd::BTBreadthMutableIterator<int> it4 = std::move(it3);
      tst = true;
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Assignment test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Assignment test failed" << std::endl; }
  }

  void TestComparison(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::List<int> lst1;
      for (int i = 0; i < 10; i++) { lst1.InsertAtBack(i); }
      lasd::BinaryTreeLnk<int> btl1(lst1);
      lasd::BinaryTreeLnk<int> btl2(lst1);
      tst = (btl1 == btl2);
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::List<int> lst1;
      for (int i = 0; i < 10; i++) { lst1.InsertAtBack(i); }
      lasd::BinaryTreeVec<int> btv(lst1);
      lasd::BinaryTreeVec<int> btv2(lst1);
      tst = (btv == btv2);
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::List<int> lst1;
      for (int i = 0; i < 10; i++) { lst1.InsertAtBack(i); }
      lasd::BST<int> bst1(lst1);
      lasd::BST<int> bst2(lst1);
      tst = (bst1 == bst2);
    } catch (const std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Comparison test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Comparison test failed" << std::endl; }
  }

  // Tests an iterator with a large number of random integers
  void TestLargeIterator(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;
    lasd::List<int> lst;
    ex1::RandomIntNSizeList(lst);

    lasd::BinaryTreeVec<int> btv(lst);
    lasd::BTInOrderIterator<int> it(btv);

    try {
      for (ulong i = 0; i <= lst.Size(); i++) {
        ++it;
      }
    } catch (const std::out_of_range& e) { tst = true; std::cout << e.what() << std::endl; } // error should be catched

    if (tst) { std::cout << "#Test " << loctest << ": Large iterator test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Large iterator test failed" << std::endl; }
  }

  // Tests an empty tree
  void TestEmptyTree(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;
    lasd::BST<int> bst;

    try {
      // test 1
      bst.Min();
      testerr++; // should not be executed
    } catch (const std::exception& e) { tst = true; }
    try {
      // test 2
      bst.Max();
      testerr++; // should not be executed
    } catch (const std::exception& e) { tst = true; }
    try {
      // test 3
      bst.Remove(10) ? tst = false, testerr++ : tst = true;
    } catch (const std::exception& e) { tst = true; }

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

  // Tests descending insertion in BST
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

  // Tests successor and predecessor in BST
  void TestSuccessorPredecessor(uint &loctest, uint &testerr) {
    bool tst = false;
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
      (bst.Successor(5) == 10) ? tst = true : testerr++;
      (bst.Successor(10) == 15) ? tst = true : testerr++;
      (bst.Predecessor(35) == 30) ? tst = true : testerr++;
      (bst.Predecessor(30) == 25) ? tst = true : testerr++;
      bst.InOrderTraverse(&TraversePrint<int>);
      std::cout << std::endl;
      std::cout << "Testing RemovePredecessor and RemoveSuccessor..." << std::endl;
      bst.RemovePredecessor(30);
      bst.RemoveSuccessor(5);
      bst.InOrderTraverse(&TraversePrint<int>);
      std::cout << std::endl;
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Successor and Predecessor test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Successor and Predecessor test failed" << std::endl; }
  }

  void TestMaxMin(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::List<int> lst;
      lst.InsertAtBack(20);
      lst.InsertAtBack(10);
      lst.InsertAtBack(30);
      lst.InsertAtBack(5);
      lst.InsertAtBack(15);
      lst.InsertAtBack(25);
      lst.InsertAtBack(35);

      lasd::BST<int> bst(lst);
      (bst.Max() == 35) ? tst = true : testerr++;
      (bst.Min() == 5) ? tst = true : testerr++;
      std::cout << "Testing RemoveMax and RemoveMin..." << std::endl;
      bst.RemoveMax();
      bst.RemoveMin();
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Max and Min test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Max and Min test failed" << std::endl; }
  }

  // Tests large insertion in binary trees
  void TestLargeInsertion(uint &loctest, uint &testerr) {
    bool tst = true;
    loctest++;  

    lasd::List<int> lst;

    const int numElements = 20000;
    for (int i = 0; i < numElements; ++i) {
      lst.InsertAtBack(i);  
    }

    try {
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      lasd::BinaryTreeLnk<int> bt(lst);
      if (bt.Size() != numElements) {
        tst = false;
      }
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "BinaryTreeLnk of " << numElements << " elements created in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      lasd::BinaryTreeVec<int> btvec(lst);
      if (btvec.Size() != numElements) {
        tst = false;
      }
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "BinaryTreeVec of " << numElements << " elements created in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      lasd::BST<int> bst(lst);
      if (bst.Size() != numElements) {
        tst = false;
      }
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "BST of " << numElements << " elements created in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Large insertion test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Large insertion test failed" << std::endl; testerr++; }
  }
}

void Ex2Tests(uint& loctestnum, uint& loctesterr) {
  std::cout << endl << "----------~*~#~*~ Ex2Tests ~*~#~*~----------" << endl;
  
  ex2::TestConstructors(loctestnum, loctesterr);
  ex2::TestComparison(loctestnum, loctesterr);
  ex2::TestAssignment(loctestnum, loctesterr);
  ex2::TestLargeIterator(loctestnum, loctesterr);
  ex2::TestEmptyTree(loctestnum, loctesterr);
  ex2::TestDuplicateInsertion(loctestnum, loctesterr);
  ex2::TestSingleElementTree(loctestnum, loctesterr);
  ex2::TestRootRemoval(loctestnum, loctesterr);
  ex2::TestDescendingInsertion(loctestnum, loctesterr);
  ex2::TestSuccessorPredecessor(loctestnum, loctesterr);
  ex2::TestMaxMin(loctestnum, loctesterr);
  ex2::TestLargeInsertion(loctestnum, loctesterr);
  
  std::cout << "----------End of Ex2Tests!---------- " << "Errors/Tests: " << "(" << loctesterr << "/" << loctestnum << ") " << endl;
  std::cout << endl;
}

/* ************************************************************************** */

namespace ex3 {

  // EXERCISE 3 TESTS

  void TestConstructors(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::Vector<int> vec;
      lasd::List<int> lst;
      lasd::HashTableClsAdr<int> ht(vec);
      lasd::HashTableOpnAdr<int> htop(vec);
      lasd::HashTableClsAdr<int> ht2(lst);
      lasd::HashTableOpnAdr<int> htop2(lst);

      lasd::HashTableClsAdr<int> ht3(ht);
      lasd::HashTableOpnAdr<int> htop3(htop);
      lasd::HashTableClsAdr<int> ht4(std::move(ht3));
      lasd::HashTableOpnAdr<int> htop4(std::move(htop3));
      tst = true;
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Constructors test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Constructors test failed" << std::endl; testerr++; }
  }

  void TestAssignment(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::List<int> lst;
      lasd::HashTableClsAdr<int> ht2(lst);
      lasd::HashTableOpnAdr<int> htop2(lst);
      lasd::HashTableClsAdr<int> ht = ht2;
      lasd::HashTableOpnAdr<int> htop = htop2;

      lasd::HashTableClsAdr<int> ht3 = std::move(ht);
      lasd::HashTableOpnAdr<int> htop3 = std::move(htop);
      tst = true;
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Assignment test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Assignment test failed" << std::endl; testerr++; }
  }

  void TestComparison(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::Vector<int> vec;
      lasd::List<int> lst;
      lasd::HashTableClsAdr<int> ht(vec);
      lasd::HashTableClsAdr<int> ht2(lst);

      if (ht == ht2) { tst = true; } else { tst = false; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::Vector<int> vec;
      lasd::List<int> lst;
      lasd::HashTableOpnAdr<int> htop(vec);
      lasd::HashTableOpnAdr<int> htop2(lst);

      if (htop == htop2) { tst = true; } else { tst = false; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::Vector<int> vec(10);
      lasd::List<int> lst;
      for (int i = 0; i < 10; i++) { vec[i] = i; lst.InsertAtBack(i); }
      lasd::HashTableClsAdr<int> ht(vec);
      lasd::HashTableClsAdr<int> ht2(lst);

      if (ht == ht2) { tst = true; } else { tst = false; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::Vector<int> vec(10);
      lasd::List<int> lst;
      for (int i = 0; i < 10; i++) { vec[i] = i; lst.InsertAtBack(i); }
      lasd::HashTableOpnAdr<int> htop(vec);
      lasd::HashTableOpnAdr<int> htop2(lst);

      if (htop == htop2) { tst = true; } else { tst = false; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Comparison test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Comparison test failed" << std::endl; testerr++; }
  }

  // Tests creation of an empty table and a table with 1 element
  void TestCreationTable(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::Vector<int> vec;
      lasd::HashTableClsAdr<int> ht(vec);
      lasd::HashTableOpnAdr<int> htop(vec);
      vec.Resize(1);
      vec[0] = 1;
      lasd::HashTableClsAdr<int> ht2(vec);
      lasd::HashTableOpnAdr<int> htop2(vec);
      if (ht2.Exists(1)) { tst = true; }
      if (htop2.Exists(1)) { tst = true; } else { tst = false; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Insertion into an empty table test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Insertion into an empty table test failed" << std::endl; testerr++; }
  }

  // Tests how the table handles collisions
  void TestCollisions(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::Vector<int> vec(2);
      vec[0] = 1;
      vec[1] = 11;
      lasd::HashTableClsAdr<int> ht(vec);
      lasd::HashTableOpnAdr<int> htop(vec);
      if (ht.Exists(11) && ht.Exists(1)) { tst = true; }
      if (htop.Exists(11) && htop.Exists(1)) { tst = true; } else { tst = false; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Collision handling test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Collision handling test failed" << std::endl; testerr++; }
  }

  // Tests the removal of an element that is in the middle of a chain
  void TestRemoval(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::Vector<int> vec(4);
      vec[0] = 1;
      vec[1] = 11;
      vec[2] = 111;
      vec[3] = 1111;
      lasd::HashTableClsAdr<int> ht(vec);
      lasd::HashTableOpnAdr<int> htop(vec);
      ht.Remove(11);
      htop.Remove(11);
      if (!ht.Exists(11) && ht.Exists(1111) && ht.Exists(111) && ht.Exists(1)) { tst = true; }
      if (!htop.Exists(11) && htop.Exists(1111) && htop.Exists(111) && htop.Exists(1)) { tst = true; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Removal test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Removal test failed" << std::endl; testerr++; }
  }

  // Tests how the table handles great amount of elements
  void TestLargeTable(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::List<int> list;
      for (uint i = 0; i < 100000; i++) {
        list.InsertAtBack(i);
      }
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      lasd::HashTableClsAdr<int> ht(list);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "HashTable ClsAdr of " << list.Size() << " elements created in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
      if (ht.Size() == list.Size()) { tst = true; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::List<int> list;
      for (uint i = 0; i < 100000; i++) {
        list.InsertAtBack(i);
      }
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      lasd::HashTableOpnAdr<int> ht(list);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "HashTable OpnAdr of " << list.Size() << " elements created in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
      if (ht.Size() == list.Size()) { tst = true; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Large table test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Large table test failed" << std::endl; testerr++; }
  }

  // Tests rehashing and resizing
  void TestRehashingNResizing(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::List<int> list;
      for (uint i = 0; i < 10; i++) { list.InsertAtBack(i); }
      lasd::HashTableClsAdr<int> ht(list);
      for (uint i = 10; i < 30; i++) { list.InsertAtBack(i); }
      ht.InsertAll(list);
      for (uint i = 0; i < 30; i++) {
        if (ht.Exists(i)) { tst = true; }
        else { tst = false; break; }
      }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    try {
      lasd::List<int> list;
      for (uint i = 0; i < 10; i++) { list.InsertAtBack(i); }
      lasd::HashTableOpnAdr<int> htop(list);
      for (uint i = 10; i < 30; i++) { list.InsertAtBack(i); }
      htop.InsertAll(list);
      for (uint i = 0; i < 30; i++) {
        if (htop.Exists(i)) { tst = true; }
        else { tst = false; break; }
      }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Rehashing test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Rehashing test failed" << std::endl; testerr++; }
  }

  // Tests a particular case where the user tries to resize to 0 (or a number less than the default size)
  void TestResizingZero(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::HashTableOpnAdr<int> ht;
      ht.Resize(0); // should create a memory leak
      tst = true;
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Resizing test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Resizing test failed" << std::endl; testerr++; }

  }

  // Tests probing
  void TestProbing(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::List<int> list;
      for (uint i = 0; i < 10; i++) { list.InsertAtBack(i); }
      lasd::HashTableOpnAdr<int> ht(list);
      lasd::List<int> list2;
      for (uint i = 0; i < 10; i++) { list2.InsertAtBack(i); }
      if (!ht.InsertAll(list2)) { tst = true; } // shouldn't be inserted
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Probing test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Probing test failed" << std::endl; testerr++; }
  }
  
  // Tests remove function
  void TestRemove(uint &loctest, uint &testerr) {
    bool tst = false;
    loctest++;

    try {
      lasd::List<int> list;
      lasd::List<int> list2;
      for (uint i = 0; i < 10; i++) { list.InsertAtBack(i); }
      list2.InsertAtBack(0);
      lasd::HashTableOpnAdr<int> ht(10);
      ht.InsertAll(list);
      if (!ht.Remove(100)) { tst = true; }
      ht.Remove(0);
      if (!ht.InsertAll(list2)) { tst = false; }
    } catch (std::exception& e) { tst = false; std::cout << e.what() << std::endl; }

    if (tst) { std::cout << "#Test " << loctest << ": Remove test passed" << std::endl; }
    else { std::cout << "#Test " << loctest << ": Remove test failed" << std::endl; testerr++; }

  }

}

void Ex3Tests(uint &loctestnum, uint &loctesterr) {
  std::cout << endl << "----------~*~#~*~ Ex3Tests ~*~#~*~----------" << endl;

  ex3::TestConstructors(loctestnum, loctesterr);
  ex3::TestComparison(loctestnum, loctesterr);
  ex3::TestAssignment(loctestnum, loctesterr);
  ex3::TestCreationTable(loctestnum, loctesterr);
  ex3::TestCollisions(loctestnum, loctesterr);
  ex3::TestRemoval(loctestnum, loctesterr);
  ex3::TestLargeTable(loctestnum, loctesterr);
  ex3::TestRehashingNResizing(loctestnum, loctesterr);
  ex3::TestResizingZero(loctestnum, loctesterr);
  ex3::TestProbing(loctestnum, loctesterr);
  ex3::TestRemove(loctestnum, loctesterr);
  
  std::cout << "----------End of Ex3Tests!---------- " << "Errors/Tests: " << "(" << loctesterr << "/" << loctestnum << ") " << endl;
  std::cout << endl;
}

/* ************************************************************************** */

void mytest() {
  std::cout << endl << "~*~#~*~ mytestSuite ~*~#~*~ " << endl;
  uint loctestnum = 0, loctesterr = 0;

  Ex1Tests(loctestnum, loctesterr);
  Ex2Tests(loctestnum, loctesterr);
  Ex3Tests(loctestnum, loctesterr);

  std::cout << "----------End of Tests!----------" << endl;
}