
namespace lasd {

/* ************************************************************************** */

//Node functions

template <typename Data>
List<Data>::Node::Node(const Data& val){
    value = val;
    next = nullptr;
}

template <typename Data>
List<Data>::Node::Node(Data&& val) noexcept{
    std::swap(val, value);
}

template <typename Data>
List<Data>::Node::Node(const Data& val, Node* ptr){
    value = val;
    next = ptr;
}

template <typename Data>
List<Data>::Node::Node(const Node& nod){
    value = nod.value;
    next = nod.next;
}

template <typename Data>
List<Data>::Node::Node(Node&& nod) noexcept{
    std::swap(value, nod.value);
    std::swap(next, nod.next);
}

template <typename Data>
bool List<Data>::Node::operator==(const Node& nod) const noexcept{
    if(value == nod.value){
        return true;
    }
    return false;
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& nod) const noexcept{
    if(value == nod.value){
        return false;
    }else{
        return true;
    }
}

/* ************************************************************************** */

// Specific constructor

template <typename Data>
List<Data>::List(const LinearContainer<Data>& con){
    if(con.Size() != 0){
        size = con.Size();
        head = new Node(con[0]);
        Node* cur = head;
        for(unsigned long i = 1; i<size; ++i){
            cur->next = new Node(con[i]);
            cur = cur->next;
        }
        tail = cur;    
    }
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
List<Data>::List(const List<Data>& list){
    if(list.size != 0){
        Node* cur = list.head;
        head = new Node(cur->value);
        Node* tmp = head;
        while(cur->next != nullptr){
            cur = cur->next;
            tmp->next = new Node(cur->value);
            tmp = tmp->next;
        }
        tail = tmp;
        size = list.size;
    }
}

// Move constructor
template <typename Data>
List<Data>::List(List<Data>&& list) noexcept{
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
}

/* ************************************************************************** */

// Destructor
template <typename Data>
List<Data>::~List(){
    Node* ptr = head;
    Node* tmp = nullptr;
    while(ptr != nullptr){
        tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& list){
    if(list.size != 0){
        Node* cur = list.head;
        head = new Node(cur->value);
        Node* tmp = head;
        while(cur->next != nullptr){
            cur = cur->next;
            tmp->next = new Node(cur->value);
            tmp = tmp->next;
        }
        tail = tmp;
        size = list.size;
    }
    return *this;
}

// Move assignment
template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& list) noexcept{
    std::swap(head, list.head);
    std::swap(tail, list.tail);
    std::swap(size, list.size);
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool List<Data>::operator==(const List<Data>& list) const noexcept{
    if(size == list.size){
        Node* ptr1 = head;
        Node* ptr2 = list.head;
        while(ptr1 != nullptr && ptr2 != nullptr){
            if((ptr1->value)!=(ptr2->value)){
                return false;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        return true;
    }else{
        return false;
    }
}

template <typename Data>
bool List<Data>::operator!=(const List<Data>& list) const noexcept{
    return !(*this == list);
}

/* ************************************************************************** */

// Specific member functions
template <typename Data>
void List<Data>::InsertAtFront(const Data& val){
    if(size == 0){
        Node* tmp = new Node(val);
        head = tail = tmp;
    }else{
        Node* tmp = new Node(val, head);
        head = tmp;
    }
    size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& val) noexcept{
    Node* tmp = new Node(std::move(val));
    if(size == 0){  
        head = tail = tmp;
    }else{
        tmp->next = head;
        head = tmp;
    }
    size++;
}

template <typename Data>
void List<Data>::RemoveFromFront(){ 
    if(size == 0){
        throw std::length_error("Data Structure is Empty");
    }else{
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }     
}

template <typename Data>
Data List<Data>::FrontNRemove(){
    if(size == 0){
        throw std::length_error("Data Structure is Empty");
    }else{
        Data val = head->value;
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
        return val;
    }
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& val){
    Node* tmp = new Node(val);
    if(size == 0){
        head = tail = tmp;
    }else{
        tail->next = tmp;
        tail = tmp;
    }
    size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& val) noexcept{
    Node* tmp = new Node(std::move(val));
    if(size == 0){
        head = tail = tmp;
    }else{
        tail->next = tmp;
        tail = tmp;
    }
    size++;
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)
template <typename Data>
void List<Data>::Clear(){ 
    Node* ptr = head;
    Node* tmp = nullptr;
    while(ptr != nullptr){
        tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
    head = tail = nullptr;
    size = 0; 
}

/* ************************************************************************** */

// Specific member functions (inherited from LinearContainer)
template <typename Data>
Data& List<Data>::Front() const {
    if(size == 0){
        throw std::length_error("Data Structure is Empty");
    }else{
        return head->value;
    }
}

template <typename Data>
Data& List<Data>::Back() const {
    if(size == 0){
        throw std::length_error("Data Structure is Empty");
    }else{
        return tail->value;
    }  
}

template <typename Data>
Data& List<Data>::operator[](const unsigned long index) const{
    if(index < size){
        Node* tmp = head;
        unsigned long i = 0;
        while(i < index){
            i++;
            tmp = tmp->next;
        }
        return tmp->value;  
    }else{
        throw std::out_of_range("Index is greater than List size");
    }
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void List<Data>::MapPreOrder(const MapFunctor fun, void* par) {
    MapPreOrder(fun, par, head);
}

template <typename Data>
void List<Data>::MapPostOrder(const MapFunctor fun, void* par) {
    MapPostOrder(fun, par, head);
}

/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{
    FoldPreOrder(fun, par, acc, head);
}

template <typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
    FoldPostOrder(fun, par, acc, head);
}

/* ************************************************************************** */

// Auxiliary member functions (for MappableContainer)

template <typename Data>
void List<Data>::MapPreOrder(MapFunctor fun, void* par, Node* cur){
    while(cur != nullptr){
        fun(cur->value, par);
        cur = cur->next;
    }
}

template <typename Data>
void List<Data>::MapPostOrder(MapFunctor fun, void* par, Node* cur){
    if(cur != nullptr){
        MapPostOrder(fun, par, cur->next);
        fun(cur->value, par);
    }
}

/* ************************************************************************** */

// Auxiliary member functions (for FoldableContainer)

template <typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, Node* cur) const{
    while(cur != nullptr){
        fun(cur->value, par, acc);
        cur = cur->next;
    }
}

template <typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node* cur) const{
    if(cur != nullptr){
        FoldPostOrder(fun, par, acc, cur->next);
        fun(cur->value, par, acc);
    }
}

/* ************************************************************************** */

}
