
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer: virtual public TestableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer& operator=(const DictionaryContainer&) = delete;

  // Move assignment
  DictionaryContainer& operator=(DictionaryContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer&) const noexcept = delete;
  bool operator!=(const DictionaryContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // Copy of the value
  virtual bool Insert(const Data&) = 0;
  
  // Insert(argument) specifiers; // Move of the value
  virtual bool Insert(Data&&) = 0;

  // Remove(argument) specifiers;
  virtual bool Remove(const Data&) = 0;
  
  // InsertAll(argument) specifiers; // Copy of the value; From TraversableContainer; True if all are inserted
  inline virtual bool InsertAll(const TraversableContainer<Data>&);
  
  // InsertAll(argument) specifiers; // Move of the value; From MappableContainer; True if all are inserted
  inline virtual bool InsertAll(MappableContainer<Data>&&);
  
  // RemoveAll(argument) specifiers; // From TraversableContainer; True if all are removed
  inline virtual bool RemoveAll(const TraversableContainer<Data>&);

  // InsertSome(argument) specifiers; // Copy of the value; From TraversableContainer; True if some is inserted
  inline virtual bool InsertSome(const TraversableContainer<Data>&);

  // InsertSome(argument) specifiers; // Move of the value; From MappableContainer; True if some is inserted
  inline virtual bool InsertSome(MappableContainer<Data>&&);

  // RemoveSome(argument) specifiers; // From TraversableContainer; True if some is removed
  inline virtual bool RemoveSome(const TraversableContainer<Data>&);
};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
