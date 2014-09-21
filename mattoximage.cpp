/**
* This is the function to demonstrate the conversion cv::Mat to XImage
* @param ximage the X image object
* @param display the X display, for init see main() below
* @param screen the X screen, for init see main() below
* @return
*/
bool matToXImage(cv::Mat& im, XImage* ximage, Window& win, Display& display, Screen& screen)
{
if (im.empty()) return false;
LOG_FIRST_N(INFO,1)
<< ", width " << ximage->width
<< ", height " << ximage->width
<< ", offset " << ximage->xoffset
<< ", format " << ximage->format
<< ", byte_order " << ximage->byte_order
<< ", bitmap_unit " << ximage->bitmap_unit
<< ", bitmap_pad " << ximage->bitmap_pad
<< ", depth " << ximage->depth
<< ", bytes_per_line " << ximage->depth
<< ", bits_per_pixel " << ximage->bits_per_pixel
;
boost::timer t1;
XColor color;
LOG_FIRST_N(INFO,1) << im.cols << " " << im.rows << ", " << ximage->width << " " << ximage->height;
//cv::Mat tmp = cv::Mat(cv::Size(ximage.width, ximage.height), CV_8UC4);
if (screen.depths->depth == 24) {
LOG_FIRST_N(INFO,1) << "24-bit depth";
// Some of the following code is borrowed from http://www.roard.com/docs/cookbook/cbsu19.html ("Screen grab with X11" - by Marko Riedel, with an idea by Alexander Malmberg)
unsigned long rmask = screen.root_visual->red_mask,
gmask = screen.root_visual->green_mask,
bmask = screen.root_visual->blue_mask;
unsigned long rshift, rbits, gshift, gbits, bshift, bbits;
//unsigned char colorChannel[3];
rshift = 0;
rbits = 0;
while (!(rmask & 1)) {
rshift++;
rmask >>= 1;
}
while (rmask & 1) {
rbits++;
rmask >>= 1;
}
if (rbits > 8) {
rshift += rbits - 8;
rbits = 8;
}
gshift = 0;
gbits = 0;
while (!(gmask & 1)) {
gshift++;
gmask >>= 1;
}
while (gmask & 1) {
gbits++;
gmask >>= 1;
}
if (gbits > 8) {
gshift += gbits - 8;
gbits = 8;
}
bshift = 0;
bbits = 0;
while (!(bmask & 1)) {
bshift++;
bmask >>= 1;
}
while (bmask & 1) {
bbits++;
bmask >>= 1;
}
if (bbits > 8) {
bshift += bbits - 8;
bbits = 8;
}
LOG_FIRST_N(INFO,1)
<< "bshift " << bshift << " bbits " << bbits
<< ", gshift " << gshift << " gbits " << gbits
<< ", rshift " << rshift << " rbits " << rbits;
VLOG(4) << "matToXImage setup time " << t1.elapsed();
//boost::timer t2;
const int wd = ximage->width;
const int ht = ximage->height;
#if 0
for (unsigned int y = 0; y < ht; y++) {
for (unsigned int x = 0; x < wd; x++) {
//colorChannel[0] = ((color.pixel >> bshift) & ((1 << bbits) - 1)) << (8 - bbits);
//colorChannel[1] = ((color.pixel >> gshift) & ((1 << gbits) - 1)) << (8 - gbits);
//colorChannel[2] = ((color.pixel >> rshift) & ((1 << rbits) - 1)) << (8 - rbits);
//cv::Vec4b col = cv::Vec4b(colorChannel[0], colorChannel[1], colorChannel[0], 0);
cv::Vec4b col = im.at<cv::Vec4b> (y,x);
int b = col[0];
int g = col[1];
int r = col[2];
color.pixel = (r << rshift);
color.pixel |= (b << bshift);
color.pixel |= (g << gshift);
if (0) {
XPutPixel(ximage, x,y, color.pixel);
} else {
ximage->data[y * wd * 4 + x*4] = col[0];
ximage->data[y * wd * 4 + x*4+1] = col[1];
ximage->data[y * wd * 4 + x*4+2] = col[2];
}
//ximage->data[y * ximage->width + x*3+1] = col[1];
//if (ht < ht/4)
// ximage->data[y * wd + x] = color.pixel;
//ximage->data[y * wd + x] = col[0];
//ximage->data[y * ximage->width + x*3+1] = col[1];
//ximage->data[y * ximage->width + x*3+2] = col[2];
}
}
#else
// ximage->data = (char*) im.data;
memcpy(ximage->data, im.data, wd*ht*4);
#endif
VLOG(4) << "matToXImage put pixel time " << t1.elapsed();
LOG_FIRST_N(INFO,1) << "done copying mat";
} else { // Extremly slow alternative for non 24bit-depth
LOG_FIRST_N(INFO,1) <<" slow route TBD";
Colormap colmap = DefaultColormap(&display, DefaultScreen(&display));
for (unsigned int x = 0; x < ximage->width; x++) {
for (unsigned int y = 0; y < ximage->height; y++) {
color.pixel = XGetPixel(ximage, x, y);
XQueryColor(&display, colmap, &color);
cv::Vec4b col = cv::Vec4b(color.blue, color.green, color.red,0);
im.at<cv::Vec4b> (y,x) = col;
}
}
}
return true;
}
