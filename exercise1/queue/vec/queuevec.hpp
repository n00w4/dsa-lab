
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec: virtual public Queue<Data>, virtual protected Vector<Data> {

private:

protected:

  unsigned long head = 0;
  unsigned long tail = 0;

  using Vector<Data>::size;
  using Vector<Data>::elements;

public:

  // Default constructor
  QueueVec() : Vector<Data>(4) {}

  /* ************************************************************************ */

  // Specific constructor
  // A stack obtained from a TraversableContainer
  QueueVec(const TraversableContainer<Data>& tc) : Vector<Data>(tc) {}

  // A stack obtained from a MappableContainer
  QueueVec(MappableContainer<Data>&& mc) : Vector<Data>(mc) {}

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec<Data>& queuevec) : Vector<Data>(queuevec), head(queuevec.head), tail(queuevec.tail) {}

  // Move constructor
  QueueVec(QueueVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec& operator=(const QueueVec<Data>& queuevec);

  // Move assignment
  QueueVec& operator=(QueueVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec<Data>&) const noexcept;
  bool operator!=(const QueueVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  // Head() specifiers; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data& Head() const override;
  
  // Head() specifiers; // Override Queue member (mutable version; must throw std::length_error when empty)
  Data& Head() override;
  
  // Dequeue() specifiers; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override;
  
  // HeadNDequeue() specifiers; // Override Queue member (must throw std::length_error when empty)
  Data HeadNQueue() override;
  
  // Enqueue(argument) specifiers; // Override Queue member (copy of the value)
  void Enqueue(const Data&) override;
  
  // Enqueue(argument) specifiers; // Override Queue member (move of the value)
  void Enqueue(Data&&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // Empty() specifiers; // Override Container member
  bool Empty() const noexcept override;

  // Size() specifiers; // Override Container member
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

#include "queuevec.cpp"

#endif
