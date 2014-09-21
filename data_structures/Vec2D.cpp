#include "Vec2D.h"

template <class T>
Vec2D<T>::Vec2D(int width, int height){
    v=new vector<vector<T> >;
    (*v).resize(height);
    for(int y=0;y<height;y++)
        (*v)[y].resize(width);
}

template <class T>
Vec2D<T>::~Vec2D(){
    for(int y=0, height=(*v).size();y<height;y++)
        (*v)[y].clear();
    (*v).clear();
    delete v;
}

template <class T>
void Vec2D<T>::resize(int width, int height){
    (*v).resize(height);
    for(int y=0;y<height;y++)
        (*v)[y].resize(width);
}

template <class T>
vector<T> Vec2D<T>::operator[](unsigned i){
    return (*v)[i];
}

template <class T>
T Vec2D<T>::get(int x, int y){
    return (*v)[x][y];
}

template <class T>
T Vec2D<T>::set(int x, int y, T t){
    return (*v)[x][y] = t;
}
    