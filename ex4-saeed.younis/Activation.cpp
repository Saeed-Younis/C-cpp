//
// Created by youni on 20/07/2024.
//
#include "Activation.h"
#include "cmath"


Matrix activation::relu (const Matrix& a)
{
  Matrix m(a);
 for (int i=0;i<m.get_rows();i++){
   for ( int j=0;j<m.get_cols();j++)
     {
       if(m(i,j)<0)
         {
            m.set_matrix(i,j,0);
         }
     }
 }
 return m;
}
Matrix activation::softmax (const Matrix &c)
{ Matrix b(c);
  float x;
  float sum=0;
  for ( int i=0;i<b.get_rows();i++){
      for ( int j=0;j<b.get_cols();j++)
        {
          x=std::exp(b(i,j));
          sum+=x;
          b.set_matrix (i,j,x);
        }
    }
    if (sum!=0)
      {
        for ( int i = 0; i < b.get_rows (); ++i)
          {
            for ( int j = 0; j < b.get_cols (); ++j)
              {
                b.set_matrix (i, j, b (i, j) / sum);
              }
          }
      }
  return b;
}