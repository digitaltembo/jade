/*
 * Created: 8/15
 * Last Modified: 8/15
 * Last Compiled: NA
 */

#ifndef MAP_INTERFACE
#define MAP_INTERFACE

#include "../Savable.h"

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
        
        virtual unsigned size() = 0;
        
        virtual unsigned length() = 0;
        
        virtual unsigned memoryUsed() = 0;
        
        virtual bool save(FILE* stream) = 0;
        virtual bool load(FILE* stream) = 0;
    };
}

#endif