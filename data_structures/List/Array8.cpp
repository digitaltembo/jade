#include "Array8.h"

Array8::Array8(int elementSize, void (*free)(void*), int init_capacity, float expansion) : ListInterface(){
    this->elementSize = elementSize;
    this->free = free;
    this->expansion = expansion;
    capacity = init_capacity;
    data = new void*[capacity];
    length = 0;
}

void* Array8::get(pint_t index){
    return data[index];
}
void* Array8::get(void* key){
    return get((pint_t)key);
}

void* Array8::operator[](pint_t index){
    return get(index);
}

void* Array8::operator[](void* key){
    return get(key);
}

void* Array8::set(pint_t index, void* value){
    data[index] = value;
    return value;
}
    
void* Array8::set(void* key, void* value){
    return set((pint_t)key, value);
}
void* Array8::insert(pint_t index, void* value){
    if(index>length)
        return NULL;
    if(length >= capacity)
        if(!expand())
            return NULL;
    for(pint_t i = length; i > index;i--)
        data[i] = data[i-1];
    data[index] = value;
    length++;
    return value;
}

void* Array8::insert(void* key, void* value){
    return insert((pint_t)key, value);
}

void* Array8::append(void* value){
    if(length >= capacity)
        if(!expand())
            return NULL;
    data[length] = value;
    length++;
    return value;
}
    
void Array8::remove(pint_t index){
    if(index>=length)
        return;
    //(*free)(data[index]);
    data[index] = NULL;
}
    
void Array8::remove(void* key){
    remove((pint_t)key);
}

uint64_t Array8::size(){
    return elementSize*length;
}
uint64_t Array8::nodeCount(){
    return length;
}
void Array8::save(){
}

bool Array8::expand(){
    void** tmp = data;
    capacity*=expansion;
    data = new void*[capacity];
    if(data == NULL){
        capacity/=expansion;
        return false;
    }
    for(pint_t i=0;i<length;i++){
        data[i] = tmp[i];
    }
    return true;
}

Array8::~Array8(){
    //for(int i = 0;i<length;i++) (*free)(data[i]);  
    delete[] data;
}