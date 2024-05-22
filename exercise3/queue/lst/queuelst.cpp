
namespace lasd {

/* ************************************************************************** */

// Copy assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queuelist) {
    List<Data>::operator=(queuelist);
    return *this;
}

// Move assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& queuelist) noexcept {
    List<Data>::operator=(std::move(queuelist));
    return *this;
}

// Comparison operators
template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& queuelist) const noexcept {
    return List<Data>::operator==(queuelist);
}

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst<Data>& queuelist) const noexcept {
    return List<Data>::operator!=(queuelist);
}

/* ************************************************************************ */

// Specific member functions inherited from Queue
template <typename Data>
const Data& QueueLst<Data>::Head() const {
    return List<Data>::Front();
}

template <typename Data>
Data& QueueLst<Data>::Head() {
    return List<Data>::Front();
}

template <typename Data>
void QueueLst<Data>::Dequeue() {
    List<Data>::RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data>::HeadNDequeue() {
    return List<Data>::FrontNRemove();
}

template <typename Data>
void QueueLst<Data>::Enqueue(const Data& data) {
    List<Data>::InsertAtBack(data);
}

template <typename Data>
void QueueLst<Data>::Enqueue(Data&& data) {
    List<Data>::InsertAtBack(std::move(data));
}

/* ************************************************************************** */

}
