#ifndef DICT
#define DICT

#include <cstddef>
#include <iostream>

#include "Trie.h"
#define BRANCHES 29

using namespace std;

typedef void GraphNode;

typedef struct DictNode{
    DictNode* children[BRANCHES];
    GraphNode* graph;
}DictNode;

class Dictionary: public Trie {
    typedef DictNode Node;
public:
    Dictionary();
    ~Dictionary();
    void* get(void* key);
    void* operator[](void* key);
    void* set(void* key, void* value);
    void remove(void* key);
    uint64_t size();
    uint64_t nodeCount();
    void save();
    void print(void (*print_func)(void*, void*)); 
private:
    int getBranch(char c);
    void empty(DictNode* node);
    void recursiveFree(DictNode* node);
    DictNode* root;
    uint64_t nodes;
    int branches;
};
#endif
