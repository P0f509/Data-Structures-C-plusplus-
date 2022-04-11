
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public BinaryTreeLnk<Data> {

private:

protected:

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;
  using typename BinaryTreeLnk<Data>::NodeLnk;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST&);

  // Move constructor
  BST(BST&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST&);

  // Move assignment
  BST& operator=(BST&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST&) const noexcept;
  bool operator!=(const BST&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void Insert(const Data&);
  void Insert(Data&&) noexcept;
  void Remove(const Data&);

  const Data& Min() const;
  Data MinNRemove();
  void RemoveMin();

  const Data& Max() const;
  Data MaxNRemove();
  void RemoveMax();

  const Data& Predecessor(const Data&) const;
  Data PredecessorNRemove(const Data&);
  void RemovePredecessor(const Data&);

  const Data& Successor(const Data&) const;
  Data SuccessorNRemove(const Data&);
  void RemoveSuccessor(const Data&);

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override;

protected:

  // Auxiliary member functions

  Data DataNDelete(NodeLnk*);

  NodeLnk* Detach(NodeLnk*&) noexcept;

  NodeLnk* DetachMin(NodeLnk*&) noexcept;
  NodeLnk* DetachMax(NodeLnk*&) noexcept;

  NodeLnk* SkipOnLeft(NodeLnk*&) noexcept;
  NodeLnk* SkipOnRight(NodeLnk*&) noexcept;

  NodeLnk*& FindPointerToMin(NodeLnk*&) noexcept;
  NodeLnk* const& FindPointerToMin(NodeLnk* const&) const noexcept;
  NodeLnk*& FindPointerToMax(NodeLnk*&) noexcept;
  NodeLnk* const& FindPointerToMax(NodeLnk* const&) const noexcept;

  NodeLnk*& FindPointerTo(NodeLnk*&, const Data&) noexcept;
  NodeLnk* const& FindPointerTo(NodeLnk* const&, const Data&) const noexcept;

  NodeLnk*& FindPointerToPredecessor(NodeLnk*&, const Data&) noexcept;
  NodeLnk* const& FindPointerToPredecessor(NodeLnk* const&, const Data&) const noexcept;
  NodeLnk*& FindPointerToSuccessor(NodeLnk*&, const Data&) noexcept;
  NodeLnk* const& FindPointerToSuccessor(NodeLnk* const&, const Data&) const noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
