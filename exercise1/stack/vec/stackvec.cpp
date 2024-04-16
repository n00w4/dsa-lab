
namespace lasd {

/* ************************************************************************** */

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& stackvec) noexcept : Vector<Data>(std::move(stackvec)) {
    std::swap(index, stackvec.index);
}

// Copy assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stackvec) {
    Vector<Data>::operator=(stackvec);
    index = stackvec.index;
    return *this;
}

// Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stackvec) noexcept {
    Vector<Data>::operator=(std::move(stackvec));
    std::swap(index, stackvec.index);
    return *this;
}

// Comparison operators
template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& stackvec) const noexcept {
    if (index == stackvec.index) {
        for (unsigned long index = 0; index < size; index++) {
            if (Elements[index] != stackvec.Elements[index]) { return false; }
        }
        return true;
    } else {
        return false;
    }
}

template <typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data>& stackvec) const noexcept {
    return !(*this == stackvec);
}

/* ************************************************************************** */

// Specific member functions inherited from Stack
template <typename Data>
const Data& StackVec<Data>::Top() const {
    if (index != 0) { return Elements[index - 1]; }
    else { throw std::length_error("Stack is empty"); }
}

template <typename Data>
Data& StackVec<Data>::Top() {
    if (index != 0) { return Elements[index - 1]; }
    else { throw std::length_error("Stack is empty"); }
}

template <typename Data>
void StackVec<Data>::Pop() {
    if (index != 0) { Reduce(); --index; }
    else { throw std::length_error("Stack is empty"); }
}

template <typename Data>
Data StackVec<Data>::TopNPop() {
    if (index != 0) { Reduce(); return Elements[--index]; }
    else { throw std::length_error("Stack is empty"); }
}

template <typename Data>
void StackVec<Data>::Push(const Data& data) {
    Expand();
    Elements[index++] = data;
}

template <typename Data>
void StackVec<Data>::Push(Data&& data) {
    Expand();
    Elements[index++] = std::move(data);
}

// Specific member functions inherited from Container
template <typename Data>
bool StackVec<Data>::Empty() const noexcept {
    return (index == 0);
}

template <typename Data>
unsigned long StackVec<Data>::Size() const noexcept {
    return index;
}

// Specific member functions inherited from ClearableContainer
template <typename Data>
void StackVec<Data>::Clear() {
    index = 0;
    Vector<Data>::Resize(1);
}

// Auxiliary functions
template <typename Data>
void StackVec<Data>::Expand() {
    if (index == size) { Vector<Data>::Resize(size * 2); }
}

template <typename Data>
void StackVec<Data>::Reduce() {
    if (index == (size / 4)) { Vector<Data>::Resize(size / 2); }
}

/* ************************************************************************** */

}
