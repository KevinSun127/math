#include "matrix.h"
#include <cstddef>
#include <iomanip>

Matrix::Matrix():
row_(0), col_(0), values(NULL)
{
}

//dynamically allocates memory for the new matrix
Matrix::Matrix(std::size_t row, std::size_t col):
row_(row), col_(col)
{
  values = new double*[row_];
  for(int i = 0; i < row_; ++i)
  {
    values[i] = new double[col_];
    for(std::size_t j = 0; j < col_; ++j)
      //iniitalizes all values to 0
      values[i][j] = 0;
  }

}

Matrix::Matrix(const Matrix& m):
row_(m.rowCount()), col_(m.colCount())
{
  values = new double*[row_];
  for(std::size_t i = 0; i < row_; ++i)
  {
    values[i] = new double[col_];

    //populates the array
    for(std::size_t j = 0; j < col_; ++j)
      values[i][j] = m.values[i][j];
  }

}

Matrix::~Matrix()
{
  for(std::size_t i = 0; i < row_; ++i)
    delete[] values[i];
  delete[] values;
}

std::size_t Matrix::rowCount() const
{
  return row_;
}

std::size_t Matrix::colCount() const
{
  return col_;
}

void Matrix::enterValues()
{
  for(std::size_t i = 0; i < row_; ++i)
  {
    //enter each row's values
    std::cout << "Enter row " << i +1 << "'s Values." << std::endl;
    for(std::size_t j = 0; j < col_; ++j)
      std::cin >> values[i][j];
  }
  std::cout << std::endl;
}



//product of two matrices
Matrix Matrix::operator*(const Matrix& m) const
{
  Matrix prodMatrix(row_, m.colCount());

  for(std::size_t i = 0; i < row_; ++i)
    for(std::size_t j = 0; j < m.colCount(); ++j)
      for(std::size_t k = 0; k < col_; ++k)
        prodMatrix.values[i][j]+=(values[i][k]*m.values[k][j]);

    return prodMatrix;
}


Matrix Matrix::operator+(const Matrix& m) const
{
  Matrix sumMatrix(m.rowCount(), m.colCount());

  for(std::size_t i = 0; i < row_; ++i)
    for(std::size_t j = 0; j < col_; ++j)
      sumMatrix.values[i][j] = values[i][j]+m.values[i][j];

    return sumMatrix;
}

Matrix Matrix::operator-(const Matrix& m) const
{
  Matrix diffMatrix(m.rowCount(), m.colCount());

  for(std::size_t i = 0; i < row_; ++i)
    for(std::size_t j = 0; j < col_; ++j)
      diffMatrix.values[i][j] = values[i][j]-m.values[i][j];

    return diffMatrix;
}


Matrix& Matrix::operator=(const Matrix& m)
{
  //if the matrices are identical, can jump
  //right to element by element assignment
  if(!(row_ == m.rowCount() && col_ == m.colCount()))
  {
    //delete current matrix values
    if(values != NULL)
    {
      for(std::size_t i = 0; i < row_; ++i)
        delete[] values[i];
      delete[] values;
    }

    //set dimensions
    row_ = m.rowCount();
    col_ = m.colCount();

    //allocate memory
    values = new double*[row_];
    for(std::size_t i = 0; i < row_; ++i)
      values[i] = new double[col_];

  }

  //assign each element into the new Matrix
  for(std::size_t i = 0; i < row_; ++i)
    for(std::size_t j = 0; j < col_; ++j)
      values[i][j] = m.values[i][j];

  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
  (*this)=(*this)*m;
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
  for(std::size_t i = 0; i < row_; ++i)
    for(std::size_t j = 0; j < col_; ++j)
      values[i][j]+=m.values[i][j];
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
  for(std::size_t i = 0; i < row_; ++i)
    for(std::size_t j = 0; j < col_; ++j)
      values[i][j]-=m.values[i][j];
  return *this;
}


std::ostream& Matrix::print(std::ostream& out) const
{
  for(size_t i = 0; i < row_; ++i)
  {
    out << "| ";
    for(size_t j = 0; j < col_; ++j)
    {
      out << std::left << std::setw(6)
      << values[i][j] << " " << std::setw(6) ;
    }
    out << "|" << std::endl;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
  return m.print(out);
}
