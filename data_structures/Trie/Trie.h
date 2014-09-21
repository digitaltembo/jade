#ifndef TRIE
#define TRIE

#include "MapInterface.h"

using namespace std;

typedef void GraphNode;

typedef struct TrieNode{
    TrieNode** children;
    GraphNode* graph;
}TrieNode;

class Trie: public MapInterface {
    typedef TrieNode Node;
public:
    Trie();
    ~Trie();
    void* get(void* key);
    void* operator[](void* key);
    void* set(void* key, void* value);
    void remove(void* key);
    uint64_t size();
    uint64_t nodeCount();
    void save();
private:
    int getBranch(char c);
    void empty(Node* node);
    void recursiveFree(Node* node);
    Node* root;
    uint64_t nodes;
    int branches;
};

#endif