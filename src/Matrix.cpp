#include "Matrix.h"

#define SIZEBUFFER 80
#include <math.h>
Matrix::Matrix()
{
    pm       = new int*;
    pm[0]    = new int;
    pm[0][0] = 0;
    rows = columns = 1;
}

Matrix::Matrix(int rows,int columns)
{
    if(rows<=0 || columns <=0)
        throw matExp("Error de redimencion");

    int i;
    pm = new int*[rows];

    for(i=0; i<rows; i++)
        pm[i] = new int[columns];
    this->rows = rows;
    this->columns = columns;
    init(0);
}

void Matrix::init(int value)
{
    int i,j;
    for(i=0; i<rows; i++)
        for(j=0; j<columns; j++)
            pm[i][j] = value;
}

void Matrix::reSize(int rows,int columns)
{
    int i,j;

    if((this->rows == rows) && (this->columns == columns))
        return;

    Matrix newMatrix(rows,columns);

    for(i=0; i<this->rows && i<rows ; i++)
        for(j=0; j<this->columns && j<columns ; j++)
            newMatrix.pm[i][j] = this->pm[i][j];

    for(i=0; i<this->rows; i++)
        delete [] this->pm[i];
    delete [] this->pm;

    this->pm      = newMatrix.pm;
    this->rows    = rows;
    this->columns = columns;
}

int Matrix::determinant()
{
    int det = 0;
    if(rows!=columns)
        throw matExp("Determinante de una matriz no cuadrada");

    if(rows == 1)
        return pm[0][0];

    for (int j = 0; j < columns; j++)
        det += ((j%2==0)?1:-1) * pm[0][j] * cofactor(0,j);

    return det;
}

/**
fila y columna son evitadas para la asignacion de la subMatriz
**/
int Matrix::cofactor(int row,int column)
{
    int n=this->rows -1,
        x=0,
        y=0;

    Matrix subMatrix(this->rows-1,this->columns-1);

    for(int i=0;i<this->rows; i++)
        for(int j=0;j<this->rows;j++){

            if(i==row || j==column)
                continue;

            subMatrix.pm[x][y] = pm[i][j];

            if (++y >= n){
                x++;
                y=0;
            }
        }

    return subMatrix.determinant();
}
/// OPERATORS
Matrix Matrix::operator+(const Matrix& other)
{
    int i,j;

    if((rows != other.rows) || (columns != other.columns))
        throw matExp("Las matrices deben ser de la misma dimencion");

    Matrix result(rows,columns);

    for(i=0; i<rows; i++)
        for(j=0; j<columns; j++)
            result.pm[i][j] = pm[i][j] + other.pm[i][j];

    return result;
}

Matrix Matrix::operator-(const Matrix& other)
{
    int i,j;

    if((rows != other.rows) || (columns != other.columns))
        throw matExp("Las matrices deben ser de la misma dimencion");

    Matrix result(rows,columns);

    for(i=0; i<rows; i++)
        for(j=0; j<columns; j++)
            result.pm[i][j] = pm[i][j] - other.pm[i][j];

    return result;
}

Matrix& Matrix::operator=(const Matrix& other)
{
    int i;

    for(i=0; i<rows; i++)
        delete [] pm[i];

    delete [] pm;

    pm      = other.pm;
    rows    = other.rows;
    columns = other.columns;

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    int i,j;

    if((rows != other.rows) || (columns != other.columns))
        throw matExp("Las matrices deben ser de la misma dimencion");

    for(i=0; i<rows; i++)
        for(j=0; j<columns; j++)
            pm[i][j] = pm[i][j] + other.pm[i][j];

    return *this;
}
Matrix& Matrix::operator-=(const Matrix& other)
{
    int i,j;

    if((rows != other.rows) || (columns != other.columns))
        throw matExp("Error de dimencion");

    for(i=0; i<rows; i++)
        for(j=0; j<columns; j++)
            pm[i][j] = pm[i][j] - other.pm[i][j];

    return *this;
}

Matrix  Matrix::operator*(const Matrix& other)
{
    int i,j,k,sum=0;

    if(columns != other.rows)
        throw matExp("Error de dimencion");

    Matrix result(rows,other.columns);

    for(i=0; i<rows; i++)
        for(k=0; k<other.columns; k++){
            for(j=0; j<rows; j++){
                sum += (pm[i][j]) * (other.pm[j][k]);
            }
            result.pm[i][k] = sum;
            sum = 0;
        }

    return result;
}


ostream& operator<<(ostream& os, const Matrix& mat)
{
    int i,j;
    os << endl << endl;
    for(i=0; i<mat.rows; i++){

        os<< " ";
        for(j=0; j<mat.columns; j++)
            os << mat.pm[i][j] << " ";
        os << endl;

    }
    return os;
}

istream& operator>>(istream& is, Matrix& mat)
{
    int i,j,k=0,value;
    char buffer[SIZEBUFFER];

    for(i=0; i<mat.rows; i++)
        for(j=0; j<mat.columns; j++){
            if((buffer[k] = is.get()) == '\n')
                return is;

            while(buffer[k] != ' '){
                k++;
                if((buffer[k] = is.get()) == '\n'){
                    value = stoi(buffer);
                    mat.pm[i][j] = value;
                    return is;
                }
            }
            value = stoi(buffer);
            mat.pm[i][j] = value;
            k=0;
        }
    return is;
}
Matrix::~Matrix()
{
    int i;
    for(i=0; i<rows; i++)
        delete [] pm[i];
    delete [] pm;
}
