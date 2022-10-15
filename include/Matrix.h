#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "matExp.h"

using namespace std;
class Matrix
{
public:
    Matrix();
    Matrix(int rows,int columns);

    void init(int value);
    void reSize(int rows,int columns);

    Matrix  operator+(const Matrix& other);
    Matrix  operator-(const Matrix& other);
    Matrix  operator*(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

    int determinant();
    int cofactor(int row,int column);

    friend ostream& operator<<(ostream& os, const Matrix& mat);
    friend istream& operator>>(istream& is, Matrix& mat);

    ~Matrix();

private:
     int **pm,
           rows,
           columns;

};

#endif // MATRIX_H
