
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer: virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer& operator=(const MappableContainer&) = delete;
  // Move assignment
  MappableContainer& operator=(MappableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MappableContainer&) const noexcept = delete;
  bool operator!=(const MappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;
  virtual void Map(MapFun) = 0;
};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer: virtual public MappableContainer<Data>,
                                 virtual public PreOrderTraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer& operator=(const PreOrderMappableContainer&) = delete;
  // Move assignment
  PreOrderMappableContainer& operator=(PreOrderMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderMappableContainer&) const noexcept = delete;
  bool operator!=(const PreOrderMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;
  virtual void PreOrderMap(MapFun);

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  virtual void Map(MapFun) override = 0;
};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer: virtual public MappableContainer<Data>,
                                  virtual public PostOrderTraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderMappableContainer& operator=(const PostOrderMappableContainer&) = delete;

  // Move assignment
  PostOrderMappableContainer& operator=(PostOrderMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  PostOrderMappableContainer& operator==(const PostOrderMappableContainer&) const noexcept = delete;
  PostOrderMappableContainer& operator!=(const PostOrderMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;
  virtual void PostOrderMap(MapFun);

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  virtual void Map(MapFun) override = 0;
};

/* ************************************************************************** */

template <typename Data>
class InOrderMappableContainer: virtual public MappableContainer<Data>,
                                virtual public InOrderTraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~InOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  InOrderMappableContainer& operator=(const InOrderMappableContainer&) = delete;

  // Move assignment
  InOrderMappableContainer& operator=(InOrderMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  InOrderMappableContainer operator==(const InOrderMappableContainer&) const noexcept = delete;
  InOrderMappableContainer operator!=(const InOrderMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  // type InOrderMap(argument) specifiers;
  virtual void InOrderMap(MapFun);

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  virtual void Map(MapFun) override = 0;
};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer: virtual public MappableContainer<Data>,
                                virtual public BreadthTraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~BreadthMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthMappableContainer& operator=(const BreadthMappableContainer&) = delete;

  // Move assignment
  BreadthMappableContainer& operator=(BreadthMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  BreadthMappableContainer operator==(const BreadthMappableContainer&) const noexcept = delete;
  BreadthMappableContainer operator!=(const BreadthMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function
  using typename MappableContainer<Data>::MapFun;
  virtual void BreadthMap(MapFun);

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  virtual void Map(MapFun) override = 0;
};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
