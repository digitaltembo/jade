#include <stdio.h>
#include "BitwiseArray.h"

int main(){
    BitwiseArray b(2,9);
    b.set(0,511);
    b.set(1, 131071);
    //b.expand(3);
    b.set(2, 510);
    printf("Look: %lu and %lu and %lu\n", b[0], b[1], b[2]);
    b.widen(17);
    b.set(1, 131071);
    printf("Look: %lu and %lu and %lu\n", b[0], b[1], b[2]);
    
}