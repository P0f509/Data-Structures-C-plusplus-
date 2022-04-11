
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue : virtual public Container{

private:

protected:

public:

  // Destructor
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  Queue& operator=(const Queue&) = delete;

  // Move assignment
  Queue& operator=(Queue&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Queue&) const noexcept = delete;
  bool operator!=(const Queue&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual void Enqueue(const Data&) = 0;
  virtual void Enqueue(Data&&) noexcept = 0;
  virtual Data& Head() const = 0; 
  virtual void Dequeue() = 0;
  virtual Data HeadNDequeue() = 0;

};

/* ************************************************************************** */

}

#endif
