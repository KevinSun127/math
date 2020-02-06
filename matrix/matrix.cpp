#include "matrix.h"
#include <math.h>
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
    //initalizes it to an identity matrix
    for(std::size_t j = 0; j < col_; ++j)
    {
      values[i][j] = 0;
    }
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

bool Matrix::enterValues()
{
  for(std::size_t i = 0; i < row_; ++i)
  {
    //enter each row's values
    std::cout << "Enter row " << i +1 << "'s Values." << std::endl;
    for(std::size_t j = 0; j < col_; ++j)
    {
      if(!(std::cin >> values[i][j]))
        return false;
    }
  }
  std::cout << std::endl;
  return true;
}

Matrix Matrix::inverse() const
{
  if(row_!= col_)
  {
    std::cout << "Square Matrices only" << std::endl;
    return *this;
  }

  Matrix inverseMatrix(row_, col_);

  for(std::size_t i = 0; i < row_; ++i)
    inverseMatrix.values[i][i] = 1;


  Matrix augMatrix(*this);

  double rowFactor;
  double addFactor;
  for(std::size_t diag = 0; diag < row_; ++diag)
  {
    for(std::size_t i = diag; i < row_ - 1; ++i)
    {
      if(augMatrix.values[i][diag] > augMatrix.values[i + 1][diag]
          && augMatrix.values[i+1][diag] != 0)
      {
        double* temp = augMatrix.values[i];
        augMatrix.values[i] = augMatrix.values[i+1];
        augMatrix.values[i+1] = temp;

        double* temp2 = inverseMatrix.values[i];
        inverseMatrix.values[i] = inverseMatrix.values[i+1];
        inverseMatrix.values[i+1] = temp2;
      }
    }

    if(!augMatrix.values[diag][diag])
    {
      std::cout << "Inverse does not exist!" << std::endl;
      return *this;
    }

    rowFactor = (1/augMatrix.values[diag][diag]);
    for(std::size_t j = 0; j < col_; ++j)
    {
      augMatrix.values[diag][j]*=rowFactor;
      inverseMatrix.values[diag][j]*=rowFactor;
    }
    for(std::size_t i = 0; i < row_; ++i)
    {
      if(i != diag)
      {
        addFactor = augMatrix.values[i][diag];
        for(std::size_t j = 0; j < col_; ++j)
        {
          augMatrix.values[i][j]-=addFactor*augMatrix.values[diag][j];
          inverseMatrix.values[i][j]-=addFactor*inverseMatrix.values[diag][j];
        }
      }
    }
  }

  return inverseMatrix;

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
      diffMatrix.values[i][j] = values[i][j] - m.values[i][j];

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
      //outputs values rounded to nearest thousandth
      out << std::setw(8) << std::left << round(values[i][j]*100000)/100000
       << " " << std::setw(8);
    }
    out << "|" << std::endl;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
  return m.print(out);
}
