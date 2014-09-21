#include <iostream>
#include "Dict.h"

int main(){
    Dictionary d;
    char s[256];
    cin >> s;
    while(!cin.eof()){
       d.set(s,(void*)((uintptr_t)d.get(s)+1));
       cin >> s;
    }
}