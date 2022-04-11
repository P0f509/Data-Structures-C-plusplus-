
namespace lasd {

/* ************************************************************************** */

//Specific constructor
template <typename Data>
MatrixVec<Data>::MatrixVec(const unsigned long r, const unsigned long c) {
  vector.Resize(r*c);
  rows = r;
  columns = c;
}

/* ************************************************************************** */

//Copy constructor
template <typename Data>
MatrixVec<Data>::MatrixVec(const MatrixVec<Data>& matr) {
  vector = matr.vector;
  rows = matr.rows;
  columns = matr.columns;
}

//Move constructor
template <typename Data>
MatrixVec<Data>::MatrixVec(MatrixVec<Data>&& matr) noexcept {
  std::swap(vector, matr.vector);
  std::swap(rows, matr.rows);
  std::swap(columns, matr.columns);
}

/* ************************************************************************** */

//Copy assignment
template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data>& matr) {
  vector = matr.vector;
  rows = matr.rows;
  columns = matr.columns;
  return *this;
}

//Move assignment
template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& matr) noexcept {
  std::swap(rows, matr.rows);
  std::swap(columns, matr.columns);
  std::swap(vector, matr.vector);
  return *this;
}

/* ************************************************************************** */

//Comparison operators

template <typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data>& matr) const noexcept {
  if(rows == matr.rows && columns == matr.columns) {
    return (vector == matr.vector);
  }
  return false;
}


template <typename Data>
bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& matr) const noexcept {
  return !(*this == matr);
}

/* ************************************************************************** */

// Specific member functions (inherited from Matrix)

template <typename Data>
void MatrixVec<Data>::RowResize(const unsigned long newsize) {
  vector.Resize(newsize*columns);
  rows = newsize;
}


template <typename Data>
void MatrixVec<Data>::ColumnResize(const unsigned long newsize) {
  if(newsize == 0) {
    vector.Clear();
  }else if(newsize != columns) {
    Vector<Data> tmp(rows*newsize);
    unsigned long pos1 = 0, pos2 = 0;
    unsigned long acc = (newsize < columns)? (columns-newsize) : 0;
    for(unsigned long i=0; i<rows; ++i) {
      for(unsigned long j=0; j<newsize; ++j){
        if(j < columns) {
          std::swap(vector[pos1], tmp[pos2]);
          pos1++;
        }
        pos2++;
      }
      pos1 = pos1 + acc;
    }
    std::swap(vector, tmp);
  }
  columns = newsize;
}


template <typename Data>
bool MatrixVec<Data>::ExistsCell(const unsigned long i, const unsigned long j) const noexcept {
  return (i < rows && j < columns);
}


template <typename Data>
Data& MatrixVec<Data>::operator()(const unsigned long i, const unsigned long j) {
  return const_cast<Data&>(static_cast<const MatrixVec<Data>*>(this)->operator()(i, j));
}


template <typename Data>
const Data& MatrixVec<Data>::operator()(const unsigned long i, const unsigned long j) const {
  if(i < rows && j < columns) {
    return vector[(i*columns)+j];
  }else {
    throw std::out_of_range("Out of Matrix Range");
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template <typename Data>
bool MatrixVec<Data>::Empty() const noexcept {
  return ((rows * columns) == 0);
}


template <typename Data>
unsigned long MatrixVec<Data>::Size() const noexcept {
  return (rows * columns);
}


template <typename Data>
void MatrixVec<Data>::Clear() {
  vector.Clear();
  rows = 0;
  columns = 0;
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void MatrixVec<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  vector.MapPreOrder(fun, par);
}


template <typename Data>
void MatrixVec<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  vector.MapPostOrder(fun, par);
}

/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void MatrixVec<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  vector.FoldPreOrder(fun, par, acc);
}


template <typename Data>
void MatrixVec<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  vector.FoldPostOrder(fun, par, acc);
}

/* ************************************************************************** */

}
