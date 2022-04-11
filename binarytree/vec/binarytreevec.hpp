
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data> {

private:

protected:

  using BinaryTree<Data>::size;

  struct NodeVec : virtual public BinaryTree<Data>::Node {

  private:

  protected:

    Data value;
    unsigned long index;
    Vector<NodeVec*>* vec = nullptr;

  public:

    //specific constructor
    NodeVec(const Data&, const unsigned long, Vector<NodeVec*>&);

    /* ********************************************************************** */

    //Copy Constructor
    NodeVec(const NodeVec&);

    //Move Constructor
    NodeVec(NodeVec&&) noexcept;

    /* ********************************************************************** */

    //Destrcutor
    virtual ~NodeVec() = default;

    /* ********************************************************************** */

    //Copy Assignement
    NodeVec& operator=(const NodeVec&);

    //Move Assignment
    NodeVec& operator=(NodeVec&&) noexcept;

    /* ********************************************************************** */

    //Comparison operators

    bool operator==(const NodeVec&) const noexcept;
    bool operator!=(const NodeVec&) const noexcept;

    /* ********************************************************************** */

    // Specific member functions (inherited from Node)

    Data& Element() noexcept override;
    const Data& Element() const noexcept override;

    bool IsLeaf() const noexcept override;

    bool HasLeftChild() const noexcept override;
    bool HasRightChild() const noexcept override;

    typename BinaryTree<Data>::Node& LeftChild() const override;
    typename BinaryTree<Data>::Node& RightChild() const override;

  };

  Vector<NodeVec*> treeVector;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec&) const noexcept;
  bool operator!=(const BinaryTreeVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  typename BinaryTree<Data>::Node& Root() const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  using typename BreadthMappableContainer<Data>::MapFunctor;

  void MapBreadth(const MapFunctor, void*) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  using typename BreadthFoldableContainer<Data>::FoldFunctor;

  void FoldBreadth(const FoldFunctor, const void*, void*) const override;

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
