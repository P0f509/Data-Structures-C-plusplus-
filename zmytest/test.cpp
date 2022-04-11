
#include "../matrix/vec/matrixvec.hpp"

#include "../matrix/csr/matrixcsr.hpp"

#include <random>

#include <iostream>

using namespace std;

/* ************************************************** */

//Print functions

template <typename Data>
void MapPrint(const Data& dat, void* _) {
  cout<<dat<<"  ";
}


template <typename Data>
void PrintPreOrder(lasd::Matrix<Data>& mat) {
  cout<<endl<<"Matrix Pre-Order:"<<endl;
  mat.MapPreOrder(&MapPrint<Data>, (void*) nullptr);
  cout<<endl;
}


template <typename Data>
void PrintPostOrder(lasd::Matrix<Data>& mat) {
  cout<<endl<<"Matrix Post-Order:"<<endl;
  mat.MapPostOrder(&MapPrint<Data>, (void*) nullptr);
  cout<<endl;
}

/* ************************************************** */

//Fold functions

void ProductIntegers(const int& dat, const void* par, void* acc) {
  if(dat != 0 && dat < *(int*) par) {
    *(int*) acc *= dat;
  }
}


void SumFloats(const float& dat, const void* par, void* acc) {
  if(dat > *(float*)par) {
    *(float*) acc += dat;
  }
}


void StringConcatFold(const string& str, const void* par, void* acc) {
  if(str.length() <= *((int*)par)){
    *(string*)acc += str;
  }
}


void Fold(const lasd::Matrix<int>& mat) {
  int p;
  int acc = 1;
  cout<<endl<<"Insert the pivot: ";
  cin>>p;
  mat.FoldPreOrder(&ProductIntegers, &p, &acc);
  cout<<"Product of numbers less than "<<p<<" is: "<<acc<<endl;
}


void Fold(const lasd::Matrix<float>& mat) {
  float p, acc = 0.0;
  cout<<endl<<"Insert the pivot: ";
  cin>>p;
  mat.FoldPreOrder(&SumFloats, &p, &acc);
  cout<<"Sum of numbers greater than "<<p<<" is: "<<acc<<endl;
}


void Fold(const lasd::Matrix<string>& mat) {
  int p;
  string acc = "";
  cout<<endl<<"Insert the pivot: ";
  cin>>p;
  mat.FoldPreOrder(&StringConcatFold, &p, &acc);
  cout<<"Concat of the strings with lenght less or equal than "<<p<<" is: "<<acc<<endl;
}

/* ************************************************** */

//Arithmetic functions

void IntDoubleDown(int& dat, void* _){
  dat = dat*2;
}


void FloatPow(float& dat, void* _){
  dat = -dat;
  dat = dat*dat*dat;
}


void StringConcat(string& str, void* par){
  str = *(string*)par + str;
}


void Arithmetic(lasd::Matrix<int>& mat) {
  mat.MapPreOrder(&IntDoubleDown, (void*) nullptr);
  cout<<endl<<"Integers have been doubled"<<endl;
}


void Arithmetic(lasd::Matrix<float>& mat) {
  mat.MapPreOrder(&FloatPow, (void*) nullptr);
  cout<<endl<<"Floats have been modified"<<endl;
}


void Arithmetic(lasd::Matrix<string>& mat) {
  string par;
  cout<<endl<<"Insert the string to concat: ";
  cin>>par;
  mat.MapPreOrder(&StringConcat, &par);
  cout<<endl<<"Strings have been modified"<<endl;
}

/* ************************************************** */

//Matrix functions

template <typename Data>
void checkExists(lasd::Matrix<Data>& mat) {
  Data val;
  cout<<endl<<"Insert the value to found in Matrix: ";
  cin>>val;
  if(mat.Exists(val)) {
    cout<<"Value found in Matrix"<<endl;
  }else {
    cout<<"Value not found in Matrix"<<endl;
  }
}


template <typename Data>
void checkExistsCell(lasd::Matrix<Data>& mat) {
  unsigned long i, j;
  cout<<endl<<"Insert the row index: ";
  cin>>i;
  cout<<"Insert the columns index: ";
  cin>>j;
  if(mat.ExistsCell(i, j)) {
    cout<<endl<<"Cell ("<<i<<","<<j<<") exists in Matrix"<<endl;
  }else {
    cout<<endl<<"Cell ("<<i<<","<<j<<") not exists in Matrix"<<endl;
  }
}


template <typename Data>
void ReadCell(const lasd::Matrix<Data>& mat) {
  unsigned long i, j;
  cout<<endl<<"Insert the row index: ";
  cin>>i;
  cout<<"Insert the columns index: ";
  cin>>j;
  try {
    const Data val = mat(i, j);
    cout<<endl<<"Value in the cell ("<<i<<","<<j<<") is "<<val<<endl;
  }catch(out_of_range e) {
    cout<<endl<<e.what()<<endl;
  }catch(length_error e) {
    cout<<endl<<e.what()<<endl;
  }
}

