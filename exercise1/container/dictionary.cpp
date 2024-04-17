#include "dictionary.hpp"

namespace lasd {

/* ************************************************************************** */

// InsertAll - copy of the value from TraversableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& tc) {
    bool all = true;
    tc.Traverse(
        [this, &all](const Data& data) {
            all &= Insert(data);
        });
    return all;
}

// InsertAll - move of the value from MappableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& mc) {
    bool all = true;
    mc.Map(
        [this, &all](Data& data) {
            all &= Insert(std::move(data));
        });
    return all;
}

// RemoveAll from TraversableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& tc) {
    bool all = true;
    tc.Traverse(
        [this, &all](const Data& data) {
            all &= Remove(data);
        });
    return all;
}

// InsertSome - copy of the value from TraversableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& tc) {
    bool some = false;
    tc.Traverse(
        [this, &some](const Data& data) {
            some |= Insert(data);
        });
    return some;
}

// InsertSome - move of the value from MappableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& mc) {
    bool some = false;
    mc.Map(
        [this, &some](Data& data) {
            some |= Insert(std::move(data));
        });
    return some;
}

// RemoveSome from TraversableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& tc) {
    bool some = false;
    tc.Traverse(
        [this, &some](const Data& data) {
            some |= Remove(data);
        });
    return some;
}

/* ************************************************************************** */

}
