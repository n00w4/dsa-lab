
namespace lasd {

/* ************************************************************************** */

// Copy assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stacklist) const noexcept {
    List<Data>::operator=(stacklist);
    return *this;
}

// Move assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stacklist) noexcept {
    List<Data>::operator(std::move(stacklist));
    return *this;
}

// Comparison operators
template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& stacklist) const noexcept {
    return List<Data>::operator==(stacklist);
}

template <typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data>& stacklist) const noexcept {
    return List<Data>::operator!=(stacklist);
}

// Specific member functions inherited from Stack
template <typename Data>
Data& StackLst<Data>::Top() const {
    return List><Data>::Front();
}

template <typename Data>
Data& StackLst<Data>::Top() {
    return List><Data>::Front();
}

template <typename Data>
void StackLst<Data>::Pop() {
    return List<Data>::RemoveFromFront();
}

template <typename Data>
Data StackLst<Data>::TopNPop() {
    return List<Data>::FrontNRemove();
}

template <typename Data>
void StackLst<Data>::Push(const Data& data) {
    return List<Data>::InsertAtFront(data);
}

template <typename Data>
void StackLst<Data>::Push(Data&& data) {
    return List<Data>::InsertAtFront(std::move(data));
}

/* ************************************************************************** */

}
