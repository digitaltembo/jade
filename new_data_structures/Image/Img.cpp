#include "Img.h"

using namespace jade;

Img::Img(int width, int height, ImageFormat f){
    switch(f){
        case MONO:
            channels=1;
            size=width*height;
            data=new uint8_t[width*height];
            break;
        case RGB:
        case BGR:
            channels=3;
            break;
        case ARGB:
            channels=4;
            break;
    }
    size=width*height*channels;
    data=new uint8_t[size];
}

uint8_t* Img::operator[](int pos){
    return data+pos*channels;
}

uint8_t* Img::getPixel(int x, int y){
    return data+(y*width+x)*channels;
}

void Img::setPixel(int x, int y, uint8_t* pixel){
    uint8_t* pixPos=data+(y*width+x)*channels;
    for(int i=0;i<channels;i++){
        *pixPos=*pixel;
        pixPos++;
        pixel++;
    }
}
        

    
            
            