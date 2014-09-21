#include "Eye.h"

using namespace std;

Eye::Eye(){
    vc=NULL;
    opened=false;
    failed=false;
}
Eye::Eye(int deviceNum){
    vc=new cv::VideoCapture(deviceNum);
    opened=vc->isOpened();
    failed=!opened;
}
Eye::Eye(const std::string filename){
    vc=new cv::VideoCapture(filename);
    opened=vc->isOpened();
    failed=!opened;
}
        
bool Eye::open(){
    if(vc!=NULL)
        delete vc;
    vc=new cv::VideoCapture(0);
    opened=vc->isOpened();
    failed=!opened;
    return opened;
}
    
bool Eye::open(int deviceNum){
    if(vc!=NULL)
        delete vc;
    vc=new cv::VideoCapture(deviceNum);
    opened=vc->isOpened();
    failed=!opened;
    return opened;
}

bool Eye::open(std::string filename){
    if(vc!=NULL)
        delete vc;
    vc=new cv::VideoCapture(filename);
    opened=vc->isOpened();
    failed=!opened;
    return opened;
}

void Eye::close(){
    if(vc!=NULL)
        delete vc;
    vc=NULL;
}

cv::Mat& Eye::get(){
    if(!opened){
        if(failed)
            return empty;
        open();
        if(failed)
            return empty;
    }
   (*vc) >> img;
    return img;
}
    
bool Eye::isOpened(){
    return opened;
}

double Eye::getMillisPos(){
    return vc->get(CV_CAP_PROP_POS_MSEC);
}
double Eye::getFramePos(){
    return vc->get(CV_CAP_PROP_POS_FRAMES);
}
double Eye::getFrameCount(){
    return vc->get(CV_CAP_PROP_FRAME_COUNT);
}
double Eye::getAVIRatio(){ //maps time from 0 at the begining to 1 at the end
    return vc->get(CV_CAP_PROP_POS_AVI_RATIO);
} 
double Eye::getWidth(){
    return vc->get(CV_CAP_PROP_FRAME_WIDTH);
}
double Eye::getHeight(){
    return vc->get(CV_CAP_PROP_FRAME_HEIGHT);
}
double Eye::getFPS(){
    return vc->get(CV_CAP_PROP_FPS);
}
double Eye::getFourCC(){
    return vc->get(CV_CAP_PROP_POS_MSEC);
}
std::string Eye::getFourCCString(){
    union { int v; char c[5];} codec;
    codec.v=static_cast<int>(vc->get(CV_CAP_PROP_FOURCC));
    codec.c[4]='\0';
    std::string s(codec.c);
    return s;
}
double Eye::getBrightness(){
    return vc->get(CV_CAP_PROP_BRIGHTNESS);
}
double Eye::getContrast(){
    return vc->get(CV_CAP_PROP_CONTRAST);
}
double Eye::getSaturation(){
    return vc->get(CV_CAP_PROP_SATURATION);
}
double Eye::getHue(){
    return vc->get(CV_CAP_PROP_HUE);
}
double Eye::getGain(){
    return vc->get(CV_CAP_PROP_GAIN);
}
double Eye::getExposure(){
    return vc->get(CV_CAP_PROP_EXPOSURE);
}

bool Eye::setMillisPos(double m){
    return vc->set(CV_CAP_PROP_POS_MSEC, m);
}
bool Eye::setFramePos(double f){
    return vc->set(CV_CAP_PROP_POS_FRAMES,f);
}
bool Eye::setAVIRatio(double r){
    return vc->set(CV_CAP_PROP_POS_AVI_RATIO, r);
}
bool Eye::setWidth(double w){
    return vc->set(CV_CAP_PROP_FRAME_WIDTH, w);
}
bool Eye::setHeight(double h){
    return vc->set(CV_CAP_PROP_FRAME_HEIGHT, h);
}
bool Eye::setFPS(double fps){
    return vc->set(CV_CAP_PROP_FPS, fps);
}
bool Eye::setFourCC(double fps){
    return vc->set(CV_CAP_PROP_FPS, fps);
}
bool Eye::setFourCCString(std::string s){
    union { int v; char c[4];} codec;
    for(int i=0;i<4;i++)
        codec.c[i]=s.at(i);
    
    return vc->set(CV_CAP_PROP_FOURCC, static_cast<double>(codec.v));
}
bool Eye::setBrightness(double b){
    return vc->set(CV_CAP_PROP_BRIGHTNESS, b);
}
bool Eye::setContrast(double c){
    return vc->set(CV_CAP_PROP_CONTRAST, c);
}
bool Eye::setSaturation(double s){
    return vc->set(CV_CAP_PROP_SATURATION, s);
}
bool Eye::setHue(double h){
    return vc->set(CV_CAP_PROP_HUE, h);
}
bool Eye::setGain(double g){
    return vc->set(CV_CAP_PROP_GAIN, g);
}

bool Eye::setDefaults(){
    bool a=false;
    a|=setBrightness(.5);
    a|=setContrast(.5);
    a|=setSaturation(.5);
    a|=setHue(.5);
    a|=setGain(.5);
    return a;
}
bool Eye::setExposure(double e){
    return vc->set(CV_CAP_PROP_EXPOSURE, e);
}


Eye::~Eye(){
    if(vc!=NULL)
        delete vc;
}
    
