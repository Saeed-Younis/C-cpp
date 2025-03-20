// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "iostream"

#define MINIMUM_CELL 0.1
// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};

class Matrix
{

 private:
  float **matrix;
   int rows;
   int cols;
  void allocate_mat();
  void free_mat();
 public:
  void set_matrix ( int row, int col,float x);
  float get_matrix ( int row , int col) const;
  Matrix( int rows, int cols);
   int get_rows()const ;
  int get_cols()const ;
  Matrix();
  Matrix(const Matrix &m);
  ~Matrix();
  Matrix& transpose();
  Matrix& vectorize();
  void plain_print();
  Matrix dot(const Matrix& other)const ;
  double norm()const ;
  Matrix rref() const ;
  unsigned int argmax() const;
  double sum() const;
  Matrix& operator+=(const Matrix& other);
  friend Matrix operator+(const Matrix& a, const Matrix& b);
  Matrix& operator=(const Matrix& other);
  friend Matrix operator*(const Matrix& a,const Matrix& b);
  friend Matrix operator*(const Matrix& m,float scalar);
  friend Matrix operator*(float scalar, const Matrix& m);
  float& operator()( int r, int c) ;
  const float& operator()( int r, int c) const;
  float& operator[]( int m );
  const float& operator[]( int m ) const;
  friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
  friend std::istream& operator>>(std::istream& is, Matrix& m);


};




#endif //MATRIX_H