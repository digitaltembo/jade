#ifndef BITWISE_ARRAY
#define BITWISE_ARRAY

#include "stdint.h"
#include "stdio.h"

#define EXPANSION_FACTOR 2

class BitwiseArray {
public:
    BitwiseArray(int elementCount, uint8_t elementWidth);
   ~BitwiseArray();
    uint64_t get(int key);
    uint64_t operator[](int key);
    void set(int key, uint64_t value);
    void expand();
    void expand(int newCount);
    void widen(int newWidth);
    int size();
private:
    int count, capacity;
    uint8_t* arr, width;
    const static unsigned char mask[];
};

#endif
