
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
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  
  // A vector with a given initial dimension
  Vector(const unsigned long);
  
  // A vector obtained from a TraversableContainer
  Vector(const TraversableContainer<Data>&);
  
  // A vector obtained from a MappableContainer
  Vector(MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data>&);

  // Move constructor
  Vector(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector() {
    delete[] Elements;
  }

  /* ************************************************************************ */

  // Copy assignment
  Vector<Data>& operator=(const Vector<Data>&);

  // Move assignment
  Vector<Data>& operator=(Vector<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data>&) const noexcept;
  inline bool operator!=(const Vector<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)
  void Resize(const unsigned long) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  const Data& operator[](const unsigned long) const override;
  
  // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const unsigned long) override;

  // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  const Data& Front() const override;
  
  // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override;

  // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  const Data& Back() const override;

  // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override;
};

/* ************************************************************************** */

template <typename Data>
class SortableVector: virtual public Vector<Data>, virtual public SortableLinearContainer<Data> {

private:

protected:

  using Container::size;

  Data = Elements = nullptr;

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  // A vector with a given initial dimension
  SortableVector(const unsigned long);
  
  // A vector obtained from a TraversableContainer
  SortableVector(const TraversableContainer<Data>&);

  // A vector obtained from a MappableContainer
  SortableVector(MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector<Data>&);

  // Move constructor
  SortableVector(SortableVector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SortableVector() override = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector& operator=(const SortableVector&);

  // Move assignment
  SortableVector& operator=(SortableVector&&) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
