/*
 * Last Modified: 8/14
 * Compiler Flags: (? -lopencv_core) -lopencv_highgui
 * 
 * Links:
 * docs.opencv.org/modules/highgui/doc/user_interface.html
 * 
 */

#ifndef SIMPLE_DISPLAY
#define SIMPLE_DISPLAY

#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <stdio.h>

class SimpleDisplay{
public:
    SimpleDisplay(int flags = CV_WINDOW_AUTOSIZE);
    SimpleDisplay(int width, int height, int flags = CV_WINDOW_NORMAL);
    SimpleDisplay(std::string name, int flags = CV_WINDOW_AUTOSIZE);
    SimpleDisplay(std::string name, int width, int height, int flags = CV_WINDOW_NORMAL);
   ~SimpleDisplay();
   
    bool show(cv::Mat& m);
    
    void moveWindow(int x, int y);
    void resizeWindow(int width, int height);
    
    void close();
    
private:
    bool open;
    int idInt;
    char id[4];
    static int displayCount;
    std::string name;
};

#endif
    