#include "Matrix.h"

static inline double abs(double d){
    return (d<0)?-d:d;
}
Matrix::Matrix(int m, int n){
    w = n;
    h = m;
    a.resize(m*n);
}

Matrix::Matrix(Matrix* m){
    w=m->w;
    h=m->h;
    a.resize(w*h);
    for(int i=0, l=w*h;i<l;i++){
        a[i]=m->a[i];
    }
}
Matrix::~Matrix(){
    a.clear();
}

void Matrix::set(int y, int x, double d){
    a[y+x*h] = d;
}
double Matrix::get(int y, int x){
    return a[y+x*h];
}
void Matrix::identity(){
    if(w!=h){
        w = h;
        a.clear();
        a.resize(w*w);
        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                a[y+x*h] = (x==y)?1:0;
            }
        }
    }else{
        for(int y = 0; y < h; y++){
            for(int x = 0; x < w; x++){
                a[y+x*h] = (x==y)?1:0;
            }
        }
    }
}
        
    
        

int Matrix::width(){
    return w;
}
int Matrix::height(){
    return h;
}
void Matrix::transpose(){
    if(w!=h){
        Matrix* t=new Matrix(w,h);
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                t->set(y,x,a[y+x*h]);
            }
        }
        a.clear();
        a=t->a;
    }else{
        double tmp;
        for(int y=0;y<h;y++){
            for(int x=y;x<w;x++){
                tmp=a[y+x*w];
                a[y+x*w]=a[x+y*w];
                a[x+y*w]=tmp;
            }
        }
    }
}

void Matrix::rowSubtract(int r1, int r2){
    for(int x=0;x<w;x++){
        a[r1+x*h]-=a[r2+x*h];
    }
}
void Matrix::rowSwap(int r1, int r2){
    double tmp;
    for(int x=0;x<w;x++){
        tmp=a[r1+x*h];
        a[r1+x*h]=a[r2+x*h];
        a[r2+x*h]=tmp;
    }
}
void Matrix::rowMult(int r, double factor){
    for(int x=0;x<w;x++){
        a[r+x*h]*=factor;
    }
}
void Matrix::rowMultAndSub(int r1, int r2, double factor){
    for(int x=0;x<w;x++)
        a[r1+x*h]=a[r1+x*h]-factor*a[r2+x*h];
}
bool Matrix::eschelon(){
    int k,i,j,maxID, maxVal;
    for(k=0;k<h;k++){
        maxID=0;
        maxVal=0;
        for(i=k;i<h;i++){
            if(abs(a[i+k*h])>maxVal){
                maxVal=abs(a[i+k*h]);
                maxID=i;
            }
        }
        if(maxVal==0)
            return false;
        rowSwap(maxID, k);
        for(i=k+1;i<h;i++){
            rowMultAndSub(i,k, a[i+k*h]/a[k+k*h]);
        }
        rowMult(k, 1/a[k+k*h]);
    }
    return true;
}
            
bool Matrix::invertable(){
    if(w!=h)
        return false;
    switch(w){
        case 0:
        case 1:
            return true;
        case 2:
            return a[0]*a[3]-a[1]*a[2]!=0;
        case 3:
            double det =  a[0]*a[4]*a[8]
                        - a[0]*a[7]*a[5]
                        - a[3]*a[1]*a[8]
                        + a[3]*a[7]*a[2]
                        + a[6]*a[1]*a[5]
                        - a[6]*a[4]*a[2];
            return det!=0;
    }
    Matrix* e = new Matrix(this);
    bool in = e->eschelon();
    delete e;
    return in;
}

Matrix Matrix::inverse(){
    if(w != h)
        throw MyException("Invalid bounds\n");
    Matrix i2(w, h);
    Matrix revert(this);
    i2.identity();
    int k,i,j,maxID, maxVal;
    double val;
    for(k=0;k<h;k++){
        maxID=0;
        maxVal=0;
        for(i=k;i<h;i++){
            if(abs(a[i+k*h])>maxVal){
                maxVal=abs(a[i+k*h]);
                maxID=i;
            }
        }
        if(maxVal==0)
            throw MyException("Non-invertable matrix\n");
        rowSwap(maxID, k);
        i2.rowSwap(maxID, k);
        for(i=k+1;i<h;i++){
            val=a[i+k*h]/a[k+k*h];
            rowMultAndSub(i,k, val);
            i2.rowMultAndSub(i,k, val);
        }
        val=1/a[k+k*h];
        rowMult(k, val);
        i2.rowMult(k, val);
        for(j=k-1;j>=0;j--){
            val=a[j+k*h];
            rowMultAndSub(j, k, val);
            i2.rowMultAndSub(j, k, val);
        }
    }
    a=revert.a;
    return i2;
}

