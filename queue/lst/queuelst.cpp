
namespace lasd {

/* ************************************************************************** */

// Specific constructor

template <typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& con) : List<Data>::List(con){

}

/* ************************************************************************ */

// Copy constructor

template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst& queue) : List<Data>::List(queue){

}

//Move constructor

template <typename Data>
QueueLst<Data>::QueueLst(QueueLst&& queue) noexcept : List<Data>::List(std::move(queue)){

}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queue){
    List<Data>::operator=(queue);
    return *this;
}

// Move assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& queue) noexcept{
    List<Data>::operator=(std::move(queue));
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& queue) const noexcept{
    return List<Data>::operator==(queue);
}

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst<Data>& queue) const noexcept{
    return List<Data>::operator!=(queue);
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)
template <typename Data>
void QueueLst<Data>::Enqueue(const Data& dat){
    List<Data>::InsertAtBack(dat);
}

template <typename Data>
void QueueLst<Data>::Enqueue(Data&& dat) noexcept{
    List<Data>::InsertAtBack(std::move(dat));
}

template <typename Data>
Data& QueueLst<Data>::Head() const{
    return List<Data>::Front();
}

template <typename Data>
void QueueLst<Data>::Dequeue(){
    List<Data>::RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data>::HeadNDequeue(){
    return List<Data>::FrontNRemove();
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void QueueLst<Data>::Clear(){
    List<Data>::Clear();
}

/* ************************************************************************** */

}
