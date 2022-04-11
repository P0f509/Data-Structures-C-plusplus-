
namespace lasd {

/* ************************************************************************** */

//Specific constructor

template <typename Data>
BST<Data>::BST(const LinearContainer<Data>& con) {
  for(unsigned long i=0; i<con.Size(); ++i){
    Insert(con[i]);
  }
}

/* ************************************************************************** */

//Copy constructor
template <typename Data>
BST<Data>::BST(const BST<Data>& bst) : BinaryTreeLnk<Data>::BinaryTreeLnk(bst) {

}

//Move constructor
template <typename Data>
BST<Data>::BST(BST<Data>&& bst) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bst)) {

}

/* ************************************************************************** */

//Copy assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& tree) {
  BinaryTreeLnk<Data>::operator=(tree);
  return *this;
}

//Move assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& tree) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(tree));
  return *this;
}

/* ************************************************************************** */

//Comparison operators

template <typename Data>
bool BST<Data>::operator==(const BST<Data>& tree) const noexcept {
  if(size == tree.size) {
    BTInOrderIterator<Data> itr1(*this);
    BTInOrderIterator<Data> itr2(tree);
    while(!itr1.Terminated()) {
      if(*itr1 != *itr2) {
        return false;
      }
      ++itr1;
      ++itr2;
    }
    return true;
  }else {
    return false;
  }
}

template <typename Data>
bool BST<Data>::operator!=(const BST<Data>& tree) const noexcept {
  return !(*this == tree);
}

/* ************************************************************************** */

//Specific member functions

template <typename Data>
void BST<Data>::Insert(const Data& dat) {
  NodeLnk*& ptr = FindPointerTo(root, dat);
  if(ptr == nullptr) {
    ptr = new NodeLnk(dat);
    size++;
  }
}


template <typename Data>
void BST<Data>::Insert(Data&& dat) noexcept {
  NodeLnk*& ptr = FindPointerTo(root, dat);
  if(ptr == nullptr) {
    ptr = new NodeLnk(std::move(dat));
    size++;
  }
}


template <typename Data>
void BST<Data>::Remove(const Data& dat) {
  NodeLnk*& ptr = FindPointerTo(root, dat);
  if(ptr != nullptr){
    delete Detach(ptr);
  }
}


template <typename Data>
const Data& BST<Data>::Min() const {
  if(size == 0) {
    throw std::length_error("Tree is Empty");
  }else {
    return FindPointerToMin(root)->value;
  }
}


template <typename Data>
Data BST<Data>::MinNRemove() {
  if(size == 0) {
    throw std::length_error("Tree is Empty");
  }else {
    return DataNDelete(DetachMin(root));
  }
}


template <typename Data>
void BST<Data>::RemoveMin() {
  if(size == 0) {
    throw std::length_error("Tree is Empty");
  }else {
    delete DetachMin(root);
  }
}


template <typename Data>
const Data& BST<Data>::Max() const {
  if(size == 0) {
    throw std::length_error("Tree is Empty");
  }else {
    return FindPointerToMax(root)->value;
  }
}


template <typename Data>
Data BST<Data>::MaxNRemove() {
  if(size == 0) {
    throw std::length_error("Tree is Empty");
  }else {
    return DataNDelete(DetachMax(root));
  }
}


template <typename Data>
void BST<Data>::RemoveMax() {
  if(size == 0) {
    throw std::length_error("Tree is Empty");
  }else {
    delete DetachMax(root);
  }
}


template <typename Data>
const Data& BST<Data>::Predecessor(const Data& dat) const {
  NodeLnk* const& pre = FindPointerToPredecessor(root, dat);
  if(pre == nullptr){
    throw std::length_error("Predecessor not found");
  }else {
    return pre->value;
  }
}


template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& dat) {
  NodeLnk*& pre = FindPointerToPredecessor(root, dat);
  if(pre == nullptr){
    throw std::length_error("Predecessor not found");
  }else {
    return DataNDelete(Detach(pre));
  }
}


template <typename Data>
void BST<Data>::RemovePredecessor(const Data& dat) {
  NodeLnk*& pre = FindPointerToPredecessor(root, dat);
  if(pre == nullptr){
    throw std::length_error("Predecessor not found");
  }else {
    delete Detach(pre);
  }
}


