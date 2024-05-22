
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  unsigned long operator()(const Data&) const noexcept = 0;

};

/* ************************************************************************** */

template <typename Data>
class HashTable: virtual public ResizableContainer, virtual public DictionaryContainer<Data> {

private:

protected:

  using DictionaryContainer<Data>::size;

  unsigned long a = 3;
  unsigned long b = 5;
  static const unsigned long prime = 1069;

  std::default_random_engine randomN = std::default_random_engine(std::random_device{}());
  std::uniform_int_distribution<unsigned long> distributionA = std::uniform_int_distribution<unsigned long>(1, prime);
  std::uniform_int_distribution<unsigned long> distributionB = std::uniform_int_distribution<unsigned long>(0, prime);

  static const Hashable<Data> enc;

  unsigned long tablesize = 16;

public:

  // Default constructor
  HashTable() {
    a = (distributionA(randomN) * 2) + 1;
    b = std::pow(2, std::ceil(log2(distributionB(randomN))));
  }

  // Copy constructor
  HashTable(const HashTable& ht) {
    tablesize = ht.tablesize;
    size = ht.size;
    a = ht.a;
    b = ht.b;
  }

  // Move constructor
  HashTable(HashTable&& ht) noexcept {
    std::swap(tablesize, ht.tablesize);
    std::swap(size, ht.size);
    std::swap(a, ht.a);
    std::swap(b, ht.b);
  }

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable& ht) {
    size = ht.size;
    a = ht.a;
    b = ht.b;
    tablesize = ht.tablesize;
    return *this;
  }

  // Move assignment
  HashTable& operator=(HashTable&& ht) noexcept {
    std::swap(tablesize, ht.tablesize);
    std::swap(size, ht.size);
    std::swap(a, ht.a);
    std::swap(b, ht.b);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete;
  bool operator!=(const HashTable&) const noexcept = delete;

protected:

  virtual unsigned long HashKey(const Data& data) const noexcept {
    return HashKey(enc(data));
  }

  virtual unsigned long HashKey(unsigned long key) const noexcept {
    return (((a * key + b) % prime) % tablesize);
  }

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
