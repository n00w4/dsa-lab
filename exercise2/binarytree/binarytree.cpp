
namespace lasd {

/* ************************************************************************** */

// Node

// Comparison operators
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept {
    bool val = true;

    if(Element() == node.Element()) {
        if(HasLeftChild() && node.HasLeftChild()) {
            val = (LeftChild() == node.LeftChild());
        }
        else if (HasLeftChild() || node.HasLeftChild()) {
            val = false;
        }
        
        if(val) {
            if(HasRightChild() && node.HasRightChild()) {
                val = RightChild() == node.RightChild();
            }
            else if(HasRightChild() || node.HasRightChild()) {
                val = false;
            }
        }
  }
  else { val = false; }
    return val;
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

// Specific member function inherited from TraversableContainer
template <typename Data>
void BinaryTree<Data>::Traverse(TraverseFun travFun) const {
    PostOrderTraverse(travFun, Root());
}

// Specific member function inherited from PreOrderTraversableContainer
template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun travFun) const {
    PreOrderTraverse(travFun, Root());
}

// Specific member function inherited from PostOrderTraversableContainer
template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun travFun) const {
    PostOrderTraverse(travFun, Root());
}

// Specific member function inherited from InOrderTraversableContainer
template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun travFun) const {
    InOrderTraverse(travFun, Root());
}

// Specific member function inherited from BreadthTraversableContainer
template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun travFun) const {
    BreadthTraverse(travFun, Root());
}

/* ************************************************************************** */

// MutableBinaryTree

// Specific member function inherited from MappableContainer
template <typename Data>
void MutableBinaryTree<Data>::Map(MapFun mapFun) {
    PostOrderMap(mapFun, Root());
}

// Specific member function inherited from PreOrderMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun mapFun) {
    PreOrderMap(mapFun, Root());
}

// Specific member function inherited from PostOrderMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun mapFun) {
    PostOrderMap(mapFun, Root());
}

// Specific member function inherited from InOrderMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun mapFun) {
    InOrderMap(mapFun, Root());
}

// Specific member function inherited from BreadthMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun mapFun) {
    BreadthMap(mapFun, Root());
}

/* ************************************************************************** */

}
