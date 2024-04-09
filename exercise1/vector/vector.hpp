
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
  Vector(Vector<Data>&& original) : Elements(nullptr), size(original.size) {
    if (size > 0) {
      Elements = new Data[size];
      std::move(original.Elements, original.Elements + size, Elements);
    }
  }

  /* ************************************************************************ */

  // Destructor
  ~Vector() {
    delete[] Elements;
  }

  /* ************************************************************************ */

  // Copy assignment
  Vector<Data>& operator=(const Vector<Data>& original) {
    if (this != &original) {
      delete[] Elements;

      size = original.size;
      Elements = new Data[size];
      std::copy(original.Elements, original.Elements + size, Elements);
    }

    return *this;
  }

  // Move assignment
  Vector<Data>& operator=(Vector<Data>&& original) {
    if (this != &original) {
      delete[] Elements;

      size = original.size;
      Elements = new Data[size];
      std::move(original.Elements, original.Elements + size, Elements);
    }
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator=(const Vector&) const noexcept;
  bool operator!=(const Vector&) const noexcept;

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
  explicit SortableVector(const unsigned long newsize) : Vector<Data>(newsize) {}
  
  // A vector obtained from a TraversableContainer
  explicit SortableVector(const TraversableContainer<Data>& tc) : Vector<Data>(tc) {}

  // A vector obtained from a MappableContainer
  explicit SortableVector(const MappableContainer<Data>& mc) : Vector<Data>(mc) {}

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector<Data>& other) : Vector<Data>(other) {}

  // Move constructor
  SortableVector(SortableVector<Data>&& other) noexcept : Vector<Data>(std::move(other)) {}

  /* ************************************************************************ */

  // Destructor
  ~SortableVector() override = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector& operator=(const SortableVector& other) {
    Vector<Data>::operator=(other);
    return *this;
  }

  // Move assignment
  SortableVector& operator=(SortableVector&& other) noexcept {
    Vector<Data>::operator=(std::move(other));
    return *this;
  }

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
