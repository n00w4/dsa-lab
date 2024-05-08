
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
    unsigned long index = 0;
    size = tc.Size();
    Nodes = new NodeVec[size];
    tc.Traverse(
        [this, &index](const Data& data) {
            Nodes->Tree->Elements[index++] = data;
        });
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& mc) {
    unsigned long index = 0;
    size = mc.Size();
    Nodes = new NodeVec[size];
    mc.Map(
        [this, &index](const Data& data) {
            Nodes->Tree->Elements[index++] = data;
        });
}

// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btv) {
    unsigned long index = 0;
    size = btv.size;
    Nodes = new NodeVec[size];
    btv.BreadthTraverse(
        [this, &index](const Data& data) {
            Nodes->Tree->Elements[index++] = data;
        });
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
        unsigned long index = 0;
        size = btv.size;
        Nodes = new NodeVec[size];
        btv.BreadthTraverse(
            [this, &index](const Data& data) {
                Nodes->Tree->Elements[index++] = data;
            });
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
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if (size == 0) { throw std::length_error("Empty tree"); }
    return Nodes[0];
}

// Specific member function inherited from MutableBinaryTree
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    if (size == 0) { throw std::length_error("Empty tree"); }
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
    
}

template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(typename MappableContainer<Data>::MapFun mapFun, Node& node) {
    if (node != nullptr) {
        travFun(node.Element());
        if (node.HasLeftChild()) { BreadthMap(mapFun, node.LeftChild()); }
        if (node.HasRightChild()) { BreadthMap(mapFun, node.RightChild()); }
    }
}

/* ************************************************************************** */

}
