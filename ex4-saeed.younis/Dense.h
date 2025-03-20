// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"


class Dense{
 private:
  Matrix weight;
  Matrix bias;
  func act_func;
 public:
  Dense(const Matrix& weights,const Matrix& bias,func foo);
  Matrix get_weights()const ;
  Matrix get_bias() const;
  func get_activation () const;
  Matrix operator()(const Matrix& m)const;
};










#endif //DENSE_H