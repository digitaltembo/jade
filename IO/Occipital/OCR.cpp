#include "OCR.h"


OCR::OCR(){
    tess=new tesseract::TessBaseAPI();
    tess->Init(NULL, "eng");
    imagePix=NULL;
    imageSet=false;
}

OCR::OCR(std::string filename){
    tess=new tesseract::TessBaseAPI();
    tess->Init(NULL, "eng");
    imagePix=pixRead(filename.c_str());
    tess->SetImage(imagePix);
    imageSet=true;
}

OCR::OCR(cv::Mat m){
    tess=new tesseract::TessBaseAPI();
    tess->Init(NULL, "eng");
    imagePix=NULL;
    imageMat=m;
    tess->SetImage((uchar*)m.data, m.size().width, m.size().height, m.channels(), m.step1());
    imageSet=true;
}

std::string OCR::getText(){
    if(imageSet){
        return std::string(tess->GetUTF8Text());
    }else{
        return "";
    }
}

std::string OCR::getText(std::string filename){
    imagePix=pixRead(filename.c_str());
    tess->SetImage(imagePix);
    imageSet=true;
    return getText();
}
    
std::string OCR::getText(cv::Mat m){
    imageMat=m;
    tess->SetImage((uchar*)m.data, m.size().width, m.size().height, m.channels(), m.step1());
    imageSet=true;
    return getText();
}

OCR::~OCR(){
    if(imagePix!=NULL){
        pixDestroy(&imagePix);
    }
    tess->End();
}
    
    
    