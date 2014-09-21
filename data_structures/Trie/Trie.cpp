#include "Trie.h"

Trie::Trie(){
    root = new Node;
    branches = 0;
    empty(root);
    nodes = 0;
}

void* Trie::get(void* key){
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
void* Trie::set(void* key, void* value){
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

void* Trie::operator[](void* key){
    return get(key);
}
void Trie::remove(void* key){
    (void)key;
}

void Trie::save(){
}

uint64_t Trie::size(){
    return nodes*sizeof(Node);
}
uint64_t Trie::nodeCount(){
    return nodes;
}

int Trie::getBranch(char c){
    return -1;
}

void Trie::empty(Node* node){
    for(int i=0; i<branches; i++)
        node->children[i] = NULL;
    node->graph = NULL;
}
    
// Memory
Trie::~Trie(){
    recursiveFree(root);
}

void Trie::recursiveFree(Node* node){
    for(int i=0; i<branches; i++)
        if(node->children[i]!=NULL)
            recursiveFree(node->children[i]);
    delete node;
}