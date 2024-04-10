
namespace lasd {

/* ************************************************************************** */

// Specific Vector constructors
// A vector with a given initial dimension
template <typename Data>
Vector<Data>::Vector(const unsigned long newsize) {
    size = newsize;
    Elements = new Data[size]{};
}

// A vector obtained from a TraversableContainer
template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& tc) : Vector(tc.Size()) {
    unsigned long index = 0;
    tc.Traverse(
        [this, &index](const Data& data) {
            Elements[index++] = data;
        }
    );
}

// A vector obtained from a MappableContainer
template <typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& mc) : Vector(mc.Size()) {
    unsigned long index = 0;
    mc.Map(
        [this, &index](const Data& data) {
            Elements[index++] = std::move(data);
        }
    );
}

/* ************************************************************************** */

// Vector copy constructor
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec) {
   size = vec.size;
   Elements = new Data[size];
   std::copy(vec.Elements, vec.Elements + size, Elements);
}

// Vector move constructor
template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
   std::swap(size, vec.size);
   std::swap(Elements, vec.Elements);
}

// Vector destructor
template <typename Data>
Vector<Data>::~Vector() {
    delete[] Elements;
}

// Vector copy assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
    Vector<Data> * tempvec = new Vector<Data>(vec);
    std::swap(*tempvec, *this);
    delete tempvec;
    return *this;
}

// Vector move assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept {
    Vector<Data> * tempvec = new Vector<Data>(vec);
    std::move(*tempvec, *this);
    return *this;
}

// Vector comparison operators
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept {
    if (size == vec.size) {
        for (unsigned long index = 0; index < size; index++) {
            if (Elements[index] != vec.Elements[index]) { return false; }
        }
        return true;
    } else { return false; }
}

template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept {
    return !(*this == vec);
}

// Specific Vector member functions inherited from ResizableContainer
template <typename Data>
void Vector<Data>::Clear() {
    delete[] Elements;
    Elements = nullptr;
    size = 0;
}

template <typename Data>
void Vector<Data>::Resize(const unsigned long newsize) {
    if (newsize == 0) {
        Resize();
    } else if (size != newsize) {
        Data * Temp = new Data[newsize] {};
        unsigned long min = (size < newsize) ? size : newsize;
        for (unsigned long index = 0; index < min; index++) {
            std::swap(Elements[index], Temp[index]);
        }
        std::swap(Elements, Temp);
        size = newsize;
        delete[] Temp;
    }
}

// Vector specific member functions inherited from LinearContainer
template <typename Data>
const Data& Vector<Data>::operator[](const unsigned long index) const {
    if (index < size) {
        return Elements[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename Data>
Data& Vector<Data>::operator[const unsigned long index] {
    if (index < size) {
        return Elements[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename Data>
const Data& Vector<Data>::Front() const {
    if (size != 0) {
        return Elements[0];
    } else {
        throw std::length_error("Empty vector");
    }
}

template <typename Data>
Data& Vector<Data>::Front() {
    if (size != 0) {
        return Elements[0];
    } else {
        throw std::length_error("Empty vector");
    }
}

template <typename Data>
const Data& Vector<Data>::Back() const {
    if (size != 0) {
        return Elements[size-1];
    } else {
        throw std::length_error("Empty vector");
    }
}

template <typename Data>
Data& Vector<Data>::Back() {
    if (size != 0) {
        return Elements[size-1];
    } else {
        throw std::length_error("Empty vector");
    }
}

/* ************************************************************************** */

// Specific SortableVector constructors
// A vector with a given initial dimension
template <typename Data>
SortableVector::SortableVector(const unsigned long newsize) : Vector<Data>(newsize) {}

// A vector obtained from a TraversableContainer
template <typename Data>
SortableVector::SortableVector(const TraversableContainer<Data>& tc) : Vector<Data>(tc.Size()) {}

// A vector obtained from a MappableContainer
template <typename Data>
SortableVector::SortableVector(MappableContainer<Data>&& mc) : Vector<Data>(mc.Size()) {}

// SortableVector copy constructor
template <typename Data>
SortableVector::SortableVector(const SortableVector<Data>& sv) : Vector<Data>(sv) {}

// SortableVector move constructor
template <typename Data>
SortableVector::SortableVector(SortableVector<Data>&& sv) noexcept : Vector<Data>(sv) {}

// SortableVector copy assignment
template <typename Data>
SortableVector& SortableVector::operator=(const SortableVector& sv) {
    Vector<Data>::operator=(sv);
    return *this;
}

// SortableVector move assignment
template <typename Data>
SortableVector& SortableVector::operator=(SortableVector&& sv) noexcept {
    Vector<Data>::operator(std::move(sv));
    return *this;
}

}
