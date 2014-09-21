#include "TriangleImage.h"

TriangleImage::TriangleImage(){
}
TriangleImage::TriangleImage(Mat& mat, int x1, int y1, int x2, int y2, int x3, int y3){
    getImage(mat, x1, y1, x2, y2, x3, y3);
}
TriangleImage::TriangleImage(Mat& mat, TrianglePoints p){
    getImage(mat, p);
}
Mat& TriangleImage::getImage(){
    return img;
}

Mat& TriangleImage::getImage(Mat& mat, int x1, int y1, int x2, int y2, int x3, int y3){
    p.p[0]=x1;
    p.p[1]=y1;
    p.p[2]=x2;
    p.p[3]=y2;
    p.p[4]=x3;
    p.p[5]=x3;
    return getImage(mat);
}

Mat& TriangleImage::getImage(Mat& mat, TrianglePoints points){
    p=points;
    return getImage(mat);
}

Mat& TriangleImage::getImage(Mat& mat){
    getBoundingBox(p);
    
    for(int i=0;i<6;i+=2){
        p.p[i]-=boundingBox[0];
        p.p[i+1]-=boundingBox[1];
    }
    calculateStuff();
    img.create(boundingBox[2],boundingBox[3], CV_8UC4);
    
    uchar* pixelPtr = (uchar*)mat.data;
    int matY=boundingBox[1], matX;
    for(int y=0;y<img.rows;y++){
        matX=boundingBox[0];
        for(int x=0;x<img.cols;x++){
            if(inTriangle(x,y)){
                img.at<Vec4b>(x,y)=Vec4b(pixelPtr[matY + matX + 1],
                                         pixelPtr[matY + matX + 2],
                                         pixelPtr[matY + matX + 0],
                                         255);
            }else{
                img.at<Vec4b>(x,y)=Vec4b(255,255,255,0);
            }
            matX+=3;
        }
        matY+=mat.cols*3;
    }
    return img;
}

Mat& TriangleImage::drawImage(Mat& mat, int x1, int y1, int x2, int y2, int x3, int y3){
    TrianglePoints nTri={{x1,y1,x2,y2,x3,y3}};
    return drawImage(mat, nTri);
    
}
Mat& TriangleImage::drawImage(Mat& mat, TrianglePoints nTri){ 
    /* calculate affine transform */
    transform[0]=((float)(p.p[0]-p.p[2])*(nTri.p[1]-nTri.p[5])-(p.p[0]-p.p[4])*(nTri.p[1]-nTri.p[3]))/
                 ((nTri.p[0]-nTri.p[2])*(nTri.p[1]-nTri.p[5])-(nTri.p[0]-nTri.p[4])*(nTri.p[1]-nTri.p[3]));
    transform[1]=(((float)p.p[0]-p.p[2])*(nTri.p[0]-nTri.p[4])-(p.p[0]-p.p[4])*(nTri.p[0]-nTri.p[2]))/
                 ((nTri.p[1]-nTri.p[3])*(nTri.p[0]-nTri.p[4])-(nTri.p[1]-nTri.p[5])*(nTri.p[0]-nTri.p[2]));
    transform[2]=p.p[0]-transform[0]*nTri.p[0]-transform[1]*nTri.p[1];
    transform[3]=((float)(p.p[1]-p.p[3])*(nTri.p[1]-nTri.p[5])-(p.p[1]-p.p[5])*(nTri.p[1]-nTri.p[3]))/
                 ((nTri.p[0]-nTri.p[2])*(nTri.p[1]-nTri.p[5])-(nTri.p[0]-nTri.p[4])*(nTri.p[1]-nTri.p[3]));
    transform[4]=((float)(p.p[1]-p.p[3])*(nTri.p[0]-nTri.p[4])-(p.p[1]-p.p[5])*(nTri.p[0]-nTri.p[2]))/
                 ((nTri.p[1]-nTri.p[3])*(nTri.p[0]-nTri.p[4])-(nTri.p[1]-nTri.p[5])*(nTri.p[0]-nTri.p[2]));
    transform[5]=p.p[1]-transform[3]*nTri.p[0]-transform[4]*nTri.p[1];
    
    getBoundingBox(nTri);
    float nX, nY;
    Vec4b c;
    Vec3b c2;
    uchar* pixelPtr = (uchar*)mat.data;
    int matI=0;
    for(int y=boundingBox[1];y<boundingBox[1]+boundingBox[3];y++){
        for(int x=boundingBox[0];x<boundingBox[0]+boundingBox[2];x++){
            nX=(int)(transform[0]*x+transform[1]*y+transform[2]);
            nY=(int)(transform[3]*x+transform[4]*y+transform[5]);
            if(constrained(nX,nY)){
                c=img.at<Vec4b>(nX,nY);
                if(c[3]!=0){
                    pixelPtr[matI]=c[0];
                    pixelPtr[matI+1]=c[1];
                    pixelPtr[matI+2]=c[2];
                }
            }
            matI+=3;
        }
    }
    return mat;
}
bool TriangleImage::inTriangle(int x, int y){
    if(positive){
        s=(vals[0]+vals[1]*x+vals[2]*y);
        t=(vals[3]+vals[4]*x+vals[5]*y);
        return s>0 && t>0&&(s+t)<twice_area;
    }else{
        s=-(vals[0]+vals[1]*x+vals[2]*y);
        t=-(vals[3]+vals[4]*x+vals[5]*y);
        return s>0 && t>0&&(s+t)<-twice_area;
    }
}

