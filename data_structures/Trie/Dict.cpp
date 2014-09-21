#include "Dict.h"

Dictionary::Dictionary(){
    root = new Node;
    branches = BRANCHES;
    empty(root);
    nodes = 0;
}

void* Dictionary::get(void* key){
    char* cKey = (char*)key;
    Node* iter=root;
    while(*cKey != '\0'){
        int i = getBranch(*cKey);
        if(i==-1){
            cKey++;
        }else{
            iter=iter->children[i];
            if(iter==NULL)
                return NULL;
            cKey++;
        }
    }
    return iter->graph;
}
void* Dictionary::set(void* key, void* value){
    char* cKey = (char*)key;
    GraphNode* gValue = (GraphNode*)value;
    Node* iter=root;
    while(*cKey != '\0'){
        int i = getBranch(*cKey);
        if(i==-1){
            cKey++;
        }else{
            if(iter->children[i]==NULL){
                iter->children[i]=new Node;
                empty(iter->children[i]);
                nodes++;
            }
            iter=iter->children[i];
            cKey++;
        }
    }
    iter->graph=gValue;
    return (void*)gValue;
}

void* Dictionary::operator[](void* key){
    return get(key);
}
void Dictionary::remove(void* key){
    (void)key;
}

void Dictionary::save(){
}


uint64_t Dictionary::size(){
    return nodes*sizeof(Node);
}
uint64_t Dictionary::nodeCount(){
    return nodes;
}

int Dictionary::getBranch(char c){
    if(c >= 'a' && c <= 'z')
        return c-'a';
    if(c >= 'A' && c <= 'Z')
        return c-'A';
    switch(c){
        case ' ':
            return 26;
        case '\'':
            return 27;
        case '-':
            return 28;
    }
    return -1;
}

void Dictionary::empty(Node* node){
    for(int i=0; i<BRANCHES; i++)
        node->children[i] = NULL;
    node->graph = NULL;
}

// Memory
Dictionary::~Dictionary(){
    recursiveFree(root);
}

void Dictionary::recursiveFree(Node* node){
    for(int i=0; i<BRANCHES; i++)
        if(node->children[i]!=NULL)
            recursiveFree(node->children[i]);
    delete node;
    node = NULL;
}