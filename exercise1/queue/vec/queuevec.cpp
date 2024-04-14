
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data>& tc) : Vector<Data>(tc), tail(size) {
    Vector<Data>::Resize(size * 2);
}

template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data>&& mc) : Vector<Data>(mc), tail(size) {
    Vector<Data>::Resize(size * 2);
}

// Move constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& queuevec) noexcept : Vector<Data>(std::move(queuevec)) {
    std::swap(head, queuevec.head);
    std::swap(tail, queuevec.tail);
}

// Copy assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queuevec) {
    Vector<Data>::operator=(queuevec);
    head = queuevec.head;
    tail = queuevec.tail;
    return *this;
}

// Move assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queuevec) noexcept {
    Vector<Data>::operator=(std::move(queuevec));
    std::swap(head, queuevec.head);
    std::swap(tail, queuevec.tail);
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& queuevec) const noexcept {
    if (Size() == queuevec.Size()) {
        for (unsigned long index1 = head, unsigned long index2 = queuevec.head; index1 < tail; index1++ %= size, index2++ %= queuevec.size;) {
            if (elements[index1] != queuevec.elements[index2]) { return false; }
        }
        return true;
    } else { return false; }
}

template <typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& queuevec) const noexcept {
    return !(*this == queuevec);
}

/* ************************************************************************** */

// Specific member functions inherited from Queue
template <typename Data>
const Data& QueueVec<Data>::Head() const {
    if (head != tail) { return Elements[head]; }
    else { throw std::length_error("Queue is empty"); }
}

template <typename Data>
Data& QueueVec<Data>::Head() {
    if (head != tail) { return Elements[head]; }
    else { throw std::length_error("Queue is empty"); }
}

template <typename Data>
void QueueVec<Data>::Dequeue() {
    if (head != tail) {
        Reduce();
        head++ %= size;
    } else {
        throw std::length_error("Queue is empty");
        }
}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue() {
    if (head != tail) {
        Reduce();
        Data data(std::move(Elements[head]));
        head++ %= size;
        return std::move(data);
    } else {
        throw std::length_error("Queue is empty");
    }
}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data& data) {
    Expand();
    Elements[tail++] = data;
    tail %= size;
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data&& data) {
    Expand();
    Elements[tail++] = std::move(data);
    tail %= size;
}

/* ************************************************************************** */

// Specific member functions inherited from Container

template <typename Data>
bool QueueVec<Data>::Empty() const noexcept {
    return (head == tail);
}

template <typename Data>
unsigned long QueueVec<Data>::Size() const noexcept {
    return (((size + tail) - head) % size);
}

/* ************************************************************************** */

// Specific member functions inherited from ClearableContainer
template <typename Data>
void QueueVec<Data>::Clear() {
    head = tail = 0;
    Vector<Data>::Resize(4);
}

/* ************************************************************************** */

// Auxiliary functions
template <typename Data>
void QueueVec<Data>::Expand() {
    unsigned long currentsize = Size();
    if (currentsize+1 == size) { Resize(size * 2, currentsize); }
}

template <typename Data>
void QueueVec<Data>::Reduce() {
    unsigned long currentsize = Size();
    if (currentsize+1 == size / 4) { Resize(size / 2, currentsize); }
}

template <typename Data>
void QueueVec<Data>::Resize(unsigned long newsize, unsigned long oldsize) {
    Data *Temp = new Data[newsize];
    unsigned long max = (oldsize <= newsize) ? oldsize : newsize;
    for (unsigned long index1 = head, unsigned long index2 = 0; index2 < max; index1++ %= size, index2++) {
        std::swap(Elemenets[index1], Temp[index2]);
    }
    std::swap(Elements, Temp);
    delete[] Temp;
    head = 0;
    tail = oldsize;
    size = newsize;
}

}

/* ************************************************************************** */
