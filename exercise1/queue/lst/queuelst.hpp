
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst: virtual public Queue<Data>, virtual protected List<Data>{

private:

protected:

  using List<Data>::size;
  using List<Data>::Node;

public:

  // Default constructor
  QueueLst() : List<Data>() {};

  /* ************************************************************************ */

  // Specific constructor
  // A queue obtained from a TraversableContainer
  QueueLst(const TraversableContainer<Data>& tc) : List<Data>(tc) {}
  
  // A queue obtained from a MappableContainer
  QueueLst(MappableContainer<Data>&& mc) : List<Data>(mc) {}

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst<Data>& queuelist) : List<Data>(queuelist) {};

  // Move constructor
  QueueLst(QueueLst<Data>&& queuelist) noexcept : List<Data>(std::move(queuelist)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueLst& operator=(const QueueLst<Data>&) const noexcept;

  // Move assignment
  QueueLst& operator=(QueueLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst&) const noexcept;
  bool operator!=(const QueueLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  // Head() specifiers; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data& Head() const override;
  
  // Head() specifiers; // Override Queue member (mutable version; must throw std::length_error when empty)
  Data& Head() override;

  // Dequeue() specifiers; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override;
  
  // HeadNDequeue() specifiers; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override;  
  
  // Enqueue(argument) specifiers; // Override Queue member (copy of the value)
  void Enqueue(const Data&) override;
  
  // Enqueue(argument) specifiers; // Override Queue member (move of the value)
  void Enqueue(Data&&) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
