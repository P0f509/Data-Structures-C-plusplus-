
namespace lasd {

/* ************************************************************************** */

//NodeLnk functions

//Specific constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& val) {
  value = val;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& val) noexcept {
  std::swap(value, val);
}

//Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& node) {
  value = node.value;
  left = node.left;
  right = node.right;
}

//Move constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& node) noexcept {
  std::swap(value, node.value);
  std::swap(left, node.left);
  std::swap(right, node.right);
}

//Destructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
  delete left;
  delete right;
}

//Copy assignment
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& node) {
  value = node.value;
  left = node.left;
  right = node.right;
  return *this;
}

//Move assignment
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& node) noexcept {
  std::swap(value, node.value);
  std::swap(left, node.left);
  std::swap(right, node.right);
  return *this;
}

//Comparison operators

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::operator==(const NodeLnk& node) const noexcept {
  return BinaryTree<Data>::Node::operator==(node);
}


template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::operator!=(const NodeLnk& node) const noexcept {
  return BinaryTree<Data>::Node::operator!=(node);
}


// Specific member functions (inherited from Node)

template <typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
  return value;
}


template <typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
  return value;
}


template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept {
  return (left == nullptr && right == nullptr);
}


template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
  return (left != nullptr);
}


template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
  return (right != nullptr);
}


template <typename Data>
typename BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
  if(left != nullptr){
    return *left;
  } else {
    throw std::out_of_range("Left Child does not exists");
  }
}


template <typename Data>
typename BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
  if(right != nullptr){
    return *right;
  } else {
    throw std::out_of_range("Right Child does not exists");
  }
}

/* ************************************************************************** */

//Specific constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& con) {
  size = con.Size();
  if(size != 0) {
    root = BuildTreebyCon(con, 0);
  }
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk& bt) {
  size = bt.size;
  if(size != 0){
    root = BuildTreebyBT(bt.root);
  }
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk&& bt) noexcept {
  std::swap(root, bt.root);
  std::swap(size, bt.size);
}

/* ************************************************************************** */

// Destructor
template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
  delete root;
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt) {
  size = bt.size;
  if(size != 0){
    root = BuildTreebyBT(bt.root);
  }
  return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept {
  std::swap(root, bt.root);
  std::swap(size, bt.size);
  return *this;
}


/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk& bt) const noexcept {
  return BinaryTree<Data>::operator==(bt);
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk& bt) const noexcept {
  return BinaryTree<Data>::operator!=(bt);
}

/* ************************************************************************** */

// Specific member functions (inherited from BinaryTree)
template <typename Data>
typename BinaryTree<Data>::Node& BinaryTreeLnk<Data>::Root() const {
  if(size == 0) {
    throw std::length_error("Tree is empty");
  }else {
    return *root;
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)
template <typename Data>
void BinaryTreeLnk<Data>::Clear() {
  delete root;
  root = nullptr;
  size = 0;
}

/* ************************************************************************** */

//Auxuliary member functions

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::BuildTreebyCon(const LinearContainer<Data>& con, const unsigned long index) {
  NodeLnk* node = new NodeLnk(con[index]);
  if(2*index+1 < con.Size()){
    node->left = BuildTreebyCon(con, 2*index+1);
  }
  if(2*index+2 < con.Size()){
    node->right = BuildTreebyCon(con, 2*index+2);
  }
  return node;
}


template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::BuildTreebyBT(const NodeLnk* cur) {
  NodeLnk* node = new NodeLnk(cur->Element());
  if(cur->HasLeftChild()){
    node->left = BuildTreebyBT(cur->left);
  }
  if(cur->HasRightChild()){
    node->right = BuildTreebyBT(cur->right);
  }
  return node;
}


/* ************************************************************************** */

}