template <typename Data>
void WriteCell(lasd::Matrix<Data>& mat) {
  unsigned long i, j;
  Data val;
  cout<<endl<<"Insert the row index: ";
  cin>>i;
  cout<<"Insert the columns index: ";
  cin>>j;
  cout<<"Insert the value to Insert: ";
  cin>>val;
  try {
    mat(i, j) = val;
    cout<<endl<<"Value "<<val<<" inserted in the cell ("<<i<<","<<j<<")"<<endl;
  }catch(out_of_range e) {
    cout<<endl<<e.what()<<endl;
  }
}


template <typename Data>
void ResizeR(lasd::Matrix<Data>& mat) {
  unsigned long row;
  cout<<endl<<"Insert the new value of rows: ";
  cin>>row;
  mat.RowResize(row);
  cout<<endl<<"Matrix Resized"<<endl;
}


template <typename Data>
void ResizeC(lasd::Matrix<Data>& mat) {
  unsigned long cols;
  cout<<endl<<"Insert the new value of columns: ";
  cin>>cols;
  mat.ColumnResize(cols);
  cout<<endl<<"Matrix Resized"<<endl;
}


/* ************************************************** */

template <typename Data>
void MatrixMenu(lasd::Matrix<Data>& matrix) {
  int choice;
  do {
    cout<<endl<<"1)Print PreOrder"<<endl<<"2)Print PostOrder"<<endl<<"3)Check Exists of a value"<<endl<<"4)Exists Cell"<<endl<<"5)Read in a Cell";
    cout<<endl<<"6)Write in a Cell"<<endl<<"7)Resize Rows"<<endl<<"8)Resize Columns"<<endl<<"9)Fold functions"<<endl<<"10)Change Data with Arithmetic functions";
    cout<<endl<<"11)Print Size"<<endl<<"12)Empty Test"<<endl<<"13)Clear Matrix"<<endl<<"14)Get Rows Number"<<endl<<"15)Get Columns Number"<<endl<<"16)Exit"<<endl;
    cin>>choice;

    switch (choice)
    {

    case 1:
    PrintPreOrder(matrix);
    break;

    case 2:
    PrintPostOrder(matrix);
    break;

    case 3:
    checkExists(matrix);
    break;

    case 4:
    checkExistsCell(matrix);
    break;

    case 5:
    ReadCell(matrix);
    break;

    case 6:
    WriteCell(matrix);
    break;

    case 7:
    ResizeR(matrix);
    break;

    case 8:
    ResizeC(matrix);
    break;

    case 9:
    Fold(matrix);
    break;

    case 10:
    Arithmetic(matrix);
    break;

    case 11:
    cout<<endl<<"Size of Matrix is "<<matrix.Size()<<endl;
    break;

    case 12:
    if(matrix.Empty()) {
      cout<<endl<<"Matrix is Empty"<<endl;
    }else {
      cout<<endl<<"Matrix is not Empty"<<endl;
    }
    break;

    case 13:
    matrix.Clear();
    cout<<endl<<"Matrix Cleared"<<endl;
    break;

    case 14:
    cout<<endl<<"Rows Number is "<<matrix.RowNumber()<<endl;
    break;

    case 15:
    cout<<endl<<"Columns Number is "<<matrix.ColumnNumber()<<endl;
    break;

    case 16:
    matrix.Clear();
    cout<<endl<<"Goodbye!"<<endl<<endl;
    break;

    default:
    cout<<"Please, insert a valid choice"<<endl;
    break;
    }

  }while(choice != 16);
}

/* ************************************************** */

//Matrix Int Builders

void BuildMatrixVecInt(unsigned long rows, unsigned long cols) {
  lasd::MatrixVec<int> mat(rows, cols);
  if(rows != 0 && cols != 0) {
    unsigned long num;
    cout<<endl<<"Insert the max number of element to Insert in Matrix: ";
    cin>>num;
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> dist1(0, rows-1);
    uniform_int_distribution<int> dist2(0, cols-1);
    uniform_int_distribution<int> dist3(-500, 500);
    for(unsigned long i=0; i<num; ++i) {
      mat(dist1(gen), dist2(gen)) = dist3(gen);
    }
  }
  MatrixMenu(mat);
}


void BuildMatrixCSRint(unsigned long rows, unsigned long cols) {
  lasd::MatrixCSR<int> mat(rows, cols);
  if(rows != 0 && cols != 0) {
    unsigned long num;
    cout<<endl<<"Insert the max number of element to Insert in Matrix: ";
    cin>>num;
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> dist1(0, rows-1);
    uniform_int_distribution<int> dist2(0, cols-1);
    uniform_int_distribution<int> dist3(-500, 500);
    for(unsigned long i=0; i<num; ++i) {
      mat(dist1(gen), dist2(gen)) = dist3(gen);
    }
  }
  MatrixMenu(mat);
}

/* ************************************************** */

//Matrix Float Builders

