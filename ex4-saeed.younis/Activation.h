// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

typedef Matrix (*func)(const Matrix& m);
// Insert Activation namespace here...
namespace activation{
    Matrix relu(const Matrix& a);
    Matrix softmax(const Matrix &c);
}










#endif //ACTIVATION_H