
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List: virtual public ClearableContainer, virtual public LinearContainer<Data>,
            virtual public DictionaryContainer<Data> {

private:

protected:

  using Container::size;

  struct Node {

    Data element;
    Node* next = nullptr; 

    /* ********************************************************************** */

    // Default constructor
    inline Node() = default;

    // Specific constructors
    inline Node(const Data& data) : element(data) {};
    inline Node(Data&& data) noexcept : element(std::move(data)) {};

    /* ********************************************************************** */

    // Copy constructor
    inline Node(const Node& node) : element(node.element) {};

    // Move constructor
    inline Node(Node&& node) noexcept; 

    /* ********************************************************************** */

    // Destructor
    virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    inline bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions
    virtual Node* Clone(Node*);

  };

  Node* head = nullptr;
  Node* tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  // A list obtained from a TraversableContainer
  List(const TraversableContainer<Data>&);

  // A list obtained from a MappableContainer
  List(MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  List(const List&);

  // Move constructor
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const List&) const noexcept;
  inline bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // Copy of the value
  void InsertAtFront(const Data& data);
  
  // Move of the value
  void InsertAtFront(Data&&);
  
  // (must throw std::length_error when empty)
  void RemoveFromFront();
  
  // (must throw std::length_error when empty)
  Data FrontNRemove();
  
  // Copy of the value
  void InsertAtBack(const Data& data);

  // Move of the value
  void InsertAtBack(Data&&);

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  // Insert(argument) specifier; // Copy of the value
  bool Insert(const Data& data) override;
  
  // Insert(argument) specifier; // Move of the value
  bool Insert(Data&& data) override;

  // Remove(argument) specifier;
  bool Remove(const Data& data) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // operator[] specifiers; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  const Data& operator[](const unsigned long) const override;

  // operator[] specifiers; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const unsigned long) override;
  
  // Front() specifiers; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  const Data& Front() const override;
  
  // Front() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override;
  
  // Back() specifiers; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  const Data& Back() const override;

  // Back() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  
  void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;
  void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  void PostOrderMap(MapFun) override;

protected:

  // Auxiliary functions for TraversableContainer
  void PreOrderTraverse(TraverseFun, const Node*) const;
  void PostOrderTraverse(TraverseFun, const Node*) const;

  // Auxiliary functions for MappableContainer
  void PreOrderMap(MapFun, Node*);
  void PostOrderMap(MapFun, Node*);

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
