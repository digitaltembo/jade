/***********************************************************
* Last Modified: 7/25                                      *
*                                                          *
* Test of Eye and FaceTracker                              *
***********************************************************/

#include "../IO/Occipital/FaceTracker.h"
#include "../IO/Occipital/Eye.h"
#include <iostream>
#include "../tools/TriangleImage.h"
#include "../IO/Occipital/FakeWebcam.h"

using namespace cv;
using namespace std;

void poly(Mat& img, vector<Point> points, Scalar c){
        const Point* p=&points[0];
        const int numPoints=points.size();
        fillPoly( img, &p, &numPoints,1, c);
}
        
    
int main(){
    Eye e(0);
        printf("%f x %f\n",e.getWidth(), e.getHeight());
    FaceTracker face;
    
    string window_name="Hi!!", window_2="helo??";
    namedWindow(window_name, CV_WINDOW_KEEPRATIO); 
    namedWindow(window_2, CV_WINDOW_KEEPRATIO);
        Mat m, f=imread("data/FaceDatabases/faces94/malestaff/doraj/doraj.6.jpg",CV_LOAD_IMAGE_COLOR);

    face.track(f);
    Mat fImg=face.getFaceImage(f);
    face.reset();
    
    FakeWebcam cam(640,480);
    
    TriangleImage t;
    TrianglePoints tps={{10,10,400,240,320,400}};
    TrianglePoints tps2={{0,400,320,0,640,400}};
    while(1){
        m=e.get();
        if(m.empty())
            break;
        face.track(m);
        poly(m,face.getFaceOutline(), Scalar(255,255,255));
        vector<Point> eyes=face.getEyes();
        poly(m, vector<Point>(&eyes[0], &eyes[6]), Scalar(0,0,0));
        poly(m, vector<Point>(&eyes[6], &eyes[12]), Scalar(0,0,0));
        vector<Point> mouth=face.getMouth();
        poly(m, vector<Point>(&mouth[0], &mouth[12]), Scalar(0,0,255));
        poly(m, vector<Point>(&mouth[12], &mouth[18]), Scalar(0,0,0));
        
        if(!face.isTracking())
            cout << "Hmph\n";
        //t.getImage(m, tps);
        imshow(window_2, fImg);
        cam.write(m);
        imshow(window_name,m);
        int c=waitKey(5);
        if(c==27){
            cam.close();
            break;
        }
    }
    return 0;
}
        