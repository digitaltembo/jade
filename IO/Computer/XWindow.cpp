#include "XWindow.h"

using namespace jade;

XWindow::XWindow(int width, int height){
    d=XOpenDisplay(NULL);
    screen=DefaultScreen(d);
    fg=WhitePixel(d, screen);
    bg=BlackPixel(d, screen);
    w = XCreateSimpleWindow(d, RootWindow(d, screen), 0,0, width, height, 1,
                            bg, fg);
    XSelectInput(d, w, StructureNotifyMask);
    this->width=width;
    this->height=height;
    in=NULL;
    colormap=XCreateColormap(d, w, DefaultVisual(d, screen), AllocNone);
    drawer=new XDrawer(d, w, colormap, width, height);
    map();  
}

XWindow::XWindow(Display* disp, int width, int height){
    d=disp;
    screen=DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, screen), 0,0, width, height, 1,
                            BlackPixel(d, screen), WhitePixel(d, screen));
    
    colormap=XCreateColormap(d, w, DefaultVisual(d, screen), AllocNone);
    drawer=new XDrawer(d, w, colormap, width, height);
    this->width=width;
    this->height=height;
    in=NULL;
    map();
}

void XWindow::background(){
    drawer->background();
}
    
void XWindow::background(int greyscale){ 
    drawer->background(greyscale);
}

void XWindow::background(int r, int g, int b){
    drawer->background(r, g, b);
}

void XWindow::noStroke(){
    drawer->noStroke();
}
void XWindow::stroke(){
    drawer->stroke();
}

void XWindow::stroke(int greyscale){
    drawer->stroke(greyscale);
}

void XWindow::stroke(int r, int g, int b){
    drawer->stroke(r, g, b);
}

void XWindow::noFill(){
    drawer->noFill();
}
void XWindow::fill(){
    drawer->fill();
}
void XWindow::fill(int greyscale){
    drawer->fill(greyscale);
}

void XWindow::fill(int r, int g, int b){
    drawer->fill(r, g, b);
}

void XWindow::rect(int x, int y, int width, int height){
    drawer->rect(x, y, width, height);
}

void XWindow::point(int x, int y){
    drawer->point(x, y);
}
void XWindow::line(int x1, int y1, int x2, int y2){
    drawer->line(x1, y1, x2, y2);
}
void XWindow::tri(int x1, int y1, int x2, int y2, int x3, int y3){
    drawer->tri(x1, y1, x2, y2, x3, y3);
}
void XWindow::polygon(BoxedArray<Vec2<short> > points){
    drawer->polygon(points);
}
void XWindow::polygon(BoxedArray<Vec2<short> > points, int shape){
    drawer->polygon(points, shape);
}
void XWindow::polyline(BoxedArray<Vec2<short> > points){
    drawer->polyline(points);
}
void XWindow::circle(int x, int y, int r){
    drawer->circle(x, y, r);
}
void XWindow::ellipse(int x, int y, int width, int height){
    drawer->ellipse(x, y, width, height);
}

void XWindow::image(Pixmap p, int pixmap_width, int pixmap_height, int x, int y){
    drawer->image(p,pixmap_width, pixmap_height, x, y);
}

void XWindow::map(){
    XMapWindow(d,w);
    
    for(;;) {
            XEvent e;
            XNextEvent(d, &e);
            if (e.type == MapNotify)
                  break;
      }
}

void XWindow::unmap(){
    XUnmapWindow(d,w);
}

void XWindow::minimize(){
    XIconifyWindow(d,w,screen);
}

void XWindow::maximize(){
    XClientMessageEvent ev;
    Atom prop;

    prop = XInternAtom(d, "WM_CHANGE_STATE", False);
    if(prop == None)
        return;
    ev.type = ClientMessage;
    ev.window = w;
    ev.message_type = prop;
    ev.format = 32;
    ev.data.l[0] = NormalState;
    XSendEvent(d, RootWindow(d, screen), False,
            SubstructureRedirectMask|SubstructureNotifyMask,
            (XEvent *)&ev);
}

