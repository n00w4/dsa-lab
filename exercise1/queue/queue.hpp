
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue: virtual public ClearableContainer {

private:

protected:

public:

  // Destructor
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  Queue& operator=(const Queue&) = delete;

  // Move assignment
  Queue& operator=(Queue&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Queue&) const noexcept = delete;
  bool operator!=(const Queue&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // Head() specifiers; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual const Data& Head() const = 0;

  // Head() specifiers; // (mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Head() = 0;
  
  // Dequeue() specifiers; // (concrete function must throw std::length_error when empty)
  virtual void Dequeue() = 0;
  
  // HeadNDequeue() specifiers; // (concrete function must throw std::length_error when empty)
  virtual Data HeadNDequeue() = 0;
  
  // Enqueue(argument) specifiers; // Copy of the value
  virtual void Enqueue(const Data&) = 0;
  
  // Enqueue(argument) specifiers; // Move of the value
  virtual void Enqueue(Data&&) = 0;

};

/* ************************************************************************** */

}

#endif
