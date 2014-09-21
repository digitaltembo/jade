#ifndef BOOLA
#define BOOLA

#include "stdint.h"

class BoolArray{
public:
    BoolArray(int size);
   ~BoolArray();
    bool get(int i);
    bool set(int i, bool b);
private:
    uint16_t* arr;
};
    
#endif