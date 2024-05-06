#include "traversable.hpp"

namespace lasd {

/* ************************************************************************** */

// TraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFunction, Accumulator inAcc) const {
    Traverse(
        [&inAcc, foldFunction](const Data& data) {
            inAcc = foldFunction(data, inAcc);
        });
    return inAcc;
}

template <typename Data>
inline bool TraversableContainer<Data>::Exists(const Data& in) const noexcept {
    bool exists = false;
    Traverse(
        [&in, &exists](const Data& data) {
            exists |= (data == in);
        });
    return exists;
}

// PreOrderTraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFunction, Accumulator inAcc) const {
    PreOrderTraverse(
        [&inAcc, foldFunction](const Data& data) {
            inAcc = foldFunction(data, inAcc);
        });
    return inAcc;
}

template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
    PreOrderTraverse(traverseFunction);
}

// PostOrderTraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFunction, Accumulator inAcc) const {
    PostOrderTraverse(
        [&inAcc, foldFunction](const Data& data) {
            inAcc = foldFunction(data, inAcc);
        });
    return inAcc;
}

template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
    PostOrderTraverse(traverseFunction);
}

// InOrderTraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> foldFunction, Accumulator inAcc) const {
    InOrderTraverse(
        [&inAcc, foldFunction](const Data& data) {
            inAcc = foldFunction(data, inAcc);
        });
    return inAcc;
}

template <typename Data>
inline void InOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
    InOrderTraverse(traverseFunction);
}

// BreadthTraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> foldFunction, Accumulator inAcc) const {
    BreadthTraverse(
        [&inAcc, foldFunction](const Data& data) {
            inAcc = foldFunction(data, inAcc);
        });
    return inAcc;
}

template <typename Data>
inline void BreadthTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
    BreadthTraverse(traverseFunction);
}

/* ************************************************************************** */

}
