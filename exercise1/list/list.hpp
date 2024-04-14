
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
class List: virtual public ClearableContainer, virtual public LinearContainer<Data>
            virtual public DictionaryContainer<Data> {

private:

protected:

  using Container::size;

  struct Node {

    Data element;
    Data * next = nullptr; 

    /* ********************************************************************** */

    // Default constructor
    Node() = default;

    // Specific constructors
    Node(const Data& data) : element(data) {};
    Node(Data&&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node& node) : element(node.element) {};

    // Move constructor
    Node(Node&& node) noexcept; 

    /* ********************************************************************** */

    // Destructor
    ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions
    virtual Node* Clone(Node*)

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
  List(const List<Data>&);

  // Move constructor
  List(List<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List<Data>&);

  // Move assignment
  List& operator=(List<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // Copy of the value
  void InsertAtFront(const Data& data);
  
  // Move of the value
  void InsertAtFront(Data&&) noexcept;
  
  // (must throw std::length_error when empty)
  void RemoveFromFront();
  
  // (must throw std::length_error when empty)
  Data FrontNRemove();
  
  // Copy of the value
  void InsertAtBack(const Data& data);

  // Move of the value
  void InsertAtBack(Data&&) noexcept;

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
  inline const Data& Front() const override;
  
  // Front() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  inline Data& Front() override;
  
  // Back() specifiers; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline const Data& Back() const override;

  // Back() specifiers; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  inline Data& Back() override;

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
  void PreOrderTraverse(TraverseFun, Node*) const;
  void PostOrderTraverse(TraverseFun, Node*) const;

  // Auxiliary functions for MappableContainer
  void PreOrderMap(MapFun, Node*);
  void PostOrderMap(MapFun, Node*);

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
