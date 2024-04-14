
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer: virtual public PreOrderMappableContainer<Data>,
                       virtual public PostOrderMappableContainer<Data> {
 
private:

protected:
  
  using Container::size;

public:

  // Destructor
  ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) = delete;

  // Move assignment
  LinearContainer& operator=(LinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer&) const noexcept;
  bool operator!=(const LinearContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  virtual const Data& operator[](unsigned long) const = 0;
  
  // (mutable version; concrete function must throw std::out_of_range when out of range)
  virtual Data& operator[](unsigned long) = 0;

  // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual const Data& Front() const;

  // (mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Front();

  // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual const Data& Back() const;
  
  // (mutable version; concrete function must throw std::length_error when empty)
  virtual Data& Back();

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  virtual void Traverse(TraverseFun) override; 

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  virtual void PreOrderTraverse(TraverseFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  virtual void PostOrderTraverse(TraverseFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;
  virtual void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  virtual void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  virtual void PostOrderMap(MapFun) override;
};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer: virtual public LinearContainer<Data> {

private:

protected:

  using Container::Size;
  using LinearContainer<Data>::operator[];

public:

  // Destructor
  ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer&) = delete;

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SortableLinearContainer&) const noexcept;
  bool operaetor!=(const SortableLinearContainer&) const noexcept;
  

  /* ************************************************************************ */

  // Specific member function
  virtual void Sort() noexcept;

protected:

  // Auxiliary member functions
  void QuickSort(unsigned long p, unsigned long r) noexcept;

  unsigned long Partition(unsigned long p, unsigned long r) noexcept;
};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
