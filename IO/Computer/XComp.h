/*********************************************************************************************
 *   Last Modified: Before                                                                   *
 *   Compilation Flags: -lX11                                                                *
 *                                                                                           *
 *   Links:                                                                                  *
 *   http://tronche.com/gui/x/xlib/                                                          *
 *   (Screenshot code temporarily taken from)                                                *
 *   http://stackoverflow.com/questions/8249669/how-do-take-a-screenshot-correctly-with-xlib *
 *                                                                                           *
 *********************************************************************************************/

#ifndef XCOMP
#define XCOMP

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <png.h>

class XComp {
public:
    XComp();
   ~XComp();
    void mouseMove(int x, int y);
    void click();
    void rightClick();
    void mouseClick();
    void mouseClick(int button);
    void mousePress();
    void mousePress(int button);
    void mouseRelease();
    void mouseRelease(int button);
    
    void scrollUp();
    void scrollDown();
    void mousePaste();
    
    void type(const char* keys);
    void typeSlowly(const char* keys, int delay);
    void type(int keycode);
    void type(int keycode, int modifiers);
    void keyPress(int keycode);
    void keyPress(int keycode, int modifiers);
    void keyRelease(int keycode);
    void keyRelease(int keycode, int modifiers);
    void writeScreenshot();
    
    int screenWidth();
    int screenHeight();
private:
    unsigned screenCount;
    Window root;
    Window inFocus;
    Display* display;
    XWindowAttributes gwa;
};

#endif