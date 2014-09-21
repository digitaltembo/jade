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

#ifndef EAR
#define EAR

#include <alsa/asoundlib.h>
#include <sndfile.hh>
#include <pthread.h>

class Ear {
public:
    Ear();
    Ear(int cCount, unsigned sRate, snd_pcm_format_t format);
   ~Ear();
    void setChannelCount(int i);
    void setStereo();
    void setMono();
    void setSampleRate(unsigned rate);
    void setFormat(int format);
    void setFormat(snd_pcm_format_t format);
    void setDevice(std::string device);
    
    bool init();
    
    int listen(void* buffer, int bufferLength); //populates array buffer, returns frames

    void startRecording(std::string title);
    void stopRecording();
        
    void close();
    
    snd_pcm_hw_params_t *params;
    std::string deviceName;
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

struct ThreadClosure {
    std::string title;
    Ear* ear;
};

#endif
    