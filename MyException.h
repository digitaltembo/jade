#ifndef MY_EX
#define MY_EX

#include <exception>
#include <string>

using namespace std;

struct MyException : public exception
{
   string s;
   MyException(string ss){
       s=ss;
    }
   ~MyException() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};

#endif