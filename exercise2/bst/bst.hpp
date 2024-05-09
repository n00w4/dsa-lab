
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST: virtual public ClearableContainer, virtual public DictionaryContainer<Data>, virtual protected BinaryTreeLnk<Data> {

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
  BST(const TraversableContainer<Data>& tc) : BinaryTreeLnk<Data>(tc) {};
  // A bst obtained from a MappableContainer
  BST(MappableContainer<Data>&& mc) : BinaryTreeLnk<Data>(std::move(mc)) {};

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST& bst) : BinaryTreeLnk<Data>(bst) {};

  // Move constructor
  BST(BST&& bst) noexcept : BinaryTreeLnk<Data>(std::move(bst)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST&);

  // Move assignment
  BST& operator=(BST&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  using BinaryTreeLnk<Data>::operator==;
  bool operator==(const BST&) const noexcept;
  
  using BinaryTreeLnk<Data>::operator!=; 
  inline bool operator!=(const BST&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // Min(argument) specifiers; // (concrete function must throw std::length_error when empty)
  const Data& Min() const;
  // MinNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  Data MinNRemove();
  // RemoveMin(argument) specifiers; // (concrete function must throw std::length_error when empty)
  void RemoveMin();

  // Max(argument) specifiers; // (concrete function must throw std::length_error when empty)
  const Data& Max() const;
  // MaxNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove();
  // RemoveMax(argument) specifiers; // (concrete function must throw std::length_error when empty)
  void RemoveMax();

  // Predecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  const Data& Predecessor(const Data&) const;
  // PredecessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&);
  // RemovePredecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&);

  // Successor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  const Data& Successor(const Data&) const;
  // SuccessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&);
  // RemoveSuccessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&);

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  // Root(argument) specifiers; // Override BinaryTree member
  using BinaryTreeLnk<Data>::Root;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  // Insert(argument) specifiers; // Override DictionaryContainer member (Copy of the value)
  bool Insert(const Data&) override;
  // Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
  bool Insert(Data&&) override;
  // Remove(argument) specifiers; // Override DictionaryContainer member
  bool Remove(const Data&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  // Exists(argument) specifiers; // Override TestableContainer member
  bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // Clear(argument) specifiers; // Override ClearableContainer member
  using BinaryTreeLnk<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

  // DataNDelete(argument) specifiers;
  Data DataNDelete(const NodeLnk*);

  // Detach(argument) specifiers;
  NodeLnk* Detach(const NodeLnk*&) noexcept;

  // DetachMin(argument) specifiers;
  NodeLnk* DetachMin(NodeLnk*&) noexcept;
  // DetachMax(argument) specifiers;
  NodeLnk* DetachMax(NodeLnk*&) noexcept;

  // Skip2Left(argument) specifiers;
  NodeLnk* Skip2Left(NodeLnk*) noexcept;
  // Skip2Right(argument) specifiers;
  NodeLnk* Skip2Right(NodeLnk*) noexcept;

  // FindPointerToMin(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk*& FindPointerToMin(NodeLnk*&) noexcept;
  const NodeLnk* const& FindPointerToMin(const NodeLnk*const&) const noexcept;

  // FindPointerToMax(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk*& FindPointerToMax(NodeLnk*&) noexcept;
  const NodeLnk* const& FindPointerToMax(const NodeLnk*const&) const noexcept;

  // FindPointerTo(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk*& FindPointerTo(NodeLnk*&, const Data&) noexcept;
  const NodeLnk* const& FindPointerTo(const NodeLnk*const&, const Data&) const noexcept;

  // FindPointerToPredecessor(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk** FindPointerToPredecessor(NodeLnk*&, const Data&) noexcept;
  const NodeLnk* const* FindPointerToPredecessor(const NodeLnk*const&, const Data&) const noexcept;
  
  // FindPointerToSuccessor(argument) specifiers; // Both mutable & unmutable versions
  NodeLnk** FindPointerToSuccessor(NodeLnk*&, const Data&) noexcept;
  const NodeLnk* const* FindPointerToSuccessor(const NodeLnk*const&, const Data&) const noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
