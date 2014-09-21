#include FaceTracker.h

FaceTracker::FaceTracker(){
    wFound[0]=7;
    wFailed[0]=11;
    wFailed[1]=9;
    wFailed[2]=7;
    
    fpd=-1;
    nIter=10;
    clamp=3.0;
    fTol=0.01;
    check=false;
    
    failed=true;
    
    model=FACETRACKER::Tracker("../data/FaceTracker/face2.tracker");
    Mat tri=FACETRACKER::IO::LoadTri("../data/FaceTracker/face.tri");
    Mat con=FACETRACKER::IO::LoadCon("../data/FaceTracker/face.conr");
    Mat grayImg;
}

Mat FaceTracker::track(Mat img){
    if(scale !=1)
        resize(img, img, Size(scale*img.cols, scale*img.rows));
    cvtColor(img, grayImg, CV_BGR2GRAY);
    failed=model.track(grayImg, 
                       (customWindows) ? wCustom : (failed) ? wFailed : wFound,
                       fpd, nIter, clamp, fTol, check);
    return model._shape;
}

Mat FaceTracker::getConections(){
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

Mat& FaceTracker::drawPoints(Mat& img, Mat& visi, Scalar c){
    Mat visi=model._clm._visi[model._clm.GetViewIdx()];
    Point p1; 
    for(i = 0; i < n; i++){    
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
    Mat visi= model._clm._visi[model._clm.GetViewIdx()]
    Point p1, p2;
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
    Mat visi=model._clm._visi[model._clm.GetViewIdx()];
    for(i = 0; i < tri.rows; i++){
        if(visi.at<int>(tri.at<int>(i,0),0) == 0 ||
        visi.at<int>(tri.at<int>(i,1),0) == 0 ||
        visi.at<int>(tri.at<int>(i,2),0) == 0)continue;
        p1 = Point(model._shape.at<double>(tri.at<int>(i,0),0),
                    model._shape.at<double>(tri.at<int>(i,0)+n,0));
        p2 = Point(model._shape.at<double>(tri.at<int>(i,1),0),
                    model._shape.at<double>(tri.at<int>(i,1)+n,0));
        line(image,p1,p2,c);
        p1 = Point(model._shape.at<double>(tri.at<int>(i,0),0),
                    model._shape.at<double>(tri.at<int>(i,0)+n,0));
        p2 = Point(model._shape.at<double>(tri.at<int>(i,2),0),
                    model._shape.at<double>(tri.at<int>(i,2)+n,0));
        line(image,p1,p2,c);
        p1 = Point(model._shape.at<double>(tri.at<int>(i,2),0),
                    model._shape.at<double>(tri.at<int>(i,2)+n,0));
        p2 = Point(model._shape.at<double>(tri.at<int>(i,1),0),
                    model._shape.at<double>(tri.at<int>(i,1)+n,0));
        line(image,p1,p2,c);
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

void FaceTracker::setSearchwindowSizes(vector<int> sizes){
    customWindows=true;
    wCustom=sizes;
}

void FaceTracker::setDetectionFrequency(int frames){
    fdp=frames;
}


void FaceTracker::setOptimazationSteps(int steps){
    nInter=steps;
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

FaceTracker::~Facetracker(){
}



        
    