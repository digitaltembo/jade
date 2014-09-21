/*
 * Created: 9/12
 * Last Modified: 9/12
 * Last Compiled: 9/12
 * 
 */

#ifndef JADE_DRAWER
#define JADE_DRAWER

#include "../new_data_structures/List/BoxedArray.hpp"

namespace jade {
    //TODO:
    template <class T>
    class Vec2{
        T t1, t2;
    };
    
    class Drawer{
    public:
        Drawer(){
        }
        virtual ~Drawer(){
        }
        
        virtual void background() = 0;
        virtual void background(int greyscale) = 0;
        virtual void background(int r, int g, int b) = 0;
        
        virtual void stroke() = 0;
        virtual void stroke(int greyscale) = 0;
        virtual void stroke(int r, int g, int b) = 0;
        virtual void fill() = 0;
        virtual void fill(int greyscale) = 0;
        virtual void fill(int r, int g, int b) = 0;
        
        virtual void noStroke() = 0;
        virtual void noFill() = 0;
        
        virtual void rect(int x, int y, int w, int height) = 0;
        virtual void tri(int x1, int y1, int x2, int y2, int x3, int y3) = 0;
        virtual void point(int x, int y) = 0;
        virtual void line(int x1, int y1, int x2, int y2) = 0;
        virtual void polygon(BoxedArray<Vec2<short> > points) = 0;
        virtual void polyline(BoxedArray<Vec2<short> > points) = 0;
        virtual void circle(int x, int y, int r) = 0;
        virtual void ellipse(int x, int y, int width, int height) = 0;
    private:
        bool isStroke, isFill;
    };
}

#endif
