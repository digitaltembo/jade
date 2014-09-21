#include "../IO/Computer/XWindow.h"
#include <unistd.h>
#include <iostream>
#include <math.h>
using namespace std;
using namespace jade;
int main(){
    XWindow w(400,400);
    Pixmap p=w.createPixmap(400,400,1);
    w.move(200,200);
    w.flush();
    usleep(10000);
    w.background(255,0,0);
    w.fill(0,255,0);
    w.noStroke();
    w.rect(100,100,300,300);
    w.flush();
    cout << 1 << endl;
    while(1){}
    return 0;
}