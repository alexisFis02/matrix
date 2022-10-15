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

        void inicializar(int valor);
        void redimencionar(int rows,int columns);

        Matrix  operator+(const Matrix& other);
        Matrix  operator-(const Matrix& other);
        Matrix  operator*(const Matrix& other);

        Matrix& operator=(const Matrix& other);
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const Matrix& other);

        int determinante();
        int cofactor(int fila, int columna);

        friend ostream& operator<<(ostream& sal, const Matrix& mat);
        friend istream& operator>>(istream& is, Matrix& mat);

        ~Matrix();

    private:
        int **pm,
              rows,
              columns;

};

#endif // MATRIX_H
