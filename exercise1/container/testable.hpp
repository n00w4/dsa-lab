
#ifndef TESTABLE_HPP
#define TESTABLE_HPP

/* ************************************************************************** */

#include "container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TestableContainer: virtual public Container<Data> {

private:

protected:

public:

  // Destructor
  virtual ~TestableContainer() = default;
  /* ************************************************************************ */

  // Copy assignment
  TestableContainer& operator=(const TestableContainer&) = delete;

  // Move assignment
  TestableContainer& operator=(TestableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TestableContainer&) const noexcept = delete;
  bool operator!=(TestableContainer&&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function
  virtual bool Exists(Data) const noexcept = 0;
};

/* ************************************************************************** */

}

#endif
