/****************************************************************************
 *   Last Modified: Before                                                  *
 *   Compilation Flags: NA                                                  *
 *                                                                          *
 *   Just a speech-to-text type thing                                       *
 ****************************************************************************/
#ifndef WERNICKE
#define WERNICKE

#include <string>
#include "stdlib.h"

typedef void (*hearFunc)(std::string* s);

class Wernicke {
public:
    Wernicke(){}
   ~Wernicke(){}
    virtual bool startListening(hearFunc h) = 0;
    virtual void stopListening() = 0;
    virtual string getString(FILE* rawAudio) = 0;
private:
    hearFunc heard;
    bool listening;
};

#endif
    