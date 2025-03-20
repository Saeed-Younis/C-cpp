//
// Created by youni on 20/07/2024.
//
#include "MlpNetwork.h"

MlpNetwork::MlpNetwork (const Matrix weights[], const Matrix biases[]) :layers
    {Dense(weights[0],biases[0],activation::relu),
     Dense(weights[1], biases[1],activation::relu),
     Dense(weights[2],biases[2],activation::relu),
     Dense(weights[3],biases[3],activation::softmax)}
{}
digit MlpNetwork::operator() (const Matrix &m)const  {
  Matrix in=m;
  for (int i=0;i<MLP_SIZE;i++)
    {
      in=layers[i](in);
    }
  digit result={in.argmax(),in[in.argmax()]};
  return result;
}