Matrix& Matrix::invert(){
    if(w != h)
        throw MyException("Invalid bounds\n");
    Matrix i2(w, h);
    i2.identity();
    int k,i,j,maxID, maxVal;
    double val;
    for(k=0;k<h;k++){
        maxID=0;
        maxVal=0;
        for(i=k;i<h;i++){
            if(abs(a[i+k*h])>maxVal){
                maxVal=abs(a[i+k*h]);
                maxID=i;
            }
        }
        if(maxVal==0)
            throw MyException("Non-invertable matrix\n");
        rowSwap(maxID, k);
        i2.rowSwap(maxID, k);
        for(i=k+1;i<h;i++){
            val=a[i+k*h]/a[k+k*h];
            rowMultAndSub(i,k, val);
            i2.rowMultAndSub(i,k, val);
        }
        val=1/a[k+k*h];
        rowMult(k, val);
        i2.rowMult(k, val);
        for(j=k-1;j>=0;j--){
            val=a[j+k*h];
            rowMultAndSub(j, k, val);
            i2.rowMultAndSub(j, k, val);
        }
    }
    a=i2.a;
    return *this;
}

void Matrix::print(){
    int i,j;
    for(i=0;i<h;i++){
        printf("[ ");
        for(j=0;j<w;j++){
            printf("%f ",a[i+j*h]);
        }
        printf("]\n");
    }
}

Matrix  Matrix::operator+(Matrix m){
    if(w==m.width()&& h==m.height()){
        Matrix m2(this);
        m2+=m;
        return m2;
    }else{
        throw MyException("Invalid Bounds");
    }
}
        
Matrix& Matrix::operator+=(Matrix m){
    if(w==m.width()&&h==m.height()){
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
               a[i+j*h]+=m.get(i,j);
            }
        }
        return *this;
    }
    throw MyException("Invalid Bounds");
}
    
Matrix  Matrix::operator-(Matrix m){
    if(w==m.width() && h==m.height()){
        Matrix m2(this);
        m2+=m;
        return m2;
    }else{
        throw MyException("Invalid Bounds");
    }
}
Matrix& Matrix::operator-=(Matrix m){
    if(w==m.width()&&h==m.height()){
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
               a[i+j*h]-=m.get(i,j);
            }
        }
        return *this;
    }
    throw MyException("Invalid Bounds");
}

Matrix  Matrix::operator*(Matrix m){
    if(w==m.h){
        Matrix m2(h, m.w);
        int i,j,k;
        double sum;
        for(i=0;i<h;i++){
            for(j=0;j<m.w;j++){
                sum=0;
                for(k=0;k<w;k++)
                    sum+=a[i+k*h]*m.a[k+j*w];
                m2.set(i,j,sum);
            }
        }
        return m2;
    }else{
        throw MyException("Invalid Bounds");
    }
}

Matrix& Matrix::operator*=(Matrix m){
    if(w==m.h){
        (*this)=(*this)*m;
        return *this;
    }else{
        throw MyException("Invalid Bounds");
    }
}
        
    
Matrix  Matrix::operator*(uint64_t i){
    Matrix m(this);
    m*=i;
    return m;
}
Matrix& Matrix::operator*=(uint64_t i){
    for(int x = 0, j=w*h;x<j;x++)
        a[x]*=i;
    return *this;
}
Matrix  Matrix::operator*(double d){
    Matrix m(this);
    m*=d;
    return m;
}
Matrix& Matrix::operator*=(double d){
    for(int i = 0, j=w*h;i<j;i++)
        a[i]*=d;
    return *this;
}

Matrix  Matrix::operator/(Matrix m){
    m.invert();
    return this->operator*(m);
}
Matrix& Matrix::operator/=(Matrix m){
    m.invert();
   return this->operator*=(m);
}
Matrix  Matrix::operator/(uint64_t i){
    Matrix m(this);
    m/=i;
    return m;
}
    
Matrix& Matrix::operator/=(uint64_t i){
    for(int x = 0, j=w*h;x<j;x++)
        a[x]/=i;
    return *this;
}
Matrix  Matrix::operator/(double d){
    Matrix m(this);
    m/=d;
    return m;
}
Matrix& Matrix::operator/=(double d){
    for(int x = 0, j=w*h;x<j;x++)
        a[x]/=d;
    return *this;
}