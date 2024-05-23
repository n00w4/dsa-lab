
namespace lasd {

/* ************************************************************************** */

// Specific constructors
// A hash table of a given size
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long newsize) {
    tablesize = std::pow(2, std::ceil(log2((newsize <= 16) ? 16 : newsize)));
    table = new Data[tablesize] {};
    tableFlag = new Flag[tablesize] {};
}

// A hash table obtained from a TraversableContainer
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& tc) : HashTableOpnAdr(tc.Size() * 2) {
    InsertAll(tc);
}

// A hash table of a given size obtained from a TraversableContainer
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long newsize, const TraversableContainer<Data>& tc) : HashTableOpnAdr(newsize) {
    InsertAll(tc);
}

// A hash table obtained from a MappableContainer
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data>&& mc) : HashTableOpnAdr(mc.Size() * 2) {
    InsertAll(std::move(mc));
}

// A hash table of a given size obtained from a MappableContainer
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long newsize, MappableContainer<Data>&& mc) : HashTableOpnAdr(newsize) {
    InsertAll(std::move(mc));
}

/* ************************************************************************* */

// Copy constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& ht) : HashTable<Data>::HashTable(ht) {
    table = new Data[tablesize] {};
    tableFlag = new Flag[tablesize] {};
    for (unsigned long i = 0; i < tablesize; i++) {
        table[i] = ht.table[i];
        tableFlag[i] = ht.tableFlag[i];
    }
}

// Move constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& ht) noexcept : HashTable<Data>::HashTable(std::move(ht)) {
    std::swap(table, ht.table);
    std::swap(tableFlag, ht.tableFlag);
}

/* ************************************************************************* */

// Copy assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& ht) {
    HashTable<Data>::operator=(ht);
    delete[] table;
    delete[] tableFlag;
    table = new Data[tablesize] {};
    tableFlag = new Flag[tablesize] {};
    for (unsigned long i = 0; i < tablesize; i++) {
        table[i] = ht.table[i];
        tableFlag[i] = ht.tableFlag[i];
    }
    return *this;
}

// Move assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& ht) noexcept {
    HashTable<Data>::operator=(std::move(ht));
    std::swap(table, ht.table);
    std::swap(tableFlag, ht.tableFlag);
    return *this;
}

/* ************************************************************************* */

// Comparison operators
template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& ht) const noexcept {
    if (size != ht.size) { return false; }
    for (unsigned long i = 0; i < tablesize; i++) {
        if (tableFlag[i] == used) {
            if (!ht.Exists(table[i])) { return false; }
        }
    }
    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& ht) const noexcept {
    return !(*this == ht);
}

/* ************************************************************************* */

// Specific member functions inherited from DictionaryContainer
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& data) {
    unsigned long probIndex = 0;
    if (size * 2 >= tablesize) { Resize(tablesize * 2); }
    unsigned long index = FindEmpty(data, probIndex);
    if (tableFlag[index] != used) {
        table[index] = data;
        tableFlag[index] = used;
        size++;
        return !Remove(++probIndex, data);
    }
    probIndex = 0;
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& data) {
    unsigned long probIndex = 0;
    if (size * 2 >= tablesize) { Resize(tablesize * 2); }
    unsigned long index = FindEmpty(data, probIndex);
    if (tableFlag[index] != used) {
        table[index] = std::move(data);
        tableFlag[index] = used;
        size++;
        return !Remove(++probIndex, data);
    }
    probIndex = 0;
    return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data) {
    unsigned long probIndex = 0;
    return Remove(probIndex, data);
}

/* ************************************************************************* */

// Specific member functions inherited from TestableContainer
template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
    unsigned long probIndex = 0;
    unsigned long index = HashKey(Hashable<Data>()(data));
    return Find(index, probIndex, data);
}

/* ************************************************************************* */

// Specific member functions inherited from ResizableContainer
template <typename Data>
void HashTableOpnAdr<Data>::Resize(const unsigned long newsize) {
    unsigned long tempTableSize = (newsize == 16) ? 16 : std::pow(2, std::ceil(log2(newsize)));

    Data* tempTable = new Data[tempTableSize] {};
    Flag* tempTableFlag = new Flag[tempTableSize] {};

    std::swap(tempTable, table);
    std::swap(tempTableFlag, tableFlag);
    std::swap(tempTableSize, tablesize);
    
    size = 0;

    for (unsigned long i = 0; i < tempTableSize; i++) {
        if (tempTableFlag[i] == used) { Insert(tempTable[i]); }
    }
    delete[] tempTable;
    delete[] tempTableFlag;
}

/* ************************************************************************* */

// Specific member functions inherited from ClearableContainer
template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
    for (unsigned long i = 0; i < tablesize; i++) { tableFlag[i] = deleted; }
    size = 0;
}

/* ************************************************************************* */

// Auxiliary functions
template <typename Data>
unsigned long HashTableOpnAdr<Data>::HashKey(const Data& data, const unsigned long& probIndex) const noexcept {
    unsigned long index = HashKey(Hashable<Data>()(data));
    return ( index + tablesize + ((probIndex * probIndex) + probIndex) /2 ) % tablesize;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Find(unsigned long& index, unsigned long& probIndex, const Data& data) const noexcept {
    unsigned long tempIndex = HashKey(data, probIndex);
    unsigned long jumps = 0;
    do {
        if (jumps == tablesize - 1) { return false; }
        if ((table[tempIndex] == data) && (tableFlag[tempIndex] == used)) { index = tempIndex; return true; }
        tempIndex = HashKey(data, ++probIndex);
        jumps++;
    } while (!(tableFlag[tempIndex] == unused));
    return false;
}

template <typename Data>
unsigned long HashTableOpnAdr<Data>::FindEmpty(const Data& data, unsigned long& probIndex) const noexcept {
    unsigned long tempIndex = HashKey(data, probIndex);
    while ((tableFlag[tempIndex] == used) && (table[tempIndex] != data)) {
        tempIndex = HashKey(data, ++probIndex);
    }
    return tempIndex;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(unsigned long& probIndex, const Data& data) noexcept {
    unsigned long tempIndex = 0;
    if (Find(tempIndex, probIndex, data)) {
        tableFlag[tempIndex] = deleted;
        size--;
        probIndex = 0;
        if ((size < tablesize / 5) && (tablesize > 16)) { Resize(tablesize / 2); }
        return true;
    }
    probIndex = 0;
    return false;
}

/* ************************************************************************** */

}
