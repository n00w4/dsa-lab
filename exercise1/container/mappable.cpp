#include "mappable.hpp"

namespace lasd {

/* ************************************************************************** */
// PreOrderMappableContainer implementations
template <typename Data>
inline void PreOrderMappableContainer<Data>::PreOrderMap(MapFun mapFun) {
    PreOrderMap(mapFun);
};

// PostOrderMappableContainer implementations
template <typename Data>
inline void PostOrderMappableContainer<Data>::PostOrderMap(MapFun mapFun) {
    PostOrderMap(mapFun);
};

// InOrderMappableContainer implementations
template <typename Data>
inline void InOrderMappableContainer<Data>::InOrderMap(MapFun mapFun) {
    InOrderMap(mapFun);
};

// BreadthMappableContainer implementations
template <typename Data>
inline void BreadthMappableContainer<Data>::BreadthMap(MapFun mapFun) {
    BreadthMap(mapFun);
};

/* ************************************************************************** */

}
