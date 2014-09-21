/*
 * Created: 8/15
 * Last Modified: 8/15
 * Last Compiled: NA
 */

#ifndef MAP_INTERFACE
#define MAP_INTERFACE

#include <stdint.h>

#include "../../Savable.h"

namespace jade {
    template<class KEY, class VALUE>
    class MapInterface : public Savable{
    public:
        MapInterface(){
        }
        virtual ~MapInterface(){
        }
        
        virtual VALUE& get(KEY key) = 0;
        virtual VALUE& operator[](KEY key) = 0;
        
        virtual VALUE& set(KEY key, VALUE value) = 0;
        
        virtual VALUE& insert(KEY key, VALUE value) = 0;
        
        virtual VALUE& append(VALUE value) = 0;
        
        virtual void remove(KEY index) = 0;
        
        virtual KEY find(VALUE value) = 0;
        
        virtual int64_t size() = 0;
        
        virtual int64_t length() = 0;
        
        virtual int64_t memoryUsed() = 0;
        
        typedef int (*KeyCmpFunc)(KEY& k1, KEY& k2);
        typedef int (*ValueCmpFunc)(VALUE& v1, VALUE& v2);
        
        void setValueCompare(ValueCmpFunc v){
            valueCmp=v;
            valueCmpSet=true;
        }
        
        ValueCmpFunc valueCmp;
        bool valueCmpSet;
    };
}

#endif