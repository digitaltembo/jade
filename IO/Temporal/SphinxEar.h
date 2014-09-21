#ifndef SPHINX_EAR
#define SPHINX_EAR

#include <pocketsphinx.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/time.h>

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/cont_ad.h>

#include <string>

#include "Wernicke.h"

class SphinxEar : public Wernicke {
public:
    SphinxEar();
   ~SphinxEar();
    bool startListening(hearFunc h);
    void stopListening();
    string getString(FILE* rawAudio);
    void listenLoop();
private:
    hearFunc heard;
    pthread_t* listenThread;
    ps_decoder_t *ps;
    cmd_ln_t *config;
    bool listening;
};

#endif