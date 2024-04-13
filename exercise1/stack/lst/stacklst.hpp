
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst: virtual public Stack<Data>, virtual protected List<Data> {

private:

protected:

  using List<Data>::size;
  using List<Data>::Node;

public:

  // Default constructor
  StackLst() : List<Data>() {};

  /* ************************************************************************ */

  // Specific constructor
  // A stack obtained from a TraversableContainer
  StackLst(const TraversableContainer<Data>& tc) : List<Data>(tc) {}
  
  // A stack obtained from a MappableContainer
  StackLst(MappableContainer<Data>&& mc) : List<Data>(mc) {}

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst<Data>& stacklist) : List<Data>(stacklist) {};

  // Move constructor
  StackLst(StackLst<Data>&& stacklist) noexcept : List<Data>(std::move(stacklist)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator=(const StackLst<Data>&) const noexcept;

  // Move assignment
  StackLst& operator=(StackLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst&) const noexcept;
  bool operator!=(const StackLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  // Top() specifiers; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data& Top() const override;

  // Top() specifiers; // Override Stack member (mutable version; must throw std::length_error when empty)
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

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
