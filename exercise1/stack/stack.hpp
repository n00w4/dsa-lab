
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack: virtual public ClearableContainer {

private:

protected:

public:

  // Destructor
  ~Stack() = default;

  /* ************************************************************************ */

  // Copy assignment
  Stack& operator=(const Stack&) = delete;

  // Move assignment
  Stack& operator=(Stack&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Stack&) const noexcept = delete;
  bool operator!=(const Stack&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual const Data& Top() const = 0;

  // (mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Top() = 0;
  
  // (concrete function must throw std::length_error when empty)
  virtual void Pop() = 0;
  
  // (concrete function must throw std::length_error when empty)
  virtual Data TopNPop() = 0;
  
  // Push() specifiers; // Copy of the value
  virtual void Push(const Data&) = 0;
  
  // Push() specifiers; // Move of the value
  virtual void Push(Data&&) = 0;

};

/* ************************************************************************** */

}

#endif
