#include "LinkedListTail.h"

LinkedListTail::LinkedListTail(int elementSize, void (*free)(void*) ) : ListInterface(){
    this->elementSize = elementSize;
    this->free = free;
    length = 0;
    head = NULL;
    tail = NULL;
}

void* LinkedListTail::get(pint_t index){
   if(index>=length)
        return NULL;
   if(index == length-1)
       return tail->data;
    pint_t i = 0;
    ListNode* iter = head;
    while(i<index){
        iter = iter->next;
        i++;
    }
    return iter->data;
}
void* LinkedListTail::get(void* key){
    return get((pint_t)key);
}

void* LinkedListTail::operator[](pint_t index){
    return get(index);
}

void* LinkedListTail::operator[](void* key){
    return get(key);
}

void* LinkedListTail::set(pint_t index, void* value){
    if(index>=length)
        return NULL;
    if(index == length-1){
        tail->data = value;
        return tail->data;
    }
    pint_t i = 0;
    ListNode* iter = head;
    while(i<index){
        iter = iter->next;
        i++;
    }
    iter->data = value;
    return iter->data;
}
    
void* LinkedListTail::set(void* key, void* value){
    return set((pint_t)key, value);
}
void* LinkedListTail::insert(pint_t index, void* value){
    if(index>length)
        return NULL;
    pint_t i = 0;
    ListNode* iter = head;
    ListNode* insert = new ListNode;
    if(insert == NULL)
        return NULL;
    insert->data = value;
    
    if(index == 0){
        insert->next = iter;
        head = insert;
        if(length == 0)
            tail = insert;
        length++;
        return insert->data;
    }
    if(index == length){
        insert->next = NULL;
        tail->next = insert;
        tail = insert;
        return insert->data;
    }
    
    while(i<index-1){
        iter = iter->next;
        i++;
    }
    insert->next = iter->next;
    iter->next = insert;
    
    length++;
    return insert->data;
}

void* LinkedListTail::insert(void* key, void* value){
    return insert((pint_t)key, value);
}

void* LinkedListTail::append(void* value){
    ListNode* insert = new ListNode;
    if(insert == NULL)
        return NULL;
    insert->next = NULL;
    insert->data = value;
    if(length == 0){
        head = tail = insert;
        length++;
        return insert->data;
    }
    tail->next = insert;
    tail = insert;
    length++;
    return insert->data;
}
    
void LinkedListTail::remove(pint_t index){
    if(index>=length||length==0)
        return;
    pint_t i = 0;
    if(index=0){
        ListNode* tmp=head;
        delete tmp->data;
        head=head->next;
        delete tmp;
        length--;
    }
        
    ListNode* iter = head, pIter;
    while(i<index){
        pIter = iter;
        iter = iter->next;
        i++;
    }
    delete iter->data;
    pIter->next=iter->next;
    delete iter;
    length--;
}
    
void LinkedListTail::remove(void* key){
    remove((pint_t)key);
}

uint64_t LinkedListTail::size(){
    return elementSize*length;
}
uint64_t LinkedListTail::nodeCount(){
    return length;
}
void LinkedListTail::save(){
}


LinkedListTail::~LinkedListTail(){
    ListNode* iter = head;
    while(iter != NULL){
        ListNode* tmp = iter->next;
        //(*free)(iter->data);
        delete iter;
        iter = tmp;
    }
    head = NULL;
}