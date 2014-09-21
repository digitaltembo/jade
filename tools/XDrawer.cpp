#include "XDrawer.h"
using namespace jade;

XDrawer::XDrawer(Display* dpy, Drawable draw, Colormap cols, int wide, int high){
    isFill=false;
    isStroke=true;
    d=dpy;
    w=draw;
    width=wide;
    height=high;
    graphics=XCreateGC(d, w, 0, NULL);
    colormap = cols;
    fillCol=strokeCol=0;
}

XDrawer::XDrawer(Display* dpy, Drawable draw, int wide, int high){
    isFill=false;
    isStroke=true;
    d=dpy;
    w=draw;
    width=wide;
    height=high;
    graphics=XCreateGC(d, w, 0, NULL);
    colormap = XCreateColormap(d, w, DefaultVisual(d, 0), AllocNone);
    fillCol=strokeCol=0;
}


XDrawer::~XDrawer(){
    XFreeGC(d, graphics);
}

void XDrawer::setDefaultColors(){
    
    XColor c = {0,65535,65535,65535};
    XAllocColor(d, colormap, &c);
    fillCol=c.pixel;
    c.red=c.green=c.blue=0;
    XAllocColor(d, colormap, &c);
    strokeCol=c.pixel;
}

void XDrawer::background(){
    XSetForeground(d, graphics, fillCol);
    XFillRectangle(d, w, graphics, 0,0,width, height);
    XSetForeground(d, graphics, strokeCol);
}
    
void XDrawer::background(int greyscale){ 
    greyscale=greyscale << 8;
    XColor c = {0,greyscale, greyscale, greyscale};
    XAllocColor(d, colormap, &c);
    XSetForeground(d, graphics, c.pixel);
    XFillRectangle(d, w, graphics, 0,0,width, height);
    XSetForeground(d, graphics, strokeCol);
}

void XDrawer::background(int r, int g, int b){
    XColor c = {0,r << 8, g << 8, b << 8};
    XAllocColor(d, colormap, &c);
    XSetForeground(d, graphics, c.pixel);
    XFillRectangle(d, w, graphics, 0,0,width, height);
    XSetForeground(d, graphics, strokeCol);
}

void XDrawer::noStroke(){
    isStroke=false;
}
void XDrawer::stroke(){
    isStroke=true;
}

void XDrawer::stroke(int greyscale){ 
    isStroke=true;
    greyscale=greyscale << 8;
    XColor c = {0,greyscale, greyscale, greyscale};
    XAllocColor(d, colormap, &c);
    strokeCol=c.pixel;
    XSetForeground(d, graphics, c.pixel);
}

void XDrawer::stroke(int r, int g, int b){
    isStroke=true;
    XColor c = {0,r << 8, g << 8, b << 8};
    XAllocColor(d, colormap, &c);
    strokeCol=c.pixel;
    XSetForeground(d, graphics, c.pixel);
}

void XDrawer::allocatedStroke(XCol color){
    strokeCol=color;
}

void XDrawer::noFill(){
    isFill=false;
}
void XDrawer::fill(){
    isFill=true;
}
void XDrawer::fill(int greyscale){ 
    isFill=true;
    greyscale=greyscale << 8;
    XColor c = {0,greyscale, greyscale, greyscale};
    XAllocColor(d, colormap, &c);
    fillCol=c.pixel;
}

void XDrawer::fill(int r, int g, int b){
    isFill=true;
    XColor c = {0,r << 8, g << 8, b << 8};
    XAllocColor(d, colormap, &c);
    fillCol=c.pixel;
}

void XDrawer::allocatedFill(XCol color){
    fillCol=color;
    isFill=true;
}

void XDrawer::rect(int x, int y, int width, int height, XCol color){
    XSetForeground(d, graphics, color);
    XFillRectangle(d, w, graphics, x, y, width, height);
    XSetForeground(d, graphics, strokeCol);
}
void XDrawer::rect(int x, int y, int width, int height){
    if(isFill){
        XSetForeground(d, graphics, fillCol);
        XFillRectangle(d, w, graphics, x, y, width, height);
        XSetForeground(d, graphics, strokeCol);
    }
    if(isStroke){
        XDrawRectangle(d, w, graphics, x, y, width, height);
    }
}

