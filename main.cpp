
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  int choice;
  do{
     std::cout << "Lasd Libraries 2020" << std::endl <<"-------------------";
     std::cout<<std::endl<<"Select an Option:"<<std::endl<<"1)MatrixVec Test Suite"<<std::endl<<"2)MatrixCSR Test Suite"<<std::endl<<"3)Lasd Test"<<std::endl<<"4)Exit"<<std::endl;
     std::cin>>choice;
     switch (choice)
     {
     case 1:
      startMatrixVecTest();
      break;

     case 2:
      startMatrixCsrTest();
      break;

     case 3:
      lasdtest();
      break;

    case 4:
      break;

     default:
       std::cout<<"Please, insert a valid choice!"<<std::endl;
       break;
     }

  }while(choice != 4);

  return 0;
}
