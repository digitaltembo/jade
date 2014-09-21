#include "FaceTracker.h"

using namespace std;
using namespace cv;

FaceTracker::FaceTracker(){
    wFound=vector<int>(1);
    wFound[0]=7;
    wFailed=vector<int>(3);
    wFailed[0]=11;
    wFailed[1]=9;
    wFailed[2]=7;
    
    fpd=-1;
    nIter=5;
    clamp=3.0;
    fTol=0.01;
    check=false;
    customWindows=false;
    
    failed=true;
    scale=1.0;
    
    model.Load("data/FaceTracker/face2.tracker");
    tri=FACETRACKER::IO::LoadTri("data/FaceTracker/face.tri");
    con=FACETRACKER::IO::LoadCon("data/FaceTracker/face.con");
    
    face.resize(26); //points [0,25]
    nose.resize(10); //points [26,35]
    eyes.resize(12); //points [36,47] (first six, my right eye)
    mouth.resize(18); //points [48,65] (last six, inner mouth)
}

Mat FaceTracker::track(Mat img){
    if(scale !=1)
        resize(img, img, Size(scale*img.cols, scale*img.rows));
    cvtColor(img, grayImg, CV_BGR2GRAY);
    failed=model.Track(grayImg, 
                       (customWindows) ? wCustom : (failed) ? wFailed : wFound,
                       fpd, nIter, clamp, fTol, check);
    if(failed)
        reset();
    return model._shape;
}

Mat FaceTracker::getConnections(){
    return con;
}
Mat FaceTracker::getTriangles(){
    return tri;
}
Mat FaceTracker::getVisible(){
    return model._clm._visi[model._clm.GetViewIdx()];
}

void FaceTracker::reset(){
    model.FrameReset();
}

void FaceTracker::loadModel(char* fname){
    model.Load(fname);
}

bool FaceTracker::isTracking(){
    return !failed;
}
Mat& FaceTracker::drawPoints(Mat& img){
    return drawPoints(img,CV_RGB(255,0,0));
}

Mat& FaceTracker::drawPoints(Mat& img, Scalar c){
    Mat visi=model._clm._visi[model._clm.GetViewIdx()];
    Point p1; 
    int n=model._shape.rows/2;
    for(int i = 0; i < n; i++){    
        if(visi.at<int>(i,0) == 0)continue;
        p1 = Point(model._shape.at<double>(i,0),model._shape.at<double>(i+n,0));
        circle(img,p1,2,c);
    }
    return img;
}

Mat& FaceTracker::drawLines(Mat& img){
    return drawLines(img, CV_RGB(0,0,255));
}
Mat& FaceTracker::drawLines(Mat& img, Scalar c){
    Mat visi= model._clm._visi[model._clm.GetViewIdx()];
    Point p1, p2;
    int n=model._shape.rows/2;
    for(int i = 0; i < con.cols; i++){
        if(visi.at<int>(con.at<int>(0,i),0) == 0 ||
           visi.at<int>(con.at<int>(1,i),0) == 0)
            continue;
        p1 = Point(model._shape.at<double>(con.at<int>(0,i),0),
                    model._shape.at<double>(con.at<int>(0,i)+n,0));
        p2 = Point(model._shape.at<double>(con.at<int>(1,i),0),
                    model._shape.at<double>(con.at<int>(1,i)+n,0));
        line(img,p1,p2,c,1);
    }
    return img;
}

Mat& FaceTracker::drawTriangles(Mat& img){
    return drawTriangles(img, CV_RGB(0,0,0));
}
Mat& FaceTracker::drawTriangles(Mat& img, Scalar c){
    Point p1, p2;
    int n=model._shape.rows/2;
    Mat visi=model._clm._visi[model._clm.GetViewIdx()];
    for(int i = 0; i < tri.rows; i++){
        if(visi.at<int>(tri.at<int>(i,0),0) == 0 ||
        visi.at<int>(tri.at<int>(i,1),0) == 0 ||
        visi.at<int>(tri.at<int>(i,2),0) == 0)continue;
        p1 = Point(model._shape.at<double>(tri.at<int>(i,0),0),
                    model._shape.at<double>(tri.at<int>(i,0)+n,0));
        p2 = Point(model._shape.at<double>(tri.at<int>(i,1),0),
                    model._shape.at<double>(tri.at<int>(i,1)+n,0));
        line(img,p1,p2,c);
        p1 = Point(model._shape.at<double>(tri.at<int>(i,0),0),
                    model._shape.at<double>(tri.at<int>(i,0)+n,0));
        p2 = Point(model._shape.at<double>(tri.at<int>(i,2),0),
                    model._shape.at<double>(tri.at<int>(i,2)+n,0));
        line(img,p1,p2,c);
        p1 = Point(model._shape.at<double>(tri.at<int>(i,2),0),
                    model._shape.at<double>(tri.at<int>(i,2)+n,0));
        p2 = Point(model._shape.at<double>(tri.at<int>(i,1),0),
                    model._shape.at<double>(tri.at<int>(i,1)+n,0));
        line(img,p1,p2,c);
    }
    return img;
}
  
