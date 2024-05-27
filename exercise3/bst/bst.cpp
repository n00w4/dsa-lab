
namespace lasd {

/* ************************************************************************** */

// BST

// A bst obtained from a TraversableContainer
template <typename Data>
BST<Data>::BST(const TraversableContainer<Data>& tc) {
    tc.Traverse([this](const Data& data) {
        Insert(data);
    });
}

// A bst obtained from a MappableContainer
template <typename Data>
BST<Data>::BST(MappableContainer<Data>&& mc) {
    mc.Map([this](const Data& data) {
        Insert(std::move(data));
    });
}

// Copy assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst){
  BinaryTreeLnk<Data>::operator=(bst);
  return *this;
}

// Move assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
    BinaryTreeLnk<Data>::operator=(std::move(bst));
    return *this;
}

// Comparison operators
template <typename Data>
bool BST<Data>::operator==(const BST &bt) const noexcept {
    if (size == bt.size) {
        BTInOrderIterator<Data> iterThis(*this);
        BTInOrderIterator<Data> iterOther(bt);
        for (; !iterThis.Terminated(); ++iterThis, ++iterOther) {
            if((*iterThis) != (*iterOther)) {  return false; }
        }
        return true;
    }
    return false;
}

template <typename Data>
bool BST<Data>::operator!=(const BST &bt) const noexcept {
    return !(*this == bt);
}

/* ************************************************************************ */

// Specific member functions
template <typename Data>
const Data& BST<Data>::Min() const {
    if (root == nullptr) {
        throw std::length_error("Access to an empty BST.");
    }
    return FindPointerToMin(root)->element;
}

template <typename Data>
Data BST<Data>::MinNRemove() {
    if (root == nullptr) {
        throw std::length_error("Access to an empty BST.");
    }
    return DataNDelete(DetachMin(root));
}

template <typename Data>
void BST<Data>::RemoveMin() {
    if (root == nullptr) {
        throw std::length_error("Access to an empty BST.");
    }
    delete DetachMin(root);    
}

template <typename Data>
const Data& BST<Data>::Max() const {
    if (root == nullptr) {
        throw std::length_error("Access to an empty BST.");
    }
    return FindPointerToMax(root)->element;
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
    if (root == nullptr) {
        throw std::length_error("Access to an empty BST.");
    }
    return DataNDelete(DetachMax(root));
}

template <typename Data>
void BST<Data>::RemoveMax() {
    if (root == nullptr) {
        throw std::length_error("Access to an empty BST.");
    }
    delete DetachMax(root);
}

template <typename Data>
const Data& BST<Data>::Predecessor(const Data& data) const {
    const typename BST<Data>::NodeLnk* const* pointer = FindPointerToPredecessor(root, data);
    if (*pointer == nullptr) {
        throw std::length_error("Predecessor not found");
    }
    return (*pointer)->element;   
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& data) {
    typename BST<Data>::NodeLnk** pointer = FindPointerToPredecessor(root, data);
    if (pointer == nullptr) {
        throw std::length_error("Predecessor not found");
    }
    return DataNDelete(Detach(*pointer));
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& data) {
    typename BST<Data>::NodeLnk** pointer = FindPointerToPredecessor(root, data);
    if (pointer == nullptr) {
        throw std::length_error("Predecessor not found");
    }
    delete Detach(*pointer);
}

/* ************************************************************************ */

template <typename Data>
const Data& BST<Data>::Successor(const Data& data) const {
    const typename BST<Data>::NodeLnk* const* pointer = FindPointerToSuccessor(root, data);
    if (pointer == nullptr) {
        throw std::length_error("Successor not found");
    }
    return (*pointer)->element;
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& data) {
    typename BST<Data>::NodeLnk** pointer = FindPointerToSuccessor(root, data);
    if (pointer == nullptr) {
        throw std::length_error("Successor not found");
    }
    return DataNDelete(Detach(*pointer));
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& data) {
    const typename BST<Data>::NodeLnk** pointer = FindPointerToSuccessor(root, data);
    if (pointer == nullptr) {
        throw std::length_error("Successor not found");
    }
    delete Detach(*pointer);
}

/* ************************************************************************** */

// Specific member functions inherited from DictionaryContainer
template <typename Data>
bool BST<Data>::Insert(const Data& data) {
    NodeLnk*& pointer = FindPointerTo(root, data);
    if (pointer == nullptr) {
        pointer = new NodeLnk(data);
        size++;
        return true;
    }
    return false;
}