void XWindow::fullscreen(){
    XEvent xev;
    Atom wm_state = XInternAtom(d, "_NET_WM_STATE", False);
    Atom fullscreen = XInternAtom(d, "_NET_WM_STATE_FULLSCREEN", False);

    memset(&xev, 0, sizeof(xev));
    xev.type = ClientMessage;
    xev.xclient.window = w;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 1;
    xev.xclient.data.l[1] = fullscreen;
    xev.xclient.data.l[2] = 0;

    XSendEvent(d, DefaultRootWindow(d), False,
    SubstructureNotifyMask, &xev);
}


void XWindow::move(uint32_t x, uint32_t y){
    XMoveWindow(d,w,x,y);
}

void XWindow::resize(uint32_t x, uint32_t y){
    XResizeWindow(d,w,x, y);
}

void XWindow::moveToTop(){
    XRaiseWindow(d, w);
}

void XWindow::moveToBottom(){
    XLowerWindow(d,w);
}

void XWindow::setCursor(int c){
    cursor=XCreateFontCursor(d,c);
    XDefineCursor(d,w,cursor);
    XFreeCursor(d, cursor);
}

void XWindow::setTitle(std::string s){
     const char* c=s.c_str();
    XSetIconName(d,w,c);
    XStoreName(d,w,c);
}

void XWindow::setWindowTitle(std::string s){
    XStoreName(d,w,s.c_str());
}

void XWindow::setIconTitle(std::string s){
    XSetIconName(d,w,s.c_str());
}
void XWindow::flush(){
    XFlush(d);
}

void XWindow::setShape(Pixmap& mask, int xOff, int yOff){
    XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, mask, ShapeSet);
    XShapeCombineMask(d, w, ShapeClip, xOff,yOff, mask, ShapeSet);
}

void XWindow::setShape(uint8_t* pixels, int width, int height, jade::ImageFormat f, int xOff, int yOff){
    switch(f){
        case jade::MONO:
            pix=XCreatePixmapFromBitmapData(d, w, (char*) pixels, width, height, bg, fg, 8);
            XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, pix, ShapeSet);
            XShapeCombineMask(d, w, ShapeClip, xOff,yOff, pix, ShapeSet);
            break;
        case jade::RGB: case jade::BGR:
            pix=XCreatePixmapFromBitmapData(d, w, (char*) pixels, width, height, bg, fg, 24);
            XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, pix, ShapeSet);
            XShapeCombineMask(d, w, ShapeClip, xOff,yOff, pix, ShapeSet);
            break;
        case jade::ARGB:
            pix=XCreatePixmapFromBitmapData(d, w, (char*) pixels, width, height, bg, fg, 32);
            XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, pix, ShapeSet);
            XShapeCombineMask(d, w, ShapeClip, xOff,yOff, pix, ShapeSet);
            break;
    }
}
        
void XWindow::addShape(Pixmap& mask, int xOff, int yOff){
    XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, mask, ShapeUnion);
    XShapeCombineMask(d, w, ShapeClip, xOff,yOff, mask, ShapeUnion);
}


void XWindow::addShape(uint8_t* pixels, int width, int height, jade::ImageFormat f, int xOff, int yOff){
    switch(f){
        case jade::MONO:
            pix=XCreatePixmapFromBitmapData(d, w, (char*) pixels, width, height, bg, fg, 8);
            XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, pix, ShapeUnion);
            XShapeCombineMask(d, w, ShapeClip, xOff,yOff, pix, ShapeUnion);
            break;
        case jade::RGB: case jade::BGR:
            pix=XCreatePixmapFromBitmapData(d, w, (char*) pixels, width, height, bg, fg, 24);
            XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, pix, ShapeUnion);
            XShapeCombineMask(d, w, ShapeClip, xOff,yOff, pix, ShapeUnion);
            break;
        case jade::ARGB:
            pix=XCreatePixmapFromBitmapData(d, w, (char*) pixels, width, height, bg, fg, 32);
            XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, pix, ShapeUnion);
            XShapeCombineMask(d, w, ShapeClip, xOff,yOff, pix, ShapeUnion);
            break;
    }
}

