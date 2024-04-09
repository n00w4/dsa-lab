
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector: virtual public ResizableContainer, virtual public LinearContainer<Data> {

private:

protected:

  using Container::size;

  Data = Elements = nullptr;

public:

  // Default constructor
  Vector() : Elements(nullptr), size(0) {}

  /* ************************************************************************ */

  // Specific constructors
  
  // A vector with a given initial dimension
  explicit Vector(const unsigned long newsize) : Elements(new Data[newsize]), size(newsize) {}
  
  // A vector obtained from a TraversableContainer
  explicit Vector(const TraversableContainer<Data>& tc) : Elements(new Data[tc.Size()]), size(tc.Size()) {}
  
  // A vector obtained from a MappableContainer
  explicit Vector(const MappableContainer<Data>& mc) : Elements(new Data[mc.Size()]), size(mc.Size()) {}

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data>& original) : Elements(nullptr), size(original.size) {
    if (size > 0) {
      Elements = new Data[size];
      std::copy(original.Elements, original.Elements + size, Elements);
      }
  }

  // Move constructor
  // Vector(argument) specifiers;
  Vector(Vector<Data>&& original) : Elements(nullptr), size(original.size) {
    if (size > 0) {
      Elements = new Data[size];
      std::move(original.Elements, original.Elements + size, Elements);
    }
  }

  /* ************************************************************************ */

  // Destructor
  // ~Vector() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  // type operator[](argument) specifiers; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  // type Front() specifiers; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  // type Front() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  // type Back() specifiers; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  // type Back() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // using Container::???;

  // ...

public:

  // Default constructor
  // SortableVector() specifiers;

  /* ************************************************************************ */

  // Specific constructors
  // SortableVector(argument) specifiers; // A vector with a given initial dimension
  // SortableVector(argument) specifiers; // A vector obtained from a TraversableContainer
  // SortableVector(argument) specifiers; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // SortableVector(argument) specifiers;

  // Move constructor
  // SortableVector(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~SortableVector() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
