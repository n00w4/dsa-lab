
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec: virtual public MutableBinaryTree<Data>, virtual protected Vector<Data> {

private:

public:

  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;

  struct NodeVec: virtual MutableNode {

    BinaryTreeVec* Tree = nullptr;

    /* ************************************************************************ */

    // Default constructor
    NodeVec() = default;

    // Destructor
    virtual ~NodeVec() = default;

    /* ************************************************************************ */

    // Specific member functions inherited from Node
    inline const Data& Element() const noexcept override;
    inline Data& Element() noexcept override;
    inline bool IsLeaf() const noexcept override;
    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;

    virtual const Node& LeftChild() const override;
    virtual const Node& RightChild() const override;

    /* ************************************************************************ */

    // Specific member functions inherited from MutableNode
    virtual MutableNode& LeftChild() override;
    virtual MutableNode& RightChild() override;

  protected:

    // Auxiliary function
    virtual unsigned long Index() const noexcept;

  };

  NodeVec* Nodes = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(const TraversableContainer<Data>&);
  // A binary tree obtained from a MappableContainer
  BinaryTreeVec(MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec&) const noexcept;
  inline bool operator!=(const BinaryTreeVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  // Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)
  const NodeVec& Root() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  // Root() specifiers; // Override MutableBinaryTree member (throw std::length_error when empty)
  NodeVec& Root() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // Clear() specifiers; // Override ClearableContainer member
  void Clear() override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  
  void Traverse(TraverseFun) const override;

  // Specific member function (inherited from PreOrderTraversableContainer)
  void PreOrderTraverse(TraverseFun) const override;

  // Specific member function (inherited from PostOrderTraversableContainer)
  void PostOrderTraverse(TraverseFun) const override;

  // Specific member function (inherited from InOrderTraversableContainer)
  void InOrderTraverse(TraverseFun) const override;

  // Specific member function (inherited from BreadthTraversableContainer)

  // BreadthTraverse(arguments) specifiers; // Override BreadthTraversableContainer member
  void BreadthTraverse(TraverseFun) const override;

  /* ************************************************************************ */
  
  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;
  
  void Map(MapFun) override;

  // Specific member function (inherited from PreOrderMappableContainer)
  void PreOrderMap(MapFun) override;

  // Specific member function (inherited from PostOrderMappableContainer)
  void PostOrderMap(MapFun) override;

  // Specific member function (inherited from InOrderMappableContainer)
  void InOrderMap(MapFun) override;

  // Specific member function (inherited from BreadthMappableContainer)

  // BreadthMap(arguments) specifiers; // Override BreadthMappableContainer member
  void BreadthMap(MapFun) override;

protected:

  // Auxiliary functions
  void BreadthTraverse(TraverseFun, const Node&) const;
  void BreadthMap(MapFun, Node&);

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
