
namespace lasd {

/* ************************************************************************** */

// NodeLnk

// Specific constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& data) noexcept {
    std::swap(element, data);
}

// Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& node) {
    element = node.element;
    left = node.left;
    right = node.right;
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& node) noexcept {
    std::swap(element, node.element);
    std::swap(left, node.left);
    std::swap(right, node.right);
}

// Destructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete left;
    delete right;
};

// Comparison operators
template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::operator==(const NodeLnk& node) const noexcept {
    return (element == node.element) && ((left == nullptr && node.left == nullptr) || ((left != nullptr && node.left != nullptr) && (*left == *node.left))) \
        && ((right == nullptr && node.right == nullptr) || ((right != nullptr && node.right != nullptr) && (*right == *node.right)));
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::operator!=(const NodeLnk& node) const noexcept {
    return !(*this == node);
}

// Specific member functions (inherited from Node)
template <typename Data>
inline const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return element;
}

template <typename Data>
inline Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return element;
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept {
    return (left == nullptr) && (right == nullptr);
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return (left != nullptr);
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    return (right != nullptr);
}

template <typename Data>
inline const typename BinaryTreeLnk<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    if (left != nullptr) { return *left; }
    else { throw std::length_error("No left child"); }
}

template <typename Data>
inline const typename BinaryTreeLnk<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    if (right != nullptr) { return *right; }
    else { throw std::length_error("No right child"); }
}

// Specific member functions (inherited from MutableNode)

template <typename Data>
inline typename BinaryTreeLnk<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::LeftChild() {
    if (left != nullptr) { return *left; }
    else { throw std::length_error("No left child"); }
}

template <typename Data>
inline typename BinaryTreeLnk<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::RightChild() {
    if (right != nullptr) { return *right; }
    else { throw std::length_error("No right child"); }
}

/* ************************************************************************** */

// BinaryTreeLnk

// Specific constructors
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& tc) {
    size = tc.Size();
    StackLst<NodeLnk**> stack;
    stack.Push(&root);
    tc.Traverse([&stack] (const Data& data) {
        NodeLnk*& currentNode = *stack.Top();
        currentNode = new NodeLnk(data);
        stack.Push(&currentNode->right);
        stack.Push(&currentNode->left);
    })
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data>&& mc) {
    size = mc.Size();
    StackLst<NodeLnk**> stack;
    stack.Push(&root);
    mc.Map([&stack] (const Data& data) {
        NodeLnk*& currentNode = *stack.Top();
        currentNode = new NodeLnk(std::move(data));
        stack.Push(&currentNode->right);
        stack.Push(&currentNode->left);
    });
}

// Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& btl) {
    if (btl.root != nullptr) {
        root = new NodeLnk(*btl.root);
        size = btl.size;
    }
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& btl) noexcept {
    std::swap(root, btl.root);
    std::swap(size, btl.size);
}

// Destructor
template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    delete root;
}

// Copy assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& btl) {
    if (root == nullptr) {
        if (btl.root != nullptr) {
            root = new NodeLnk(*btl.root);
        }
    } else {
        if (btl.root == nullptr) {
            delete root;
            root = nullptr;
        } else {
            *root = *btl.root;
        }
    }
    size = btl.size;
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& btl) noexcept {
    std::swap(root, btl.root);
    std::swap(size, btl.size);
    return *this;
}

// Comparison operators
template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& btl) const noexcept {
    return (size == btl.size) && ((root == btl.root) || ((root != nullptr) && (btl.root != nullptr) && (*root == *btl.root)));
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& btl) const noexcept {
    return !(*this == btl);
}

// Specific member functions (inherited from BinaryTree)
template <typename Data>
const typename BinaryTreeLnk<Data>::Node& BinaryTreeLnk<Data>::Root() const {
    if (root != nullptr) { return *root; }
    else { throw std::length_error("Empty tree"); }
}

// Specific member functions (inherited from MutableBinaryTree)
template <typename Data>
typename BinaryTreeLnk<Data>::MutableNode& BinaryTreeLnk<Data>::Root() {
    if (root != nullptr) { return *root; }
    else { throw std::length_error("Empty tree"); }
}

// Specific member functions (inherited from ClearableContainer)
template <typename Data>
void BinaryTreeLnk<Data>::Clear() {
    delete root;
    root = nullptr;
    size = 0;
}

/* ************************************************************************** */

}
