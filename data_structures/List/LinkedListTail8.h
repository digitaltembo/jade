#ifndef LINKED_LIST_TAIL_8
#define LINKED_LIST_TAIL_8

#include "ListInterface.h"

#ifndef LIST_NODE
#define LIST_NODE
typedef struct ListNode{
    void* data;
    ListNode* next;
}ListNode;
#endif

class LinkedListTail8: public ListInterface {
public:
    LinkedListTail8(int elementSize, void (*free)(void*));
    ~LinkedListTail8();
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
    uint8_t length, elementSize;
    void (*free)(void*);
    ListNode* head;
    ListNode* tail;
};

#endif
