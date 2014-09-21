#ifndef ARRAY
#define ARRAY

#include "ListInterface.h"

class Array: public ListInterface {
public:
    Array(int elementSize, void (*free)(void*), int init_capacity = 5, float expansion = 2.0);
    ~Array();
    void* get(void* key);
    void* get(pint_t index);
    
    void* operator[](void* key);
    void* operator[](pint_t index);
    
    void* set(void* key, void* value);
    void* set(pint_t index, void* value);
    
    void* insert(void* key, void* value);
    void* insert(pint_t index, void* value);
    
    void* append(void* value);
    
    void remove(void* key);
    void remove(pint_t index);
    
    uint64_t size();
    uint64_t nodeCount();
    void save();
private:
    uint64_t length, elementSize, capacity;
    float expansion;
    void (*free)(void*);
    bool expand();
    void** data;
};

#endif
