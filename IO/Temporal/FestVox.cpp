#include "FestVox.h"

static string gVoices[VOICE_COUNT] = {"(voice_us1_mbrola)", "(voice_cmu_us_slt_arctic_clunits)","(voice_cmu_us_clb_arctic_clunits)",
                "(voice_lp_diphone)", "(voice_czech_dita)", "(voice_suo_fi_lj_diphone)",
                "(hy_fi_mv_diphone)", "(voice_pc_diphone)", "(voice_cmu_us_jmk_arctic_clunits)",
                "(voice_us3_mbrola)", "(voice_rab_diphone)", "(voice_cmu_us_rms_arctic_clunits)",
                "(voice_kal_diphone)", "(voice_cmu_us_awb_arctic_clunits)", "(voice_ked_diphone)",
                "(voice_cmu_us_bdl_arctic_clunits)", "(voice_us2_mbrola)", "(voice_don_diphone)",
                "(voice_msu_ru_nsh_clunits)", "(voice_czech_krb)", 
                "(voice_czech_machac)", "(voice_czech_ph)"};


              
              
FestVox::FestVox(){
    int heap_size = 310000;  // default scheme heap size
    int load_init_files = 1; // we want the festival init files loaded
    femaleCount = 7;
    maleCount = 15;
    festival_initialize(load_init_files,heap_size);
    for(int i=0;i<VOICE_COUNT;i++)
        voices[i] = gVoices[i];
}

FestVox::~FestVox(){
    festival_tidy_up();
    //delete[] voices;
}
void FestVox::say(char* s){
        festival_say_text(s);
}
void FestVox::say(string s){
        festival_say_text(s.c_str());
}
void FestVox::setVoice(int id){
    printf("%i and %s\n",id, voices[id%VOICE_COUNT].c_str());
    festival_eval_command(voices[id%VOICE_COUNT].c_str());
}
void FestVox::setVoice(bool female, int id){
    if(female)
        festival_eval_command(voices[id%femaleCount].c_str());
    else
        festival_eval_command(voices[id%maleCount+femaleCount].c_str());;
}
    
int FestVox::voiceCount(){
    return VOICE_COUNT;
}

int FestVox::voiceCount(bool female){
    return (female)?femaleCount : maleCount;
}