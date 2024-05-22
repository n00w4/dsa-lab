
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr: virtual public HashTable<Data> {

private:

protected:

  using Container::size;
  using HashTable<Data>::tablesize;
  using HashTable<Data>::HashKey;

  lasd::BST<Data>* table = nullptr;

public:

  // Default constructor
  HashTableClsAdr() { table = new lasd::BST<Data>[tablesize] {}; };

  /* ************************************************************************ */

  // Specific constructors
  // A hash table of a given size
  HashTableClsAdr(const unsigned long);
  // A hash table obtained from a TraversableContainer
  HashTableClsAdr(const TraversableContainer<Data>&);
  // A hash table of a given size obtained from a TraversableContainer
  HashTableClsAdr(const unsigned long, const TraversableContainer<Data>&);
  // A hash table obtained from a MappableContainer
  HashTableClsAdr(MappableContainer<Data>&&);
  // A hash table of a given size obtained from a MappableContainer
  HashTableClsAdr(const unsigned long, MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr&);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableClsAdr() {
    delete[] table;
  };

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr& operator=(const HashTableClsAdr&);

  // Move assignment
  HashTableClsAdr& operator=(HashTableClsAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr&) const noexcept;
  bool operator!=(const HashTableClsAdr&) const noexcept;

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
  virtual bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Resize the hashtable to a given size
  virtual void Resize(const unsigned long) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  // type Clear() specifiers; // Override Container member
  virtual void Clear() override;

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