Mat& FaceTracker::draw(){
    if(grayImg.empty()||failed)
        return grayImg;
    drawTriangles(grayImg);
    drawLines(grayImg);
    drawPoints(grayImg);
    return grayImg;
}

Mat& FaceTracker::draw(Mat& img){
    if(failed)
        return img;
    drawTriangles(img);
    drawLines(img);
    drawPoints(img);
    return img;
}
Mat& FaceTracker::drawAndTrack(Mat& img){
    track(img);
    return draw(img);   
}

vector<Point> FaceTracker::getFaceOutline(){
    if(!failed){
        int id=model._clm.GetViewIdx();
        Point lastPoint(-1,-1);
        for(int i=0;i<17;i++){
            if(model._clm._visi[id].at<int>(i,0)==0){
                face[i]=lastPoint;
            }else{
                lastPoint=Point(model._shape.at<double>(i,0), 
                              model._shape.at<double>(i+TOTALFACEPOINTS,0));
                face[i]=lastPoint;
            }
        }
        for(int i=17;i<26;i++){
            if(model._clm._visi[id].at<int>(i,0)==0){
                face[42-i]=lastPoint;
            }else{
                lastPoint=Point(model._shape.at<double>(i,0), 
                              model._shape.at<double>(i+TOTALFACEPOINTS,0));
                face[42-i]=lastPoint;
            }
        }
        for(int i=0;i<26;i++){
            if(face[i].x==-1){
                face[i]=lastPoint;
            }else{
                break;
            }
        }
    }else{
        for(int i=0;i<26;i++){
            face[i]=Point(-1,-1);
        }
    }
    return face;
}

vector<Point> FaceTracker::getNose(){
    if(!failed){
        int id=model._clm.GetViewIdx();
        int off=26;
        Point lastPoint;
        for(int i=0;i<10;i++){
            if(model._clm._visi[id].at<int>(i+off,0)==0){
                nose[i]=lastPoint;
            }else{
                lastPoint=Point(model._shape.at<double>(i+off,0), 
                              model._shape.at<double>(i+off+TOTALFACEPOINTS,0));
                nose[i]=lastPoint;
            }
        
        }
    }else{
        for(int i=0;i<10;i++){
            nose[i]=Point(-1,-1);
        }
    }
    return nose;
}

vector<Point> FaceTracker::getEyes(){
    if(!failed){
        int id=model._clm.GetViewIdx();
        int off=36;
        Point lastPoint;
        for(int i=0;i<12;i++){
            if(model._clm._visi[id].at<int>(i+off,0)==0){
                eyes[i]=lastPoint;
            }else{
                lastPoint=Point(model._shape.at<double>(i+off,0), 
                              model._shape.at<double>(i+off+TOTALFACEPOINTS,0));
                eyes[i]=lastPoint;
            }
        
        }
    }else{
        for(int i=0;i<12;i++){
            eyes[i]=Point(-1,-1);
        }
    }
    return eyes;
}

vector<Point> FaceTracker::getMouth(){
    if(!failed){
        int id=model._clm.GetViewIdx();
        int off=48;
        Point lastPoint;
        for(int i=0;i<18;i++){
            if(model._clm._visi[id].at<int>(i+off,0)==0){
                mouth[i]=lastPoint;
            }else{
                lastPoint=Point(model._shape.at<double>(i+off,0), 
                              model._shape.at<double>(i+off+TOTALFACEPOINTS,0));
                mouth[i]=lastPoint;
            }
        }
    }else{
        for(int i=0;i<18;i++){
            mouth[i]=Point(-1,-1);
        }
    }
    return mouth;
}
                
Mat FaceTracker::getFaceImage(Mat& img){
    Mat mask(img.rows, img.cols, CV_8UC1);
    mask.setTo(0);
    getFaceOutline();
    const Point* p=&face[0];
    const int numPoints=face.size();
    int minX=10000, minY=10000, maxX=-10, maxY=-10;
    for(int i=0;i<numPoints;i++){
        if(face[i].x<minX)
            minX=face[i].x;
        if(face[i].y<minY)
            minY=face[i].y;
        if(face[i].x>maxX)
            maxX=face[i].x;
        if(face[i].y>maxY)
            maxY=face[i].y;
    }
    Rect roi(minX, minY, maxX-minX, maxY-minY);
    fillPoly(mask, &p, &numPoints, 1, Scalar(255, 255, 255));
    Mat faceImage(img.rows, img.cols, CV_8UC3);
    faceImage.setTo(255);
    img.copyTo(faceImage, mask);
    Mat croppedFaceImage=faceImage(roi);
    return croppedFaceImage;
}
        
            

void FaceTracker::setSearchWindowSizes(vector<int> sizes){
    customWindows=true;
    wCustom=sizes;
}

void FaceTracker::setDetectionFrequency(int frames){
    fpd=frames;
}


void FaceTracker::setOptimazationSteps(int steps){
    nIter=steps;
}

void FaceTracker::setClampingFactor(double clamping){
    clamp=clamping;
}

void FaceTracker::setConTolerance(double ct){
    fTol=ct;
}

void FaceTracker::setCheckTracking(bool fCheck){
    check=fCheck;
}

void FaceTracker::setScale(float s){
    scale=s;
}

FaceTracker::~FaceTracker(){
}



        
    