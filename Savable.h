/* 
 * Created: Before
 * Last Modified: 8/16
 * Last Successfully Comiled: NA
 */
#ifndef SAVABLE
#define SAVABLE

#include <stdio.h>
#include <string>

template <class T>
struct Saver{
    bool (*save)(FILE* stream, T& obj) = NULL;
    T* (*load)(FILE* stream) = NULL;
};

class Savable{
public:
    virtual bool saveToStream(FILE* stream) = 0;
    
    bool saveToFile(std::string filename){
        FILE* fp=fopen(filename.c_str(), "w");
        if(fp==NULL)
            return false;
        bool saved=saveToStream(fp);
        fclose(fp);
        return saved;
    }
    
    bool saveToFile(char* filename){
        FILE* fp=fopen(filename, "w");
        if(fp==NULL)
            return false;
        bool saved=saveToStream(fp);
        fclose(fp);
        return saved;
    }
    
    
    virtual bool loadFromStream(FILE* stream) = 0;
    
    bool loadFromFile(std::string filename){
        FILE* fp=fopen(filename.c_str(), "r");
        if(fp==NULL)
            return false;
        bool loaded=loadFromStream(fp);
        fclose(fp);
        return loaded;
    }
    
    bool loadFromFile(char* filename){
        FILE* fp=fopen(filename, "r");
        if(fp==NULL)
            return false;
        bool loaded=loadFromStream(fp);
        fclose(fp);
        return loaded;
    }
};
#endif