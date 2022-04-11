
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> {

private:

protected:

  using BinaryTree<Data>::size;

  struct NodeLnk : virtual public BinaryTree<Data>::Node {

  private:

  protected:

  public:

    Data value;
    NodeLnk* left = nullptr;
    NodeLnk* right = nullptr;

    //specific constructor
    NodeLnk(const Data&);
    NodeLnk(Data&&) noexcept;

    /* ********************************************************************** */

    //Copy constructor
    NodeLnk(const NodeLnk&);

    //Move constructor
    NodeLnk(NodeLnk&&) noexcept;

    /* ********************************************************************** */

    //Destructor
    virtual ~NodeLnk();

    /* ********************************************************************** */

    //Copy assignment
    NodeLnk& operator=(const NodeLnk&);

    //Move assignment
    NodeLnk& operator=(NodeLnk&&) noexcept;

    /* ********************************************************************** */

    //Comparison operators
    bool operator==(const NodeLnk&) const noexcept;
    bool operator!=(const NodeLnk&) const noexcept;

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

  NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept;
  bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  typename BinaryTree<Data>::Node& Root() const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override;


protected:

  // Auxiliary member functions

  NodeLnk* BuildTreebyCon(const LinearContainer<Data>&, const unsigned long);

  NodeLnk* BuildTreebyBT(const NodeLnk*);

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
