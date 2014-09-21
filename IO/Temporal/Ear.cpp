#include "Ear.h"

using namespace std;

Ear::Ear(){
    recording=NULL;
    channelCount=1;
    sampleRate=44100;
    
/*
 * Other possible formats, see:
 * http://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m.html#gaa14b7f26877a812acbb39811364177f8
 */
    audioFormat=SND_PCM_FORMAT_S16_LE;
    deviceName="default";
    broken=false;
}

Ear::Ear(int cCount, unsigned sRate, snd_pcm_format_t format){
    recording=NULL;
    channelCount=cCount;
    sampleRate=sRate;
/*    
 *  Other possible names, see:
 *  http://www.alsa-project.org/main/index.php/DeviceNames
 */
    deviceName="default";
/*
 * Other possible formats, see:
 * http://www.alsa-project.org/alsa-doc/alsa-lib/group___p_c_m.html#gaa14b7f26877a812acbb39811364177f8
 */
    audioFormat=format;
    broken=false;
}

void Ear::setChannelCount(int i){
    channelCount=i;
}
void Ear::setStereo(){
    channelCount=2;
}
void Ear::setMono(){
    channelCount=1;
}
void Ear::setSampleRate(unsigned rate){
    sampleRate=rate;
}
void Ear::setFormat(int format){
    audioFormat=(snd_pcm_format_t)format;
}
void Ear::setFormat(snd_pcm_format_t format){
    audioFormat=format;
}
void Ear::setDevice(string device){
    deviceName=device;
}

bool Ear::init(){
    int err;
    if ((err = snd_pcm_open(&capture_handle, (const char*)deviceName.c_str(), SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        fprintf (stderr, "cannot open audio device %s (%s)\n", 
            deviceName.c_str(),
            snd_strerror (err));
        broken=true;
        return false;
    }
    open=true;
    if ((err = snd_pcm_hw_params_malloc(&params)) < 0) {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
            snd_strerror (err));
        broken=true;
        return false;
    }
                        
    if ((err = snd_pcm_hw_params_any(capture_handle, params)) < 0) {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
            snd_strerror (err));
        broken=true;
        return false;
    }

    if ((err = snd_pcm_hw_params_set_access (capture_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf (stderr, "cannot set access type (%s)\n",
            snd_strerror (err));
        broken=true;
        return false;
    }

    if ((err = snd_pcm_hw_params_set_format (capture_handle, params, audioFormat)) < 0) {
        fprintf (stderr, "cannot set sample format (%s)\n",
            snd_strerror (err));
        broken=true;
        return false;
    }

    if ((err = snd_pcm_hw_params_set_rate(capture_handle, params, sampleRate, 0)) < 0) {
        fprintf (stderr, "cannot set sample rate (%s)\n",
            snd_strerror (err));
        broken=true;
        return false;
    }

    if ((err = snd_pcm_hw_params_set_channels (capture_handle, params, channelCount)) < 0) {
        fprintf (stderr, "cannot set channel count (%s)\n",
            snd_strerror (err));
        broken=true;
        return false;
    }

    if ((err = snd_pcm_hw_params (capture_handle, params)) < 0) {
        fprintf (stderr, "cannot set parameters (%s)\n",
            snd_strerror (err));
        broken=true;
        return false;
    }

    //snd_pcm_hw_params_free (params);
    
    if ((err = snd_pcm_prepare (capture_handle)) < 0) {
        fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
            snd_strerror (err));
        broken=true;
        return false;
    }
    return true;
}

int Ear::listen(void* buffer, int bufferLength){
    if(!broken){
        int err;
        if ((err = snd_pcm_readi(capture_handle, buffer, bufferLength)) < 0) {
            fprintf (stderr, "read from audio interface failed (%s)\n",
                snd_strerror (err));
            broken=true;
            return -1;
        }
        return err;
    }
    return -1;
}

void recordingLoopCleanup(void* buffer){
    short* buf=(short*)buffer;
    delete[] buf;
}
void* recordingLoop(void* closure){
    struct ThreadClosure* tcl=(struct ThreadClosure*)closure;
    Ear* ear=tcl->ear;
    int format=SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    SndfileHandle outfile(tcl->title, SFM_WRITE, format, ear->channelCount, ear->sampleRate);
    snd_pcm_uframes_t frames;
    snd_pcm_hw_params_get_period_size(ear->params, &frames, 0);
    int bufferSize=frames*(ear->channelCount);
    short* buffer=new short[bufferSize];
    pthread_cleanup_push(recordingLoopCleanup, buffer);
    while(true){
        ear->listen(buffer, bufferSize);
        outfile.write(buffer, bufferSize);
        //printf("listening!!!!\n");
    }
    pthread_cleanup_pop(0);
    return NULL;
}

void Ear::startRecording(string title){
    tcl=new struct ThreadClosure;
    tcl->title=title;
    tcl->ear=this;
    recording=new pthread_t;
    pthread_create(recording, NULL, recordingLoop, tcl);
    if(recording!=NULL){   
        pthread_detach(*recording);
    }
}

void Ear::stopRecording(){
    if(recording!=NULL){
        pthread_cancel(*recording);
    }
    delete tcl;
    delete recording;
    tcl=NULL;
    recording=NULL;
}

void Ear::close(){
    snd_pcm_hw_params_free(params);
    snd_pcm_drain(capture_handle);
    snd_pcm_close(capture_handle);
    snd_config_update_free_global();
    open=false;
}

Ear::~Ear(){
    if(tcl!=NULL)
        delete tcl;
    if(recording!=NULL)
        delete recording;
    if(open)
        close();
}


    