#include "XComp.h"

XComp::XComp(){
    display = XOpenDisplay(0);
    screenCount = 0;
    if(display != NULL){
        root = DefaultRootWindow(display);
        XGetWindowAttributes(display, root, &gwa);
    }
}

XComp::~XComp(){
    if(display != NULL){
        XCloseDisplay(display);
        display = NULL;
    }
}
int XComp::screenWidth(){
    return gwa.width;
}
int XComp::screenHeight(){
    return gwa.height;
}
void XComp::mouseMove(int x, int y){
    if(display != NULL){
        XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
        XFlush(display);
    }
}

void XComp::click(){
    mouseClick(Button1);
}
void XComp::rightClick(){
    mouseClick(Button3);
}
void XComp::mouseClick(){
    mouseClick(Button1);
}
void XComp::mouseClick(int button){
    XEvent event;
    
    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);

    usleep(100000);

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);
}
void XComp::mousePaste(){
    mouseClick(Button3);
}

void XComp::scrollUp(){
    mouseClick(Button4);
}

void XComp::scrollDown(){
    mouseClick(Button5);
}
void XComp::mousePress(){
    mousePress(Button1);
}

void XComp::mouseRelease(){
    mouseRelease(Button1);
}

void XComp::mousePress(int button){
      XEvent event;
    
    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);
}

void XComp::mouseRelease(int button){      
    XEvent event;
    
    memset(&event, 0x00, sizeof(event));

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);
}
void XComp::type(const char* keys){
    for(int i=0;keys[i]!='\0';i++){
        if(keys[i] >= 'A' && keys[i] <= 'Z')
            type(keys[i]-'A'+'a', XK_Shift_L);
        else if(keys[i] == '\n')
                type(XK_KP_Enter, 0);
        else if(keys[i] == '?')
                type(XK_question, XK_Shift_L);
        else
            type((int)keys[i],0);
    }
}
void XComp::typeSlowly(const char* keys, int delay){
    for(int i=0;keys[i]!='\0';i++){
        if(keys[i] >= 'A' && keys[i] <= 'Z')
            type(keys[i]-'A'+'a', XK_Shift_L);
        else if(keys[i] == '\n')
                type(XK_KP_Enter, 0);
        else if(keys[i] == '?')
                type(XK_question, XK_Shift_L);
        else
            type((int)keys[i],0);
        usleep(delay);
    }
}
void XComp::type(int keycode){
    type(keycode, 0);
}
void XComp::type(int keycode, int modifiers){
    XKeyEvent event;
    event.display = display;
    int revert;
    XGetInputFocus(display, &inFocus, &revert);
    event.window = inFocus;
    event.root = root;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.same_screen = True;
    event.keycode     = XKeysymToKeycode(display, keycode);
    event.state       = modifiers;
    event.type = KeyPress;
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
    event.type = KeyRelease;
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
}
void XComp::keyPress(int keycode){
    keyPress(keycode,0);
}
void XComp::keyPress(int keycode, int modifiers){
    XKeyEvent event;
    event.display = display;
    int revert;
    //XGetInputFocus(display, &inFocus, &revert);
    event.window = root;
    event.root = root;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.same_screen = True;
    event.keycode     = XKeysymToKeycode(display, keycode);
    event.state       = modifiers;
    event.type = KeyPress;
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
}
void XComp::keyRelease(int keycode){
    keyRelease(keycode, 0);
}
void XComp::keyRelease(int keycode, int modifiers){
    XKeyEvent event;
    event.display = display;
    int revert;
    XGetInputFocus(display, &inFocus, &revert);
    event.window = inFocus;
    event.root = root;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.same_screen = True;
    event.keycode     = XKeysymToKeycode(display, keycode);
    event.state       = modifiers;
    event.type = KeyRelease;
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
}

void XComp::writeScreenshot(){
    XImage *image = XGetImage(display,root, 0,0 , gwa.width, gwa.height,AllPlanes, ZPixmap);
    FILE *fp;
    int code = 0;
    png_structp png_ptr;
    png_infop png_info_ptr;
    png_bytep png_row;

    // Open file
    char fName[20];
    sprintf(fName, "screen-%i.png",screenCount); 
    fp = fopen (fName, "wb");
    if (fp == NULL){
        fprintf (stderr, "Could not open file for writing\n");
        code = 1;
    }

    // Initialize write structure
    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL){
        fprintf (stderr, "Could not allocate write struct\n");
        code = 1;
    }

    // Initialize info structure
    png_info_ptr = png_create_info_struct (png_ptr);
    if (png_info_ptr == NULL){
        fprintf (stderr, "Could not allocate info struct\n");
        code = 1;
    }

    // Setup Exception handling
    if (setjmp (png_jmpbuf (png_ptr))){
        fprintf(stderr, "Error during png creation\n");
        code = 1;
    }

    png_init_io (png_ptr, fp);

    // Write header (8 bit colour depth)
    png_set_IHDR (png_ptr, png_info_ptr, gwa.width, gwa.height,
            8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    // Set title
    char *title = "Screenshot";
    if (title != NULL){
        png_text title_text;
        title_text.compression = PNG_TEXT_COMPRESSION_NONE;
        title_text.key = "Title";
        title_text.text = title;
        png_set_text (png_ptr, png_info_ptr, &title_text, 1);
    }

    png_write_info (png_ptr, png_info_ptr);

    // Allocate memory for one row (3 bytes per pixel - RGB)
    png_row = new png_byte[3*gwa.width];

    // Write image data
    int x, y;
    for (y = 0; y < gwa.height; y++){
        for (x = 0; x < gwa.width; x++){
            unsigned long pixel = XGetPixel (image, x, y);

            unsigned char blue = pixel & 0xFF;
            unsigned char green = (pixel & 0xFF00) >> 8; 
            unsigned char red = (pixel & 0xFF0000) >> 16;
            png_byte *ptr = &(png_row[x*3]);
            ptr[0] = red;
            ptr[1] = green;
            ptr[2] = blue;
        }
        png_write_row (png_ptr, png_row);
    }

    // End write
    png_write_end (png_ptr, NULL);

    // Free
    fclose (fp);
    if (png_info_ptr != NULL) png_free_data (png_ptr, png_info_ptr, PNG_FREE_ALL, -1);
    if (png_ptr != NULL) png_destroy_write_struct (&png_ptr, (png_infopp)NULL);
    if (png_row != NULL) delete[] (png_row);
    screenCount++;
}