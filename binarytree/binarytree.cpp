
namespace lasd {

/* ************************************************************************** */

// Node functions

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept {

  if(Element() == node.Element()) {

    if(HasLeftChild() && node.HasLeftChild()) {
      if(!(LeftChild() == node.LeftChild())) {
        return false;
      }
    }else if(HasLeftChild() || node.HasLeftChild()) {
      return false;
    }

    if(HasRightChild() && node.HasRightChild()) {
      if(!(RightChild() == node.RightChild())) {
        return false;
      }
    }else if(HasRightChild() || node.HasRightChild()) {
      return false;
    }

    return true;

  }else {

    return false;

  }

}


template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept {
  return !(*this == node);
}

/* ************************************************************************** */

//Binary Tree functions

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept {
  if(size == bt.size){
    if(size == 0){
      return true;
    }else {
      return Root() == bt.Root();
    }
  }else {
    return false;
  }
}


template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const noexcept {
  return !(*this == bt);
}


template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  if(size > 0){
    MapPreOrder(fun, par, &(Root()));
  }
}


template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  if(size > 0){
    MapPostOrder(fun, par, &(Root()));
  }
}


template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if(size > 0){
    FoldPreOrder(fun, par, acc, &(Root()));
  }
}


template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if(size > 0){
    FoldPostOrder(fun, par, acc, &(Root()));
  }
}


template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par) {
  if(size > 0){
    MapInOrder(fun, par, &(Root()));
  }
}


template <typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if(size > 0){
    FoldInOrder(fun, par, acc, &(Root()));
  }
}


template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par) {
  if(size > 0){
    MapBreadth(fun, par, &(Root()));
  }
}


template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const {
  if(size > 0){
    FoldBreadth(fun, par, acc, &(Root()));
  }
}


template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par, Node* curr) {
  fun(curr->Element(), par);
  if(curr->HasLeftChild()){
    MapPreOrder(fun, par, &(curr->LeftChild()));
  }
  if(curr->HasRightChild()){
    MapPreOrder(fun, par, &(curr->RightChild()));
  }
}


template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par, Node* curr) {
  if(curr->HasLeftChild()){
    MapPostOrder(fun, par, &(curr->LeftChild()));
  }
  if(curr->HasRightChild()){
    MapPostOrder(fun, par, &(curr->RightChild()));
  }
  fun(curr->Element(), par);
}


template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, Node* curr) const {
  fun(curr->Element(), par, acc);
  if(curr->HasLeftChild()){
    FoldPreOrder(fun, par, acc, &(curr->LeftChild()));
  }
  if(curr->HasRightChild()){
    FoldPreOrder(fun, par, acc, &(curr->RightChild()));
  }
}


template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node* curr) const {
  if(curr->HasLeftChild()){
    FoldPostOrder(fun, par, acc, &(curr->LeftChild()));
  }
  if(curr->HasRightChild()){
    FoldPostOrder(fun, par, acc, &(curr->RightChild()));
  }
  fun(curr->Element(), par, acc);
}


template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par, Node* curr) {
  if(curr->HasLeftChild()){
    MapInOrder(fun, par, &(curr->LeftChild()));
  }
  fun(curr->Element(), par);
  if(curr->HasRightChild()){
    MapInOrder(fun, par, &(curr->RightChild()));
  }
}


template <typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc, Node* curr) const {
  if(curr->HasLeftChild()){
    FoldInOrder(fun, par, acc, &(curr->LeftChild()));
  }
  fun(curr->Element(), par, acc);
  if(curr->HasRightChild()){
    FoldInOrder(fun, par, acc, &(curr->RightChild()));
  }
}


template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par, Node* curr) {
  QueueLst<Node*> queue;
  queue.Enqueue(curr);
  while(!(queue.Empty())) {
    Node* node = queue.HeadNDequeue();
    fun(node->Element(), par);
    if(node->HasLeftChild()) {
      queue.Enqueue(&(node->LeftChild()));
    }
    if(node->HasRightChild()) {
      queue.Enqueue(&(node->RightChild()));
    }
  }
}


template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc, Node* curr) const {
  QueueLst<Node*> queue;
  queue.Enqueue(curr);
  while(!(queue.Empty())) {
    Node* node = queue.HeadNDequeue();
    fun(node->Element(), par, acc);
    if(node->HasLeftChild()) {
      queue.Enqueue(&(node->LeftChild()));
    }
    if(node->HasRightChild()) {
      queue.Enqueue(&(node->RightChild()));
    }
  }
}

/* ************************************************************************** */

// BTPreOrderIterator functions

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) {
  if(bt.Size() > 0){
    current = &(bt.Root());
  }
}


template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& iterator) {
  current = iterator.current;
  stack = iterator.stack;
}


template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& iterator) noexcept {
  std::swap(current, iterator.current);
  std::swap(stack, iterator.stack);
}


template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& iterator) {
  current = iterator.current;
  stack = iterator.stack;
  return *this;
}


template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& iterator) noexcept {
  std::swap(current, iterator.current);
  std::swap(stack, iterator.stack);
  return *this;
}


template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& iterator) const noexcept {
  return ((current == iterator.current) && (stack == iterator.stack));
}


template <typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& iterator) const noexcept {
  return !(*this == iterator);
}


template <typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
  if(Terminated()){
    throw std::out_of_range("Node does not exists");
  }else{
    return current->Element();
  }
}


template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
  return (current == nullptr);
}


