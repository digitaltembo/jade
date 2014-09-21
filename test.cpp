#include <iostream>
#include "Matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "IO/SphinxEar.h"
#include "IO/FestVox.h"
#include "IO/XComp.h"
#include "Matrix.h"
#include <math.h>
#include "IO/Ear.h"
#include "IO/Terminal.h"
#include <string>
#define SIZE 6
#define VOICES 8
using namespace std;
/*
const char* voices[] = {"(voice_cmu_us_jmk_arctic_clunits)", "(voice_rab_diphone)","(voice_cmu_us_rms_arctic_clunits)","(voice_kal_diphone)",
                    "(voice_cmu_us_clb_arctic_clunits)","(voice_cmu_us_awb_arctic_clunits)","(voice_ked_diphone)","(voice_cmu_us_slt_arctic_clunits)",
                    "(voice_cmu_us_bdl_arctic_clunits)","(voice_don_diphone)"};*/
const char* opts[SIZE] = {"God is dead.","Life is meaningless.","All is transe-ent.","Suffering is inevitable.",
                 "Everyone you know and love will die.", "The pain will never stop."};
FestVox* v;
string word;
void heard(string* s){
    printf("heard: %s\n", s->c_str());
    word = *s;
}
void testAuditory(){
    char s[256];
    SphinxEar ear;
    v=new FestVox();
    ear.startListening(*heard);
    word = "hello";
    while(gets(s)){
        if(s[0]=='.')
            break;
        v->say(word.c_str());
    }
}
void testX(){
    XComp x;
    x.mouseMove(600, 300);
    x.mouseClick();
    x.typeSlowly(" hello ", 100000);
    x.mouseRelease();
}

void matrix(){
    Matrix m(3,3);
    Matrix m2(3,3);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            m.set(i,j,rand()%100);
            m2.set(i,j,j+3);
        }
    }
    m.print();
    m.invert();
    m.print();
    m.invert();
    m.print();
}
void hearingTest(){
    Ear e(1, 16000, SND_PCM_FORMAT_S16_LE);
    e.init();
    e.startRecording("hello.wav");
    sleep(4);
    e.stopRecording();
}
void terminalTest(){
    Terminal t;
    t.println("hello");
    t.initAnimScreen(30,10);
    for(int i=0;i>-1;i++){
        t.setChar(i,i,' ');
        t.setChar(i+1, i+1,'*');
        
        usleep(100000);
        t.draw();
    }
        
}
int main(){
    //terminalTest();
    //hearingTest();
    //matrix();
    testX();
    //popen("firefox \"https://www.google.com/search?hl=en&site=imghp&tbm=isch&source=hp&bih=653&q=puppies&oq=puppies\"","r");
}









