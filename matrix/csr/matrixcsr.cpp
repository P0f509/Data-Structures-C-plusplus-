
namespace lasd {

/* ************************************************************************** */

//Default constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR() {
  R.Resize(1);
  R[0] = &head;
}

/* ************************************************************************** */

//Specific constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const unsigned long r, const unsigned long c) {
  rows = r;
  columns = c;
  R.Resize(rows+1);
  for(unsigned long i=0; i<= rows; ++i) {
    R[i] = &head;
  }
}

/* ************************************************************************** */

//Copy constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& matr) {
  rows = matr.rows;
  columns = matr.columns;
  R.Resize(rows+1);
  Node* ptr = matr.head;
  Node** cur = &head;
  unsigned long i = 0;
  while(ptr != nullptr) {
    *cur = new Node(ptr->value);
    size++;
    while(i <= rows && ptr == *matr.R[i]) {
      R[i] = cur;
      i++;
    }
    cur = &((*cur)->next);
    ptr = ptr->next;
  }
  while(i <= rows) {
    R[i] = cur;
    i++;
  }
}


//Move constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data>&& matr) noexcept {
  std::swap(head, matr.head);
  std::swap(size, matr.size);
  std::swap(rows, matr.rows);
  std::swap(columns, matr.columns);
  std::swap(R, matr.R);
  for(unsigned long i=0; i<=rows && R[i]==&matr.head; ++i) {
    R[i] = &head;
  }
  matr.R.Resize(1);
  matr.R[0] = &matr.head;
}

/* ************************************************************************** */

//Copy assignment
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data>& matr) {
  rows = matr.rows;
  columns = matr.columns;
  R.Resize(rows+1);
  Node* ptr = matr.head;
  Node** cur = &head;
  unsigned long i = 0;
  while(ptr != nullptr) {
    *cur = new Node(ptr->value);
    size++;
    while(i <= rows && ptr == *matr.R[i]) {
      R[i] = cur;
      i++;
    }
    cur = &((*cur)->next);
    ptr = ptr->next;
  }
  while(i <= rows) {
    R[i] = cur;
    i++;
  }
  return *this;
}


//Move assignment
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data>&& matr) noexcept {
  std::swap(head, matr.head);
  std::swap(size, matr.size);
  std::swap(rows, matr.rows);
  std::swap(columns, matr.columns);
  std::swap(R, matr.R);
  for(unsigned long i=0; i<=rows && R[i]==&matr.head; ++i) {
    R[i] = &head;
  }
  for(unsigned long i=0; i<=matr.rows && matr.R[i]==&head; ++i) {
    matr.R[i] = &matr.head;
  }
  return *this;
}

/* ************************************************************************** */

//Comparison operators

template <typename Data>
bool MatrixCSR<Data>::operator==(const MatrixCSR<Data>& matr) const noexcept {
  if(rows == matr.rows && columns == matr.columns) {
    unsigned long i = 0;
    Node** ptr1 = nullptr;
    Node** ptr2 = nullptr;
    while(i < rows) {
      ptr1 = R[i];
      ptr2 = matr.R[i];
      while(ptr1 != R[i+1] && ptr2 != matr.R[i+1]) {
        if((*ptr1)->value != (*ptr2)->value) {
          return false;
        }
        ptr1 = &((*ptr1)->next);
        ptr2 = &((*ptr2)->next);
      }
      if(ptr1 != R[i+1] || ptr2 != matr.R[i+1]) {
        return false;
      }
      i++;
    }
    return true;
  }
  return false;
}


template <typename Data>
bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& matr) const noexcept {
  return !(*this == matr);
}

/* ************************************************************************** */

// Specific member functions (inherited from Matrix)

template <typename Data>
void MatrixCSR<Data>::RowResize(const unsigned long newsize) {
  if(newsize == 0) {
    List<std::pair<Data, unsigned long>>::Clear();
  }else if(newsize < rows) {
    Node* tmp = *R[newsize];
    while(tmp != nullptr) {
      Node* auxptr = tmp->next;
      delete tmp;
      tmp = auxptr;
      size--;
    }
    *R[newsize] = nullptr;
  }
  R.Resize(newsize+1);
  for(unsigned long i=rows+1; i<=newsize; ++i) {
    R[i] = R[rows];
  }
  rows = newsize;
}


