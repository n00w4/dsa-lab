
namespace lasd {

/* ************************************************************************** */

// Specific constructors
// A hash table of a given size
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newsize) {
    tablesize = std::pow(2, std::ceil(log2((newsize <= 16) ? 16 : newsize)));
    table = new BST<Data>[tablesize] {};
}

// A hash table obtained from a TraversableContainer
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& tc) : HashTableClsAdr(tc.Size()) {
    InsertAll(tc);
}

// A hash table of a given size obtained from a TraversableContainer
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newsize, const TraversableContainer<Data>& tc) : HashTableClsAdr(newsize) {
    InsertAll(tc);
}

// A hash table obtained from a MappableContainer
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& mc) : HashTableClsAdr(mc.Size()) {
    InsertAll(std::move(mc));
}

// A hash table of a given size obtained from a MappableContainer
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newsize, MappableContainer<Data>&& mc) : HashTableClsAdr(newsize) {
    InsertAll(std::move(mc));
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& ht) : HashTable<Data>(ht) {
    table = new BST<Data>[tablesize] {};
    std::copy(ht.table, ht.table + tablesize, table);
}

// Move constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& ht) noexcept : HashTable<Data>(std::move(ht)) {
    std::swap(table, ht.table);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& ht) {
    HashTable<Data>::operator=(ht);
    delete[] table;
    table = new BST<Data>[tablesize] {};
    for (unsigned long i = 0; i < tablesize; i++) {
        table[i] = ht.table[i];
    }
    return *this;
}

// Move assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& ht) noexcept {
    HashTable<Data>::operator=(std::move(ht));
    std::swap(table, ht.table);
    return *this;   
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& ht) const noexcept {
    bool isEqual = true;
    if (size != ht.size) { return false; }
    for (unsigned long i = 0; i < tablesize; i++) {
        table[i].Traverse([&ht](const Data& data) {
            if (!ht.Exists(data)) { isEqual = false; return; }
        });
        if (!isEqual) { return false; }
    }
    return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& ht) const noexcept {
    return !(*this == ht);
}

/* ************************************************************************** */

// Specific member functions inherited from DictionaryContainer
template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& data) {
    if (table[HashKey(data)].Insert(data)) {
        size++;
        return true;
    }
    return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& data) {
    if (table[HashKey(data)].Insert(std::move(data))) {
        size++;
        return true;
    }
    return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& data) {
    if (table[HashKey(data)].Remove(data)) {
        size--;
        return true;
    }
    return false;
}

/* ************************************************************************** */

// Specific member functions inherited from TestableContainer
template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& data) const noexcept {
    return table[HashKey(data)].Exists(data);
}

/* ************************************************************************** */

// Specific member functions inherited from ResizableContainer
template <typename Data>
void HashTableClsAdr<Data>::Resize(const unsigned long newsize) {
    size = 0;
    unsigned long newtablesize = (newsize <= 16) ? 16 : std::pow(2, std::ceil(log2(newsize)));
    lasd::BST<Data>* newtable = new BST<Data>[newtablesize] {};
    std::swap(newtable, table);
    std::swap(newtablesize, tablesize);
    for (unsigned long i = 0; i < newtablesize; i++) {
        InsertAll(newtable[i]);
    }
    delete[] newtable;
}

/* ************************************************************************ */

// Specific member functions inherited from ClearableContainer
template <typename Data>
void HashTableClsAdr<Data>::Clear() {
    delete[] table;
    table = new BST<Data>[tablesize] {};
    size = 0;
}

/* ************************************************************************** */

}
