// Created by youni on 20/07/2024.

#include "Matrix.h"
#include "iostream"
#include <stdexcept>
#include <complex>


Matrix::Matrix (int rows, int cols) : rows (rows), cols (cols)
{
  if (rows <= 0 || cols <= 0)
    {
      throw std::invalid_argument ("Invalid argument");
    }
  allocate_mat ();
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          this->matrix[i][j] = 0;
        }
    }
}

int Matrix::get_rows () const
{
  return rows;
}

int Matrix::get_cols () const
{
  return cols;
}

void Matrix::allocate_mat ()
{
  matrix = new float *[rows];
  for (int i = 0; i < rows; i++)
    {
      matrix[i] = new float[cols];
    }
}

void Matrix::free_mat ()
{
  for (int i = 0; i < rows; i++)
    {
      delete[] matrix[i];
    }
  delete[] matrix;
}

Matrix::Matrix () : rows (1), cols (1)
{
  allocate_mat ();
  matrix[0][0] = 0;
}

Matrix::Matrix (const Matrix &m) : rows (m.rows), cols (m.cols)
{
  allocate_mat ();
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          matrix[i][j] = m.matrix[i][j];
        }
    }
}

Matrix::~Matrix ()
{
  free_mat ();
}

Matrix &Matrix::transpose ()
{
  Matrix transpose (cols, rows);
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          transpose.matrix[j][i] = matrix[i][j];
        }
    }
  std::swap (*this, transpose);
  return *this;
}

Matrix &Matrix::vectorize ()
{
  Matrix new_vec (rows * cols, 1);
  int counter = 0;
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          new_vec.matrix[counter++][0] = matrix[i][j];
        }
    }
  std::swap (*this, new_vec);
  return *this;
}

void Matrix::plain_print ()
{
  for (int i = 0; i < rows; i++)
    {
      if (i != 0)
        {
          std::cout << std::endl;
        }
      for (int j = 0; j < cols; j++)
        {
          if (j == cols - 1)
            {
              std::cout << matrix[i][j];
            }
          else
            {
              std::cout << matrix[i][j] << " ";
            }
        }
    }
}

Matrix Matrix::dot (const Matrix &other) const
{
  if (rows != other.rows || cols != other.cols)
    {
      throw std::invalid_argument ("Matrices dimensions must match");
    }
  Matrix mul_mat (rows, cols);
  for (int j = 0; j < rows; j++)
    {
      for (int m = 0; m < cols; m++)
        {
          mul_mat.matrix[j][m] = this->matrix[j][m] * other.matrix[j][m];
        }
    }
  return mul_mat;
}

double Matrix::norm () const
{
  double sum = 0;
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          sum += this->matrix[i][j] * this->matrix[i][j];
        }
    }
  return std::sqrt (sum);
}
Matrix Matrix::rref() const
{
  Matrix result(*this);
  int lead = 0;
  int row_count = result.get_rows();
  int column_count = result.get_cols();
  for (int r = 0; r < row_count; ++r)
    {
      if (lead >= column_count)
        {
          break;
        }
      int i = r;
      while (result.matrix[i][lead] == 0)
        {++i;
          if (i == row_count)
            {
              i = r;
              ++lead;
              if (lead == column_count)
                {
                  return result;
                }
            }
        }
      if (i != r)
        {
          std::swap(result.matrix[i], result.matrix[r]);
        }float pivot_value = result.matrix[r][lead];
      for (int j = 0; j < column_count; ++j)
        {
          result.matrix[r][j] /= pivot_value;
        }
      for (int i = 0; i < row_count; ++i)
        {
          if (i != r)
            {
              float factor = result.matrix[i][lead];
              for (int j = 0; j < column_count; ++j)
                {
                  result.matrix[i][j] -= factor * result.matrix[r][j];
                }
            }
        }++lead;
    }return result;
}

unsigned int Matrix::argmax () const
{
   unsigned int counter=0;

  float max_value = matrix[0][0];
  for (int i = 0; i < rows ; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          unsigned index=static_cast<unsigned int>(i*cols+j);
          if (matrix[i][j] > max_value)
            {
              max_value=matrix[i][j];
              counter=index;
            }
        }
    }
  return counter;
}

double Matrix::sum () const
{
  double result = 0;
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          result += matrix[i][j];
        }
    }
  return result;
}

