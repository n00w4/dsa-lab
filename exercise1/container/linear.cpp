
namespace lasd {

/* ************************************************************************** */
// Specific member functions Linear Container
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
/* ************************************************************************** */

// Specific member function SortableContainer
template <typename Data>
inline void LinearContainer<Data>::Sort() noexcept {
    QuickSort(0, size-1);
}

// QuickSort implementation

}
