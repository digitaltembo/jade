/*
 * Last Modified: 8/13
 * Compiler Flags: -lzbar -lopencv_core -lopencv_imgproc
 *
 * Links:
 * zbar.sourceforge.net/api/index.html
 * blog.ayoungprogrammer.com/2013/07/tutorial-scanning-barcodes-qr-codes.html
*/

#ifndef ZIP_READER
#define ZIP_READER

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include "zbar.h"


struct ZipTextRect{
    cv::RotatedRect r;
    zbar::zbar_symbol_type_t type;
    std::string content;
};

class ZipReader{
public:
    ZipReader();
   ~ZipReader();
   
    std::vector<std::string> getStringValues(cv::Mat& m);
    std::vector<struct ZipTextRect> getZipCodes(cv::Mat& m);
    std::string getName(zbar::zbar_symbol_type_t t);
private:
    zbar::Image* image;
    zbar::ImageScanner scanner;
};

#endif
    
    
    
