/*
 * Created: 8/15
 * Last Modified: 8/23
 * Last Compiled: 8/23
 * Compiler Flags: None?
 * 
 */

#ifndef BOXED_ARRAY
#define BOXED_ARRAY

#include "ListInterface.hpp"


namespace jade{
    
    template<class T>
    class BoxedArray : public ListInterface<T>{
        
        typedef int (*ValueCmpFunc)(T& v1, T& v2);
        typedef void (*DeleteFunc)(T* t);
        
    public:
        BoxedArray(int size=1, float expansion=2){
            elementSaver=NULL;
            elementCapacity=size;
            data=new T[elementCapacity];
            if(data==NULL){
                elementCapacity=0;
            }
            elementCount=0;
            this->expansion=expansion;
            valueCmpSet=false;
            elementSize=sizeof(T);
            deleteFunc=NULL;
        }
       ~BoxedArray(){
           freeMemory();
        }
        
        T* getRaw(){
            return data;
        }

        T& get(int64_t index){
            if(index>=elementCount){
                while(index>=elementCapacity)
                    if(!expand())
                        return failure;
                elementCount=index+1;
            }
            return data[index];
        }
        T& operator[](int64_t index){
            if(index>=elementCount){
                while(index>=elementCapacity)
                    if(!expand())
                        return failure;
                elementCount=index+1;
            }
            return data[index];
        }
        T& set(int64_t index, T value){
            return data[index]=value;
        }
        
        T& insert(int64_t index, T value){
            if(index<elementCount){
                if(elementCapacity-elementCount<=1)
                    if(!expand())
                        return failure;
                for(int64_t i=elementCount;i>index;i--){
                    data[i]=data[i-1];
                }
                data[index]=value;
                elementCount++;
                return data[index];
            }else{
                bool failed;
                while(index>=elementCapacity){
                    if(!expand()){
                        failed=true;
                        break;
                    }
                }
                if(!failed){
                    data[index]=value;
                    elementCount=index+1;
                    return data[index];
                }
                return failure;
            }
        }
        
        T& append(T value){
            if(elementCount==elementCapacity)
                if(!expand())
                    return failure;
            data[elementCount]=value;
            elementCount++;
            return data[elementCount];
        }
        
        T& push(T value){
            if(elementCount==elementCapacity)
                if(!expand())
                    return failure;
            data[elementCount]=value;
            elementCount++;
            return data[elementCount];
        }
        T& top(){
            if(elementCount==0)
                return failure;
            return data[elementCount-1];
        }
        T pop(){
            if(elementCount>0)
                elementCount--;
            return data[elementCount];
        }
        
        void remove(int64_t index){
            if(index<elementCount){
                for(int i=index;i<elementCount-1;i++)
                    data[i]=data[i+1];
                elementCount--;
            }
        }
        
        int64_t find(T value){
            if(valueCmpSet==true){
                for(int64_t i=0;i<elementCount;i++)
                    if(this->valueCmp(value, data[i])==0)
                        return i;
            }else{
                return -1;
            }
        }
                
        
        void shrink(){
            T* tmp=new T[elementCount];
            if(tmp!=NULL){
                for(int i=0;i<elementCount;i++)
                    tmp[i]=data[i];
                delete[] data;
                data=tmp;
                elementCapacity=elementCount;
            }
                
        }
        
        void resize(int64_t count){
            T* tmp=new T[count];
            if(tmp!=NULL){
                for(int i=0;i<count&&i<elementCount;i++)
                    tmp[i]=data[i];
                delete[] data;
                data=tmp;
                elementCapacity=count;
            }
        }
            
        
        int64_t size(){
            return elementCount;
        }
        int64_t length(){
            return elementCount;
        }
        
        int64_t capacity(){
            return elementCapacity;
        }
        
        int64_t memoryUsed(){
            return elementCapacity*elementSize;
        }
        bool saveToStream(FILE* stream){
            fwrite(&elementCount, sizeof(int64_t), 1, stream);
            if(elementSaver==NULL || elementSaver->save==NULL)
                return fwrite(data, elementSize, elementCount, stream)==elementCount;
            else{
                bool broken=false;
                for(int64_t i=0;i<elementCount;i++){
                    if(!elementSaver->save(stream, data[i])){
                        broken=true;
                        break;
                    }
                }
                return !broken;
            }
        }
        bool loadFromStream(FILE* stream){
            freeMemory();
            fread(&elementCount, sizeof(int64_t), 1, stream);
            data=new T[elementCount];
            if(data==NULL)
                return -1;
            if(elementSaver==NULL || elementSaver->load==NULL)
                return fread(data, elementSize, elementCount, stream)==elementCount;
            else{
                bool broken=false;
                T* tmp;
                for(int64_t i=0;i<elementCount;i++){
                    tmp=elementSaver->load(stream);
                    if(tmp==NULL){
                        broken=true;
                        break;
                    }
                    data[i]=*tmp;
                    delete tmp;
                }
                return !broken;
            }
                
        }
        
        void setFailure(T fail){
            failure=fail;
        }
            
            
    private:
        int64_t elementCount, elementCapacity, elementSize;
        struct Saver<T>* elementSaver;
        float expansion;
        bool expand(){
            T* tmp = new T[(int64_t)(elementCapacity*expansion)+1];
            if(tmp==NULL)
                return false;
            for(int64_t i=0;i<elementCount;i++){
                tmp[i]=data[i];
            }
            delete[] data;
            data=tmp;
            elementCapacity*=expansion;
            return true;
        }
        
        void freeMemory(){
           if(deleteFunc!=NULL){
               for(int i=0;i<elementCount;i++){
                   deleteFunc(&data[i]);
               }
           }
           delete[] data;
        }
        T* data;
        T failure;
        
        ValueCmpFunc valueCmp;
        DeleteFunc deleteFunc;
        bool valueCmpSet;
        
    };
}

#endif