/*
 * Created: 8/15
 * Last Modified: 8/15
 * Last Compiled: 
 */

#ifndef MY_LINKED_LIST
#define MY_LINKED_LIST

#include "ListInterface.hpp"

namespace jade{
    template<class T>
    class BoxedLinkedList : private ListInterface<T> {
        
        typedef int (*ValueCmpFunc)(T& v1, T& v2);
        typedef void (*DeleteFunc)(T* t);
        typedef bool (*SaveFunc)(FILE* stream, T& obj);
        typedef T* (*LoadFunc)(FILE* stream);
        
        typedef struct ListNode{
            T data;
            ListNode* next;
        }ListNode;
        
    public:
        BoxedLinkedList(){
            head=tail=tmp=NULL;
        }
       ~BoxedLinkedList(){
           freeMemory();
        }
        
        T& get(unsigned key){
            if(elementCount==0){
                //SUUPER ERROR
                return T();
            }
            if(key>=elementCount){
                //ERROR!
                return head->data;
            }
            tmp=head;
            unsigned index=0;
            while(index<key){
                tmp=tmp->next;
                index++;
            }
            return tmp->value;
        }
        
        T& operator[](unsigned key){
            if(elementCount==0){
                //SUUPER ERROR
                return T();
            }
            if(key>=elementCount){
                //ERROR!
                return head->data;
            }
            tmp=head;
            unsigned index=0;
            while(index<key){
                tmp=tmp->next;
                index++;
            }
            return tmp->value;
        }
        
        T& set(unsigned key, T value){
            if(elementCount==0){
                if(key==0){
                    head=tail=new LinkNode;
                    head->data=value;
                    head->next=NULL;
                    elementCount=1;
                    return head->data.
                }
                head=new LinkNode;
                LinkNode* tmp=head;
                int index=0;
                while(index<key){
                    tmp->next=new LinkNode;
                    tmp=tmp->next;
                    index++
                }
                tmp->data=value;
                elemenctCount=index;
                tail=tmp;
                tail->next=NULL;
                return tmp->data;
                
            }
            if(key>=elementCount){
                LinkNode* tmp=tail;
                int index=elementCount-1;
                while(index<key){
                    tmp->next=new LinkNode;
                    tmp=tmp->next;
                    index++
                }
                tmp->data=value;
                elemenctCount=index+1;
                tail=tmp;
                tail->next=NULL;
                return tmp->data;
            }
            LinkNode* tmp=head;
            unsigned index=0;
            while(index<key){
                tmp=tmp->next;
                index++;
            }
            tmp->data=value;
            return tmp->data;
        }
        
        T& insert(unsigned key, T value){
            if(elementCount==0){
                if(key==0){
                    head=tail=new LinkNode;
                    head->data=value;
                    head->next=NULL;
                    elementCount=1;
                    return head->data.
                }
                head=new LinkNode;
                LinkNode* tmp=head;
                int index=0;
                while(index<key){
                    tmp->next=new LinkNode;
                    tmp=tmp->next;
                    index++
                }
                tmp->data=value;
                elemenctCount=index;
                tail=tmp;
                tail->next=NULL
                return tmp->data;
                
            }
            if(key>=elementCount){
                LinkNode* tmp=tail;
                int index=elementCount-1;
                while(index<key){
                    tmp->next=new LinkNode;
                    tmp=tmp->next;
                    index++
                }
                tmp->data=value;
                elemenctCount=index+1;
                tail=tmp;
                tail->next=NULL;
                return tmp->data;
            }
            if(key==0){
                LinkNode* tmp=new LinkNode;
                tmp->next=head;
                tmp->data=value;
                head=tmp;
                elementCount++;
                return head->data;
            }
            LinkNode* tmp=head, newNode=new LinkNode;
            newNode->data=value;
            unsigned index=0;
            while(index<key){
                tmp=tmp->next;
                index++;
            }
            newNode->next=tmp;
            elemenctCount++;
            return newNode->data;
        }
            
        
        T& append(T value){
            if(elementCount==0){
                head=tail=new ListNode;
                head->data=value;
                head->next=NULL;
                return head->data;
            }
            tail->next=new LinkNode;
            tail=tail->next;
            tail->data=value;
            tail->next=NULL;
            return tail->data;
        }
        
        void remove(unsigned index){
            if(index<elementCount){
                if(index=0){
                    ListNode* tmp=head->next;
                    delete head;
                    head=tmp;
                    elementCount--;
                    return;
                }
            unsigned index=0;
            while(index<key){
                tmp=tmp->next;
                index++;
            }
        
        unsigned find(T value)
        
        unsigned size(){
            return elementCount;
        }
        
        unsigned length(){
            return elementCount;
        }
        
        unsigned memoryUsed(){
            return elementCount*elementSize;
        }
        
        bool saveToStream(FILE* stream){
            fwrite(&elementCount, sizeof(int64_t), 1, stream);
            bool broken = false;
            ListNode* tmp=head;
            if(elementSaver==NULL || elementSaver->save==NULL){
                while(tmp!=NULL && !broken){
                    if(fwrite(tmp->data, elementSize, 1, stream)!=1) {
                        broken=true;
                        break;
                    }
                    tmp=tmp->next;
                }
            }else{
                while(tmp!=NULL && !broken){
                    if(!elementSaver->save(stream, tmp->data)){
                        broken=true;
                        break;
                    }
                    tmp=tmp->next;
                }
            }
            return !broken;    
        }
        bool loadFromStream(FILE* stream){
            freeMemory();
            fread(&elementCount, sizeof(int64_t), 1, stream);
            bool broken=false;
            head=new ListNode[elementCount];
            if(head==NULL)
                return false;
            ListNode* tmp=head;
            if(loadFunc==NULL){
                for(int i=0;!broken&&i<elementCount;i++){
                    if(fread(&(tmp->data), elementSize, 1, stream) != 0){
                        broken=true;
                        break;
                    }
                    tmp->next=tmp+1;
                    tmp++;
                }
                tail=tmp-1;
            }else{
                T* tmpObj;
                for(int i=0;!broken&&i<elementCount;i++){
                    tmpObj=loadFunc(stream);
                    if(tmpObj==NULL)){
                        broken=true;
                        break;
                    }
                    tmp->data=*tmpObj;
                    delete tmpObj;
                    tmp->next=tmp+1;
                    tmp++;
                }
                tail=tmp-1;
            }
                
            return !broken;
                

        }
    private:
        int64_t elementCount, elementSize;
        ListNode* head, tail;
        struct Saver<T>* elementSaver;
        
        LoadFunc loadFunc;
        SaveFunc saveFunc;
        
        void freeMemory(){ 
            if(deleteFunc!=NULL){
                while(head!=NULL){
                    tail=head;
                    head=head->next;
                    deleteFunc(&(tmp->data));
                    delete tail;
                }
            }else{
                while(head!=NULL){
                    tail=head;
                    head=head->next;
                    delete tail;
                }
            }   
        }
        
    };