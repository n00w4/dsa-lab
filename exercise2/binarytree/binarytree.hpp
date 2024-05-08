
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

// #include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
// #include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree: virtual public PreOrderTraversableContainer<Data>, virtual public PostOrderTraversableContainer<Data>, virtual public InOrderTraversableContainer<Data>,
                  virtual public BreadthTraversableContainer<Data> {

private:

protected:

  using Container::size;

public:

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    bool operator!=(const Node&) const noexcept;

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node&) = delete;

    // Move assignment
    Node& operator=(Node&&) noexcept = delete;

    /* ********************************************************************** */

    // Specific member functions

    // Element() specifiers; // Immutable access to the element (concrete function should not throw exceptions)
    virtual const Data& Element() const noexcept = 0;

    // IsLeaf() specifiers; // (concrete function should not throw exceptions)
    virtual bool IsLeaf() const noexcept = 0;
    
    // HasLeftChild() specifiers; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0;

    // HasRightChild() specifiers; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0;

    // LeftChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node& LeftChild() const = 0;
    
    // RightChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node& RightChild() const = 0;
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree& operator=(const BinaryTree&) = delete;

  // Move assignment
  BinaryTree& operator=(BinaryTree&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree&) const noexcept;
  bool operator!=(const BinaryTree&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // Root() specifiers; // (concrete function must throw std::length_error when empty)
  virtual const Node& Root() const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;

  // Traverse(arguments) specifiers; // Override TraversableContainer member
  void Traverse(TraverseFun travFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member
  void PreOrderTraverse(TraverseFun travFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // PostOrderTraverse(arguments) specifiers; // Override PostOrderTraversableContainer member
  void PostOrderTraverse(TraverseFun travFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  // InOrderTraverse(arguments) specifiers; // Override InOrderTraversableContainer member
  void InOrderTraverse(TraverseFun travFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  // BreadthTraverse(arguments) specifiers; // Override BreadthTraversableContainer member
  void BreadthTraverse(TraverseFun travFun) const override;

protected:

  // Auxiliary functions
  // virtual void PreOrderTraverse(TraverseFun, const Node&) const;
  // virtual void PostOrderTraverse(TraverseFun, const Node&) const;
  // virtual void InOrderTraverse(TraverseFun, const Node&) const;
  virtual void BreadthTraverse(TraverseFun, const Node&) const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree: virtual public ClearableContainer, virtual public BinaryTree<Data>, virtual public PreOrderMappableContainer<Data>,
                         virtual public PostOrderMappableContainer<Data>, virtual public InOrderMappableContainer<Data>, virtual public BreadthMappableContainer<Data> {

private:

protected:

  using Container::size;
  using typename BinaryTree<Data>::Node;

public:

  struct MutableNode: virtual Node {
    
    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const MutableNode&) const noexcept = default;
    bool operator!=(const MutableNode&) const noexcept = default;

    // Copy assignment
    MutableNode& operator=(const MutableNode&) = delete;

    // Move assignment
    MutableNode& operator=(MutableNode&&) noexcept = delete;

    /* ********************************************************************** */

    // Specific member functions

    // Element() specifiers; // Mutable access to the element (concrete function should not throw exceptions)
    using Node::Element;
    virtual Data& Element() noexcept = 0;
    // LeftChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    using Node::LeftChild;
    virtual MutableNode& LeftChild() = 0;
    // RightChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    using Node::RightChild;
    virtual MutableNode& RightChild() = 0;

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree& operator=(const MutableBinaryTree&) = delete;

  // Move assignment
  MutableBinaryTree& operator=(MutableBinaryTree&&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // Root() specifiers; // (concrete function must throw std::length_error when empty)
  using BinaryTree<Data>::Root;
  virtual MutableNode& Root() = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  // Override MappableContainer member
  void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // Override PreOrderMappableContainer member
  void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // Override PostOrderMappableContainer member
  void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  // Override InOrderMappableContainer member
  void InOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  // Override BreadthMappableContainer member
  void BreadthMap(MapFun) override;

protected:

  // Auxiliary functions
  virtual void PreOrderMap(MapFun, Node&);
  virtual void PostOrderMap(MapFun, Node&);
  virtual void InOrderMap(MapFun, Node&);
  virtual void BreadthMap(MapFun, Node&);

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator: virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stack;

public:

  // Specific constructors
  // An iterator over a given binary tree
  BTPreOrderIterator(const BinaryTree<Data>& bt) {
    if (!bt.Empty()) { stack.Push(root = &bt.Root()); }
  };

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator& iter) : root(iter.root), stack(iter.stack) {};

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator&& iter) noexcept {
    std::swap(root, iter.root);
    std::swap(stack, iter.stack);
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator& operator=(const BTPreOrderIterator& iter) {
    root = iter.root;
    stack = iter.stack;
    return *this;
  };

  // Move assignment
  BTPreOrderIterator& operator=(BTPreOrderIterator&& iter) noexcept {
    std::swap(root, iter.root);
    std::swap(stack, iter.stack);
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator&) const noexcept = default;
  bool operator!=(const BTPreOrderIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override {
    if (!stack.Empty()) { return stack.Top()->Element(); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

  // Terminated() specifiers; // (should not throw exceptions)
  bool Terminated() const noexcept override {
    return stack.Empty();
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // operator++() specifiers; // (throw std::out_of_range when terminated)
  ForwardIterator<Data>& operator++() override {
    const typename BinaryTree<Data>::Node& node = *stack.TopNPop();
    if (node.HasLeftChild()) { stack.Push(&node.LeftChild()); }
    if (node.HasRightChild()) { stack.Push(&node.RightChild()); }
    return *this;
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override {
    if (root != nullptr) {
      stack.Clear();
      stack.Push(root);
    }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator: virtual public MutableIterator<Data>, virtual public BTPreOrderIterator<Data> {

private:

protected:

  using BTPreOrderIterator<Data>::stack;

public:

  // Specific constructors
  // An iterator over a given mutable binary tree
  BTPreOrderMutableIterator(MutableBinaryTree<Data>& mbt) : BTPreOrderIterator<Data>(mbt) {};

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator& iter) : BTPreOrderIterator<Data>(iter) {};

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator&& iter) noexcept : BTPreOrderIterator<Data>(iter) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator& iter) {
    BTPreOrderIterator<Data>::operator=(iter);
  };

  // Move assignment
  BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&& iter) noexcept {
    BTPreOrderIterator<Data>::operator=(std::move(iter));
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator&) const noexcept = default;
  bool operator!=(const BTPreOrderMutableIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (!stack.Empty()) { return stack.Top()->Element(); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator: virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stack;

public:

  // Specific constructors
  // An iterator over a given binary tree
  BTPostOrderIterator(const BinaryTree<Data>& bt) {
    if (!bt.Empty()) { stack.Push(root = &bt.Root()); }
  };

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator& iter) : root(iter.root), stack(iter.stack) {};

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator&& iter) noexcept {
    std::swap(root, iter.root);
    std::swap(stack, iter.stack);
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator& operator=(const BTPostOrderIterator& iter) {
    root = iter.root;
    stack = iter.stack;
  };

  // Move assignment
  BTPostOrderIterator& operator=(BTPostOrderIterator&& iter) {
    std::swap(root, iter.root);
    std::swap(stack, iter.stack);
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator&) const noexcept = default;
  bool operator!=(const BTPostOrderIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override {
    if (!stack.Empty()) { return stack.Top()->Element(); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

  // Terminated() specifiers; // (should not throw exceptions)
  bool Terminated() const noexcept override {
    return stack.Empty();
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // operator++() specifiers; // (throw std::out_of_range when terminated)
  ForwardIterator<Data>& operator++() override {
    const typename BinaryTree<Data>::Node& node = *stack.TopNPop();
    if (node.HasLeftChild()) { stack.Push(&node.LeftChild()); }
    if (node.HasRightChild()) { stack.Push(&node.RightChild()); }
    return *this;
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override {
    if (root != nullptr) {
      stack.Clear();
      stack.Push(root);
    }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator: virtual public MutableIterator<Data>, virtual public BTPostOrderIterator<Data> {

private:

protected:

  using BTPostOrderIterator<Data>::stack;

public:

  // Specific constructors
  // An iterator over a given mutable binary tree
  BTPostOrderMutableIterator(MutableBinaryTree<Data>& mbt) : BTPostOrderIterator<Data>(mbt) {};

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator& iter) : BTPostOrderIterator<Data>(iter) {};

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator&& iter) noexcept : BTPostOrderIterator<Data>(iter) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator& iter) {
    BTPostOrderIterator<Data>::operator=(iter);
  };

  // Move assignment
  BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&& iter) noexcept {
    BTPostOrderIterator<Data>::operator=(std::move(iter));
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator&) const noexcept = default;
  bool operator!=(const BTPostOrderMutableIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (!stack.Empty()) { return stack.Top()->Element(); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator: virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stack;

public:

  // Specific constructors
  // An iterator over a given binary tree
  BTInOrderIterator(const BinaryTree<Data>& bt) {
    if (!bt.Empty()) { stack.Push(root = &bt.Root()); }
  };

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator& iter) : root(iter.root), stack(iter.stack) {};

  // Move constructor
  BTInOrderIterator(BTInOrderIterator&& iter) noexcept {
    std::swap(root, iter.root);
    std::swap(stack, iter.stack);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator& operator=(const BTInOrderIterator& iter) {
    root = iter.root;
    stack = iter.stack;
  };

  // Move assignment
  BTInOrderIterator& operator=(BTInOrderIterator&& iter) noexcept {
    std::swap(root, iter.root);
    std::swap(stack, iter.stack);
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator&) const noexcept = default;
  bool operator!=(const BTInOrderIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override {
    if (!stack.Empty()) { return stack.Top()->Element(); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

  // Terminated() specifiers; // (should not throw exceptions)
  bool Terminated() const noexcept {
    return stack.Empty();
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // operator++() specifiers; // (throw std::out_of_range when terminated)
  ForwardIterator<Data>& operator++() override {
    const typename BinaryTree<Data>::Node& node = *stack.TopNPop();
    if (node.HasLeftChild()) { stack.Push(&node.LeftChild()); }
    if (node.HasRightChild()) { stack.Push(&node.RightChild()); }
    return *this;
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override {
    if (root != nullptr) {
      stack.Push(root);
      stack.Clear();
    }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator: virtual public MutableIterator<Data>, virtual public BTInOrderIterator<Data> {

private:

protected:

  using BTInOrderIterator<Data>::stack;

public:

  // Specific constructors
  // An iterator over a given mutable binary tree
  BTInOrderMutableIterator(MutableBinaryTree<Data>& mbt) : BTInOrderIterator<Data>(mbt) {};

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator& iter) : BTInOrderIterator<Data>(iter) {};

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator&& iter) noexcept : BTInOrderIterator<Data>(iter) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator& iter) {
    BTInOrderIterator<Data>::operator=(iter);
  };

  // Move assignment
  BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&& iter) noexcept {
    BTInOrderIterator<Data>::operator=(std::move(iter));
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator<Data>&) const noexcept = default;
  bool operator!=(const BTInOrderMutableIterator<Data>&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() {
    if (!stack.Empty()) { return stack.Top()->Element(); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator: virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {

private:

protected:
  
  const typename BinaryTree<Data>::Node* root = nullptr;
  QueueLst<const typename BinaryTree<Data>::Node*> queue;

public:

  // Specific constructors
  // An iterator over a given binary tree
  BTBreadthIterator(const BinaryTree<Data>& bt) {
    if (!bt.Empty()) { queue.Enqueue(root = &bt.Root()); }
  };

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator& iter) : root(iter.root), queue(iter.queue) {};

  // Move constructor
  BTBreadthIterator(BTBreadthIterator&& iter) noexcept {
    std::swap(root, iter.root);
    std::swap(queue, iter.queue);
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator& operator=(const BTBreadthIterator& iter) {
    root = iter.root;
    queue = iter.queue;
  };

  // Move assignment
  BTBreadthIterator& operator=(BTBreadthIterator&& iter) noexcept {
    std::swap(root, iter.root);
    std::swap(queue, iter.queue);
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator<Data>&) const noexcept = default;
  bool operator!=(const BTBreadthIterator<Data>&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override {
    if (!queue.Empty()) { return queue.Head(); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

  // Terminated() specifiers; // (should not throw exceptions)
  bool Terminated() const noexcept override {
    return queue.Empty();
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // operator++() specifiers; // (throw std::out_of_range when terminated)
  ForwardIterator<Data>& operator++() override {
    const typename BinaryTree<Data>::Node& node = *queue.HeadNDequeue();
    if (node.HasLeftChild()) { queue.Enqueue(&node.LeftChild()); }
    if (node.HasRightChild()) { queue.Enqueue(&node.RightChild()); }
    return *this;
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override {
    if (root != nullptr) {
      queue.Clear();
      queue.Enqueue(root);
    }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator: virtual public MutableIterator<Data>, virtual public BTBreadthIterator<Data> {

private:

protected:

  using BTBreadthIterator<Data>::queue;

public:

  // Specific constructors
  // An iterator over a given mutable binary tree
  BTBreadthMutableIterator(MutableBinaryTree<Data>& mbt) : BTBreadthIterator<Data>(mbt) {};

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator<Data>& iter) : BTBreadthIterator<Data>(iter) {};

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&& iter) noexcept : BTBreadthIterator<Data>(iter) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator<Data>& operator=(const BTBreadthMutableIterator<Data>& iter) {
    BTBreadthIterator<Data>::operator=(iter);
  };

  // Move assignment
  BTBreadthMutableIterator<Data>& operator=(BTBreadthMutableIterator<Data>&& iter) noexcept {
    BTBreadthIterator<Data>::operator=(std::move(iter));
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator<Data>&) const noexcept = default;
  bool operator!=(const BTBreadthMutableIterator<Data>&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (!queue.Empty()) { return const_cast<Data&>(queue.Head()); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
