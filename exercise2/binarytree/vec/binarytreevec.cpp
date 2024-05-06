
namespace lasd {

/* ************************************************************************** */

// NodeVec

// Specific member functions inherited from Node
template <typename Data>
inline const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return Tree->Elements[Index()];
}

template <typename Data>
inline Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return Tree->Elements[Index()];
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept {
    return (2 * Index() + 1 >= Tree->size);
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (2 * Index() + 1 < Tree->size);
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return (2 * Index() + 2 < Tree->size);
}

template <typename Data>
const typename BinaryTreeVec<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    unsigned long child = 2 * Index() + 1;
    if (child < Tree->size) { return Tree->Nodes[child]; }
    else { throw std::length_error("No left child"); }
}

template <typename Data>
const typename BinaryTreeVec<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    unsigned long child = 2 * Index() + 2;
    if (child < Tree->size) { return Tree->Nodes[child]; }
    else { throw std::length_error("No right child"); }
}

// Specific member functions inherited from MutableNode
template <typename Data>
typename BinaryTreeVec<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::LeftChild() {
    unsigned long child = 2 * Index() + 1;
    if (child < Tree->size) { return Tree->Nodes[child]; }
    else { throw std::length_error("No left child"); }
}

template <typename Data>
typename BinaryTreeVec<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::RightChild() {
    unsigned long child = 2 * Index() + 2;
    if (child < Tree->size) { return Tree->Nodes[child]; }
    else { throw std::length_error("No right child"); }
}

// Auxiliary function
template <typename Data>
unsigned long BinaryTreeVec<Data>::NodeVec::Index() const noexcept {
    if (Tree == nullptr) { return 0; }
    else { return (this - Tree->Nodes) / 2; }
}

/* ************************************************************************** */

// BinaryTreeVec

// Specific constructors
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& tc) {
    size = tc.Size();
    Nodes = new NodeVec[size];
    for (unsigned long index = 0; index < size; index++) {
        Nodes[index] = NodeVec(this, index, tc[index]);
    }
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& mc) {
    size = mc.Size();
    Nodes = new NodeVec[size];
    for (unsigned long index = 0; index < size; index++) {
        Nodes[index] = NodeVec(this, index, std::move(mc[index]));
    }
}

// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btv) {
    size = btv.size;
    Nodes = new NodeVec[size];
    for (unsigned long index = 0; index < size; index++) {
        Nodes[index] = NodeVec(this, index, btv[index]);
    }
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& btv) noexcept {
    std::swap(size, btv.size);
    std::swap(Nodes, btv.Nodes);
}

// Destructor
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
    delete[] Nodes;
}

// Copy assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& btv) {
    if (this != &btv) {
        delete[] Nodes;
        size = btv.size;
        Nodes = new NodeVec[size];
        for (unsigned long index = 0; index < size; index++) {
            Nodes[index] = NodeVec(this, index, btv[index]);
        }
    }
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& btv) noexcept {
    if (this != &btv) {
        delete[] Nodes;
        std::swap(size, btv.size);
        std::swap(Nodes, btv.Nodes);
    }
    return *this;
}

// Comparison operators
template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& btv) const noexcept {
    if (size == btv.size) {
        for (unsigned long index = 0; index < size; index++) {
            if (Nodes[index] != btv.Nodes[index]) { return false; }
        }
        return true;
    } else { return false; }
}

template <typename Data>
inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& btv) const noexcept {
    return !(*this == btv);
}

// Specific member function inherited from BinaryTree
template <typename Data>
const typename BinaryTree<Data>::Node& BinaryTreeVec<Data>::Root() const {
    return Nodes[0];
}

// Specific member function inherited from MutableBinaryTree
template <typename Data>
typename MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::Root() {
    return Nodes[0];
}

// Specific member function inherited from ClearableContainer
template <typename Data>
void BinaryTreeVec<Data>::Clear() {
    delete[] Nodes;
    Nodes = nullptr;
    size = 0;
}

// Specific member function inherited from BreadthTraversableContainer
template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(typename TraversableContainer<Data>::TraverseFun travFun) const {
    BreadthTraverse(travFun, Root());
}

// Specific member function inherited from BreadthMappableContainer
template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(typename MappableContainer<Data>::MapFun mapFun) {
    BreadthMap(mapFun, Root());
}

// Auxiliary functions
template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(typename TraversableContainer<Data>::TraverseFun travFun, const Node& node) const {
    if (node.IsLeaf()) { travFun(node.Element()); }
    else {
        if (node.HasLeftChild()) { BreadthTraverse(travFun, node.Left()); }
        if (node.HasRightChild()) { BreadthTraverse(travFun, node.Right()); }
    }
}

/* ************************************************************************** */

}
