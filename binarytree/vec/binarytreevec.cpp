
namespace lasd {

/* ************************************************************************** */

//NodeVec functions


//specific constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& val, const unsigned long i, Vector<NodeVec*>& btVec) {
  value = val;
  index = i;
  vec = &btVec;
}

//Copy Constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const NodeVec& node) {
  value = node.value;
  index = node.index;
  vec = node.vec;
}

//Move Constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(NodeVec&& node) noexcept {
  std::swap(value, node.value);
  std::swap(index, node.index);
  std::swap(vec, node.vec);
}

//Copy Assignment
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& node) {
  value = node.value;
  index = node.index;
  vec = node.vec;
  return *this;
}

//Move Assignment
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& node) noexcept {
  std::swap(value, node.value);
  std::swap(index, node.index);
  std::swap(vec, node.vec);
  return *this;
}

//Comparison operators

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::operator==(const NodeVec& node) const noexcept {
  return BinaryTree<Data>::Node::operator==(node);
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::operator!=(const NodeVec& node) const noexcept {
  return BinaryTree<Data>::Node::operator!=(node);
}

// Specific member functions (inherited from Node)

template <typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
  return value;
}


template <typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
  return value;
}


template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept {
  return !(HasLeftChild() || HasRightChild());
}


template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
  return ((index*2)+1 < vec->Size());
}


template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
  return((index*2)+2 < vec->Size());
}


template <typename Data>
typename BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
  if((index*2)+1 < vec->Size()) {
    return *(vec->operator[]((index*2)+1));
  }else {
    throw std::out_of_range("Left Child does not exists");
  }
}


template <typename Data>
typename BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() const {
  if((index*2)+2 < vec->Size()) {
    return *(vec->operator[]((index*2)+2));
  }else {
    throw std::out_of_range("Right Child does not exists");
  }
}

/* ************************************************************************** */

//Specific constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& con) {
  size = con.Size();
  treeVector.Resize(size);
  for(unsigned long i=0; i<size; ++i){
    treeVector[i] = new NodeVec(con[i], i, treeVector);
  }
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& bt) {
  size = bt.size;
  treeVector.Resize(size);
  for(unsigned long i=0; i<size; ++i){
    treeVector[i] = new NodeVec(bt.treeVector[i]->Element(), i, treeVector);
  }
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& bt) noexcept {
  std::swap(size, bt.size);
  std::swap(treeVector, bt.treeVector);
}

/* ************************************************************************** */

// Destructor
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
  for(unsigned long i=0; i<size; ++i){
    delete treeVector[i];
  }
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt) {
  size = bt.size;
  treeVector.Resize(size);
  for(unsigned long i=0; i<size; ++i){
    treeVector[i] = new NodeVec(bt.treeVector[i]->Element(), i, treeVector);
  }
  return *this;
}

// Move assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& bt) noexcept {
  std::swap(size, bt.size);
  std::swap(treeVector, bt.treeVector);
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& bt) const noexcept {
  return BinaryTree<Data>::operator==(bt);
}


template <typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& bt) const noexcept {
  return BinaryTree<Data>::operator!=(bt);
}

/* ************************************************************************** */

// Specific member functions (inherited from BinaryTree)

template <typename Data>
typename BinaryTree<Data>::Node& BinaryTreeVec<Data>::Root() const {
  if(size == 0){
    throw std::length_error("Tree is empty");
  }else {
    return *treeVector[0];
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template <typename Data>
void BinaryTreeVec<Data>::Clear() {
  for(unsigned long i=0; i<size; ++i){
    delete treeVector[i];
    treeVector[i] = nullptr;
  }
  size = 0;
}

/* ************************************************************************** */

// Specific member functions (inherited from BreadthMappableContainer)

template <typename Data>
void BinaryTreeVec<Data>::MapBreadth(const MapFunctor fun, void* par) {
  for(unsigned long i=0; i<size; ++i) {
    fun(treeVector[i]->Element(), par);
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from BreadthFoldableContainer)

template <typename Data>
void BinaryTreeVec<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const {
  for(unsigned long i=0; i<size; ++i) {
    fun(treeVector[i]->Element(), par, acc);
  }
}

/* ************************************************************************** */

}
