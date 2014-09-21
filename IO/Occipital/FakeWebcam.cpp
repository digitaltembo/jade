#include "FakeWebcam.h"

using namespace cv;

FakeWebcam::FakeWebcam(){
}

FakeWebcam::FakeWebcam(int w, int h){
    init(w, h);
}

bool FakeWebcam::init(int w, int h){
    frameWidth=w;
    frameHeight=h;
    frameSize=w*h*3;
    fdwr = open("/dev/video1", O_RDWR);
    if(fdwr<0){
        fprintf(stderr,"Failed to open device\n");
        return false;
    }

    ret_code = ioctl(fdwr, VIDIOC_QUERYCAP, &vid_caps);
    if(ret_code == -1){
        fprintf(stderr, "Failed to do something or other\n");
        return false;
    }

    memset(&vid_format, 0, sizeof(vid_format));

    vid_format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    vid_format.fmt.pix.width = frameWidth;
    vid_format.fmt.pix.height = frameHeight;
    vid_format.fmt.pix.pixelformat = V4L2_PIX_FMT_BGR24;
    vid_format.fmt.pix.sizeimage = frameSize;
    vid_format.fmt.pix.field = V4L2_FIELD_NONE;
    vid_format.fmt.pix.bytesperline = frameWidth*3;
    vid_format.fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;
    ret_code = ioctl(fdwr, VIDIOC_S_FMT, &vid_format);
    if(ret_code == -1){
        fprintf(stderr, "Failed to do something or other again\n");
        return false;
    }
    initialized=true;
    return true;
}

bool FakeWebcam::write(Mat& m){
    if(!initialized)
        return false;
    if(frameHeight!=m.rows|| frameWidth!=m.cols)
        return false;
    ::write(fdwr, m.data, frameSize);
    return true;
}

void FakeWebcam::close(){
    if(initialized){
        pause();
        ::close(fdwr);
    }
}

FakeWebcam::~FakeWebcam(){
}
           
    
