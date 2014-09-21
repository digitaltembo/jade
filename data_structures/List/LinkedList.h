#ifndef LINKED_LIST
#define LINKED_LIST

#include "ListInterface.h"

#ifndef LIST_NODE
#define LIST_NODE
typedef struct ListNode{
    void* data;
    ListNode* next;
}ListNode;
#endif

class LinkedList: public ListInterface {
public:
    LinkedList(int elementSize, void (*free)(void*));
    ~LinkedList();
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
    uint64_t length, elementSize;
    void (*free)(void*);
    ListNode* head;
};

#endif
