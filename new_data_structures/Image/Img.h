/*
 * Created: 8/22
 * Last Modified: 9/8
 * Last Compiled: 9/8
 * 
 * Simple Image Class
 */

#ifndef JADE_IMG
#define JADE_IMG

#include <stdint.h>

namespace jade {
    
    typedef struct color_Mono{
        uint8_t c;
    } Color_Mono;
    
    typedef struct color_RGB{
        uint8_t red, green, blue;
    } Color_RGB;
    
    typedef struct color_ARGB{
        union {
            uint8_t c[4];
            int i;
        };
    } Color_ARGB;
    
    enum ImageFormat {
        MONO, RGB, BGR, ARGB
    };
    class Img{
    public:
        Img(int width, int height, ImageFormat f=RGB);
        Img(uint8_t* pix, int width, int height, ImageFormat f);
       ~Img();
        
        uint8_t* operator[](int pos);
        uint8_t* getPixel(int x, int y);
        void setPixel(int x, int y, uint8_t* pixel);
        
        int width, height, size;
        char format, channels;
        uint8_t* data;
    };
}

#endif