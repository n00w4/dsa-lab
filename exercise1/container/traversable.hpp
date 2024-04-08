
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer: virtual public TestableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~TraversableContainer() = default;
  /* ************************************************************************ */

  // Copy assignment
  TraversableContainer& operator=(const TraversableContainer&) = delete;

  // Move assignment
  TraversableContainer& operator=(TraversableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TraversableContainer&) const noexcept;
  bool operator!=(const TraversableContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  using TraverseFun = std::function<void(const Data &)>;
  virtual void Traverse(TraverseFun) noexcept = 0;


  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

  template <typename Accumulator>
  Accumulator Fold<Accumulator>(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)
  bool Exists(Data) override = 0;
};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer: virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer& operator=(const PreOrderTraversableContainer&) = delete;

  // Move assignment
  PreOrderTraversableContainer& operator=(PreOrderMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderMappableContainer&) const noexcept;
  bool operator!=(const PreOrderMappableContainer&) const noexcept;
  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;
  virtual void PreOrderTraverse(TraverseFun) noexcept = 0;


  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PreOrderFold<Accumulator>(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse(TraverseFun) override = 0;
};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer: virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderTraversableContainer& operator=(const PostOrderTraversableContainer&) = delete;

  // Move assignment
  PostOrderTraversableContainer& operator=(PostOrderTraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderTraversableContainer&) const noexcept;
  bool operator!=(const PostOrderTraversableContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;
  virtual void PostOrderTraverse(TraverseFun) = 0;


  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PostOrderFold<Accumulator>(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse(TraverseFun) override = 0;
};

/* ************************************************************************** */

template <typename Data>
class InOrderTraversableContainer: virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~InOrderTraversableContainer() = default;
  /* ************************************************************************ */

  // Copy assignment
  InOrderTraversableContainer& operator=(const InOrderTraversableContainer&) = delete;

  // Move assignment
  InOrderTraversableContainer& operator=(InOrderTraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderTraversableContainer&) const noexcept;
  bool operator!=(const InOrderTraversableContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;
  virtual void InOrderTraverse(TraverseFun) = 0;


  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator InOrderFold<Accumulator>(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse (TraverseFun) override = 0;
};

/* ************************************************************************** */

template <typename Data>
class BreadthTraversableContainer: virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~BreadthTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthTraversableContainer& operator=(const BreadthTraversableContainer&) = delete;

  // Move assignment
  BreadthTraversableContainer& operator=(BreadthTraversableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthTraversableContainer&) const noexcept;
  bool operator!=(const BreadthTraversableContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;
  virtual void BreadthTraverse(TraverseFun) = 0;


  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator BreadthFold<Accumulator>(FoldFun<Accumulator>, Accumulator) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse(TraverseFun) override = 0;
};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
