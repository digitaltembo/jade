#include "Command.h"

using namespace std;

Command::Command(){
    isAsync=false;
    isExecuting=0;
    pthread_mutex_init(&myMutex, NULL);
    asyncCmd=new pthread_t;
}

Command::Command(const Command& toCopy){
    isAsync=false;
    isExecuting=0;
}

void Command::setAsync(bool async){
    isAsync=async;
}
    
int Command::execute(string s){
    isExecuting=1;
    if(isAsync){
        struct CommandClosure* cl=new struct CommandClosure;
        cl->toExecute=s.c_str();
        cl->data=NULL;
        cl->isExecuting=&isExecuting;
        cl->mutex=&myMutex;
        pthread_create(asyncCmd, NULL, asyncExecute, cl);
        return 0;
    }else{
        return system(s.c_str());
    }
}

void* Command::asyncExecute(void* cl){
    CClosure* c=(CClosure*)cl;
    system(c->toExecute);
    *(c->isExecuting)=0;
    return NULL;
}
int Command::executeWithInput(string s, string in){
    return executeWithInput(s, in, isAsync);
}

int Command::executeWithInput(string s, string in, bool isAsync){
    if(isAsync){
        struct CommandClosure* cl=new struct CommandClosure;
        input=in;
        writing=true;
        cl->toExecute=s.c_str();
        cl->data=&input;
        cl->isExecuting=&isExecuting;
       // cl->writing=&writing;
        cl->mutex=&myMutex;
        pthread_create(asyncCmd, NULL, asyncExecuteWithOutput, cl);
        return 0;
    }else{
        FILE* pipe = popen(s.c_str(), "r");
        if (!pipe) 
            return 1;
        fwrite(in.c_str(), sizeof(char), in.length(), pipe); 
        pclose(pipe);
        return 0;
    }
    return 0;
}

void* Command::asyncExecuteWithInput(void* cl){
    CClosure* c=(CClosure*)cl;
    string s(c->toExecute);
    FILE* pipe = popen(s.c_str(), "r");
    if (!pipe){
        *(c->isExecuting)=0;
        return NULL;
    }
    char buffer[128];
    pthread_mutex_lock(c->mutex);
    *(c->data)="";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
                c->data->append(buffer,128);
    }
    pclose(pipe);
    *(c->isExecuting)=0;
    pthread_mutex_unlock(c->mutex);
    
    return NULL;
}

string Command::executeWithOutput(string s){
    return executeWithOutput(s, isAsync);
}
string Command::executeWithOutput(string s, bool isAsync){
    isExecuting=1;
    if(isAsync){
        struct CommandClosure* cl=new struct CommandClosure;
        cl->toExecute=s.c_str();
        cl->data=&output;
        cl->isExecuting=&isExecuting;
        cl->mutex=&myMutex;
        pthread_create(asyncCmd, NULL, asyncExecuteWithOutput, cl);
        return "";
    }else{
        FILE* pipe = popen(s.c_str(), "r");
        if (!pipe){
            isExecuting=0;
            return "ERROR";
        }
        char buffer[128];
        string result = "";
        while(!feof(pipe)) {
            if(fgets(buffer, 128, pipe) != NULL)
                    result += buffer;
        }
        pclose(pipe);
        return result;
    }
}

void* Command::asyncExecuteWithOutput(void* cl){
    CClosure* c=(CClosure*)cl;
    string s(c->toExecute);
    FILE* pipe = popen(s.c_str(), "r");
    if (!pipe){
        *(c->isExecuting)=0;
        return NULL;
    }
    char buffer[128];
    pthread_mutex_lock(c->mutex);
    *(c->data)="";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
                c->data->append(buffer,128);
    }
    pclose(pipe);
    *(c->isExecuting)=0;
    pthread_mutex_unlock(c->mutex);
    
    return NULL;
}

void Command::wait(){
    if(isExecuting==1){
        pthread_join(*asyncCmd, NULL);
    }
}

string Command::getOutput(){
    return output;
}

bool Command::doneExecuting(){
    return isExecuting==0;
}
Command::~Command(){
    wait();
    delete asyncCmd;
}