void XWindow::subtractShape(Pixmap& mask, int xOff, int yOff){
    XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, mask, ShapeSubtract);
    XShapeCombineMask(d, w, ShapeClip, xOff,yOff, mask, ShapeSubtract);
}

void XWindow::subtractShape(uint8_t* pixels, int width, int height, jade::ImageFormat f, int xOff, int yOff){
    switch(f){
        case jade::MONO:
            pix=XCreatePixmapFromBitmapData(d, w, (char*) pixels, width, height, bg, fg, 8);
            XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, pix, ShapeSubtract);
            XShapeCombineMask(d, w, ShapeClip, xOff,yOff, pix, ShapeSubtract);
            break;
        case jade::RGB: case jade::BGR:
            pix=XCreatePixmapFromBitmapData(d, w, (char*) pixels, width, height, bg, fg, 24);
            XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, pix, ShapeSubtract);
            XShapeCombineMask(d, w, ShapeClip, xOff,yOff, pix, ShapeSubtract);
            break;
        case jade::ARGB:
            pix=XCreatePixmapFromBitmapData(d, w, (char*) pixels, width, height, bg, fg, 32);
            XShapeCombineMask(d, w, ShapeBounding, xOff,yOff, pix, ShapeSubtract);
            XShapeCombineMask(d, w, ShapeClip, xOff,yOff, pix, ShapeSubtract);
            break;
    }
}

void XWindow::setShapeCircle(){
    int val=(height<width)?height:width;
    Pixmap shape_mask = XCreatePixmap (d,w,val,val, 1);
    GC shapeGC = XCreateGC (d, shape_mask, 0, NULL);

    /* erase the pixmap as a mask */
    XSetForeground (d, shapeGC, 0);
    XFillRectangle (d, shape_mask, shapeGC, 0,0, val,val);
    XSetForeground (d, shapeGC, 1);
    /* draw the bounding/clipping shape : a circle */
    XFillArc(d, shape_mask, shapeGC, 0,0, val,val, 0,23040);
    setShape(shape_mask);
}

void XWindow::refreshDrawer(){
    delete drawer;
    drawer=new XDrawer(d, w, colormap, width, height);
}
    

XImage* XWindow::createXImage(jade::Img i){
    XImage *x=XCreateImage(d, XDefaultVisual(d, 0) , i.channels*8, XYPixmap, 0, (char*)i.data, i.width, i.height, i.channels*8, 0);
    return x;
}

Pixmap XWindow::createPixmap(int width, int height, int depth){
    Pixmap p;
    return XCreatePixmap(d, w, width, height, depth);
}

XDrawer* XWindow::getDrawer(){
    return drawer;
}

XDrawer* XWindow::getDrawer(Pixmap pix, int width, int height){
    return new XDrawer(d, pix,colormap, width, height);
}

void XWindow::setupListener(){
    in=new XInput;
    XSelectInput(d, w, KeyPressMask | KeyRelease | ButtonPressMask |
                       ButtonReleaseMask | PointerMotionMask | StructureNotifyMask);
    event=new XEvent;
}
void XWindow::listen(){
    XNextEvent(d, event);
    switch(event->type){
        case ButtonPress:
            in->pMousePressed=in->mousePressed;
            in->mousePressed=true;
            in->pMouseX=in->mouseX;
            in->pMouseY=in->mouseY;
            
            if(!in->pMousePressed&&listeners->mousePressed!=NULL){
                listeners->mousePressed();
            }
            
            if(listeners->mouseMoved!=NULL&(in->mouseX-in->pMouseX!=0||in-in->mouseY-in->pMouseY!=0)){
                listeners->mouseMoved;
            }
            break;
    }
}
    
    
    
    
XWindow::~XWindow(){
}