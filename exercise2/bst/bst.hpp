
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST: virtual public ClearableContainer, virtual public DictionaryContainer<Data>, virtual public BinaryTree<Data>, virtual public BinaryTreeLnk<Data> {

private:

protected:

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;
  using typename BinaryTreeLnk<Data>::NodeLnk;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  // A bst obtained from a TraversableContainer
  BST(const TraversableContainer<Data>& tc);
  // A bst obtained from a MappableContainer
  BST(MappableContainer<Data>&& mc);

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data>& bst);

  // Move constructor
  BST(BST<Data>&& bst) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST();

  /* ************************************************************************ */

  // Copy assignment
  BST<Data>& operator=(const BST<Data>& bst);

  // Move assignment
  BST<Data>& operator=(BST<Data>&& bst) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  using BinaryTreeLnk<Data>::operator==;
  bool operator==(const BST<Data>&) const noexcept;
  
  using BinaryTreeLnk<Data>::operator==; 
  inline bool operator!=(const BST<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // type Min(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type MinNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type RemoveMin(argument) specifiers; // (concrete function must throw std::length_error when empty)

  // type Max(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type MaxNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type RemoveMax(argument) specifiers; // (concrete function must throw std::length_error when empty)

  // type Predecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  // type PredecessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  // type RemovePredecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)

  // type Successor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  // type SuccessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  // type RemoveSuccessor(argument) specifiers; // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  // type Root(argument) specifiers; // Override BinaryTree member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  // type Insert(argument) specifiers; // Override DictionaryContainer member (Copy of the value)
  // type Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
  // type Remove(argument) specifiers; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear(argument) specifiers; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

  // type DataNDelete(argument) specifiers;

  // type Detach(argument) specifiers;

  // type DetachMin(argument) specifiers;
  // type DetachMax(argument) specifiers;

  // type Skip2Left(argument) specifiers;
  // type Skip2Right(argument) specifiers;

  // type FindPointerToMin(argument) specifiers; // Both mutable & unmutable versions
  // type FindPointerToMax(argument) specifiers; // Both mutable & unmutable versions

  // type FindPointerTo(argument) specifiers; // Both mutable & unmutable versions

  // type FindPointerToPredecessor(argument) specifiers; // Both mutable & unmutable versions
  // type FindPointerToSuccessor(argument) specifiers; // Both mutable & unmutable versions

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
