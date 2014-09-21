/*
 * Created: 8/21
 * Last Modified: 9/8
 * Last Compiled: 9/8
 * 
 * Compiler Flags: -lX11 -lXext
 * 
 * Links:
 * http://www.x.org/releases/X11R7.6/
 * 
 */

#ifndef XWINDOW
#define XWINDOW

#include <stdint.h>
#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
#include <string>
#include <iostream>
#include <string.h>

#include "../../new_data_structures/Image/Img.h"
#include "../../tools/XDrawer.h"

struct XInputSimple{
    bool mousePressed, keyPressed;
    int mouseX, mouseY;
    unsigned key;
    char mouseButton;
    
    unsigned keyModifiers;
};

struct XInput{
    /* mouseClicked=mousePressed&!pMousePressed;
     * mouseReleased=pMousePressed&!mousePressed;
     */
    bool mousePressed, pMousePressed;
    int mouseX, mouseY;
    int pMouseX, pMouseY;
    char mouseButton;
    unsigned mouseModifiers;

    bool keyPressed, pKeyPressed;
    unsigned key;
    unsigned keyModifiers;
};

struct XListener{
    void (*mousePressed)();
    void (*mouseReleased)();
    void (*mouseDragged)();
    void (*mouseMoved)();
    
    void (*keyPressed)(unsigned key);
    void (*keyReleased)(unsigned key);
};

class XInputListener {
    void mousePressed() {};
    void mouseReleased() {};
    void keyPressed() {};
    void keyReleased() {};
};

class XWindow : private jade::Drawer{
public:
    XWindow(int width = 640, int height = 480);
    XWindow(Display *d, int width = 640, int height = 480);
   ~XWindow();
    
    void map();
    void unmap();
    void minimize();
    void maximize();
    void flush();
    void listen();
    void setupListener();
    void fullscreen();
    
    void setShape(Pixmap& x, int xOff=0, int yOff=0);
    void addShape(Pixmap& x, int xOff=0, int yOff=0);
    void subtractShape(Pixmap& x, int xOff=0, int yOff=0);
    void setShape(uint8_t* pixels, int width, int height, jade::ImageFormat f, int xOff=0, int yOff=0);
    void addShape(uint8_t* pixels, int width, int height, jade::ImageFormat f, int xOff=0, int yOff=0);
    void subtractShape(uint8_t* pixels, int width, int height, jade::ImageFormat f, int xOff=0, int yOff=0);
    void setShapeCircle();
    
    XImage* createXImage(jade::Img);
    XImage* createXImage(uint8_t* pixels, int width, int height, jade::ImageFormat f);
    Pixmap createPixmap(int width, int height, int depth=24); //TODO:is 24 correct?
    Pixmap createPixmap(uint8_t* pixels, int width, int height, jade::ImageFormat f);
    void freePixmap(Pixmap* pix);
    
    jade::XDrawer* getDrawer(Pixmap pix, int width, int height);
    jade::XDrawer* getDrawer();
    
    
    
    void setCursor(int c);
    
    void setTitle(std::string s);
    void setWindowTitle(std::string s);
    void setIconTitle(std::string s);
    
    void move(uint32_t x, uint32_t y);
    void resize(uint32_t w, uint32_t h);
    
    void moveToTop();
    void moveToBottom();
    
    void refreshDrawer();
    void background();
    void background(int greyscale);
    void background(int r, int g, int b);
    
    void stroke();
    void stroke(int greyscale);
    void stroke(int r, int g, int b);
    void fill();
    void fill(int greyscale);
    void fill(int r, int g, int b);
    
    void noStroke();
    void noFill();
    
    void rect(int x, int y, int width, int height);
    void tri(int x1, int y1, int x2, int y2, int x3, int y3);
    void point(int x, int y);
    void line(int x1, int y1, int x2, int y2);
    void polygon(jade::BoxedArray<jade::Vec2<short> > points);
    void polygon(jade::BoxedArray<jade::Vec2<short> > points, int shape=Complex);
    void polyline(jade::BoxedArray<jade::Vec2<short> > points);
    
    void circle(int x, int y, int r);
    void ellipse(int x, int y, int width, int height);
    
    void image(Pixmap p, int pixmap_width, int pixmap_height, int x, int y);
    
    
private:
    Display* d;
    Cursor cursor;
    Window w;
    int width, height, screen;
    
    struct XInput* in;
    struct XListener* listeners;
    XEvent* event;
    Pixmap pix, backgroundImg;
    unsigned long bg, fg;
    
    Colormap colormap;
    jade::XDrawer* drawer;
    
    
    
};

#endif