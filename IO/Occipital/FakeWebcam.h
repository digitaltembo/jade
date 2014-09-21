/*****************************************************************************************
 *   Last Modified: 8/13                                                                 *
 *   Compiler Flags: ??                                                                  *
 *                                                                                       *
 *   Links:                                                                              *
 *   https://code.google.com/p/v4l2loopback/source/browse/test.c                         *
 *   http://answers.opencv.org/question/21876/opencv-capture-forward-to-v4l2-loopback/   *
 *****************************************************************************************/
#ifndef FAKE_WEBCAM
#define FAKE_WEBCAM

#include <fcntl.h>
#include <unistd.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include "opencv2/core/core.hpp"


class FakeWebcam{
public:
    FakeWebcam();
    FakeWebcam(int w, int h);
   ~FakeWebcam();
    
    bool init(int w, int h);
    bool write(cv::Mat& m);
    void close();
private:
    int frameWidth, frameHeight, frameSize;
    bool initialized;
    
    struct v4l2_capability vid_caps;
    struct v4l2_format vid_format;
    
    int fdwr, ret_code;

};

#endif
    
    
