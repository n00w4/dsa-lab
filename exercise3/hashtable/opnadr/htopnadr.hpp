
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "bitset"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr: virtual public HashTable<Data> {

private:

  enum Flag { unused, used, deleted };

protected:

  using Container::size;
  using HashTable<Data>::tablesize;
  using HashTable<Data>::HashKey;

  Data* table = nullptr;
  Flag* tableFlag = nullptr;

public:

  // Default constructor
  HashTableOpnAdr() {
    table = new Data[tablesize] {};
    tableFlag = new Flag[tablesize] {};
  };

  /* ************************************************************************ */

  // Specific constructors
  // A hash table of a given size
  HashTableOpnAdr(const unsigned long);
  // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(const TraversableContainer<Data>&);
  // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(const unsigned long, const TraversableContainer<Data>&);
  // A hash table obtained from a MappableContainer
  HashTableOpnAdr(MappableContainer<Data>&&);
  // A hash table of a given size obtained from a MappableContainer
  HashTableOpnAdr(const unsigned long, MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr&);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableOpnAdr() {
    delete[] table;
    delete[] tableFlag;
  };

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr&);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr&) const noexcept;
  bool operator!=(const HashTableOpnAdr&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::InsertSome;
  using DictionaryContainer<Data>::RemoveAll;
  using DictionaryContainer<Data>::RemoveSome;

  // type Insert(argument) specifiers; // Override DictionaryContainer member (Copy of the value)
  virtual bool Insert(const Data&) override;
  // type Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
  virtual bool Insert(Data&&) override;
  // type Remove(argument) specifiers; // Override DictionaryContainer member
  virtual bool Remove(const Data&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member
  virtual bool Exists(const Data&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Resize the hashtable to a given size
  virtual void Resize(const unsigned long) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  // type Clear() specifiers; // Override Container member
  virtual void Clear() override;

protected:

  // Auxiliary member functions

  unsigned long HashKey(const Data&, const unsigned long&) const noexcept;
  bool Find(unsigned long&, unsigned long&, const Data&) const noexcept;
  unsigned long FindEmpty(const Data&, unsigned long&) const noexcept;
  bool Remove(unsigned long&, const Data&) noexcept;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
