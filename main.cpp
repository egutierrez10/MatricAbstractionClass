#include "mymatrix.h"
#include <iostream>
using namespace std;

int main(){
    
    mymatrix<int> M; //Default constructor
    M(0, 0) = 123; //Use ()operator function
    M(1, 1) = 456;
    M(2, 2) = 789;
    M(3, 3) = -99;
    M.growcols(1, 8); //Grow matrix by 8 columns in row 1
    
     for (int r = 0; r < M.numrows(); ++r) // Loop through the # of rows in the matrix
     {
      for (int c = 0; c < M.numcols(r); ++c) // Loop through the # of columns in the matrix
          cout << M(r, c) << " "; //Print each value at position (r,c)
          cout << endl;
     }
    
    mymatrix<int> M2(2,2); //Parameterized constructor
    
    M2.at(0,0) = 5; //Use of at() function to update the value at row 1 and column 0
    for(int i = 0; i < M2.numrows(); ++i){
        for(int j = 0; j < M2.numcols(i); ++j){
            M2(i,j) = 2;
        }
    }
    
    //Call copy constructor
    mymatrix<int> M1 = M2;
    M1.at(0,0) = 11;
    M1(0,1) = 10;
    
    cout << "Printing M1 matrix: " << endl;
    M1._output();
    cout << endl;
    cout << "Printing M2 matrix: " << endl;
    M2._output();
    cout << endl;
    
    mymatrix<int> M3(M1); //Other way to call copy constructor
    M3.at(0,0) = 21;
    M3(0,1) = 20;
    cout << "Printing M1 matrix: " << endl;
    M1._output();
    cout << endl;
    cout << "Printing M2 matrix: " << endl;
    M2._output();
    cout << endl;
    cout << "Printing M3 matrix: " << endl;
    M3._output();
    cout << endl;
    
    //Scalar multiplication
    mymatrix<int> M4;
    M4 = M3 * 2;
    cout << "Scalar Multiplication: " << endl;
    M4._output();
    cout << endl;
    
    //Matrix multiplication
    mymatrix<int> M5;
    M5 = M1 * M2;
    cout << "Matrix Multiplication: " << endl;
    M5._output();
    cout << endl;
    
    //Size 
    cout << "How many elements in Matrix 4? " << M4.size() << endl;
    
    //Grow
    cout << "Now to grow our matrix to a 5x5: " << endl;
    M5.grow(5,5);
    M5._output();
    cout << endl;
    
    //How about other types of matrices?
    mymatrix<double> M6(2,2);
    for(int i = 0; i < M6.numrows(); ++i){
        for(int j = 0; j < M6.numcols(i); ++j){
            M6(i,j) = 2.75;
        }
    }
    mymatrix<char> M7(2,2);
    for(int i = 0; i < M6.numrows(); ++i){
        for(int j = 0; j < M6.numcols(i); ++j){
            M7(i,j) = 'a';
        }
    }
    mymatrix<string> M8(2,2);
    for(int i = 0; i < M8.numrows(); ++i){
        for(int j = 0; j < M8.numcols(i); ++j){
            M8(i,j) = "Hi";
        }
    }
    cout << "Printing M6-double matrix: " << endl;
    M6._output();
    cout << endl;
    cout << "Printing M7-char matrix: " << endl;
    M7._output();
    cout << endl;
    cout << "Printing M8-string matrix: " << endl;
    M8._output();
    cout << endl;
    return 0;
}