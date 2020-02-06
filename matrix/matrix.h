#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
  public:
    Matrix();
    Matrix(std::size_t row, std::size_t col);
    Matrix(const Matrix& m);
    ~Matrix();

    //returns the number of rows
    std::size_t rowCount() const;
    //returns the number of columns
    std::size_t colCount() const;

    //prompts the user to enter matrix values -- row by row
    bool enterValues();

    //returns inverse of Matrix
    Matrix inverse() const;

    //Arithmetic + Assignment + Matrix Operators
    Matrix operator*(const Matrix& m) const;
    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix& operator=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);

    //outputting matrix
    std::ostream& print(std::ostream& out) const;
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);


  private:
    //stores the matrix in an array of doubles
    double** values;

    //stores number of rows and columns
    std::size_t row_, col_;
};

#endif
