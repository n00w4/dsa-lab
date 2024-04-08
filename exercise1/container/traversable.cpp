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

/* ************************************************************************** */

}