template <typename Data>
const Data& BST<Data>::Successor(const Data& dat) const {
  NodeLnk* const& suc = FindPointerToSuccessor(root, dat);
  if(suc == nullptr){
    throw std::length_error("Successor not found");
  }else {
    return suc->value;
  }
}


template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& dat) {
  NodeLnk*& suc = FindPointerToSuccessor(root, dat);
  if(suc == nullptr){
    throw std::length_error("Successor not found");
  }else {
    return DataNDelete(Detach(suc));
  }
}


template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& dat) {
  NodeLnk*& suc = FindPointerToSuccessor(root, dat);
  if(suc == nullptr){
    throw std::length_error("Successor not found");
  }else {
    delete Detach(suc);
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template <typename Data>
bool BST<Data>::Exists(const Data& dat) const noexcept {
  return (FindPointerTo(root, dat) != nullptr);
}

/* ************************************************************************** */

// Auxiliary member functions

template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk* ptr) {
  Data ret = ptr->value;
  delete ptr;
  return ret;
}


template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {
  if(node != nullptr) {
    if(node->right == nullptr) {
      return SkipOnLeft(node);
    }else if(node->left == nullptr) {
      return SkipOnRight(node);
    }else {
      NodeLnk* tmp = DetachMin(node->right);
      std::swap(tmp->value, node->value);
      return tmp;
    }
  }else {
    return nullptr;
  }
}


template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept {
  return SkipOnRight(FindPointerToMin(node));
}


template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept {
  return SkipOnLeft(FindPointerToMax(node));
}


template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnLeft(NodeLnk*& node) noexcept {
  NodeLnk* tmp = nullptr;
  if(node != nullptr) {
    std::swap(tmp, node->left);
    std::swap(tmp, node);
    size--;
  }
  return tmp;
}


template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnRight(NodeLnk*& node) noexcept {
  NodeLnk* tmp = nullptr;
  if(node != nullptr) {
    std::swap(tmp, node->right);
    std::swap(tmp, node);
    size--;
  }
  return tmp;
}


template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& node) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));
}


template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& node) const noexcept {
  NodeLnk* const* ptr = &node;
  NodeLnk* cur = node;
  if(cur != nullptr) {
    while(cur->left != nullptr) {
      ptr = &(cur->left);
      cur = cur->left;
    }
  }
  return *ptr;
}


template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& node) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(node));
}


template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& node) const noexcept {
  NodeLnk* const* ptr = &node;
  NodeLnk* cur = node;
  if(cur != nullptr) {
    while(cur->right != nullptr) {
      ptr = &(cur->right);
      cur = cur->right;
    }
  }
  return *ptr;
}


template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, const Data& dat) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node, dat));
}


template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, const Data& dat) const noexcept {
  NodeLnk* const* ptr = &node;
  NodeLnk* cur = node;
  while(cur != nullptr && cur->value != dat) {
    if(cur->value < dat) {
      ptr = &(cur->right);
      cur = cur->right;
    }else {
      ptr = &(cur->left);
      cur = cur->left;
    }
  }
  return *ptr;
}


template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(NodeLnk*& node, const Data& dat) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node, dat));
}


template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(NodeLnk* const& node, const Data& dat) const noexcept {
  NodeLnk* const* ptr = nullptr;
  NodeLnk* const* cur = &node;
  while(*cur != nullptr) {
    if((*cur)->value == dat) {
      if((*cur)->left != nullptr) {
        return FindPointerToMax((*cur)->left);
      }
      cur = &((*cur)->left);
      break;
    }else if((*cur)->value < dat) {
      ptr = cur;
      cur = &((*cur)->right);
    }else {
      cur = &((*cur)->left);
    }
  }
  if(ptr == nullptr) {
    ptr = cur;
  }
  return *ptr;
}


template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(NodeLnk*& node, const Data& dat) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node, dat));
}


template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, const Data& dat) const noexcept {
  NodeLnk* const* ptr = nullptr;
  NodeLnk* const* cur = &node;
  while(*cur != nullptr) {
    if((*cur)->value == dat) {
      if((*cur)->right != nullptr) {
        return FindPointerToMin((*cur)->right);
      }
      cur = &((*cur)->right);
      break;
    }else if((*cur)->value < dat) {
      cur = &((*cur)->right);
    }else {
      ptr = cur;
      cur = &((*cur)->left);
    }
  }
  if(ptr == nullptr) {
    ptr = cur;
  }
  return *ptr;
}


/* ************************************************************************** */

}
