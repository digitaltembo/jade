#include "SimpleDisplay.h"

int SimpleDisplay::displayCount = 0;

SimpleDisplay::SimpleDisplay(int flags){
    if(displayCount==999)
        displayCount=0;
    idInt=++displayCount;
    sprintf(id, "%d",idInt);
    name="Window " + std::string(id);
    cv::namedWindow(name, flags);
    open=true;
}

SimpleDisplay::SimpleDisplay(int width, int height, int flags){
    if(displayCount==999)
        displayCount=0;
    idInt=++displayCount;
    sprintf(id, "%d",idInt);
    name="Window " + std::string(id);
    cv::namedWindow(name, flags);
    resizeWindow(width, height);
    open=true;
}

SimpleDisplay::SimpleDisplay(std::string name, int flags){
    this->name=name;
    cv::namedWindow(name, flags);
    open=true;
}


SimpleDisplay::SimpleDisplay(std::string name, int width, int height, int flags){
    this->name=name;
    cv::namedWindow(name, flags);
    resizeWindow(width, height);
    open=true;
}

bool SimpleDisplay::show(cv::Mat& m){
    if(open){
        cv::imshow(name, m);
        int c=cv::waitKey(5);
        if(c==27)
            close();
    }
    return open;
}

void SimpleDisplay::moveWindow(int x, int y){
    if(open)
        cv::moveWindow(name, x, y);
}

void SimpleDisplay::resizeWindow(int width, int height){
    if(open)
        cv::resizeWindow(name, width, height);
}

void SimpleDisplay::close(){
    if(open){
        cv::destroyWindow(name);
        open=false;
    }
}

SimpleDisplay::~SimpleDisplay(){
    close();
}