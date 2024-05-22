
namespace lasd {

/* ************************************************************************** */

// NodeVec

// Constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data& dat, unsigned long indx, Vector<NodeVec*>* vec) {
    element = dat;
    indexNode = indx;
    vectorPointer = vec;
}

// Specific member functions inherited from Node
template <typename Data>
inline const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return element;
}

template <typename Data>
inline Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return element;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept {
    return (indexNode * 2 + 1) >= (vectorPointer->Size());
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (indexNode * 2 + 1) < (vectorPointer->Size());
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return (indexNode * 2 + 2) < (vectorPointer->Size());
}

template <typename Data>
const typename BinaryTreeVec<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(!HasLeftChild()) { throw std::out_of_range("No left child"); }

    return *(vectorPointer->operator[](indexNode * 2 + 1));
}

template <typename Data>
const typename BinaryTreeVec<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if(!HasRightChild()) { throw std::out_of_range("No right child"); }

    return *(vectorPointer->operator[](indexNode * 2 + 2));
}

// Specific member functions inherited from MutableNode
template <typename Data>
typename BinaryTreeVec<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if (!HasLeftChild()) { throw std::out_of_range("No left child"); }

    return *(vectorPointer->operator[](indexNode * 2 + 1));
}

template <typename Data>
typename BinaryTreeVec<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::RightChild() {
    if (!HasRightChild()) { throw std::out_of_range("No right child"); }

    return *(vectorPointer->operator[](indexNode * 2 + 2));
}

/* ************************************************************************** */

// BinaryTreeVec

// Specific constructors
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& tc) {
    unsigned long index = 0;
    size = tc.Size();
    treevector = new Vector<NodeVec*>(size);
    
    tc.Traverse(
        [this, &index](const Data& data) {
            NodeVec* node = new NodeVec(const_cast<Data&>(data), index, treevector);
            treevector->operator[](index++) = node;
        });
    
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& mc) {
    unsigned long index = 0;
    size = mc.Size();
    treevector = new Vector<NodeVec*>(size);
    
    mc.Map(
        [this, &index](Data& data) {
            NodeVec* node = new NodeVec(std::move(data), index, treevector);
            treevector->operator[](index++) = std::move(node);
        });
}

// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btv) {
    size = btv.size;
    treevector = new Vector<NodeVec*>(size);
    for (unsigned long index = 0; index < size; index++) {
        NodeVec* node = new NodeVec(btv.treevector->operator[](index)->Element(), index, treevector);
        treevector->operator[](index) = node;
    }
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& btv) noexcept {
    treevector = new Vector<NodeVec*>();
    std::swap(size, btv.size);
    std::swap(treevector, btv.treevector);
}

// Destructor
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
    Clear();
    delete treevector;
    treevector = nullptr;
}

// Copy assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& btv) {
    BinaryTreeVec<Data>* tmpbt = new BinaryTreeVec<Data>(btv);
	std::swap(*this, *tmpbt);
	delete tmpbt;
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& btv) noexcept {
    std::swap(size, btv.size);
    std::swap(treevector, btv.treevector);
    return *this;
}

// Comparison operators
template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& btv) const noexcept {
    return BinaryTree<Data>::operator==(btv);
}

template <typename Data>
inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& btv) const noexcept {
    return !(*this == btv);
}

// Specific member function inherited from BinaryTree
template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if (size == 0) { throw std::length_error("Empty tree"); }
    return *(treevector->operator[](0));
}

// Specific member function inherited from MutableBinaryTree
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    if (size == 0) { throw std::length_error("Empty tree"); }
    return *(treevector->operator[](0));
}

// Specific member function inherited from ClearableContainer
template <typename Data>
void BinaryTreeVec<Data>::Clear() {
    if(size > 0) {
        for(unsigned long i = 0; i < size; i++) {
            delete (*treevector)[i];
        }
        treevector->Clear();
        size = 0;
    }
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

/* ************************************************************************ */

// Auxiliary functions
template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(typename TraversableContainer<Data>::TraverseFun travFun, const NodeVec& node) const {
    for (unsigned int index = 0; index < size; index++) {
        travFun(treevector->operator[](index)->Element());
    }
}

template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(typename MappableContainer<Data>::MapFun mapFun, NodeVec& node) {
    for (unsigned int index = 0; index < size; index++) {
        mapFun(treevector->operator[](index)->Element());
    }
}

/* ************************************************************************** */

}
