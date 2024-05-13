
namespace lasd {

/* ************************************************************************** */

// Node move constructor
template <typename Data>
inline List<Data>::Node::Node(Node&& node) noexcept {
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
    return (element == node.element) && ((next == nullptr && node.next == nullptr) || ((next != nullptr && node.next != nullptr) && (*next == *node.next)));

}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& node) const noexcept {
    return !(*this == node);
}

// Node specific member functions
template <typename Data>
typename List<Data>::Node* List<Data>::Node::Clone(Node* tail) {
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
        });
}

template <typename Data>
List<Data>::List(MappableContainer<Data>&& mc) {
    mc.Map(
        [this](Data& data) {
            InsertAtBack(std::move(data));
        });
}

// List copy constructor
template <typename Data>
List<Data>::List(const List<Data>& list) {
    if (list.tail != nullptr) {
        tail = new Node(*list.tail);
        head = list.head->Clone(tail);
        size = list.size;
    }
}

// List move constructor
template <typename Data>
List<Data>::List(List<Data>&& list) noexcept {
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
}

// List destructor
template <typename Data>
List<Data>::~List() {
    delete head;
}

// List copy assignment operator
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& list) {
    // Check if the current list size is less than or equal to the size of 'list'
    if (size <= list.size) {
        // If 'tail' is nullptr, create a new temporary list and swap contents with the current list
        if (tail == nullptr) {
            List<Data>* temp = new List<Data>(list);  // Create a new temporary list
            std::swap(*temp, *this);  // Swap contents between the temporary list and the current list
            delete temp;  // Delete the temporary list
        } else {
            // Copy elements from 'list' to the current list
            Node* currentSource = list.head;  // Pointer to the current node in the source list
            for (Node* currentDest = head; currentDest != nullptr; currentDest = currentDest->next, currentSource = currentSource->next) {
                currentDest->element = currentSource->element;  // Copy element from source to destination
            }
            // If there are remaining elements in the source list, add them to the end of the current list
            if (currentSource != nullptr) {
                Node* newTail = new Node(*list.tail);  // Create a new node for the element of 'list.tail'
                tail->next = currentSource->Clone(newTail);  // Connect the new node to the end of the current list
                tail = newTail;  // Update 'tail' to point to the new node
            } 
        } 
    } else {
        // If the current list size is greater than the size of 'list'
        if (list.tail == nullptr) {
            // If 'list' is empty, delete all nodes in the current list
            delete head;
            head = tail = nullptr;
        } else {
            // Copy elements from 'list' to the current list
            Node* currentDest = head;  // Pointer to the current node in the destination list
            for (Node* currentSource = list.head; currentSource != nullptr; currentSource = currentSource->next, tail = currentDest, currentDest = currentDest->next) {
                currentDest->element = currentSource->element;  // Copy element from source to destination
            }
            delete currentDest;  // Delete the last remaining node that was not copied
            tail->next = nullptr;  // Set the 'next' pointer of the last node to nullptr
        }
    }
    
    // Update the size of the current list with the size of 'list'
    size = list.size;
    // Return a reference to 'this' to support chained assignment
    return *this;
}


// List move assignment
template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& list) noexcept {
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
    return *this; 
}

// List comparison operators
template <typename Data>
inline bool List<Data>::operator==(const List<Data>& list) const noexcept{
    return (size == list.size) && ((head == nullptr && list.head == nullptr) || ((head != nullptr && list.head != nullptr) && (*head == *list.head)));
}

template <typename Data>
inline bool List<Data>::operator!=(const List<Data>& list) const noexcept {
    return !(*this == list);
}

/* ************************************************************************** */

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
void List<Data>::InsertAtFront(Data&& data) {
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
        if (head == tail) { head = tail = nullptr; }
        else { head = head->next; }
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
        Node* front = head;
        if (head == tail) { head = tail = nullptr; }
        else { head = head->next; }
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
    if (tail == nullptr) { head = newnode; }
    else { tail->next = newnode; }
    tail = newnode;
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& data) {
    Node* newnode = new Node(std::move(data));
    if (tail == nullptr) { head = newnode; }
    else { tail->next = newnode; }
    tail = newnode;
    size++;
}

/* ************************************************************************** */

// Specific member function inherited from ClearableContainer
template <typename Data>
void List<Data>::Clear() {
    delete head;
    head = tail = nullptr;
    size = 0;
}

