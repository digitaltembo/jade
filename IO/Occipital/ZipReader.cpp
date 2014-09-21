#include "ZipReader.h"

ZipReader::ZipReader(){
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
    image=NULL;
}

std::vector<std::string> ZipReader::getStringValues(cv::Mat& m){
    if(image!=NULL)
        image->set_data(NULL, 0);
    image=new zbar::Image(m.cols, m.rows, "Y800", (uchar*)m.data, m.cols*m.rows);
    int n=scanner.scan(*image);
    std::vector<std::string> strings;
//     if(n==-1)
//         error
    if(n==-1||n==0)
        return strings;
    for(zbar::Image::SymbolIterator iter=image->symbol_begin(), last=image->symbol_end();
        iter!=last; ++iter){
        strings.push_back(iter->get_data());
    }
    return strings;
}
        
std::vector<struct ZipTextRect> ZipReader::getZipCodes(cv::Mat& m){
    if(image!=NULL)
        image->set_data(NULL, 0);
    image=new zbar::Image(m.cols, m.rows, "Y800", (uchar*)m.data, m.cols*m.rows);
    int n=scanner.scan(*image);
    std::vector<struct ZipTextRect> codes;
//     if(n==-1)
//         error
    if(n==-1||n==0)
        return codes;
    std::vector<cv::Point> vp(4);
    for(zbar::Image::SymbolIterator iter=image->symbol_begin(), last=image->symbol_end();
        iter!=last; ++iter){   
        int n = iter->get_location_size();  
        for(int i=0;i<n;i++){
            if(i<4)
                vp[i]=cv::Point(iter->get_location_x(i),iter->get_location_y(i));
            else
                vp.push_back(cv::Point(iter->get_location_x(i),iter->get_location_y(i))); 
        }  
        cv::RotatedRect r = cv::minAreaRect(vp);  
        struct ZipTextRect zipCode = {r, iter->get_type(), iter->get_data()};
        codes.push_back(zipCode);
        vp.resize(4);
    }
    return codes;
}

std::string ZipReader::getName(zbar::zbar_symbol_type_t t){
    return std::string(zbar::zbar_get_symbol_name(t));
}
        
    
ZipReader::~ZipReader(){
    if(image!=NULL)
        image->set_data(NULL, 0);
}
   
    
    std::vector<struct ZipTextRect> getZipCodes();