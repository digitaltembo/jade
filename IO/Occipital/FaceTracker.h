/****************************************************************************
 *   Last Modified: 7/25                                                    *
 *   Compiler Flags:                                                        *
 *   -I /usr/local/include/opencv                                           *
 *   -L /usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc      *
 *   -lopencv_objdetect                                                     *
 *                                                                          *
 *   Links:                                                                 *
 *   https://github.com/kylemcdonald/FaceTracker                            *
 *                                                                          *
 *   A thin wrapper for the FaceTracker library, created by Jason Mora      *
 *   Sagih and                                                              *
 *   maintained by Kyle McDonald. See any of the files in the enclosed      *
 *   FaceTracker folder for copywrite information.                          *
 ****************************************************************************/

#ifndef MY_FACETRACKER
#define MY_FACETRACKER

#include "FaceTrackerFiles/Tracker.h"
#include <opencv/highgui.h>
#include <vector>

#define TOTALFACEPOINTS 66

class FaceTracker{
public:
    FaceTracker();
   ~FaceTracker();
    
   /* returns points making up the face in a cv::Mat array
    */
    cv::Mat track(cv::Mat img);
    
    cv::Mat getTriangles();
    cv::Mat getConnections();
    cv::Mat getVisible();
    
    void reset();
    
    void loadModel(char* fname);
    
    bool isTracking();
    
    /* draws the tracking info either on the greyscale or the passed in image */
    cv::Mat& draw();
    cv::Mat& draw(cv::Mat& img);
    cv::Mat& drawAndTrack(cv::Mat& img);
    
    /*draws the stuff on the input image in the input color */
    cv::Mat& drawPoints(cv::Mat& img);
    cv::Mat& drawPoints(cv::Mat& img, cv::Scalar color);
    
    cv::Mat& drawLines(cv::Mat& img);
    cv::Mat& drawLines(cv::Mat& img, cv::Scalar color);
    
    cv::Mat& drawTriangles(cv::Mat& img);
    cv::Mat& drawTriangles(cv::Mat& img, cv::Scalar color);
    
    std::vector<cv::Point> getFaceOutline();
    std::vector<cv::Point> getEyes();
    std::vector<cv::Point> getNose();
    std::vector<cv::Point> getMouth();
    
    cv::Mat getFaceImage(cv::Mat& img);
    
    /* Sets list of search window sizes (from large to small
     */
    void setSearchWindowSizes(std::vector<int> sizes);
    
    /* Sets the number of frames between detections
     * A value of -1 indicates never, and is default
     */
    void setDetectionFrequency(int frames);
    
    /* Sets number of optimization steps to preform
     * default: 10
     */
    void setOptimazationSteps(int steps);
    
    /* Sets the shape model parameter clamping factor
     * default: 3
     */
    void setClampingFactor(double clamp);
    
    /* Sets convergence tolerance of optimization
     * default: 0.01
     */
    void setConTolerance(double ct);
    
    /* Sets whether to ensure tracking success
     * default: false
     * (True makes it very slow? and not very good?)
     */
    void setCheckTracking(bool check);
    
    void setScale(float s);
    
private:
    std::vector<int> wFound, wFailed, wCustom;
    int fpd;
    int nIter;
    double clamp;
    double fTol;
    float scale;
    bool failed;
    bool customWindows;
    bool check;
    
    
    FACETRACKER::Tracker model;
    cv::Mat tri, con, grayImg;
    std::vector<cv::Point> face, eyes, nose, mouth;
};

#endif