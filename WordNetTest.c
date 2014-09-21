#include <stdio.h>
#include "wn.h"
#include "wngrind.h"
int main(){
    char a[30]="HELLO";
    wninit();
    while(gets(a)[0]!='.'){
        SynsetPtr s = findtheinfo_ds(a,NOUN, -HYPOPTR, 0);
        while(s!=NULL){
            int i,j;
            for(i=0,j=s->wcount;i<j;i++)
                printf("%s ", s->words[i]);
            printf("\nDef: %s\n\n",s->defn);
            s=s->ptrlist;
        }
    }
    return 0;
}