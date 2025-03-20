//
// Created by youni on 20/07/2024.
//
#include "Dense.h"

Dense::Dense(const Matrix& weights,const Matrix& bias,func foo)
:weight(weights),bias(bias),act_func(foo){}

Matrix Dense::get_weights () const
{
  return weight;
}
Matrix Dense::get_bias () const
{
  return bias;
}
func Dense::get_activation () const
{
  return act_func;
}
Matrix Dense::operator() (const Matrix &m)const
{
  Matrix result=(weight*m)+bias;
  return act_func(result);
}
