#include "SphinxEar.h"

#define MDIR "/usr/share/pocketsphinx/model"

using namespace std;

void* listen(void* ear){
    SphinxEar* s = (SphinxEar*)ear;
    s->listenLoop();
    return NULL;
}

SphinxEar::SphinxEar(){
    config = cmd_ln_init(NULL, ps_args(), TRUE,
                            "-hmm", MDIR "/hmm/wsj1",
                            "-lm", MDIR "/lm/wsj/wlist5o.3e-7.vp.tg.lm.DMP",
                            "-dict", MDIR "/lm/wsj/wlist5o.dic",
                            NULL);
    ps = ps_init(config);
    listenThread = NULL;
    listening = false;
}

SphinxEar::~SphinxEar(){
    stopListening();
    ps_free(ps);
}

bool SphinxEar::startListening(hearFunc h){
    if(listening)
        stopListening();
    heard = h;
    listenThread = new pthread_t;
    listening = pthread_create(listenThread, NULL, 
                                     listen, (void*)this) == 0;
    return listening;
}

void SphinxEar::stopListening(){
    if(listening){
        pthread_cancel(*listenThread);
        listenThread = NULL;
        listening = false;
    }
}

string SphinxEar::getString(FILE* rawAudio){
    return NULL;
}


/* Sleep for specified msec */
static void
sleep_msec(int32 ms)
{
    struct timeval tmo;

    tmo.tv_sec = 0;
    tmo.tv_usec = ms * 1000;

    select(0, NULL, NULL, NULL, &tmo);
}
void SphinxEar::listenLoop(){
    ad_rec_t *ad;
    int16 adbuf[4096];
    int32 k, ts, rem;
    char const *hyp;
    char const *uttid;
    cont_ad_t *cont;

    if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),
                          (int)cmd_ln_float32_r(config, "-samprate"))) == NULL)
        E_FATAL("Failed top open audio device\n");

    /* Initialize continuous listening module */
    if ((cont = cont_ad_init(ad, ad_read)) == NULL)
        E_FATAL("Failed to initialize voice activity detection\n");
    if (ad_start_rec(ad) < 0)
        E_FATAL("Failed to start recording\n");
    if (cont_ad_calib(cont) < 0)
        E_FATAL("Failed to calibrate voice activity detection\n");

    for (;;) {
        /* Indicate listening for next utterance */
        fflush(stdout);
        fflush(stderr);

        /* Wait data for next utterance */
        while ((k = cont_ad_read(cont, adbuf, 4096)) == 0)
            sleep_msec(100);

        if (k < 0)
            E_FATAL("Failed to read audio\n");

        /*
* Non-zero amount of data received; start recognition of new utterance.
* NULL argument to uttproc_begin_utt => automatic generation of utterance-id.
*/
        if (ps_start_utt(ps, NULL) < 0)
            E_FATAL("Failed to start utterance\n");
        ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        fflush(stdout);

        /* Note timestamp for this first block of data */
        ts = cont->read_ts;

        /* Decode utterance until end (marked by a "long" silence, >1sec) */
        for (;;) {
            /* Read non-silence audio data, if any, from continuous listening module */
            if ((k = cont_ad_read(cont, adbuf, 4096)) < 0)
                E_FATAL("Failed to read audio\n");
            if (k == 0) {
                /*
* No speech data available; check current timestamp with most recent
* speech to see if more than 1 sec elapsed. If so, end of utterance.
*/
                if ((cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
                    break;
            }
            else {
                /* New speech data received; note current timestamp */
                ts = cont->read_ts;
            }

            /*
* Decode whatever data was read above.
*/
            rem = ps_process_raw(ps, adbuf, k, FALSE, FALSE);

            /* If no work to be done, sleep a bit */
            if ((rem == 0) && (k == 0))
                sleep_msec(20);
        }

        /*
* Utterance ended; flush any accumulated, unprocessed A/D data and stop
* listening until current utterance completely decoded
*/
        ad_stop_rec(ad);
        while (ad_read(ad, adbuf, 4096) >= 0);
        cont_ad_reset(cont);
        fflush(stdout);
        /* Finish decoding, obtain and print result */
        ps_end_utt(ps);
        hyp = ps_get_hyp(ps, NULL, &uttid);
        (*heard)(new string(hyp));
        fflush(stdout);


        /* Resume A/D recording for next utterance */
        if (ad_start_rec(ad) < 0)
            E_FATAL("Failed to start recording\n");
    }

    cont_ad_close(cont);
    ad_close(ad);
}



        