Matrix &Matrix::operator+= (const Matrix &other)
{
  if (rows != other.rows || cols != other.cols)
    {
      throw std::invalid_argument ("Invalid rows or cols");
    }
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          this->matrix[i][j] += other.matrix[i][j];
        }
    }
  return *this;
}

Matrix operator+ (const Matrix &a, const Matrix &b)
{
  if (a.rows != b.rows || a.cols != b.cols)
    {
      throw std::invalid_argument ("Invalid rows or cols");
    }
  Matrix result (a.rows, a.cols);
  for (int i = 0; i < a.rows; i++)
    {
      for (int j = 0; j < a.cols; j++)
        {
          result.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        }
    }
  return result;
}

Matrix &Matrix::operator= (const Matrix &other)
{
  if (this == &other)
    {
      return *this;
    }
  free_mat ();
  rows = other.rows;
  cols = other.cols;
  allocate_mat ();
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          matrix[i][j] = other.matrix[i][j];
        }
    }
  return *this;
}

Matrix operator* (const Matrix &a, const Matrix &b)
{
  if (a.cols != b.rows)
    {
      throw std::invalid_argument ("Invalid rows or cols");
    }
  Matrix result (a.rows, b.cols);

  for (int i = 0; i < a.rows; ++i)
    {
      for (int j = 0; j < b.cols; ++j)
        {
          result.matrix[i][j] = 0;
          for (int k = 0; k < a.cols; ++k)
            {
              result.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
    }
  return result;
}

Matrix operator* (const Matrix &m, float scalar)
{
  Matrix result (m.rows, m.cols);
  for (int i = 0; i < m.rows; i++)
    {
      for (int j = 0; j < m.cols; j++)
        {
          result.matrix[i][j] = m.matrix[i][j] * scalar;
        }
    }
  return result;
}

Matrix operator* (float scalar, const Matrix &m)
{
  Matrix result (m.rows, m.cols);
  for (int i = 0; i < m.rows; i++)
    {
      for (int j = 0; j < m.cols; j++)
        {
          result.matrix[i][j] = scalar * m.matrix[i][j];
        }
    }
  return result;
}

float &Matrix::operator() (int r, int c)
{
  if (!(r >= 0 && r < rows && c >= 0 && c < cols))
    {
      throw std::out_of_range ("Index is out of range");
    }
  return matrix[r][c];
}

const float &Matrix::operator() (int r, int c) const
{
  if (!(r >= 0 && r < rows && c >= 0 && c < cols))
    {
      throw std::out_of_range ("Index is out of range");
    }
  return matrix[r][c];
}

float &Matrix::operator[] (int m)
{
  if (m < 0 || m >= rows * cols)
    {
      throw std::out_of_range ("Index is out of range");
    }
  int row = m / cols;
  int col = m % cols;
  return matrix[row][col];
}

const float &Matrix::operator[] (int m) const
{
  if (m < 0 || m >= rows * cols)
    {
      throw std::out_of_range ("Index is out of range");
    }
  int row = m / cols;
  int col = m % cols;
  return matrix[row][col];
}

std::ostream &operator<< (std::ostream &output, const Matrix &m)
{
  for (int i = 0; i < m.rows; ++i)
    {
      for (int j = 0; j < m.cols; ++j)
        {
          if (m (i, j) > MINIMUM_CELL)
            {
              output << "**";
            }
          else
            {
              output << "  ";
            }
        }
      output << std::endl;
    }
  return output;
}

std::istream &operator>>(std::istream &input, Matrix &m)
{
  std::streamsize total_elements = m.get_rows () * m.get_cols ();

  for (std::streamsize i = 0; i < total_elements; ++i)
    {
      float value;
      if (input.read (reinterpret_cast<char *>(&value), sizeof (float)))
        {
          m.matrix[i / m.get_cols ()][i % m.get_cols ()] = value;
        }
      else
        {
          throw std::runtime_error ("Failed to read enough data into the matrix.");
        }

    }

  return input;
}

float Matrix::get_matrix (int row, int col) const
{
  if (!(row>=0 &&row < rows&& col>=0 && col < cols))
    {
    throw std::out_of_range ("Index is out of range");
    }
  return this->matrix[row][col];
}

void Matrix::set_matrix (int row, int col, float x)
{
  if (!(row>=0 &&row < rows&& col>=0 && col < cols))
    {
      throw std::out_of_range ("Index is out of range");
    }
  this->matrix[row][col] = x;
}
