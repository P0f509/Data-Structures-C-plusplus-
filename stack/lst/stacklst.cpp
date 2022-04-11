
namespace lasd {

/* ************************************************************************** */

//Specific Constructor

template <typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& con) : List<Data>::List(con){

}

/* ************************************************************************** */

//Copy constructor

template <typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& st) : List<Data>::List(st){

}

//Move constructor

template <typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& st) noexcept : List<Data>::List(std::move(st)){

}

/* ************************************************************************** */

//Copy assignment

template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& st){
    List<Data>::operator=(st);
    return *this;
}

//Move assignment

template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& st) noexcept{
    List<Data>::operator=(std::move(st));
    return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& st) const noexcept{
    return List<Data>::operator==(st);
}

template <typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data>& st) const noexcept{
    return List<Data>::operator!=(st);
}

/* ************************************************************************** */

// Specific member functions (inherited from Stack)

template <typename Data>
void StackLst<Data>::Push(const Data& dat){
    List<Data>::InsertAtFront(dat);
}

template <typename Data>
void StackLst<Data>::Push(Data&& dat) noexcept{
    List<Data>::InsertAtFront(std::move(dat));
}

template <typename Data>
Data& StackLst<Data>::Top() const{
    return List<Data>::Front();
}

template <typename Data>
void StackLst<Data>::Pop(){
    List<Data>::RemoveFromFront();
}

template <typename Data>
Data StackLst<Data>::TopNPop(){
    return List<Data>::FrontNRemove();
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template <typename Data>
void StackLst<Data>::Clear(){
    List<Data>::Clear();
}

/* ************************************************************************** */

}
