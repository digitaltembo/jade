#include "BitwiseArray.h"

const unsigned char BitwiseArray::mask[] = 
                        {1, 3, 7, 15, 31, 63, 127, 255};

BitwiseArray::BitwiseArray(int elementCount, uint8_t elementWidth){
    count=elementCount;
    width=elementWidth;
    capacity=((count*width)>>3)+1;
    arr=new uint8_t[capacity];
}

BitwiseArray::~BitwiseArray(){
    delete[] arr;
}

uint64_t BitwiseArray::get(int key){
    uint64_t num=0;
    int bitLoc=key*width;
    int byteLoc=(bitLoc)>>3;
    int diff=bitLoc-(byteLoc<<3);
    num=(arr[byteLoc]>>diff);
    diff=8-diff;
    if(width<diff)
        return num&mask[width-1];
    else if(width==diff)
        return num;
    else{
        int bitsLeft=width-diff;
        while(bitsLeft>8){
            byteLoc++;
            num|=((uint64_t)arr[byteLoc])<<(width-bitsLeft);
            bitsLeft-=8;
        }
        byteLoc++;
        num|=((uint64_t)(arr[byteLoc]&mask[bitsLeft-1]))<<(width-bitsLeft);
        return num;
    }
}
    

uint64_t BitwiseArray::operator[](int key){
    return get(key);
}

void BitwiseArray::set(int key, uint64_t value){
    if(key>=count){
        fprintf(stderr, "Key %i exceeds array bounds of %i, expanding array\n", key, count);
        expand(key+2);
        if(key>=count)
            return;
    }
    int bitLoc=key*width;
    int byteLoc=(bitLoc)>>3;
    int diff=8-(bitLoc-(byteLoc<<3));
    if(width<diff){
        diff=8-diff;
        value=value<<diff;
        arr[byteLoc]=(arr[byteLoc]&~(mask[width-1]<<diff))|(uint8_t)value;
        return;
    }
    else{
        arr[byteLoc]<<=diff;
        arr[byteLoc]>>=diff;
        arr[byteLoc]|=(uint8_t)(value<<(8-diff));
        if(width==diff)
            return;
        //int bitsLeft=width-diff;
        while((width-diff)>8){
            byteLoc++;
            arr[byteLoc]=(uint8_t)(value>>diff);
            diff+=8;
        }
        byteLoc++;
        arr[byteLoc]=(arr[byteLoc]&~mask[width-diff-1])|(uint8_t)(value>>diff);
    }
}
    
void BitwiseArray::expand(){
    expand(capacity*EXPANSION_FACTOR);
}
void BitwiseArray::expand(int exp){
    int nCapacity=((exp*width)>>3)+1;
    if(nCapacity>capacity){
        uint8_t* newArr=new uint8_t[nCapacity];
        if(newArr==NULL){
            fprintf(stderr, "Unable to expand array, out of memory\n");
            return;
        }
        for(int i=0;i<capacity;i++){
            newArr[i]=arr[i];
        }
        for(int i=capacity;i<nCapacity;i++){
            newArr[i]=0;
        }
        delete[] arr;
        arr=newArr;
        capacity=nCapacity;
    }
    count=exp;
}

void BitwiseArray::widen(int newWidth){
    BitwiseArray newBitArr(count, newWidth);
    for(int i=0;i<count;i++){
        newBitArr.set(i,get(i));
    }
    uint8_t* newArr=new uint8_t[newBitArr.capacity];
    for(int i=0;i<newBitArr.capacity;i++){
        newArr[i]=newBitArr.arr[i];
    }
    delete[] arr;
    arr=newArr;
    capacity=newBitArr.capacity;
    width=newWidth;
}
int BitwiseArray::size(){
    return count;
}