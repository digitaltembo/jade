#include "../IO/FestVox.h"
#include <cstdlib>
#include <unistd.h>
int main(int argc, char* argv[]){
    FestVox v;
    v.setVoice(FestVox::James);
    if(argc==3)
        v.say(argv[2]);
    else
        v.say("Tis a noble thought");
    return 0;
}
    