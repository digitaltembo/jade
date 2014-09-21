/****************************************************************************
 *   Last Modified: Before                                                  *
 *   Compilation Flags: NA                                                  *
 *                                                                          *
 *   Just a text-to-speech type thing                                       *
 ****************************************************************************/

#ifndef VOICEBOX
#define VOICEBOX

#include <string>

class VoiceBox{
public:
    VoiceBox(){}
   ~VoiceBox(){}
    virtual void say(char* s) = 0;
    virtual void say(std::string s) = 0;
    virtual void setVoice(int id) = 0;
    virtual void setVoice(bool female, int id) = 0;
    virtual int voiceCount() = 0;
    virtual int voiceCount(bool female) = 0;
private:
    char* voices[];
    int femaleVoiceCount;
    int maleVoiceCount;
};

#endif
    