/****************************************************************************
 *   Last Modified: 8/8                                                     *
 *   Compiler Flags: Meh                                                    *
 *                                                                          *
 *   Links:                                                                 *
 *   Soooo many                                                             *
 ****************************************************************************/

#ifndef EMAIL
#define EMAIL

#include "../Computer/Command.h"

#include <string>

class Email{
public:
    Email();
   ~Email();
    
    void sendEmail(std::string toAddress, std::string content);
    void sendEmail(std::string toAddress, std::string subject, std::string content);
    
    Email& startMessage();
    Email& addContent(std::string s);
    Email& addReciever(std::string r);
    Email& addSubject(std::string s);
    void sendMessage();
    
private:
    std::string addresses, subject, content;
    Command c;
};

#endif

