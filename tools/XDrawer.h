/*
 * Created: 9/12
 * Last Modified: 9/12
 * Last Compiled: 9/12
 * 
 */

#ifndef JADE_XDRAWER
#define JADE_XDRAWER

#include <X11/Xlib.h>

#include "Drawer.h"

namespace jade {
    
    class XDrawer : private Drawer{
        
        typedef unsigned long XCol;
    public:
        
        XDrawer(Display* d, Drawable w, int wide, int high);
        XDrawer(Display* d, Drawable w, Colormap cols, int wide, int high);
       ~XDrawer();
        
        void setDefaultColors();
        void background();
        void background(int greyscale);
        void background(int r, int g, int b);
        
        void stroke();
        void stroke(int greyscale);
        void stroke(int r, int g, int b);
        void allocatedStroke(XCol color);
        void fill();
        void fill(int greyscale);
        void fill(int r, int g, int b);
        void allocatedFill(XCol color);
        
        void noStroke();
        void noFill();
        
        void rect(int x, int y, int w, int height);
        void rect(int x, int y, int w, int height, XCol color);
        void tri(int x1, int y1, int x2, int y2, int x3, int y3);
        void point(int x, int y);
        void line(int x1, int y1, int x2, int y2);
        void polygon(BoxedArray<Vec2<short> > points, int shape);
        void polygon(BoxedArray<Vec2<short> > points);
        void polyline(BoxedArray<Vec2<short> > points);
        
        void circle(int x, int y, int r);
        void circle(int x, int y, int r, XCol color);
        void ellipse(int x, int y, int width, int height);
    
        void image(Pixmap p, int pixmap_width, int pixmap_height, int x, int y);
        
        void justTryThis();
    private:
        Display* d;
        Drawable w;
        GC graphics;
        Colormap colormap;
        bool isStroke, isFill;
        XCol fillCol, strokeCol;
        int width, height;
        
    };
}

#endif
