#include "BoolArray.h"

BoolArray::BoolArray(int size){
    int s=size/16;
    arr=new uint16_t[s];
    for(int i=0;i<s;i++){
        arr[s]=0;
    }
}
BoolArray::~BoolArray(){
    delete[] arr;
}
bool BoolArray::get(int i){
    return (arr[i/16]>>(i%16))&1;
}

bool BoolArray::set(int i, bool b){
     return arr[i/16]|=b<<(i%16);
}
