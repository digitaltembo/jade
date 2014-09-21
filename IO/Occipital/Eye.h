/****************************************************************************
 *   Last Modied: 7/26                                                      *
 *   Compilation Flags:                                                     *
 *   -I /usr/local/include/opencv                                           *
 *   -L /usr/local/lib -lopencv_core -lopencv_highgui                       *
 *                                                                          *
 *   Links:                                                                 *
 *   Docs:                                                                  *
 *      http://docs.opencv.org/                                             *
 *   OpenCV Download:                                                       *
 *      https://github.com/jayrambhia/Install-OpenCV/tree/master/Ubuntu     *
 *                                                                          *
 *    Simple wrapper for the OpenCV VideoCapture class                      *
 *                                                                          *
 ****************************************************************************/

#ifndef EYE
#define EYE

#include "opencv2/highgui/highgui.hpp"

class Eye{
public:
    Eye();
    Eye(int deviceNum);
    Eye(std::string filename);
   ~Eye();
    bool open();
    bool open(int deviceNum);
    bool open(std::string filename);
    void close();
    
    cv::Mat& get();
    
    bool isOpened();
    
    double getMillisPos();
    double getFramePos();
    double getFrameCount();
    double getAVIRatio(); //maps time from 0 at the begining to 1 at the end
    double getWidth();
    double getHeight();
    double getFPS();
    double getFourCC();
    std::string getFourCCString();
    double getExposure();
    
    double getBrightness();
    double getContrast();
    double getSaturation();
    double getHue();
    double getGain();
    
    
    bool setMillisPos(double m);
    bool setFramePos(double f);
    bool setAVIRatio(double r);
    bool setWidth(double w);
    bool setHeight(double h);
    bool setFPS(double fps);
    bool setFourCC(double c);
    bool setFourCCString(std::string c);
    bool setExposure(double e);
    
    bool setBrightness(double b);
    bool setContrast(double c);
    bool setSaturation(double s);
    bool setHue(double h);
    bool setGain(double g);
    
    bool setDefaults();
    
    bool opened;
private:
    cv::VideoCapture* vc;
    bool isFile;
    bool failed;
    cv::Mat img;
    cv::Mat empty;
};

#endif