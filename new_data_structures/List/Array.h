/*
 * Created: 8/15
 * Last Modified: 8/15
 * Last Compiled: NA
 */

#ifndef MY_ARRAY
#define MY_ARRAY

#include <stdio.h>


namespace jade{
    
    template<class T>
    class ListInterface : public MapInterface<unsigned, T> {
    public:
        Array(int size=0, int capacity=1, float expansion=2){
            if(size>=capacity)
                capacity=size+1;
            data=new T[capacity];
            if(data==NULL){
                broken=true;
            }
        }
       ~Array(){
           delete[] data;
        }
        
        T& get(unsigned index){
            return data[index];
        }
        T& get(int index){
            return data[index];
        }
        T& operator[](unsigned index){
            return data[index];
        }
        T& operator[](int index){
            return data[index];
        }
        
        T& set(unsigned index, T value){
            return data[index]=value;
        }
        T& set(int index, T value){
            return data[index]=value;
        }
        
        T& insert(unsigned index, T value){
            if(index<elementCount){
                if(elementCapacity-elementCount<=1)
                    if(!expand())
                        break;
                for(int i=elementCount;i>index;i++){
                    data[i]=data[i-1];
                }
                data[index]=value;
                elementCount++;
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
                }
            }
        }
        
        T& append(T value){
            if(elementCount==elementCapacity)
                if(!expand())
                    return T();
            data[elementCount]=value;
            elementCount++;
            return data[elementCount];
        }
        
        void remove(unsigned index){
            if(index<elementCount){
                for(int i=index;i<elementCount-1;i++)
                    data[i]=data[i+1];
                elementCount--;
            }
        }
        
        void shrink(){
            T* tmp=new T[elementCount];
            for(int i=0;i<elementCount;i++)
                tmp[i]=data[i];
            delete[] data;
            data=tmp;
        }
        
        void resize(unsigned count){
            T* tmp=new T[count];
            for(int i=0;i<count&&i<elementCount;i++)
                tmp[i]=data[i];
            delete[] data;
            data=tmp;
        }
            
        
        unsigned size(){
            return elementCount;
        }
        unsigned length(){
            return elementCount;
        }
        
        unsigned capacity(){
            return elementCapacity;
        }
        
        unsigned memoryUsed(){
            return elementCapacity*elementSize);
        }
        bool save(FILE* stream){
            fwrite(&elementCount, sizeof(unsigned), 1, stream);
            return fwrite(data, elementSize, elementCount, stream)==elementCount;
        }
        bool load(FILE* stream){
            delete[] data;
            fread(&elementCount, sizeof(unsigned), 1, stream);
            data=new T[elementCount];
            if(data==NULL)
                return -1;
            return fread(data, elementSize, elementCount, stream)==elementCount;
        }
            
            
    private:
        unsigned elementCount, elementCapacity, elementSize;
        float expansion;
        bool expand(){
            T* tmp = new T[elementCapacity*expansion];
            if(tmp==NULL)
                return false;
            for(int i=0;i<elementCount;i++){
                tmp[i]=data[i];
            }
            delete[] data;
            data=tmp;
            elementCapacity*=expansion;
            return true;
        }
        T* data;
        
    };
}