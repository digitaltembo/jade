/*
 * Created: 8/17
 * Last Modified: 8/17
 * Last Compiled: Meh
 * 
 * Compiler flags: -lxcb
 * 
 * Links: 
 * http://www.x.org/releases/X11R7.6/
 * 
 */

#ifndef XWINDOW
#define XWINDOW

#include <xcb/xcb.h>

class XWindow{
public:
    XWindow(int width = 640, int height = 480);
    XWindow(xcb_connection_t *c,int width = 640, int height = 480);
    XWindow(xcb_connection_t *c, xcb_screen_t = NULL, int width = 640, int height = 480);
   ~XWindow();
    
    void map();
    void unmap();
private:
    xcb_connection_t *c;
    xcb_screen_t     *screen;
    xcb_window_t      win;
};

#endif
    
    