void TriangleImage::calculateStuff(){
    twice_area = (-p.p[3] * p.p[4] + p.p[1] * (-p.p[2] + p.p[4]) + p.p[0] * (p.p[3] - p.p[5]) + p.p[2] * p.p[5]);
    positive=(twice_area>=0);
    vals[0]=p.p[1] * p.p[4] - p.p[0] * p.p[5];
    vals[1]=p.p[5] - p.p[1];
    vals[2]=p.p[0] - p.p[4];
    vals[3]=p.p[0] * p.p[3] - p.p[1] * p.p[2];
    vals[4]=p.p[1] - p.p[3];
    vals[5]=p.p[2] - p.p[0];
    
}
void TriangleImage::getBoundingBox(TrianglePoints points){
    if(points.p[0]<points.p[2]){
        if(points.p[0]<points.p[4]){
            boundingBox[0]=points.p[0];
            if(points.p[2]<points.p[4]){
                boundingBox[2]=points.p[4];
            }else{
                boundingBox[2]=points.p[2];
            }
        }else{
            boundingBox[0]=points.p[4];
            boundingBox[2]=points.p[2];
        }
    }else{
        if(points.p[2]<points.p[4]){
            boundingBox[0]=points.p[2];
            if(points.p[0]<points.p[4]){
                boundingBox[2]=points.p[4];
            }else{
                boundingBox[2]=points.p[0];
            }
        }else{
            boundingBox[0]=points.p[4];
            boundingBox[2]=points.p[0];
        }
    }
    
    if(points.p[1]<points.p[3]){
        if(points.p[1]<points.p[5]){
            boundingBox[1]=points.p[1];
            if(points.p[3]<points.p[5]){
                boundingBox[3]=points.p[5];
            }else{
                boundingBox[3]=points.p[3];
            }
        }else{
            boundingBox[1]=points.p[5];
            boundingBox[3]=points.p[3];
        }
    }else{
        if(points.p[3]<points.p[5]){
            boundingBox[1]=points.p[3];
            if(points.p[1]<points.p[5]){
                boundingBox[3]=points.p[5];
            }else{
                boundingBox[3]=points.p[1];
            }
        }else{
            boundingBox[1]=points.p[5];
            boundingBox[3]=points.p[1];
        }
    }
    boundingBox[2]-=boundingBox[0];
    boundingBox[3]-=boundingBox[1];
}

bool TriangleImage::constrained(int x, int y){
    return x>=0 && x<img.cols && y>=0 && y<img.rows;
}
TriangleImage::~TriangleImage(){
}


    