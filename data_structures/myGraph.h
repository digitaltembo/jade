#ifndef GRAPH
#define GRAPH

#define INIT_COUNT 5
#define EXPAND 2

using namespace std; 
typedef struct GraphNode Graphnode;

typedef struct Edge{
    short type;
    GraphNode* n;
}Edge;

struct GraphNode{
    Edge** parents, children;
    unsigned pCount, cCount, pCap, cCap;
    unsigned id;
    string name;
    void* content;
    short contentType;
}

class Graph {
public:
    Graph();
    ~Graph();
    GraphNode* add(string address);
    GraphNode* add(unsigned* address);
    GraphNode* find(string address);
    GraphNode* find(unsigned* address);
    GraphNode* merge(GraphNode* a, GraphNode* b);
private:
    GraphNode* newGraphNode(string name);
    GraphNode* newGraphNode(string name, int pCount, int cCount, int qCount);
    GraphNode* newGraphNode(string name, int pCount, int cCount, int qCount,
                            void* content, char contentType);
    GraphNode* findChild(GraphNode* node, string child);
    GraphNode* root;
    unsigned long long size;
}

#endif