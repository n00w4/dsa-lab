
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

// Specific member function inherited from TraversableContainer
template <typename Data>
void BinaryTree<Data>::Traverse(TraverseFun travFun) const {
    if (!(this->Empty())) { PreOrderTraverse(travFun, Root()); }
}

// Specific member function inherited from PreOrderTraversableContainer
template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun travFun) const {
    if (!(this->Empty())) { PreOrderTraverse(travFun, Root()); }
}

// Specific member function inherited from PostOrderTraversableContainer
template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun travFun) const {
    if (!(this->Empty())) { PostOrderTraverse(travFun, Root()); }
}

// Specific member function inherited from InOrderTraversableContainer
template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun travFun) const {
    if (!(this->Empty())) { InOrderTraverse(travFun, Root()); }
}


// Specific member function inherited from BreadthTraversableContainer
template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun travFun) const {
    if (!(this->Empty())) { BreadthTraverse(travFun, Root()); }
}

// Auxiliary function

template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(typename TraversableContainer<Data>::TraverseFun travFun, const Node& node) const {
    travFun(node.Element());
    if (node.HasLeftChild()) { PreOrderTraverse(travFun, node.LeftChild()); }
    if (node.HasRightChild()) { PreOrderTraverse(travFun, node.RightChild()); }
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(typename TraversableContainer<Data>::TraverseFun travFun, const Node& node) const {
    if (node.HasLeftChild()) { PostOrderTraverse(travFun, node.LeftChild()); }
    if (node.HasRightChild()) { PostOrderTraverse(travFun, node.RightChild()); }
    travFun(node.Element());
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(typename TraversableContainer<Data>::TraverseFun travFun, const Node& node) const {
    if (node.HasLeftChild()) { InOrderTraverse(travFun, node.LeftChild()); }
    travFun(node.Element());
    if (node.HasRightChild()) { InOrderTraverse(travFun, node.RightChild()); }
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(typename TraversableContainer<Data>::TraverseFun travFun, const Node& node) const {
    lasd::QueueLst<const Node*> queue;
    queue.Enqueue(&node);
    const Node* tmp;

    while(!(queue.Empty())) {
        tmp = queue.HeadNDequeue();
        
        travFun(tmp->Element());
        if(tmp->HasLeftChild()) { queue.Enqueue(&(tmp->LeftChild())); }   
        if(tmp->HasRightChild()) { queue.Enqueue(&(tmp->RightChild())); }
  }
}

/* ************************************************************************** */

// MutableBinaryTree

// Specific member function inherited from MappableContainer
template <typename Data>
inline void MutableBinaryTree<Data>::Map(typename MappableContainer<Data>::MapFun mapFun) {
    if (!(this->Empty())) { PreOrderMap(mapFun, Root()); }
}

// Specific member function inherited from PreOrderMappableContainer
template <typename Data>
inline void MutableBinaryTree<Data>::PreOrderMap(typename MappableContainer<Data>::MapFun mapFun) {
    if (!(this->Empty())) { PreOrderMap(mapFun, Root()); }
}

// Specific member function inherited from PostOrderMappableContainer
template <typename Data>
inline void MutableBinaryTree<Data>::PostOrderMap(typename MappableContainer<Data>::MapFun mapFun) {
    if (!(this->Empty())) { PostOrderMap(mapFun, Root()); }
}

// Specific member function inherited from InOrderMappableContainer
template <typename Data>
inline void MutableBinaryTree<Data>::InOrderMap(typename MappableContainer<Data>::MapFun mapFun) {
    if (!(this->Empty())) { InOrderMap(mapFun, Root()); }
}

// Specific member function inherited from BreadthMappableContainer
template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(typename MappableContainer<Data>::MapFun mapFun) {
    if (!(this->Empty())) { BreadthMap(mapFun, Root()); }
}

/* ************************************************************************** */

// Auxiliary function

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(typename MappableContainer<Data>::MapFun mapFun, MutableNode& node) {
    mapFun(node.Element());
    if (node.HasLeftChild()) { PreOrderMap(mapFun, node.LeftChild()); }
    if (node.HasRightChild()) { PreOrderMap(mapFun, node.RightChild()); }
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(typename MappableContainer<Data>::MapFun mapFun, MutableNode& node) {
    if (node.HasLeftChild()) { PostOrderMap(mapFun, node.LeftChild()); }
    if (node.HasRightChild()) { PostOrderMap(mapFun, node.RightChild()); }
    mapFun(node.Element());
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(typename MappableContainer<Data>::MapFun mapFun, MutableNode& node) {
    if (node.HasLeftChild()) { InOrderMap(mapFun, node.LeftChild()); }
    mapFun(node.Element());
    if (node.HasRightChild()) { InOrderMap(mapFun, node.RightChild()); }
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(typename MappableContainer<Data>::MapFun mapFun, MutableNode& node) {
    lasd::QueueLst<MutableNode*> queue;
    queue.Enqueue(&node);
    MutableNode* tmp;

    while(!(queue.Empty())) {
        tmp = queue.HeadNDequeue();
        mapFun(tmp->Element());

        if(tmp->HasLeftChild()) { queue.Enqueue(&(tmp->LeftChild())); }   
        if(tmp->HasRightChild()) { queue.Enqueue(&(tmp->RightChild())); }
  }
}

/* ************************************************************************** */

}
