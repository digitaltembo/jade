#ifndef MATRIX
#define MATRIX

#include "stdint.h"
#include "stdio.h"
#include <vector>
#include "MyException.h"

class Matrix{
public:
    Matrix(int m, int n);
    Matrix(Matrix* m);
   ~Matrix();
    void set(int y, int x, double d);
    double get(int y, int x);
    void identity();
    
    int width();
    int height();
    void transpose();
    void rowSubtract(int r1, int r2);
    void rowSwap(int r1, int r2);
    void rowMult(int r1, double d);
    void rowMultAndSub(int r1, int r2, double d);
    bool eschelon();
    bool invertable();
    Matrix inverse();
    Matrix& invert();
    
    void print();
    
    Matrix  operator+(Matrix m);
    Matrix& operator+=(Matrix m);
    Matrix  operator-(Matrix m);
    Matrix& operator-=(Matrix m);
    
    Matrix  operator*(Matrix m);
    Matrix& operator*=(Matrix m);
    Matrix  operator*(uint64_t i);
    Matrix& operator*=(uint64_t i);
    Matrix  operator*(double d);
    Matrix& operator*=(double d);
    
    Matrix  operator/(Matrix m);
    Matrix& operator/=(Matrix m);
    Matrix  operator/(uint64_t i);
    Matrix& operator/=(uint64_t i);
    Matrix  operator/(double d);
    Matrix& operator/=(double d);
private:
    int w, h;
    vector<double> a;
};

#endif