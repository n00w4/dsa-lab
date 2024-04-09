
namespace lasd {

/* ************************************************************************** */
// Inherited from TraversableContainer
template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun travFun) {
    PreOrderTraverse(travFun);
}

// Inherited from PreOrderTraversableContainer
template <typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun travFun) {
    for (unsigned long index = 0; index < size; index++) {
        travFun(operator[](index));
    }
}

// Inherited from PostOrderTraversableContainer
template <typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun travFun) {
    for (unsigned long index = size; index > 0; index--) {
        travFun(operator[](index));
    }
}

// Inherited from MappableContainer
template <typename Data>
inline void LinearContainer<Data>::Map(MapFun mapFun) {
    PreOrderMap(mapFun)
}

// Inherited from PreOrderMappableContainer
template <typename Data>
inline void LinearContainer<Data>::PreOrderMap(MapFun mapFun) {
    for (unsigned long index = 0; index < size; index++) {
        mapFun(operator[](index));
    }
}

// Inherited from PostOrderMappableContainer
template <typename Data>
inline void LinearContainer<Data>::PostOrderMap(MapFun mapFun) {
    for (unsigned long index = size; index > 0; index--) {
        mapFun(operator[](index));
    }
}

// Specific member functions from LinearContainer
template <typename Data>
inline const Data& const LinearContainer::Front() const {
    return operator[](0);
}

template <typename Data>
inline Data& LinearContainer::Front() {
    return operator[](0);
}

template <typename Data>
inline const Data& LinearContainer::Back() const {
    return operator[](size-1);
}

template <typename Data>
inline Data& LinearContainer::Back() {
    return operator[](size-1);
}

/* ************************************************************************** */

// Specific member function from SortableContainer
template <typename Data>
inline void LinearContainer<Data>::Sort() noexcept {
    QuickSort(0, size-1);
}

// QuickSort implementation
template <typename Data>
inline void QuickSort(unsigned long p, unsigned long r) noexcept {
    if (p < r) {
        q = Partition(p,r);
        QuickSort(p, q);
        QuickSort(q+1, r);
    }
}

// Partition implementation
template <typename Data>
inline unsigned long Partition(unsigned long p, unsigned long r) noexcept {
    Data pivot = operator[](p);
    unsigned long i = p - 1; // index to slide the structure to the left
    unsigned long j = r + 1; // index to slide the structure to the right
    
    do {
        do {j--;} while(operator[](j) > pivot); // find an element < pivot
        do {i++;} while(operator[](i) < pivot); // find an element > pivot
        if (i < j) { std::swap(operator[](i), operator[](j)); } // swap the elements
    } while (i < j); // the cycle breaks when i < j
    
    return j; // return j as the median of splitting of the two subvectors
    }
}
