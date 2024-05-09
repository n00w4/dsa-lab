
namespace lasd {

/* ************************************************************************** */

// Node

// Comparison operators
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept {
    if (node.Element() == this->Element()){ 
        if ((this->HasRightChild() == node.HasRightChild()) && (this->HasLeftChild() == node.HasLeftChild())) {
            if (this->HasLeftChild() && this->HasRightChild()) { return ((node.LeftChild() == LeftChild()) && (node.RightChild() == RightChild())); } 
            else if (this->HasLeftChild()) { return (node.LeftChild() == LeftChild()); } 
            else if (this->HasRightChild()) { return (node.RightChild() == RightChild()); }
            else{ return true; }
        }
  }
  return false;
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept {
    return !(*this == node);
}

/* ************************************************************************** */

// BinaryTree

// Comparison operators
template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept {
    if(!(this->Empty()) && !(bt.Empty())) { return Root() == bt.Root(); }
    if((this->Empty()) && bt.Empty()) { return true; }
    else { return false; }
}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const noexcept {
    return !(*this == bt);
}

// Specific member function inherited from BreadthTraversableContainer
template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun travFun) const {
    if (!(this->Empty())) { BreadthTraverse(travFun, Root()); }
}


// Auxiliary function
template <typename Data>
void BinaryTree<Data>::BreadthTraverse(typename TraversableContainer<Data>::TraverseFun travFun, const Node& node) const {
    if (&node != nullptr) {
        travFun(node.Element());
        if (node.HasLeftChild()) { BreadthTraverse(travFun, node.LeftChild()); }
        if (node.HasRightChild()) { BreadthTraverse(travFun, node.RightChild()); }
    }
}
/* ************************************************************************** */

// MutableBinaryTree

// Specific member function inherited from BreadthMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(typename MappableContainer<Data>::MapFun mapFun) {
    if (!(this->Empty())) { BreadthMap(mapFun, Root()); }
}

// Auxiliary function
template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(typename MappableContainer<Data>::MapFun mapFun, Node& node) {
    if (&node != nullptr) {
        mapFun(const_cast<Data&>(node.Element()));
        if (node.HasLeftChild()) { BreadthMap(mapFun, const_cast<Node&>(node.LeftChild()) ); }
        if (node.HasRightChild()) { BreadthMap(mapFun, const_cast<Node&>(node.RightChild()) ); }
    }
}

/* ************************************************************************** */

}
