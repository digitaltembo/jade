#include "myGraph.h"
Graph::Graph(){
    root = newGraphNode("All Knowledge", 0, 2, 0);
    name = "All Knowledge";
    root->children[0] = newGraphNode("T");//things
    root->children[1] = newGraphNode("U");//unconected
}
GraphNode* add(string address){
    int length = address.length();
    int p = 0;
    GraphNode* iter = root, temp;
    while(length>0){
        int p2 = address.find('/',p);
        string thisName = address.substr(p,p2);
        temp=findChild(iter, thisName);
        if(temp==NULL){
            expand
        p=p2+1;
Graph::~Graph(){
    recursiveFree(root);
}
Graph::recursiveFree(GraphNode* node){
    if(node!=NULL){
        if(node->parents!=NULL)
            delete[] node->parents;
        for(int i=0;i<cCount;i++)
            recursiveFree(root->children[i]);
        
        if(node->children!=NULL)
            delete[] node->children;
        if(node->qualities!=NULL)
            delete[] node->qualities;
        node->parents=NULL;
        node->children=NULL;
        node->qualities=NULL;
        delete node;
        node=NULL;
    }
}
    
Graph::findChild(GraphNode* node,     