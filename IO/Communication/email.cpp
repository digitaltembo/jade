#include "Email.h"

Email::Email(){
}

void Email::sendEmail(string toAddress, string subject, string content){
    c.execute("echo 'Subject: "+subject+"\r\n\r\n\r\n"+content+"\r\n' | esmtp "+toAddress);
}

Email::~Email(){
}
