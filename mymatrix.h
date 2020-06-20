/*mymatrix.h*/

// 
// << Everardo Gutierrez >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #02
//

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

  //
  // Check Rentangle:
  //
  // Called by Matrix Multiplication to check that matrices
  // being multiplied are rectangular and not unevened in columns. 
  // At first instance of unevened column number, false is returned
  // else true is returned 
  bool checkRec(const mymatrix<T>& M){
    int NRows = M.Rows[0].NumCols; // set # of cols in first row as template
    for(int r = 1; r < M.NumRows; ++r){
        for(int c = 0; c < M.Rows[r].NumCols; ++c){
            if(M.Rows[r].NumCols != NRows) // check in occurdance to the # of cols in first row
                return false; 
        }
    }
    return true; 
  }

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

    //
    // TODO --
    //
    Rows = new ROW[R]; // an array with R ROW structs:
    NumRows = R;
    
    // initialize each row to have C columns:
    for(int i = 0; i < NumRows; ++i){
        Rows[i].Cols = new T[C];
        Rows[i].NumCols = C;
        // initialize the elements to their default value:
        for(int j = 0; j < Rows[i].NumCols; ++j){
            Rows[i].Cols[j] = T{}; //set default value for Type T            
        }
    }
  }

  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {
    //
    // TODO--
    //
    NumRows = other.NumRows; 
    Rows = new ROW[NumRows]; // an array with equal ROW structs to matrix assigned:
    
    // initialize each row to have columns equal to that of each row in matrix other:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[other.Rows[r].NumCols];  
      Rows[r].NumCols = other.Rows[r].NumCols;
      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = other.Rows[r].Cols[c];  // default value for type T:
      }
    }
  }

  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    //
    // TODO --
    //
    return NumRows;
  }
  
  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

    //
    // TODO --
    //    
    return Rows[r].NumCols;
  }

  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

    //
    // TODO --
    // Only grow the row to C columns if and only if the current # of columns is smaller than C
    if(Rows[r].NumCols < C){ 
        T* tempCols = new T[C]; // Create a new row with C number of columns
        for(int j = 0; j < C; ++j){           
            tempCols[j] = T{}; 
        }
        //Loop through and copy over the information from the old array
        for(int j = 0; j < Rows[r].NumCols; ++j){
           
            tempCols[j] = Rows[r].Cols[j]; 
        }
        delete[] Rows[r].Cols; // Delete Old Rows[r] array
        Rows[r].NumCols = C;   // Update NumCols to C      
        Rows[r].Cols = tempCols; // Set pointer to point to bigger row containing C columns
    }        
  }

  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");

    //
    // TODO: --
    //

    int i, current = C;
    if(NumRows == R){ // Attempting to grow matrix column wise but keeping row size the same
    for(i = 0; i < NumRows; ++i){
          growcols(i, C); // Call function growCols to grow Row i columns to size C             
      }
      return;
    }
    // Only grow the array to R rows if and only if the current # of rows is smaller than R
    if(NumRows < R){ // Grow matrix to have more rows 
      ROW* temp = new ROW[R]; // Create a new array of size R rows
      // initialize each row to have C columns:
      for(i = 0; i < R; ++i){
          
          if(i < NumRows){ // Up to NumRows-1 of the old array we must check to see if the columns must be grown to size C
              growcols(i, C); // Call function growCols to grow Row i columns to size C
              current = Rows[i].NumCols;              
          }else{
              current = C;              
          }
           temp[i].Cols = new T[current];
           temp[i].NumCols = current;
           // initialize the elements to their default value:
          for(int j = 0; j < current; ++j){
              temp[i].Cols[j] = T{}; // default value for type T:
          }
      }
      //Loop through and copy over the information from the old array
      for(i = 0; i < NumRows; i++){
          for(int j = 0; j < Rows[i].NumCols; ++j){
              temp[i].Cols[j] = Rows[i].Cols[j];
          }
      }
      delete[] Rows; // Delete Old Rows[r] array
      NumRows = R;   // Update NumRows to R
      Rows = temp;   // Set pointer to point to bigger row containing R rows  
    } 
  }

  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
    //
    // TODO --
    //
    int TotalElements = 0;
    //Loop through the entire matrix and count each element
    for(int i = 0; i < NumRows; i++){
          for(int j = 0; j < Rows[i].NumCols; ++j){
              TotalElements++;
          }
      }
    return TotalElements;
  }

  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");
    //
    // TODO --
    //
    return Rows[r].Cols[c];
  }

  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");
    //
    // TODO -- 
    //
    return this->at(r,c);
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result;
    //
    // TODO --
    //
    result.Rows = new ROW[NumRows];  // a result array to be returned with NumRows ROW structs:
    result.NumRows = NumRows;
    // initialize each row to have C columns:
    for (int r = 0; r < NumRows; ++r)
    {
      result.Rows[r].Cols = new T[Rows[r].NumCols];  // an array with resultCols elements of type T:
      result.Rows[r].NumCols = Rows[r].NumCols;

      // initialize the elements to their default value:
      for (int c = 0; c < result.Rows[r].NumCols; ++c)
      {  
      // get element from matrix at row r and col c and multiply by scalar, and save to result matrix
        result.Rows[r].Cols[c] = Rows[r].Cols[c] * scalar;  
      }
    }
    return result;
  }

  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    mymatrix<T> result;
    int resultRows = NumRows; // result matrix will have equal # of rows to first matrix (this)
    int resultCols = other.Rows[0].NumCols; // result matrix will have equal # of columns to second matrix (other)
    //
    // both matrices must be rectangular for this to work:
    //

    //
    // TODO
    // Call to checkRec function to check if the two matrixes are rectangular
    // if (this matrix is not rectangular)
    //   throw runtime_error("mymatrix::*: this not rectangular");
    //
    // if (other matrix is not rectangular)
    //   throw runtime_error("mymatrix::*: other not rectangular");
    if(!checkRec(*this))
        throw runtime_error("mymatrix::*: this not rectangular");
    if(!checkRec(other))
        throw runtime_error("mymatrix::*: other not rectangular");
    //
    // Okay, both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
    //

    //
    // TODO
    //
    // if (this matrix's # of columns != other matrix's # of rows)
    //   throw runtime_error("mymatrix::*: size mismatch");
    if(Rows[0].NumCols != other.NumRows)
        throw runtime_error("mymatrix::*: size mismatch");
    //
    // Okay, we can multiply:
    //

    //
    // TODO
    //
    result.Rows = new ROW[resultRows];  // an array with ROW structs equal to the frist matrix(this):
    result.NumRows = resultRows;
    // initialize each row to have C columns equal to the columns of each row in the second matrix(other):
    for (int r = 0; r < resultRows; ++r)
    {
      result.Rows[r].Cols = new T[resultCols];  // an array with resultCols elements of type T:
      result.Rows[r].NumCols = resultCols;

      // initialize the elements to their default value:
      for (int c = 0; c < resultCols; ++c)
      {
        result.Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
    
    //TODO:
    // Loop through both matrices and multiply each row of first matrix by column of second and save into corresponding index
    // in result matrix
    for(int i = 0; i < resultRows; i++){
        for(int j = 0; j < resultCols; ++j){
            for(int k = 0; k < Rows[0].NumCols; ++k){
                result.Rows[i].Cols[j] += Rows[i].Cols[k] * other.Rows[k].Cols[j];
            }
        }
    }
    return result;
  }
  
  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};
