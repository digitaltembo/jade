#include "../IO/Command.h"

int main(){
    Command c;
    c.setAsync(true);
    string s="sleep 2; echo 'hi'";
    c.executeWithOutput(s);
    printf("Done!!");
    //c.wait();
    printf("Output: %s\n",c.getOutput().c_str());
    unsigned i=0, tickCount=0;
    while(!c.doneExecuting()){
        i++;
        if(i==0)
            tickCount++;
    }
    printf("%i, and %i and %s\n",i, tickCount, c.getOutput().c_str());
}