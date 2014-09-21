/*
 * Created: 8/23
 * Last Modified: 8/23
 * Last Compiled: 
 * 
 */

#ifndef BOOL_ARRAY
#define BOOL_ARRAY

#include "ListInterface.hpp"

namespace jade {
    static uint8_t TOP_MASKS[] = {128,192,224,240,248,252,254,255};
    static uint8_t BOTTOM_MASKS[] = {1,3,7,15,31,63,127,255};
    static uint8_t BIT_MASKS[] = {1,2,4,8,16,32,64,128};
    class BoolArray : ListInterfac<bool>{
        BoolArray(int64_t cap=1){
            capacity=size/8+1;
            elementCapacity=capacity*8;
            data=new uint8_t[capacity];
            if(data==NULL)
                elementCapacity=0;
            elementCount=0;
        }
        
       ~BoolArray(){
            delete[] data;
        }
        
        bool get(int64_t index){
            if(index>=elementCount){
                while(index>=elementCapacity)
                    if(!expand())
                        return false;
                elementCount=index+1;
            }
            
            return (data[index/8]>>index%8) & 1;
        }
        
        bool operator[](int64_t index){
            if(index>=elementCount){
                while(index>=elementCapacity)
                    if(!expand())
                        return false;
                elementCount=index+1;
            }
            
            return (data[index/8]>>(index%8)) & 1;
        }
        
        bool set(int64_t index, bool value){
            if(index>=elementCount){
                while(index>=elementCapacity)
                    if(!expand())
                        return false;
                elementCount=index+1;
            }
            data[index/8] |=(1 << (index%8));
            return value;
        }
            
        bool insert(int64_t index, bool value){
            if(index>=elementCount){
                while(index>=elementCapacity)
                    if(!expand())
                        return false;
                elementCount=index+1;
                data[index/8] |=(1 << (index%8));
                return value;
            }else{
                uint8_t offset=index%8;
                index/=8;
                uint8_t val=data[index];
                bool extra=(val&128)==0, tmpExtra;
                if(offset==0){
                    if(value)
                        data[index]=(val<<1)+1;
                    else
                        data[index]=(val<<1);
                }else{
                    if(value)
                        data[index]=(val&BOTTOM_MASKS[offset-1]) | BIT_MASKS[offset] | ((val&TOP_MASKS[7-offset])<<1);
                    else
                        data[index]=(val&BOTTOM_MASKS[offset-1]) | ((val&TOP_MASKS[7-offset])<<1);
                }
                index++;
                while(index<elementCount/8){
                    val=data[index];
                    tmpExtra=(val&128)==0;
                    if(extra)
                        data[index]=(val<<1)|1;
                    else
                        data[index]=(val<<1);
                    index++;
                }
                return value;
            }
        }
        
        bool append(bool value){
            if(elementCount==elementCapacity)
                if(!expand())
                    return false;
            if(value)
                data[elementCount/8]|=BIT_MASKS[elementCount%8];
            elementCount++;
        }
  
    