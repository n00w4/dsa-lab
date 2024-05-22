
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
    virtual bool IsLeaf() const noexcept { return !(HasLeftChild() || HasRightChild()); };
    
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
  inline void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member
  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // PostOrderTraverse(arguments) specifiers; // Override PostOrderTraversableContainer member
  inline void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  // InOrderTraverse(arguments) specifiers; // Override InOrderTraversableContainer member
  inline void InOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  // BreadthTraverse(arguments) specifiers; // Override BreadthTraversableContainer member
  void BreadthTraverse(TraverseFun) const override;

protected:

  // Auxiliary functions
  void PreOrderTraverse(TraverseFun, const Node&) const;
  void PostOrderTraverse(TraverseFun, const Node&) const;
  void InOrderTraverse(TraverseFun, const Node&) const;
  void BreadthTraverse(TraverseFun, const Node&) const;

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
  inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // Override PreOrderMappableContainer member
  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // Override PostOrderMappableContainer member
  inline void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  // Override InOrderMappableContainer member
  inline void InOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  // Override BreadthMappableContainer member
  void BreadthMap(MapFun) override;

protected:

  // Auxiliary functions
  void PreOrderMap(MapFun, MutableNode&);
  void PostOrderMap(MapFun, MutableNode&);
  void InOrderMap(MapFun, MutableNode&);
  void BreadthMap(MapFun, MutableNode&);

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
  bool operator==(const BTPreOrderIterator& iter) const noexcept {
    if(root != iter.root) { return false; }
    if(stack != iter.stack) { return false; }
    return true;
  };

  bool operator!=(const BTPreOrderIterator& iter) const noexcept {
    return !(*this == iter);
  };

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
    if (Terminated()) { throw std::out_of_range("Iterator terminated"); }
    const typename BinaryTree<Data>::Node& node = *stack.TopNPop();
    if (node.HasRightChild()) { stack.Push(&node.RightChild()); }
    if (node.HasLeftChild()) { stack.Push(&node.LeftChild()); }
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
  BTPreOrderMutableIterator(BTPreOrderMutableIterator&& iter) noexcept : BTPreOrderIterator<Data>(std::move(iter)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator& iter) {
    BTPreOrderIterator<Data>::operator=(iter);
    return *this;
  };

  // Move assignment
  BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&& iter) noexcept {
    BTPreOrderIterator<Data>::operator=(std::move(iter));
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator& iter) const noexcept {
    return BTPreOrderIterator<Data>::operator==(iter);
  };
  bool operator!=(const BTPreOrderMutableIterator& iter) const noexcept {
    return BTPreOrderIterator<Data>::operator!=(iter);
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  using BTPreOrderIterator<Data>::operator*;
  // operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (!stack.Empty()) { return const_cast<Data&>(stack.Top()->Element()); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator: virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node* root = nullptr;
  const typename BinaryTree<Data>::Node* last = nullptr;
  StackLst<const typename BinaryTree<Data>::Node*> stack;

public:

  // Specific constructors
  // An iterator over a given binary tree
  BTPostOrderIterator(const BinaryTree<Data>& bt) {
    if (!bt.Empty()) {
      root = &bt.Root();
      GetMostLeftLeaf(bt.Root());
    }
  };

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator& iter) : root(iter.root), last(iter.last), stack(iter.stack) {};

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator&& iter) noexcept : root(iter.root), last(iter.last), stack(std::move(iter.stack)) {
    iter.root = nullptr;
    iter.last = nullptr;
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator& operator=(const BTPostOrderIterator& iter) {
    root = iter.root;
    last = iter.last;
    stack = iter.stack;
    return *this;
  };

  // Move assignment
  BTPostOrderIterator& operator=(BTPostOrderIterator&& iter) {
    std::swap(root, iter.root);
    std::swap(last, iter.last);
    std::swap(stack, iter.stack);
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator& iter) const noexcept {
    if(root != iter.root) { return false; }
    if(last != iter.last) { return false; }
    if(stack != iter.stack) { return false; }
    return true;
  };
  bool operator!=(const BTPostOrderIterator& iter) const noexcept {
    return !(*this == iter);
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override {
    if (!(Terminated())) { return stack.Top()->Element(); }
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
    if (Terminated()) { throw std::out_of_range("Iterator terminated"); }
    last = stack.TopNPop();
    if (!stack.Empty() && stack.Top()->HasRightChild() && &(stack.Top()->RightChild()) != last) {
      GetMostLeftLeaf(stack.Top()->RightChild());
    }
    return *this;
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override {
    if (root != nullptr) {
      stack.Clear();
      stack.Push(root);
      GetMostLeftLeaf(*root);
      last = root;
    }
  };

protected:
  // GetMostLeftLeaf auxiliary function
  void GetMostLeftLeaf(const typename BinaryTree<Data>::Node& node) {
    const typename BinaryTree<Data>::Node* current = &node;
    while (current != nullptr) {
        stack.Push(current);
        if (current->HasLeftChild()) {
            current = &(current->LeftChild());
        } else if (current->HasRightChild()) {
            current = &(current->RightChild());
        } else {
            current = nullptr;
        }
    }
  }

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
  BTPostOrderMutableIterator(BTPostOrderMutableIterator&& iter) noexcept : BTPostOrderIterator<Data>(std::move(iter)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator& iter) {
    BTPostOrderIterator<Data>::operator=(iter);
    return *this;
  };

  // Move assignment
  BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&& iter) noexcept {
    BTPostOrderIterator<Data>::operator=(std::move(iter));
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator& iter) const noexcept {
    return BTPostOrderIterator<Data>::operator==(iter);
  };
  bool operator!=(const BTPostOrderMutableIterator& iter) const noexcept {
    return BTPostOrderIterator<Data>::operator!=(iter);
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  using BTPostOrderIterator<Data>::operator*;
  // operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (!stack.Empty()) { return const_cast<Data&>(stack.Top()->Element()); }
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
    if (!bt.Empty()) {
      root = &bt.Root();
      GetMostLeftNode(bt.Root());
    }
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
    return *this;
  };

  // Move assignment
  BTInOrderIterator& operator=(BTInOrderIterator&& iter) noexcept {
    std::swap(root, iter.root);
    std::swap(stack, iter.stack);
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator& iter) const noexcept {
    return (root == iter.root) && (stack == iter.stack);
  };
  bool operator!=(const BTInOrderIterator& iter) const noexcept {
    return !(*this == iter);
  };

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
    if (Terminated()) { throw std::out_of_range("Iterator terminated"); }
    const typename BinaryTree<Data>::Node& node = *stack.TopNPop();
    if (node.HasRightChild()) {
      GetMostLeftNode(node.RightChild());
    }
    return *this;
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override {
    if (root != nullptr) {
      stack.Clear();
      GetMostLeftNode(*root);
    }
  };

protected:
  // GetMostLeftNode auxiliary function
  void GetMostLeftNode(const typename BinaryTree<Data>::Node& node) {
    const typename BinaryTree<Data>::Node* current = &node;
    while (current != nullptr) {
        stack.Push(current);
        if (current->HasLeftChild()) {
            current = &current->LeftChild();
        } else {
            current = nullptr;
        }
    }
}

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
  BTInOrderMutableIterator(BTInOrderMutableIterator&& iter) noexcept : BTInOrderIterator<Data>(std::move(iter)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator& iter) {
    BTInOrderIterator<Data>::operator=(iter);
    return *this;
  };

  // Move assignment
  BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&& iter) noexcept {
    BTInOrderIterator<Data>::operator=(std::move(iter));
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator<Data>& iter) const noexcept {
    return BTInOrderIterator<Data>::operator==(iter);
  };
  bool operator!=(const BTInOrderMutableIterator<Data>& iter) const noexcept {
    return BTInOrderIterator<Data>::operator!=(iter);
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  using BTInOrderIterator<Data>::operator*;
  // operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() {
    if (!stack.Empty()) { return const_cast<Data&>(stack.Top()->Element()); }
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
    return *this;
  };

  // Move assignment
  BTBreadthIterator& operator=(BTBreadthIterator&& iter) noexcept {
    std::swap(root, iter.root);
    std::swap(queue, iter.queue);
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator<Data>& iter) const noexcept {
    if(root != iter.root) { return false; }
    if(queue != iter.queue) { return false; }
    return true;
  };
  bool operator!=(const BTBreadthIterator<Data>& iter) const noexcept {
    return !(*this == iter);
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override {
    if (!queue.Empty()) { return queue.Head()->Element(); }
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
    if (queue.Empty()) { throw std::out_of_range("Iterator terminated"); }
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
  BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&& iter) noexcept : BTBreadthIterator<Data>(std::move(iter)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator<Data>& operator=(const BTBreadthMutableIterator<Data>& iter) {
    BTBreadthIterator<Data>::operator=(iter);
    return *this;
  };

  // Move assignment
  BTBreadthMutableIterator<Data>& operator=(BTBreadthMutableIterator<Data>&& iter) noexcept {
    BTBreadthIterator<Data>::operator=(std::move(iter));
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator<Data>& iter) const noexcept {
    return BTBreadthIterator<Data>::operator==(iter);
  };
  bool operator!=(const BTBreadthMutableIterator<Data>& iter) const noexcept {
    return !(*this == iter);
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  using BTBreadthIterator<Data>::operator*;
  // operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (!queue.Empty()) { return const_cast<Data&>(queue.Head()->Element()); }
    else { throw std::out_of_range("Iterator terminated"); }
  };

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
