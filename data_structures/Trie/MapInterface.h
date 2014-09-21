#ifndef MAP_INTER
#define MAP_INTER

#include <cstddef>
#include "stdint.h"

class MapInterface {
public:
    MapInterface(){}
    virtual ~MapInterface(){}
    virtual void* get(void* key) = 0;
    
    virtual void* operator[](void* key) = 0;
    
    virtual void* set(void* key, void* value) = 0;
    virtual void remove(void* key) = 0;
    virtual uint64_t size() = 0;
    virtual uint64_t nodeCount() = 0;
    virtual void save() = 0;
};

#endif


