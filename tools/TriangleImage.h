/*****************************************************************************************
 *   Last Modified 7/28                                                                  *
 *   Compilation flags: see rest of opencv                                               *
 *                                                                                       *
 *   Links:                                                                              *
 *   http://stackoverflow.com/questions/2049582/how-to-determine-a-point-in-a-triangle   *
 * http://stackoverflow.com/questions/7899108/opencv-get-pixel-information-from-mat-image*
 *   http://stackoverflow.com/questions/1114257/transform-a-triangle-to-another-triangle *
 *****************************************************************************************/

#ifndef TRIANGLE_IMAGE
#define TRIANGLE IMAGE

#include  "opencv2/core/core.hpp" 
#include "stdio.h"

using namespace cv;

typedef struct TrianglePoints{
    int p[6];
} TrianglePoints;

class TriangleImage{
public:
    TriangleImage();
    TriangleImage(Mat& mat, int x1, int y1, int x2, int y2, int x3, int y3);
    TriangleImage(Mat& mat, TrianglePoints p);
   ~TriangleImage();
   
    Mat& getImage();
    Mat& getImage(Mat& mat, int x1, int y1, int x2, int y2, int x3, int y3);
    Mat& getImage(Mat& mat, TrianglePoints p);
    Mat& drawImage(Mat& mat, int x1, int y1, int x2, int y2, int x3, int y3);
    Mat& drawImage(Mat& mat, TrianglePoints p);
private:
    TrianglePoints p;
    Mat img;
    int twice_area, s, t;
    bool positive;
    int vals[6];
    float transform[6];
    int boundingBox[4];
    Mat& getImage(Mat& mat);
    void getBoundingBox(TrianglePoints points);
    void calculateStuff();
    bool inTriangle(int x, int y);
    bool constrained(int x, int y);
};

#endif