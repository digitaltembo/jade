#include "ImageUtils.h"

using namespace jade::convert;


Mat* toMat(ofImage& img){
   return new Mat(cv::size(img.width, img.height),CV_8U3, img.getPixels());
}
ofImage* toOfImage(Mat& imgCV){
    ofImage* img=new ofImage();
    img->setFromPixels(imgCV.data, imgCV.cols, imgCV.rows, OF_IMAGE_COLOR);
    return img;
}