
namespace lasd {

/* ************************************************************************** */

//Specific constructors

template <typename Data>
Vector<Data>::Vector(const unsigned long dim) {
    Elements = new Data[dim] {};
    size = dim;
}

template <typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& con){
    size = con.Size();
    Elements = new Data[size];
    for(unsigned long i=0; i<size; ++i){
        Elements[i] = con[i];
    }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec){
    Elements = new Data[vec.size];
    for(unsigned long i=0; i<vec.size; ++i){
        Elements[i] = vec[i];
    }
    size = vec.size;
}

// Move constructor

template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept{
    std::swap(Elements, vec.Elements);
    std::swap(size, vec.size);
}

/* ************************************************************************** */

//Destructor

template <typename Data>
Vector<Data>::~Vector(){
    delete[] Elements;
}

/* ************************************************************************** */

//Copy Assignment

template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec){
    Vector<Data>* tmp = new Vector<Data>(vec);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
}

//Move Assignment

template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept{
    std::swap(Elements, vec.Elements);
    std::swap(size, vec.size);
    return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool Vector<Data>::operator==(const Vector& vec) const noexcept{
    if(size == vec.size){
        for(unsigned long i=0; i<size; ++i){
            if(Elements[i] != vec.Elements[i]){
                return false;
            }
        }
        return true;
    } else{
        return false;
    }
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector& vec) const noexcept{
    return !(*this == vec);
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
void Vector<Data>::Resize(const unsigned long newsize){
    if(newsize == 0){
        Clear();
    } else if(size != newsize){
        Data* tmp = new Data[newsize] {};
        unsigned long limit = (size < newsize)? size : newsize;
        for(unsigned long i=0; i<limit;++i){
            std::swap(Elements[i], tmp[i]);
        }
        std::swap(Elements, tmp);
        size = newsize;
        delete[] tmp;
    }

}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template <typename Data>
void Vector<Data>::Clear() {
    delete[] Elements;
    Elements = nullptr;
    size = 0;
}

/* ************************************************************************** */

// Specific member functions (inherited from LinearContainer)

template <typename Data>
Data& Vector<Data>::Front() const {

    if(size != 0){
        return Elements[0];
    } else{
        throw std::length_error("Data Structure is Empty");
    }
}

template <typename Data>
Data& Vector<Data>::Back() const {
    if(size != 0){
        return Elements[size-1];
    } else{
        throw std::length_error("Data Structure is Empty");
    }
}

template <typename Data>
Data& Vector<Data>::operator[](const unsigned long index) const{
    if(index < size){
        return Elements[index];
    } else{
        throw std::out_of_range("Index is greater than Vector size");
    }
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void Vector<Data>::MapPreOrder(const MapFunctor fun, void* par) {
    for(unsigned long i=0; i<size; ++i){
        fun(Elements[i], par);
    }
}

template <typename Data>
void Vector<Data>::MapPostOrder(const MapFunctor fun, void* par) {
    unsigned long i = size;
    while(i > 0){
        i--;
        fun(Elements[i], par);
    }
}


/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void Vector<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
     for(unsigned long i=0; i<size; ++i){
        fun(Elements[i], par, acc);
    }
} 
  
template <typename Data>
void Vector<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
    unsigned long i = size;
    while(i > 0){
        i--;
        fun(Elements[i], par, acc);
    }
}

/* ************************************************************************** */

}
