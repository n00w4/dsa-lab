#include "traversable.hpp"

namespace lasd {

/* ************************************************************************** */

// TraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFunction, Accumulator initialAcc) const {
    Accumulator acc = initialAcc;
    Traverse(
        [&acc, foldFunction](const Data &data) {
            acc = foldFunction(data, acc);
        });
    return acc;
}

template <typename Data>
inline bool TraversableContainer<Data>::Exists(const Data in) const noexcept {
    bool exists = false;
    Traverse(
        [&in, &exists](const Data &data) {
            exists |= (data == in);
        }
    )
    return exists;
}

// PreOrderTraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFunction, Accumulator initialAcc) const {
    Accumulator acc = initialAcc;
    PreOrderTraverse(
        [&acc, foldFunction](const Data &data) {
            acc = foldFunction(data, acc);
        });
    return acc;
}

template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
    PreOrderTraverse(traverseFunction);
}

// PostOrderTraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFunction, Accumulator initialAcc) const {
    Accumulator acc = initialAcc;
    PostOrderTraverse(
        [&acc, foldFunction](const Data &data) {
            acc = foldFunction(data, acc);
        });
    return acc;
}

template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
    PostOrderTraverse(traverseFunction);
}

// InOrderTraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> foldFunction, Accumulator initialAcc) const {
    Accumulator acc = initialAcc;
    InOrderTraverse(
        [&acc, foldFunction](const Data &data) {
            acc = foldFunction(data, acc);
        });
    return acc;
}

template <typename Data>
inline void InOrderTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
    InOrderTraverse(traverseFunction);
}

// BreadthTraversableContainer implementations
template <typename Data>
template <typename Accumulator>
inline Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> foldFunction, Accumulator initialAcc) const {
    Accumulator acc = initialAcc;
    BreadthTraverse(
        [&acc, foldFunction](const Data &data) {
            acc = foldFunction(data, acc);
        });
    return acc;
}

template <typename Data>
inline void BreadthTraversableContainer<Data>::Traverse(TraverseFun traverseFunction) const {
    BreadthTraverse(traverseFunction);
}

/* ************************************************************************** */

}
