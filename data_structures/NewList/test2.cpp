#include "test1.h"
#include <iostream>
template<class T>
class ListInterface : public MapInterface<unsigned, T>{
public:
    ListInterface(T obj){
        o=obj;
    }
    void hello(){
        std::cout << "hi!\n";
    }
    T maybeReturn(){
        return o;
    }
    T o;
};

int main(){
    std::cout << "hello world!\n";
    MapInterface<unsigned, std::string>* s=new ListInterface<std::string>("hi!!");
    std::cout << s->maybeReturn() << std::endl;
    
}