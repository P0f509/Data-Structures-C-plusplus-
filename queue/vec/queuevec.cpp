
namespace lasd {

/* ************************************************************************ */

// Default constructor

template <typename Data>
QueueVec<Data>::QueueVec(){
    Elements = new Data*[9]{};
    size = 9;
}

/* ************************************************************************ */

// Specific constructor

template <typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& con){
    if(con.Size() != 0){
        size = con.Size()+1;
        Elements = new Data*[size]{};
        unsigned long j = 0;
        for(unsigned long i=0; i<con.Size(); ++i){
            j++;
            Elements[j] = new Data(con[i]);
        }
        tail = 0;
    }else{
        Elements = new Data*[9]{};
        size = 9;
    }
}

/* ************************************************************************ */

// Copy constructor

template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& queue){
    size = queue.size;
    head = queue.head;
    tail = queue.tail;
    Elements = new Data*[size]{};
    for(unsigned long i=0; i<size; ++i){
        if(queue.Elements[i] != nullptr){
            Elements[i] = new Data(*(queue.Elements[i]));
        }
    }
}

// Move constructor

template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& queue) noexcept{
    std::swap(Elements, queue.Elements);
    std::swap(head, queue.head);
    std::swap(size, queue.size);
    std::swap(tail, queue.tail);
}

/* ************************************************************************ */

// Destructor

template <typename Data>
QueueVec<Data>::~QueueVec(){
    Clear();
}

/* ************************************************************************ */

// Copy assignment

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queue){
    size = queue.size;
    head = queue.head;
    tail = queue.tail;
    Elements = new Data*[size]{};
    for(unsigned long i=0; i<size; ++i){
        if(queue.Elements[i] != nullptr){
            Elements[i] = new Data(*(queue.Elements[i]));
        }
    }
    return *this;
}

// Move assignment

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queue) noexcept{
    std::swap(Elements, queue.Elements);
    std::swap(head, queue.head);
    std::swap(size, queue.size);
    std::swap(tail, queue.tail);
    return *this;
}

/* ************************************************************************ */

// Comparison operators

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& queue) const noexcept{
    if(Size() == queue.Size()){
        unsigned long it1 = head;
        unsigned long it2 = queue.head;
        while(it1 != tail && it2 != queue.tail){
            if(*(Elements[it1]) != *(queue.Elements[it2])){
                return false;
            }
            it1 = (it1 + 1)%size;
            it2 = (it2 + 1)%queue.size;
        }
        return true;
    }else{
        return false;
    }
}

template <typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& queue) const noexcept{
    return !(*this == queue);
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)


template <typename Data>
void QueueVec<Data>::Enqueue(const Data& dat){
    if((tail+1)%size == head){
        ResizeVector(size*2);
    }
    Elements[tail] = new Data(dat);
    tail = (tail+1)%size;
}


template <typename Data>
void QueueVec<Data>::Enqueue(Data&& dat) noexcept{
    if((tail+1)%size == head){
        ResizeVector(size*2);
    }
    Elements[tail] = new Data(std::move(dat));
    tail = (tail+1)%size;
}


template <typename Data>
Data& QueueVec<Data>::Head() const{
    if(Empty()){
        throw std::length_error("Queue is Empty");
    }else{
        return *(Elements[head]);
    }
}


template <typename Data>
void QueueVec<Data>::Dequeue(){
    if(Empty()){
        throw std::length_error("Queue is Empty");
    }else{
        delete Elements[head];
        Elements[head] = nullptr;
        head = (head+1)%size;
        if(Size() < size/4){
            ResizeVector(size/2);
        }
    }
}


template <typename Data>
Data QueueVec<Data>::HeadNDequeue(){
    if(Empty()){
        throw std::length_error("Queue is Empty");
    }else{
        Data ret = *(Elements[head]);
        delete Elements[head];
        Elements[head] = nullptr;
        head = (head+1)%size;
        if(Size() < size/4){
            ResizeVector(size/2);
        }
        return ret;
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
bool QueueVec<Data>::Empty() const noexcept{
    return (head == tail);
}


template <typename Data>
unsigned long QueueVec<Data>::Size() const noexcept{
    if(tail >= head){
        return (tail - head);
    }else{
        return ((size - head) + tail);
    }
}


template <typename Data>
void QueueVec<Data>::Clear(){
    for(unsigned long i=0; i<size; ++i){
        delete Elements[i];
        Elements[i] = nullptr;
    }
    head = tail = 1;
}

/* ************************************************************************ */

// Auxiliary member functions

template <typename Data>
void QueueVec<Data>::ResizeVector(const unsigned long newsize){
    Data** tmp = new Data*[newsize]{};
    unsigned long it = head;
    for(unsigned long i=1; i<=Size(); ++i){
        std::swap(tmp[i], Elements[it]);
        it = (it+1)%size;
    }
    std::swap(Elements, tmp);
    delete[] tmp;
    tail = Size()+1;
    head = 1;
    size = newsize;
}

/* ************************************************************************ */

}