void BuildMatrixVecFloat(unsigned long rows, unsigned long cols) {
  lasd::MatrixVec<float> mat(rows, cols);
  if(rows != 0 && cols != 0) {
    unsigned long num;
    cout<<endl<<"Insert the max number of element to Insert in Matrix: ";
    cin>>num;
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> dist1(0, rows-1);
    uniform_int_distribution<int> dist2(0, cols-1);
    uniform_real_distribution<float> dist3(-100, 100);
    for(unsigned long i=0; i<num; ++i) {
      mat(dist1(gen), dist2(gen)) = (float) (((int)dist3(gen) * 100 + .5)/100);
    }
  }
  MatrixMenu(mat);
}


void BuildMatrixCSRfloat(unsigned long rows, unsigned long cols) {
  lasd::MatrixCSR<float> mat(rows, cols);
  if(rows != 0 && cols != 0) {
    unsigned long num;
    cout<<endl<<"Insert the max number of element to Insert in Matrix: ";
    cin>>num;
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> dist1(0, rows-1);
    uniform_int_distribution<int> dist2(0, cols-1);
    uniform_real_distribution<float> dist3(-100, 100);
    for(unsigned long i=0; i<num; ++i) {
      mat(dist1(gen), dist2(gen)) = (float) (((int)dist3(gen) * 100 + .5)/100);
    }
  }
  MatrixMenu(mat);
}

/* ************************************************** */

//Matrix String Builders

void BuildMatrixVecString(unsigned long rows, unsigned long cols) {
  lasd::MatrixVec<string> mat(rows, cols);
  if(rows != 0 && cols != 0) {
    unsigned long num;
    cout<<endl<<"Insert the max number of element to Insert in Matrix: ";
    cin>>num;
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist('a', 'z');
    default_random_engine dre(random_device{}());
    uniform_int_distribution<int> distribution(1, 10);
    uniform_int_distribution<int> dist1(0, rows-1);
    uniform_int_distribution<int> dist2(0, cols-1);
    for(unsigned long i=0; i<num; ++i) {
      string randstr(distribution(dre),'\0');
      for(auto& c : randstr){
        c = dist(gen);
      }
      mat(dist1(dre), dist2(dre)) = randstr;
    }
  }
  MatrixMenu(mat);
}


void BuildMatrixCSRstring(unsigned long rows, unsigned long cols) {
  lasd::MatrixCSR<string> mat(rows, cols);
  if(rows != 0 && cols != 0) {
    unsigned long num;
    cout<<endl<<"Insert the max number of element to Insert in Matrix: ";
    cin>>num;
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist('a', 'z');
    default_random_engine dre(random_device{}());
    uniform_int_distribution<int> distribution(1, 10);
    uniform_int_distribution<int> dist1(0, rows-1);
    uniform_int_distribution<int> dist2(0, cols-1);
    for(unsigned long i=0; i<num; ++i) {
      string randstr(distribution(dre),'\0');
      for(auto& c : randstr){
        c = dist(gen);
      }
      mat(dist1(dre), dist2(dre)) = randstr;
    }
  }
  MatrixMenu(mat);
}

/* ************************************************** */

void startMatrixVecTest() {
  cout << endl << "~*~#~*~ Welcome to the MatrixVec Test Suite ~*~#~*~ " << endl;
  int choice;
  unsigned long rows, cols;
  cout<<endl<<"Insert the number of rows: ";
  cin>>rows;
  cout<<"Insert the number of columns: ";
  cin>>cols;
  do{
    cout<<endl<<"Choose the Data type:"<<endl<<"1)integer"<<endl<<"2)float"<<endl<<"3)string"<<endl<<"4)Exit"<<endl;
    cin>>choice;
    switch (choice)
    {
      case 1:
      BuildMatrixVecInt(rows, cols);
      break;

      case 2:
      BuildMatrixVecFloat(rows, cols);
      break;

      case 3:
      BuildMatrixVecString(rows, cols);
      break;

      case 4:
      break;

      default:
      cout<<endl<<"Insert a valid choice!"<<endl;
      break;
    }
  }while(choice < 1 || choice > 4);
}

/* ************************************************** */

void startMatrixCsrTest() {
  cout << endl << "~*~#~*~ Welcome to the MatrixCSR Test Suite ~*~#~*~ " << endl;
  int choice;
  unsigned long rows, cols;
  cout<<endl<<"Insert the number of rows: ";
  cin>>rows;
  cout<<"Insert the number of columns: ";
  cin>>cols;
  do{
    cout<<endl<<"Choose the Data type:"<<endl<<"1)integer"<<endl<<"2)float"<<endl<<"3)string"<<endl<<"4)Exit"<<endl;
    cin>>choice;
    switch (choice)
    {
      case 1:
      BuildMatrixCSRint(rows, cols);
      break;

      case 2:
      BuildMatrixCSRfloat(rows, cols);
      break;

      case 3:
      BuildMatrixCSRstring(rows, cols);
      break;

      case 4:
      break;

      default:
      cout<<endl<<"Insert a valid choice!"<<endl;
      break;
    }
  }while(choice < 1 || choice > 4);
}

/* ************************************************** */
