/****************************************************************************
 *   Last Modified: Before                                                  *
 *   Compilation Flags:                                                     *
 *      -I/usr/include/festival/ -I/usr/include/speech_tools/               *
 *      -L/usr/lib ?? -l Festival ?? -L /usr/lib/speech_tools/lib/          *
 *      -l estools -l estbase -l eststring                                  *
 *                                                                          *
 *   Links:                                                                 *
 *   Download:                                                              *
 *      http://festvox.org/download.html                                    *
 *   Docs:                                                                  *
 *      http://festvox.org/docs/manual-1.4.3/festival_toc.html              *
 *      http://festvox.org/docs/speech_tools-1.2.0/book1.htm                *
 *          (for EST, which is a thing?)                                    *
 *   Voices:                                                                *
 *      http://festvox.org/dbs/index.html                                   *
 *      http://tcts.fpms.ac.be/synthesis/mbrola.html                        *
 *                                                                          *
 ****************************************************************************/

#ifndef FESTVOX
#define FESTVOX

#include <festival.h>
#include "VoiceBox.h"

#define VOICE_COUNT 22

class FestVox : public VoiceBox {
public:
    FestVox();
   ~FestVox();
    void say(char* s);
    void say(string s);
    void setVoice(int id);
    void setVoice(bool female, int id);
    int voiceCount();
    int voiceCount(bool female);
    
    enum Voice{
        Nun, //low quality
        Mary, //medium but slow
        Ela, //Slightly british high medium
        Mona, //Italian, medium
        Linka, //Czech, low medium
        Heidi, //Finnish, medium
        
        Adam, // low, very computer
        Mario, //Italian low medium,
        Earl, //English high
        Steve, //American, low, computer
        James, //English, high medium but more reliable than Earl ** BEST
        Bob, //Americanish, "
        Dave, //American, high low, computer
        George, //English, low high
        John, //English, high low, computer
        Joe, //American, medium
        Moe, //American, low, computer
        Fred, //American, low medium
        Vlad, //Russian, doesn't work?
        
        Marek, //Czech boy, medium
        Tomas, //Czech father, low medium
        Petr //Czech guy, low medium
    };
private:
    string voices[VOICE_COUNT];
    int femaleCount, maleCount;        
};

#endif