template <typename Data>
ForwardIterator<Data>&  BTPreOrderIterator<Data>::operator++() {
  if(Terminated()){
    throw std::out_of_range("Iteration is terminated");
  }else{
    if(current->HasLeftChild()){
      if(current->HasRightChild()){
        stack.Push(&(current->RightChild()));
      }
      current = &(current->LeftChild());
    } else if(current->HasRightChild()){
      current = &(current->RightChild());
    } else {
      if(stack.Empty()){
        current = nullptr;
      }else {
        current = stack.TopNPop();
      }
    }
    return *this;
  }
}

/* ************************************************************************** */

// BTPostOrderIterator functions

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) {
  if(bt.Size() > 0){
    current = leftMostLeaf(&(bt.Root()));
  }
}


template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& iterator) {
  current = iterator.current;
  stack = iterator.stack;
}


template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& iterator) noexcept {
  std::swap(current, iterator.current);
  std::swap(stack, iterator.stack);
}


template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& iterator) {
  current = iterator.current;
  stack = iterator.stack;
  return *this;
}


template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& iterator) noexcept {
  std::swap(current, iterator.current);
  std::swap(stack, iterator.stack);
  return *this;
}


template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& iterator) const noexcept {
  return ((current == iterator.current) && (stack == iterator.stack));
}


template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& iterator) const noexcept {
  return !(*this == iterator);
}


template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const{
  if(Terminated()){
    throw std::out_of_range("Node does not exists");
  }else {
    return current->Element();
  }
}


template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
  return (current == nullptr);
}


template <typename Data>
ForwardIterator<Data>& BTPostOrderIterator<Data>::operator++() {
  if(Terminated()){
    throw std::out_of_range("Iteration is terminated");
  }else{
    if(stack.Empty()){
      current = nullptr;
    }else {
      if((stack.Top()->HasLeftChild()) && (current == &(stack.Top()->LeftChild()))) {
        if(stack.Top()->HasRightChild()) {
          current = leftMostLeaf(&(stack.Top()->RightChild()));
        }else {
          current = stack.TopNPop();
        }
      }else {
        current = stack.TopNPop();
      }
    }
    return *this;
  }
}


template <typename Data>
typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::leftMostLeaf(typename BinaryTree<Data>::Node* cur) {
  while(!(cur->IsLeaf())){
    while(cur->HasLeftChild()){
      stack.Push(cur);
      cur = &(cur->LeftChild());
    }
    if(cur->HasRightChild()){
      stack.Push(cur);
      cur = &(cur->RightChild());
    }
  }
  return cur;
}


/* ************************************************************************** */

// BTInOrderIterator functions

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) {
  if(bt.Size() > 0){
    current = leftMostNode(&(bt.Root()));
  }
}


template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& iterator) {
  current = iterator.current;
  stack = iterator.stack;
}


template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& iterator) noexcept {
  std::swap(current, iterator.current);
  std::swap(stack, iterator.stack);
}


template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& iterator) {
  current = iterator.current;
  stack = iterator.stack;
  return *this;
}


template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& iterator) noexcept {
  std::swap(current, iterator.current);
  std::swap(stack, iterator.stack);
  return *this;
}


template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& iterator) const noexcept {
  return ((current == iterator.current) && (stack == iterator.stack));
}


template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& iterator) const noexcept {
  return !(*this == iterator);
}


template <typename Data>
Data& BTInOrderIterator<Data>::operator*() const{
  if(Terminated()){
    throw std::out_of_range("Node does not exists");
  }else {
    return current->Element();
  }
}


template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
  return (current == nullptr);
}


template <typename Data>
ForwardIterator<Data>& BTInOrderIterator<Data>::operator++() {
  if(Terminated()){
    throw std::out_of_range("Iteration is terminated");
  }else{
    if(current->HasRightChild()){
      current = leftMostNode(&(current->RightChild()));
    }else {
      if(stack.Empty()){
        current = nullptr;
      }else {
        current = stack.TopNPop();
      }
    }
    return *this;
  }
}

template <typename Data>
typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::leftMostNode(typename BinaryTree<Data>::Node* cur) {
  while(cur->HasLeftChild()){
    stack.Push(cur);
    cur = &(cur->LeftChild());
  }
  return cur;
}


/* ************************************************************************** */

// BTBreadthIterator functions

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {
  if(bt.Size() > 0){
    current = &(bt.Root());
  }
}


template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& iterator) {
  current = iterator.current;
  queue = iterator.queue;
}


template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& iterator) noexcept {
  std::swap(iterator.current, current);
  std::swap(queue, iterator.queue);
}


template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& iterator) {
  current = iterator.current;
  queue = iterator.queue;
  return *this;
}


template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& iterator) noexcept {
  std::swap(iterator.current, current);
  std::swap(queue, iterator.queue);
  return *this;
}


template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& iterator) const noexcept {
  return ((current == iterator.current) && (queue == iterator.queue));
}


template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& iterator) const noexcept {
  return !(*this == iterator);
}


template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const{
  if(Terminated()){
    throw std::out_of_range("Node does not exists");
  }else{
    return current->Element();
  }
}


template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
  return (current == nullptr);
}


template <typename Data>
ForwardIterator<Data>& BTBreadthIterator<Data>::operator++() {
  if(Terminated()){
    throw std::out_of_range("Iteration is terminated");
  }else{
    if(current->HasLeftChild()){
      queue.Enqueue(&(current->LeftChild()));
    }
    if(current->HasRightChild()){
      queue.Enqueue(&(current->RightChild()));
    }
    if(queue.Empty()){
      current = nullptr;
    }else{
      current = queue.HeadNDequeue();
    }
    return *this;
  }
}

/* ************************************************************************** */

}