void XDrawer::point(int x, int y){
    XDrawPoint(d, w, graphics, x, y);
}

void XDrawer::line(int x1, int y1, int x2, int y2){
    XDrawLine(d, w, graphics, x1, y1, x2, y2);
}

void XDrawer::polyline(BoxedArray<struct Vec2<short> > points){
    XDrawLines(d, w, graphics, (XPoint*)points.getRaw(), points.size(), CoordModeOrigin);
}

void XDrawer::polygon(BoxedArray<struct Vec2<short> > points){
    if(isFill){
        XSetForeground(d, graphics, fillCol);
        XFillPolygon(d, w, graphics, (XPoint*)points.getRaw(), points.size(), Complex, CoordModeOrigin);
        XSetForeground(d, graphics, strokeCol);
    }   
    if(isStroke){
        XDrawLines(d, w, graphics, (XPoint*)points.getRaw(), points.size(), CoordModeOrigin);
        XPoint* p1=(XPoint*) &points.top(), *p2=(XPoint*) &points[0];
        line(p1->x, p1->y, p2->x, p2->y);
    }
}

void XDrawer::polygon(BoxedArray<struct Vec2<short> > points, int shape){
    if(isFill){
        XSetForeground(d, graphics, fillCol);
        XFillPolygon(d, w, graphics, (XPoint*)points.getRaw(), points.size(), shape, CoordModeOrigin);
        XSetForeground(d, graphics, strokeCol);
    }   
    if(isStroke){
        XDrawLines(d, w, graphics, (XPoint*)points.getRaw(), points.size(), CoordModeOrigin);
        XPoint* p1=(XPoint*) &points.top(), *p2=(XPoint*) &points[0];
        line(p1->x, p1->y, p2->x, p2->y);
    }
}

void XDrawer::tri(int x1, int y1, int x2, int y2, int x3, int y3){
    XPoint* points=new XPoint[3];
    points[0].x=x1;points[0].y=y1;points[1].x=x2;points[1].y=y2;points[2].x=x3;points[2].y=y3;
    if(isFill){
        XSetForeground(d, graphics, fillCol);
        XFillPolygon(d, w, graphics, points, 3, Convex, CoordModeOrigin);
        XSetForeground(d, graphics, strokeCol);
    }   
    if(isStroke){
        XDrawLines(d, w, graphics, points, 3, CoordModeOrigin);
        XDrawLine(d, w, graphics, x1,y1,x3,y3);
    }
}
void XDrawer::circle(int x, int y, int r, XCol color){
    x-=r;
    y-=r;
    r*=2;
    XSetForeground(d, graphics, color);
    XFillArc(d, w, graphics, x, y, r, r, 0, 23040);
    XSetForeground(d, graphics, strokeCol);
}
    
void XDrawer::circle(int x, int y, int r){
    x-=r;
    y-=r;
    r*=2;
    if(isFill){
        XSetForeground(d, graphics, fillCol);
        XFillArc(d, w, graphics, x, y, r, r, 0, 23040);
        XSetForeground(d, graphics, strokeCol);
    }
    if(isStroke){
        XDrawArc(d, w, graphics, x, y, r, r, 0, 23040);
    }
}

void XDrawer::ellipse(int x, int y, int width, int height){
    if(isFill){
        XSetForeground(d, graphics, fillCol);
        XFillArc(d, w, graphics, x, y, width, height, 0, 5);
        XSetForeground(d, graphics, strokeCol);
    }
    if(isStroke){
        XDrawArc(d, w, graphics, x, y, width, height, 0, 5);
    }
}

void XDrawer::image(Pixmap p, int pixmap_width, int pixmap_height, int x, int y){
    XCopyArea(d, w,p, graphics, 0, 0, pixmap_width, pixmap_height, x, y);
}


void XDrawer::justTryThis(){
    XSetForeground (d, graphics, 0);
    XFillRectangle (d, w, graphics, 0,0, width, height);
    XSetForeground (d, graphics, 1);
    /* draw the bounding/clipping shape : a circle */
    XFillArc(d, w, graphics, 0,0, 400,400, 0,23040);
}