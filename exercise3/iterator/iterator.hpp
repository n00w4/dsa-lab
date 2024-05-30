
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

protected:

public:

  // Destructor
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  Iterator<Data>& operator=(const Iterator<Data>&) = delete;

  // Move assignment
  Iterator<Data>& operator=(Iterator<Data>&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Iterator<Data>&) const noexcept = delete;
  bool operator!=(const Iterator<Data>&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // operator*() specifiers; // (non-mutable version; concrete function must throw std::out_of_range when terminated)
  virtual const Data& operator*() const = 0;

  // Terminated() specifiers; // (concrete function should not throw exceptions)
  virtual bool Terminated() const noexcept = 0;
  
};

/* ************************************************************************** */

template <typename Data>
class MutableIterator: virtual public Iterator<Data> {

private:

protected:

  using Iterator<Data>::operator*;

public:

  // Destructor
  virtual ~MutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableIterator<Data>& operator=(const MutableIterator<Data>&) = delete;

  // Move assignment
  MutableIterator<Data>& operator=(MutableIterator<Data>&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutableIterator<Data>&) const noexcept = delete;
  bool operator!=(const MutableIterator<Data>&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // operator*() specifiers; // (mutable version; concrete function must throw std::out_of_range when terminated)
  virtual Data& operator*() = 0;

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator: virtual public Iterator<Data> {

private:

protected:

public:

  // Destructor
  virtual ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ForwardIterator<Data>& operator=(const ForwardIterator<Data>&) = delete;

  // Move assignment
  ForwardIterator<Data>& operator=(ForwardIterator<Data>&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ForwardIterator<Data>&) const noexcept = delete;
  bool operator!=(const ForwardIterator<Data>&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // operator++() specifiers; // (concrete function must throw std::out_of_range when terminated)
  virtual ForwardIterator<Data>& operator++() = 0;

};

/* ************************************************************************** */

template <typename Data>
class ResettableIterator: virtual public Iterator<Data> {

private:

protected:

public:

  // Destructor
  virtual ~ResettableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResettableIterator<Data>& operator=(const ResettableIterator<Data>&) = delete;

  // Move assignment
  ResettableIterator<Data>& operator=(ResettableIterator<Data>&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResettableIterator<Data>&) const noexcept = delete;
  bool operator!=(const ResettableIterator<Data>&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // Reset() specifiers; // (concrete function should not throw exceptions)
  virtual void Reset() noexcept = 0;

};

/* ************************************************************************** */

}

#endif