template <typename Data>
bool BST<Data>::Insert(Data&& data) {
    NodeLnk*& pointer = FindPointerTo(root, data);
    if (pointer == nullptr) {
        pointer = new NodeLnk(std::move(data));
        size++;
        return true;
    }
    return false;
}

template <typename Data>
bool BST<Data>::Remove(const Data& data) {
    NodeLnk*& nodeToRemove = FindPointerTo(root, data);
    if (root == nullptr) { return false; }
    if (nodeToRemove == nullptr) { return false; }
    delete Detach(nodeToRemove);
    return true;
}

/* ************************************************************************ */

// Specific member function inherited from TestableContainer
template <typename Data>
bool BST<Data>::Exists(const Data& data) const noexcept {
    return FindPointerTo(root, data) != nullptr;
}

/* ************************************************************************** */

// Auxiliary function
template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk *node) {
    Data dat = std::move(node->element);
    delete node;
    return dat;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {
    if (node != nullptr) {
        if (node->left == nullptr) { return Skip2Right(node); }
        else if (node->right == nullptr) { return Skip2Left(node); }
        else {
          // Doesn't matter when the node has right and left children
          // BST<Data>::NodeLnk* detach = DetachMin(node->right);
            BST<Data>::NodeLnk* detach = DetachMax(node->left);
            std::swap(node->element, detach->element);
            return detach; 
        }
    }
    return nullptr;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept {
    return Skip2Right(FindPointerToMin(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept {
    return Skip2Left(FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& node) noexcept {
    NodeLnk* newleft = nullptr;
    if (node != nullptr) {
        std::swap(newleft, node->left);
        std::swap(newleft, node);
        size--;
    }
    return newleft; 
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& node) noexcept {
    NodeLnk* newright = nullptr;
    if (node != nullptr) {
        std::swap(newright, node->right);
        std::swap(newright, node);
        size--;
    }
    return newright;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& node) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));
}

template <typename Data>
const typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(const NodeLnk* const& node) const noexcept {
    const NodeLnk* const* nodeptr = &node;
    const NodeLnk* current = node;
    if (current != nullptr) {
        while (current->left != nullptr) {
            nodeptr = &current->left;
            current = current->left;
        }
    }
    return *nodeptr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk*& node) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(node));
}

template <typename Data>
const typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(const NodeLnk* const& node) const noexcept {
    const NodeLnk* const* nodeptr = &node;
    const NodeLnk* current = node;
    if (current != nullptr) {
        while (current->right != nullptr) {
            nodeptr = &current->right;
            current = current->right;
        }
    }
    return *nodeptr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk*& node, const Data& data) noexcept {
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node, data));
}

template <typename Data>
const typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(const NodeLnk* const& node, const Data& data) const noexcept {
    const NodeLnk* const* nodeptr = &node;
    const NodeLnk* current = node;
    while (current != nullptr) {
        if (current->element > data) {
            nodeptr = &current->left;
            current = current->left;
        } else if (current->element < data) {
            nodeptr = &current->right;
            current = current->right;
        } else {
            break;
        }
    }
    return *nodeptr;
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk*& node, const Data& data) noexcept {
    return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node, data));
}

template <typename Data>
const typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(const NodeLnk* const& node, const Data& data) const noexcept {
    const NodeLnk* const* nodeptr = &node;
    const NodeLnk* const* nodeprd = nullptr;
    while((*nodeptr) != nullptr && (*nodeptr)->element != data) {
        if ((*nodeptr)->element > data) { nodeptr = &(*nodeptr)->left; }
        else if ((*nodeptr)->element < data) {
            nodeprd = nodeptr;
            nodeptr = &(*nodeptr)->right;
        }
    }
    if ((*nodeptr) != nullptr && (*nodeptr)->left != nullptr) {
        nodeprd = &FindPointerToMax((*nodeptr)->left);
    }
    return nodeprd;
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk*& node, const Data& data) noexcept {
    return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node, data));
}

template <typename Data>
const typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(const NodeLnk* const& node, const Data& data) const noexcept {
    const NodeLnk* const* nodeptr = &node;
    const NodeLnk* const* nodesuc = nullptr;
    while((*nodeptr) != nullptr && (*nodeptr)->element != data) {
        if ((*nodeptr)->element < data) { nodeptr = &(*nodeptr)->right; }
        else if ((*nodeptr)->element > data) {
            nodesuc = nodeptr;
            nodeptr = &(*nodeptr)->left;
        }
    }
    if ((*nodeptr) != nullptr && (*nodeptr)->right != nullptr) {
        nodesuc = &FindPointerToMin((*nodeptr)->right);
    }
    return nodesuc;
}

/* ************************************************************************** */

}
