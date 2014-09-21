/**********************************************************************************************
 *   Last Modified: Before                                                                    *
 *   Compilation Flags: -lasound -lsndfile                                                    *
 *                                                                                            *
 *   Alsa project:                                                                            *
 *      http://www.alsa-project.org                                                           *
 *   Alsa help:                                                                               *
 *      http://www.alsa-project.org/alsa-doc/alsa-lib/                                        *
 *      http://www.alsa-project.org/main/index.php/DeviceNames                                *
 *      http://equalarea.com/paul/alsa-audio.html                                             *
 *      http://www.linuxjournal.com/article/6735                                              *
 *                                                                                            *
 *   Libsnd:                                                                                  * 
 *      http://www.mega-nerd.com/libsndfile/                                                  *
 *   Libsndhelp:                                                                              *
 *      http://parumi.wordpress.com/2007/12/16/how-to-write-wav-files-in-c-using-libsndfile/  *
 *                                                                                            *
 **********************************************************************************************/

#ifndef MOUTH
#define MOUTH

#include <alsa/asound.lib.h>

class Mouth {
public:
    Mouth();
   ~Mouth();
    void setChannelCount(int i);
    void setStereo();
    void setMono();
    void setSampleRate(unsigned rate);
    void setFormat(int format);
    void setFormat(snd_pcm_format_t format);
    void setDevice(string device);
    
    bool init();
        
    void close();
    
    snd_pcm_hw_params_t *params;
    string deviceName;
    int channelCount;
    unsigned sampleRate;
    snd_pcm_format_t audioFormat;
   
private:
    snd_pcm_t *capture_handle;
    bool broken;
    bool open;
    pthread_t *recording;
    struct ThreadClosure* tcl;
};