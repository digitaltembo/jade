/**************************************************************************************************
 *   Last Modified: Before                                                                        *
 *   Compilation Falgs: None                                                                      *
 *                                                                                                *
 *   Links:                                                                                       *
 *      http://misc.flogisoft.com/bash/tip_colors_and_formatting                                  *
 *      http://stackoverflow.com/questions/1348563/clearing-output-of-a-terminal-program-linux-c-c*
 **************************************************************************************************/

#ifndef TERMINAL
#define TERMINAL

#include "stdio.h"
#include <string>

class Terminal{
public:
    typedef enum {
        BLACK=30, RED=31, GREEN=32, YELLOW=33, BLUE=34, MAGENTA=35, CYAN=36, LIGHT_GRAY=37, 
        DARK_GRAY=90, LIGHT_RED=91, LIGHT_GREEN=92, LIGHT_YELLOW=93, LIGHT_BLUE=94, LIGHT_MAGENTA=95,
        LIGHT_CYAN=96, WHITE=97
    } TerminalColor;
    Terminal();
   ~Terminal();
    void setDefault();
    
    void setTextColor(TerminalColor c);
    void setTextHighlite(TerminalColor c);
    void setTextColorAdvanced(int col);
    void setTextHighliteAdvanced(int col);
    
    void setBold();
    void unsetBold();
    void setDim();
    void unsetDim();
    void setUnderline();
    void unsetUnderline();
    void setBlink();
    void unsetBlink();
    void setInvert();
    void unsetInvert();
    
    void initAnimScreen(int w, int h);
    void setChar(int x, int y, char c);
    void setCharWithStyle(int x, int y, char c);
    void clearScreen();
    
    void draw();
    void clearTerminal();
    
    
    void print(int i);
    void print(float i);
    void print(std::string s);
    void print(char* c);
    void println(int i);
    void println(float f);
    void println(std::string s);
    void println(char* c);
    
    
private:
    char** screen;
    bool bold, dim, blink, invert;
    std::string color;
    int width, height;
};

#endif
    