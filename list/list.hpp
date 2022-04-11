
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public LinearContainer<Data>,
             virtual public MappableContainer<Data>,
             virtual public FoldableContainer<Data> {

private:

protected:

  using LinearContainer<Data>::size;

  struct Node
  {

    Data value;
    Node* next = nullptr;

    /* ********************************************************************** */

    //Default constructor
    Node() = default;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data&);
    Node(Data&&) noexcept;
    Node(const Data&, Node*);

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node&);

    // Move constructor
    Node(Node&&) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node&) const noexcept;
    bool operator!=(const Node&) const noexcept;

    /* ********************************************************************** */

  };

  Node* head = nullptr;
  Node* tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  List(const List&);

  // Move constructor
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&);
  void InsertAtFront(Data&&) noexcept;

  void RemoveFromFront();
  Data FrontNRemove();

  void InsertAtBack(const Data&);
  void InsertAtBack(Data&&) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override;
  Data& Back() const override;

  Data& operator[](const unsigned long) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapPreOrder(const MapFunctor, void*) override;
  void MapPostOrder(const MapFunctor, void*) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void FoldPreOrder(const FoldFunctor, const void*, void*) const override;
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override;

protected:

  // Auxiliary member functions (for MappableContainer)

  void MapPreOrder(const MapFunctor, void*, Node*);
  void MapPostOrder(const MapFunctor, void*, Node*);

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer)

  void FoldPreOrder(const FoldFunctor, const void*, void*, Node*) const;
  void FoldPostOrder(const FoldFunctor, const void*, void*, Node*) const;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
