
namespace lasd {

/* ************************************************************************** */

// Default constructor

template <typename Data>
StackVec<Data>::StackVec(){
    Elements = new Data*[9]{};
    size = 9;
}

/* ************************************************************************** */

// Specific constructor
template <typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& con){
    if(con.Size() != 0){
        size = con.Size();
        Elements = new Data*[size]{};
        for(unsigned long i = 0; i<size; ++i){
            Elements[i] = new Data(con[i]);
        }
        head = size;
    }else{
        Elements = new Data*[9]{};
        size = 9;
    }
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& stack){
    size = stack.size;
    Elements = new Data*[size]{};
    head = stack.head;
    for(unsigned long i=0; i<head; ++i){
        Elements[i] = new Data(*(stack.Elements[i]));
    }
}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& stack) noexcept{
    std::swap(Elements, stack.Elements);
    std::swap(size, stack.size);
    std::swap(head, stack.head);
}

/* ************************************************************************** */

// Destructor
template <typename Data>
StackVec<Data>::~StackVec(){
    Clear();
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stack){
    size = stack.size;
    Elements = new Data*[size]{};
    head = stack.head;
    for(unsigned long i=0; i<head; ++i){
        Elements[i] = new Data(*(stack.Elements[i]));
    }
    return *this;
}

// Move assignment

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stack) noexcept{
    std::swap(Elements, stack.Elements);
    std::swap(size, stack.size);
    std::swap(head, stack.head);
    return *this;
}

/* ************************************************************************ */

// Comparison operators

template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& stack) const noexcept{
    if(head == stack.head){
        for(unsigned long i = 0; i<head; ++i){
            if(*(Elements[i]) != *(stack.Elements[i])){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}

template <typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data>& stack) const noexcept{
    return !(*this == stack);
}


/* ************************************************************************** */

// Specific member functions (inherited from Stack)

template <typename Data>
void StackVec<Data>::Push(const Data& dat){
    if(head == size){
        Vector<Data*>::Resize(2*size);
    }
    Elements[head] = new Data(dat);
    head++;
}

template <typename Data>
void StackVec<Data>::Push(Data&& dat) noexcept{
    if(head == size){
        Vector<Data*>::Resize(2*size);
    }
    Elements[head] = new Data(std::move(dat));
    head++;
}

template <typename Data>
Data& StackVec<Data>::Top() const{
    if(head == 0){
        throw std::length_error("Stack is Empty");
    }else{
        return *(Elements[head-1]);
    }
}

template <typename Data>
void StackVec<Data>::Pop(){
    if(head == 0){
        throw std::length_error("Stack is Empty");
    }else{
        delete Elements[head-1];
        Elements[head-1] = nullptr;
        head--;
        if(head < size/4){
            Vector<Data*>::Resize(size/2);
        }
    }
}

template <typename Data>
Data StackVec<Data>::TopNPop(){
    if(head == 0){
        throw std::length_error("Stack is Empty");
    }else{
        Data ret = *(Elements[head-1]);
        delete Elements[head-1];
        Elements[head-1] = nullptr;
        head--;
        if(head < size/4){
            Vector<Data*>::Resize(size/2);
        }
        return ret;
    }
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template <typename Data>
bool StackVec<Data>::Empty() const noexcept{
    return (head == 0);
}

template <typename Data>
unsigned long StackVec<Data>::Size() const noexcept{
    return head;
}


template <typename Data>
void StackVec<Data>::Clear(){
    for(unsigned long i=0; i<head; ++i){
        delete Elements[i];
        Elements[i] = nullptr;
    }
    head = 0;
}


/* ************************************************************************** */

}
