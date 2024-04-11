
namespace lasd {

/* ************************************************************************** */

// Node specific constructors
template <typename Data>
List<Data>::Node::Node(Data&& data) noexcept {
    std::swap(element, data);
}

// Node move constructor
template <typename Data>
List<Data>::Node::Node(Node&& node) noexcept {
    std::swap(element, node.element);
    std::swap(next, node.next);
}

// Node destructor
template <typename Data>
List<Data>::Node::~Node() {
    delete next;
}

// Node comparison operators
// It checks if the elements of two nodes are equal and if their next nodes are also equal or both are nullptr
template <typename Data>
bool List<Data>::Node::operator==(const Node& node) const noexcept {
    return (element == node.element) && ((next == nullptr && node.next == nullptr) || (next != nullptr && node.next != nullptr && *next == *node.next));
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& node) const noexcept {
    return !(*this == node);
}

// Node specific member functions
template <typename Data>
Node* List<Data>::Node::Clone(Node* tail) {
    if (next == nullptr) {
        return tail;
    } else {
        Node* node = new Node(element);
        node->next = next->Clone(tail);
        return node;
    }
}

/* ************************************************************************** */

// List specific constructors
template <typename Data>
List<Data>::List(const TraversableContainer<Data>& tc) {
    tc.Traverse(
        [this](const Data& data) {
            InsertAtBack(data);
        }
    )
}

template <typename Data>
List<Data>::List(MappableContainer<Data>&& mc) {
    mc.Map(
        [this](const Data& data) {
            InsertAtBack(std::move(data));
        }
    )
}

// List copy constructor
template <typename Data>
List<Data>::List(const List<Data>& list) {
    if (list.tail == nullptr) {
        tail = new Node(*list.tail);
        head = list.head->Clone(tail);
        size = list.size;
    }
}

// List move constructor
template <typename Data>
List<Data>::List(List<Data>&& list) noexcept {
    std::swap(tail, list.tail);
    std::swap(head, list.head);
    std::swap(size, list.size);
}

// List destructor
template <typename Data>
List<Data>::~List() {
    delete head;
}

// List copy assignment
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& list) {
    // Check if the current list size is less than or equal to the size of 'list'
    if (size <= list.size) {
        // If 'tail' is nullptr, create a new temporary list and swap contents with the current list
        if (tail == nullptr) {
            List<Data>* temp = new List<Data>(list);
            std::swap(*temp, *this);
            delete temp;
        } else {
            // Copy elements from 'list' to the current list
            Node* currentSource = list.head;
            for (Node* currentDest = head; currentDest != nullptr; currentDest = currentDest->next) {
                currentDest->element = currentSource->element;
                currentSource = currentSource->next;
            }

            // Add new nodes at the end of the current list, if necessary
            if (currentSource != nullptr) {
                Node* newTail = new Node(*list.tail);
                tail->next = currentSource->Clone(newTail);
                tail = newTail;
            } else {
                // If 'list.tail' is nullptr, delete the current list
                if (list.tail == nullptr) {
                    delete head;
                    head = tail = nullptr;
                } else {
                    // Copy remaining elements from 'list' to the current list
                    Node* currentDest = head;
                    for (Node* currentSource = list.head; currentSource != nullptr; currentSource = currentSource->next) {
                        currentDest->element = currentSource->element; 
                        tail = currentDest;
                        currentDest = currentDest->next;
                    }
                    delete currentDest;
                    tail->next = nullptr;
                }
            }
        }
    }
    
    size = list.size;
    return *this;
}

// List move assignment
List& List::operator=(List<Data>&& list) noexcept {
    std::swap(tail, list.tail);
    std::swap(head, list.head);
    std::swap(size, list.size);
    return *this; 
}

// List comparison operators
template <typename Data>
bool List<Data>::operator==(const List& list) const noexcept{
    return (size == list.size) && ((head == nullptr && list.head == nullptr) || (head != nullptr && list.head != nullptr && *head == *list.head));
}

template <typename Data>
bool List<Data>::operator!=(const List& list) const noexcept {
    return !(*this == list);
}

// List specific member functions
template <typename Data>
void List<Data>::InsertAtFront(const Data& data) {
    Node* newnode = new Node(data);
    newnode->next = head;
    head = newnode;
    if (tail == nullptr) {
        tail = head;
    }
    size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& data) noexcept {
    Node* newnode = new Node(std::move(data));
    newnode->next = head;
    head = newnode;
    if (tail == nullptr) {
        tail = head;
    }
    size++;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
    if (head != nullptr) {
        Node* front = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
        }
        size--;
        front->next = nullptr;
        delete front;
    } else {
        throw std::length_error("List is empty");
    }
}

template <typename Data>
Data List<Data>::FrontNRemove() {
    if (head != nullptr) {
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
        }
        size--;
        front->next = nullptr;
        Data dataToReturn(std::move(front->element));
        delete front;
        return dataToReturn;
    } else {
        throw std::length_error("List is empty");
    }
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& data) {
    Node* newnode = new Node(data);
    if (tail == nullptr) {
        head = newnode;
    } else {
        tail->next = newnode;
    }
    tail = newnode;
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& data) noexcept {
    Node* newnode = new Node(std::move(data));
    if (tail == nullptr) {
        head = newnode;
    } else {
        tail->next = newnode;
    }
    tail = newnode;
    size++;
}

}
