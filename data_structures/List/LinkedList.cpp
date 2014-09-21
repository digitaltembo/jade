#include "LinkedList.h"

LinkedList::LinkedList(int elementSize, void (*free)(void*) ) : ListInterface(){
    this->elementSize = elementSize;
    this->free = free;
    length = 0;
    head = NULL;
}

void* LinkedList::get(pint_t index){
   if(index>=length)
        return NULL;
    pint_t i = 0;
    ListNode* iter = head;
    while(i<index){
        iter = iter->next;
        i++;
    }
    return iter->data;
}
void* LinkedList::get(void* key){
    return get((pint_t)key);
}

void* LinkedList::operator[](pint_t index){
    return get(index);
}

void* LinkedList::operator[](void* key){
    return get(key);
}

void* LinkedList::set(pint_t index, void* value){
    if(index>=length)
        return NULL;
    pint_t i = 0;
    ListNode* iter = head;
    while(i<index){
        iter = iter->next;
        i++;
    }
    iter->data = value;
    return iter->data;
}
    
void* LinkedList::set(void* key, void* value){
    return set((pint_t)key, value);
}
void* LinkedList::insert(pint_t index, void* value){
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
        length++;
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

void* LinkedList::insert(void* key, void* value){
    return insert((pint_t)key, value);
}

void* LinkedList::append(void* value){
    ListNode* insert = new ListNode;
    if(insert == NULL)
        return NULL;
    insert->next = NULL;
    insert->data = value;
    if(length == 0){
        head = insert;
        length++;
        return insert->data;
    }
    ListNode* iter = head;
    while(iter->next != NULL){
        iter = iter->next;
    }
    iter->next = insert;
    length++;
    return insert->data;
}
    
void LinkedList::remove(pint_t index){
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
    
void LinkedList::remove(void* key){
    remove((pint_t)key);
}

uint64_t LinkedList::size(){
    return elementSize*length;
}
uint64_t LinkedList::nodeCount(){
    return length;
}
void LinkedList::save(){
}


LinkedList::~LinkedList(){
    ListNode* iter = head;
    while(iter != NULL){
        ListNode* tmp = iter->next;
        //(*free)(iter->data);
        delete iter;
        iter = tmp;
    }
    head = NULL;
}