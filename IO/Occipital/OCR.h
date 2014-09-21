/****************************************************************************
 *   Last Modified: 8/9                                                     *
 *   Compiler Flags: -ltesseract -llept -L /usr/local/lib -lopencv_core                                    *
 *                                                                          *
 *   Links:                                                                 *
 *   www.leptonica.org                                                      *
 *   code.google.com/p/tesseract-ocr/                                       *
 *   S^/questions/8115368/converting-cvmat-for-tesseract                    *
 ****************************************************************************/

#ifndef OCRECOG
#define OCRECOG

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "opencv2/core/core.hpp"

struct TextRect{
    int x, y, width, height;
    int confidence;
    std::string content;
};

class OCR{
public:
    OCR();
    OCR(std::string filepath);
    OCR(cv::Mat m);
   ~OCR();
    
    std::string getText();
    std::string getText(std::string filepath);
    std::string getText(cv::Mat m);
    
    std::vector<struct TextRect> getTextRects();
    std::vector<struct TextRect> getTextRects(std::string filepath);
    std::vector<struct TextRect> getTextRects(cv::Mat m);
    
    void setLang(std::string lang);
private:
    tesseract::TessBaseAPI* tess;
    bool imageSet;
    cv::Mat imageMat;
    PIX* imagePix;
};

#endif

    