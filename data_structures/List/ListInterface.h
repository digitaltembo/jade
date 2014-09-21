#ifndef LIST_INTER
#define LIST_INTER

#include "../MapInterface.h"

typedef uint64_t pint_t;

class ListInterface: public MapInterface {
public:
    ListInterface(){};
    ListInterface(int elementSize, void (*free)(void*)){};
   ~ListInterface(){};
    virtual void* get(pint_t key) = 0;
    virtual void* get(void* key) = 0;
    
    virtual void* operator[](pint_t key) = 0;
    virtual void* operator[](void* key) = 0;
    
    virtual void* set(pint_t key, void* value) = 0;
    virtual void* set(void* key, void* value) = 0;
    
    virtual void* insert(pint_t key, void* value) = 0;
    virtual void* insert(void* key, void* value) = 0;

    virtual void* append(void* value) = 0;
    
    virtual void remove(pint_t key) = 0;
    virtual void remove(void* key) = 0;
    
    virtual uint64_t size() = 0;
    virtual uint64_t nodeCount() = 0;
    virtual void save() = 0;
private:
    uint64_t length, elementSize;
    void (*free)(void*);
};

#endif
