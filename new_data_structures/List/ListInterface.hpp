/*
 * Created: 8/15
 * Last Modified: 8/15
 */

#ifndef LIST_INTERFACE
#define LIST_INTERFACE

#include "MapInterface.hpp"

namespace jade {
    
    template<class T>
    class ListInterface : public MapInterface<int64_t, T> {
    public:
        ListInterface(){
        }
        virtual ~ListInterface(){
        }
        virtual T& push(T value) = 0;
        virtual T  pop() = 0;
        virtual T&  top() = 0;
        
        virtual int64_t find(T value) = 0;
        
        void remove(T value){
            remove(find(value));
        }
        
        int64_t size(){
            return elementCount;
        }
        
        int64_t length(){
            return elementCount;
        }
        
        int64_t memoryUsed(){
            return elementCount*elementSize;
        }
        
        int64_t elementCount, elementSize;
    };
}

#endif