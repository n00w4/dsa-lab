
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec: virtual public Stack<Data>, virtual protected Vector<Data> {

private:

protected:

  unsigned long index = 0;

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  StackVec() : Vector<Data>(1) {};

  /* ************************************************************************ */

  // Specific constructor
  // A stack obtained from a TraversableContainer
  StackVec(const TraversableContainer<Data>& tc) : Vector<Data>(tc), index(size) {}
  
  // A stack obtained from a MappableContainer
  StackVec(MappableContainer<Data>&& mc) : Vector<Data>(mc), index(size) {}

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec& stackvec) : Vector<Data>(stackvec), index(size) {}

  // Move constructor
  StackVec(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec&);
  
  // Move assignment
  StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec&) const noexcept;
  bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  // Top() specifiers; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  const Data& Top() const override;
  
  // Top() specifiers; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data& Top() override;
  
  // Pop() specifiers; // Override Stack member (must throw std::length_error when empty)
  void Pop() override;

  // TopNPop() specifiers; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override;
  
  // Push(argument) specifiers; // Override Stack member (copy of the value)
  void Push(const Data&) override;
  
  // Push(argument) specifiers; // Override Stack member (move of the value)
  void Push(Data&&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // Empty() specifiers; // Override Container member
  bool Empty() const noexcept override;

  // type Size() specifiers; // Override Container member
  unsigned long Size() const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // Clear() specifiers; // Override ClearableContainer member
  void Clear() override;

protected:

  // Auxiliary functions
  void Expand();
  void Reduce();

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
