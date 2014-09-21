#include <iostream>
#include <stdio.h>
#include "data_structures/Trie/Dict.h"
#include "data_structures/List/LinkedList.h"
#include "data_structures/List/LinkedListTail.h"
#include "data_structures/List/Array.h"
#include "data_structures/BoolArray.h"

void spellCheck(){
    
    MapInterface* d = new Dictionary;
    char s[256];
    FILE* fp = fopen("/usr/share/dict/words","r");
    if(fp!=NULL){
        while(!feof(fp)){
            if(fgets(s,256,fp) != NULL){
                d->set(s,(void*)1);
            }
        }
    }
    fclose(fp);
    cout << "done" << endl;
    cout << d->nodeCount() << endl;        
    while(cin >> s){
        cout << ((d->get(s)==(void*)1)? "Yes\n":"No\n");
    }
}
void deleteString(void* s){
    delete (char*)s;
}
void list(){
    char s[20];
    Array l(sizeof(s), deleteString);
    l.append((char*)"hello!!");
    l.append((char*)"and");
    l.set((pint_t)1,(char*)"goodbye");
    for(unsigned i=0;i < l.nodeCount();i++)
        cout << (char*)l[i] << endl;
}

void boolean(){
    BoolArray a(10);
    int x;
    for(int i = 0;i<10;i++){
        cin>>x;
        a.set(i,x);
    }
    for(int i=0;i<10;i++){
        cout << a.get(i) << " ";
    }
    cout << endl;
}
    
int main(){
    //list();
    boolean();
}