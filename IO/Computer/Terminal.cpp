#include "Terminal.h"

using namespace std;

Terminal::Terminal(){
    screen=NULL;
    color="0";
    bold=dim=blink=invert=false;
}

void Terminal::setDefault(){
    printf("\e[0m");
}

void Terminal::setTextColor(TerminalColor c){
    printf("\e[%im",(int)c);
}
void Terminal::setTextHighlite(TerminalColor c){
    printf("\e[%im",(int)c+10);
}
void Terminal::setTextColorAdvanced(int c){
    printf("\e[38;5;%im",c);
}
void Terminal::setTextHighliteAdvanced(int c){
    printf("\e[48;5;%im",c);
}


void Terminal::setBold(){
    printf("\e[1m");
}
void Terminal::unsetBold(){
    printf("\e[21m");
}
void Terminal::setDim(){
    printf("\e[2m");
}
void Terminal::unsetDim(){
    printf("\e[22m");
}
void Terminal::setUnderline(){
    printf("\e[4m");
}
void Terminal::unsetUnderline(){
    printf("\e[24m");
}
void Terminal::setBlink(){
    printf("\e[5m");
}
void Terminal::unsetBlink(){
    printf("\e[25m");
}
void Terminal::setInvert(){
    printf("\e[7m");
}
void Terminal::unsetInvert(){
    printf("\e[27m");
}

void Terminal::initAnimScreen(int w, int h){
    screen=new char*[h];
    for(int i=0;i<h;i++){
        screen[i]=new char[w+1];
        for(int j=0;j<w;j++)
            screen[i][j]=' ';
        screen[i][w]='\0';
    }
    width=w;
    height=h;
}
void Terminal::setChar(int x, int y, char c){
    if(x>=0&&x<width&&y>=0&&y<height)
        screen[y][x]=c;
}
void Terminal::clearScreen(){
    for(int y=0;y<height;y++)
        for(int x=0;x<width;x++)
            screen[y][x]=' ';
}
    
void Terminal::draw(){
    clearTerminal();
    for(int y=0;y<height;y++){
        printf("%s\n",screen[y]);
    }
}

void Terminal::clearTerminal(){
    printf("\033[2J\033[1;1H");
}

void Terminal::print(int i){
    printf("%i",i);
}
void Terminal::print(float i){
    printf("%f\n",i);
}
void Terminal::print(string s){
    printf("%s", s.c_str());
}
void Terminal::print(char* c){
    printf("%s", c);
}
void Terminal::println(int i){
    printf("%i\n",i);
}
void Terminal::println(float f){
    printf("%f\n",f);
}
void Terminal::println(string s){
    printf("%s\n",s.c_str());
}
void Terminal::println(char* c){
    printf("%s\n",c);
}

Terminal::~Terminal(){
    setDefault();
    if(screen!=NULL){
        for(int y=0;y<height;y++){
            delete[] screen[y];
        }
        delete[] screen;
    }
}