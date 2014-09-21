/****************************************************************************
 *   Last Modified: 7/26                                                    *
 *   Compiler Tags: TODO                                                    *
 *                                                                          *
 *   Links:                                                                 *
 *   http://www.scribd.com/doc/53229744/Open-Frameworks-and-OpenCV          *
 ****************************************************************************/
#ifndef IMAGE_UTILS
#define IMAGE_UTILS

#include "opencv2/core/mat.hpp"
#include "openframeworks/graphics/ofImage.h" //how does this include work?

namespace jade {
    namespace convert {
        XImage* toXImage(cv::Mat m);
        
        Mat* toMat(ofImage& img);
        ofImage* toOfImage(Mat& mat);
    }
}

#endif