template <typename Data>
void MatrixCSR<Data>::ColumnResize(const unsigned long newsize) {
  if(newsize == 0) {
    List<std::pair<Data, unsigned long>>::Clear();
  }else if(newsize < columns) {
    unsigned long i = 1;
    Node** ptr = &head;
    while(i <= rows) {
      Node** nod = R[i];
      while(ptr != nod && (*ptr)->value.second < newsize) {
        ptr = &((*ptr)->next);
      }
      if(ptr != nod) {
        Node* tmp = *ptr;
        *ptr = *nod;
        *nod = nullptr;
        while(tmp != nullptr) {
          Node* auxptr = tmp->next;
          delete tmp;
          tmp = auxptr;
          size--;
        }
      }
      while(i<= rows && R[i] == nod) {
        R[i] = ptr;
        i++;
      }
    }
  }
  columns = newsize;
}


template <typename Data>
bool MatrixCSR<Data>::ExistsCell(const unsigned long i, const unsigned long j) const noexcept {
  if(i < rows && j < columns) {
    Node* cur = *R[i];
    while(cur != *R[i+1]) {
      if(cur->value.second == j) {
        return true;
      }
      cur = cur->next;
    }
  }
  return false;
}


template <typename Data>
Data& MatrixCSR<Data>::operator()(const unsigned long i, const unsigned long j) {
  if(i < rows && j < columns) {
    Node** ptr = R[i];
    Node* cur = *ptr;
    while(ptr != R[i+1] && cur->value.second < j) {
      ptr = &((*ptr)->next);
      cur = cur->next;
    }
    if(ptr == R[i+1] || cur->value.second != j) {
      *ptr = new Node();
      (*ptr)->next = cur;
      (*ptr)->value.second = j;
      size++;
      for(unsigned long it=i+1; (it<=rows) && (R[it]==ptr); ++it) {
        R[it] = &((*ptr)->next);
      }
    }
    return (*ptr)->value.first;
  }else {
    throw std::out_of_range("Out of Matrix Range");
  }
}


template <typename Data>
const Data& MatrixCSR<Data>::operator()(const unsigned long i, const unsigned long j) const {
  if(i < rows && j < columns) {
    Node* const* ptr = R[i];
    while(ptr != R[i+1] && (*ptr)->value.second < j) {
      ptr = &((*ptr)->next);
    }
    if(ptr != R[i+1] && (*ptr)->value.second == j) {
      return (*ptr)->value.first;
    }else {
      throw std::length_error("Data not present in Matrix");
    }
  }else {
    throw std::out_of_range("Out of Matrix Range");
  }
}


/* ************************************************************************** */

// Specific member functions (inherited from Container)

template <typename Data>
void MatrixCSR<Data>::Clear() {
  List<std::pair<Data, unsigned long>>::Clear();
  R.Resize(1);
  rows = 0;
  columns = 0;
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void MatrixCSR<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  List<std::pair<Data, unsigned long>>::MapPreOrder([&fun](std::pair<Data, unsigned long>& dat, void* p) {fun(dat.first, p);}, par);
}


template <typename Data>
void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  List<std::pair<Data, unsigned long>>::MapPostOrder([&fun](std::pair<Data, unsigned long>& dat, void* p) {fun(dat.first, p);}, par);
}


/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  List<std::pair<Data, unsigned long>>::FoldPreOrder([&fun](const std::pair<Data, unsigned long>& dat, const void* p, void* a) {fun(dat.first, p, a);}, par, acc);
}


template <typename Data>
void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
    List<std::pair<Data, unsigned long>>::FoldPostOrder([&fun](const std::pair<Data, unsigned long>& dat, const void* p, void* a) {fun(dat.first, p, a);}, par, acc);
}

/* ************************************************************************** */

}
