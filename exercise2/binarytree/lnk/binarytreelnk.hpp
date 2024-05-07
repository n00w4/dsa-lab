
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk: virtual public MutableBinaryTree<Data> {
private:

protected:

  using Container::size;

public:

  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

protected:

  struct NodeLnk: virtual MutableNode {
    
    NodeLnk* left = nullptr;
    NodeLnk* right = nullptr;
    Data element;

    /* ************************************************************************ */

    // Specific constructors
    NodeLnk(const Data& data) noexcept : element(data) {}
    NodeLnk(Data&&) noexcept;

    // Copy constructor
    NodeLnk(const NodeLnk&);

    // Move constructor
    NodeLnk(NodeLnk&&) noexcept;

    // Destructor
    virtual ~NodeLnk();

    // Copy assignment
    NodeLnk& operator=(const NodeLnk& node);

    // Move assignment
    NodeLnk& operator=(NodeLnk&& node) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const NodeLnk&) const noexcept;
    inline bool operator!=(const NodeLnk&) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Node)
    
    inline const Data& Element() const noexcept override;
    inline Data& Element() noexcept override;

    inline bool IsLeaf() const noexcept override;
    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;

    virtual const Node& LeftChild() const override;
    virtual const Node& RightChild() const override;

    /* ************************************************************************ */

    // Specific member functions (inherited from MutableNode)

    virtual MutableNode& LeftChild() override;
    virtual MutableNode& RightChild() override;

  };

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(const TraversableContainer<Data>&);

  // A binary tree obtained from a MappableContainer
  BinaryTreeLnk(MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept;
  bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  // Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)
  const Node& Root() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  // Root() specifiers; // Override MutableBinaryTree member (throw std::length_error when empty)
  MutableNode& Root() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // Clear() specifiers; // Override ClearableContainer member
  void Clear() override;

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