// Specific member functions inherited from MappableContainer
template <typename Data>
bool List<Data>::Insert(const Data& data) {
    for (Node* current = head; current != nullptr; current = current->next) {
        if (current->element == data) { return false; }
    }
    InsertAtBack(data);
    return true;
}

template <typename Data>
bool List<Data>::Insert(Data&& data) {
    for (Node* current = head; current != nullptr; current = current->next) {
        if (current->element == data) { return false; }
    }
    InsertAtBack(std::move(data));
    return true;
}

template <typename Data>
bool List<Data>::Remove(const Data& data) {
    Node* last = nullptr;  // Pointer to the previous node in case we need to update 'tail'
    // Traverse the list using a pointer to pointer to modify 'next' pointers
    for (Node** current = &head; *current != nullptr; last = *current, current = &((*current)->next)) {
        if ((*current)->element == data) {
            Node* node = *current;  // Save a pointer to the current node to be removed
            // Update the pointer in the previous node to skip the current node
            *current = node->next;
            // Separate the current node from the list by setting its 'next' pointer to nullptr
            node->next = nullptr;
            delete node;
            size--;
            // If the removed node was the tail of the list, update 'tail' to the previous node
            if (tail == node) { tail = last; }
            return true;
        }
    }
    return false;
}

// Specific member functions inherited from LinearContainer
template <typename Data>
const Data& List<Data>::operator[](const unsigned long index) const {
    if (index < size) {
        Node* current = head;
        for (unsigned long i = 0; i < index; i++, current = current->next) {}
        return current->element;
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename Data>
Data& List<Data>::operator[](const unsigned long index) {
    if (index < size) {
        Node* current = head;
        for (unsigned long i = 0; i < index; i++, current = current->next) {}
        return current->element;
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename Data>
const Data& List<Data>::Front() const {
    if (head != nullptr) {
        return head->element;
    } else {
        throw std::length_error("List is empty");
    }
}

template <typename Data>
Data& List<Data>::Front() {
    if (head != nullptr) {
        return head->element;
    } else {
        throw std::length_error("List is empty");
    }
}

template <typename Data>
const Data& List<Data>::Back() const {
    if (tail != nullptr) {
        return tail->element;
    } else {
        throw std::length_error("List is empty");
    }
}

template <typename Data>
Data& List<Data>::Back() {
    if (tail != nullptr) { 
        return tail->element;
    } else {
        throw std::length_error("List is empty");
    }
}

// Specific member function inherited from TraversableContainer
template <typename Data>
void List<Data>::Traverse(TraverseFun travFun) const {
    PreOrderTraverse(travFun, head);
}

// Specific member function inherited from PreOrderTraversableContainer
template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun travFun) const {
    PreOrderTraverse(travFun, head);
}

// Specific member function inherited from PostOrderTraversableContainer
template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun travFun) const {
    PostOrderTraverse(travFun, head);
}

// Specific member function inherited from MappableContainer
template <typename Data>
void List<Data>::Map(MapFun mapFun) {
    PreOrderMap(mapFun, head);
}

// Specific member function inherited from PreOrderMappableContainer
template <typename Data>
void List<Data>::PreOrderMap(MapFun mapFun) {
    PreOrderMap(mapFun, head);
}

// Specific member function inherited from PostOrderMappableContainer
template <typename Data>
void List<Data>::PostOrderMap(MapFun mapFun) {
    PostOrderMap(mapFun, head);
}

/* ************************************************************************** */

// Auxiliary functions (for TraversableContainer)
template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun travFun, const Node* currentnode) const {
    for(; currentnode != nullptr; currentnode = currentnode->next) {
        travFun(currentnode->element);
    }
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun travFun, const Node* currentnode) const {
    if (currentnode != nullptr) {
        PostOrderTraverse(travFun, currentnode->next);
        travFun(currentnode->element);
    }
}

// Auxiliary functions (for MappableContainer)
template <typename Data>
void List<Data>::PreOrderMap(MapFun mapFun, Node* currentnode) {
    for(; currentnode != nullptr; currentnode = currentnode->next) {
        mapFun(currentnode->element);
    }
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun mapFun, Node* currentnode) {
    if (currentnode != nullptr) {
        PostOrderMap(mapFun, currentnode->next);
        mapFun(currentnode->element);
    }
}

}
