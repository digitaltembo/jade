#include "../IO/Net.h"

int main(){
    Internet i;
    string s=i.load("http://www.freecarrierlookup.com/","cc=1&phonenum=8022335058&error=true&x=91&y=51");
    cout << s;
    return 0;
}
