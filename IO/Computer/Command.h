/**************************************************************************************************************
 *   Last Modified: 7/27                                                                                      *
 *   Compilation Flags: None                                                                                  *
 *                                                                                                            *
 *   Links:                                                                                                   *
 *   pthread tutorials:                                                                                       *
 *   http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html                                          *
 *   http://randu.org/tutorials/threads/                                                                      *
 *   simple execute:                                                                                          *
 *      http://stackoverflow.com/questions/9120596/run-a-program-in-linux-in-c-program                        *
 *   execute with output and easy input:                                                                      *
 *      http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c *
 **************************************************************************************************************/ 
#ifndef COMMAND
#define COMMAND

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <csignal>
#include <pthread.h>

class Command{
public:
    Command();
    Command(const Command& toCopy);
   ~Command();
    void setAsync(bool async);
    int execute(std::string s);
    int executeWithInput(std::string s, std::string input);
    int executeWithInput(std::string s, std::string input, bool isAsync);
    std::string executeWithOutput(std::string s);
    std::string executeWithOutput(std::string s, bool isAsync);
    
    bool doneExecuting();
    std::string getOutput();
    
    void wait();
private:
    pthread_mutex_t myMutex;
    bool isAsync;
    static void* asyncExecute(void* cl);
    static void* asyncExecuteWithInput(void* cl);
    static void* asyncExecuteWithOutput(void* cl);
    
    pthread_t* asyncCmd;
    
    volatile sig_atomic_t isExecuting, writing;
    std::string output, input;
};

typedef struct CommandClosure{
    const char* toExecute;
    std::string* data;
    volatile sig_atomic_t* isExecuting, writing;
    pthread_mutex_t* mutex;
} CClosure;

#endif
    