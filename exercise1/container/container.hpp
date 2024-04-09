
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

protected:

  unsigned long size = 0; 

  /* ************************************************************************ */

  // Default constructor
  Container(unsigned long size) {};

public:

  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container&) = delete;

  // Move assignment
  Container& operator=(Container&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container&) const noexcept = delete;
  bool operator!=(const Container&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  bool Empty() const noexcept {return (size==0);}

  unsigned long Size() const noexcept {return size;}
};

/* ************************************************************************** */

class ClearableContainer: virtual public Container {

public:

  // Destructor
  virtual ~ClearableContainer() override = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) = delete;

  // Move assignment
  ClearableContainer& operator=(ClearableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer&) const noexcept = delete;
  bool operator!=(const ClearableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  virtual void Clear() = 0;
};

/* ************************************************************************** */

class ResizableContainer: virtual public ClearableContainer {
public:

  // Destructor
  virtual ~ResizableContainer() override = default;

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer& operator=(const ResizableContainer&) = delete;
  // Move assignment
  ResizableContainer& operator=(ResizableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer&) const noexcept = delete;
  bool operator!=(const ResizableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  virtual void Resize(const unsigned long) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override;
};

/* ************************************************************************** */

}

#endif
