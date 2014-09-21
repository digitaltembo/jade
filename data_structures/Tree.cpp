#include "Tree.h"

Tree::Tree(DeleteFunc deleteVoid, void* deleteArgs){
    root=makeNode(NULL);
    del=deleteVoid;
    delArgs=deleteArgs;
}

Tree::Tree(DeleteFunc deleteVoid, void* deleteArgs, void* rootData){
    root=makeNode(rootData);
    del=deleteVoid;
    delArgs=deleteArgs;
}

TreeNode* Tree::getRoot(){
    return root;
}

int Tree::getChildCount(TreeNode* parent){
    return parent->childCount;
}
TreeNode** Tree::getChildren(TreeNode* parent){
    return parent->children;
}
TreeNode* Tree::getChild(TreeNode* parent, int childID){
    if(childID>=parent->childCount)
        return NULL;
    return parent->children[childID];
}

void* Tree::getData(TreeNode* node){
    return node->data;
}

void Tree::setData(TreeNode* node, void* data){
    node->data=data;
}

void Tree::addChild(TreeNode* parent, void* childData){
    if(!expand(parent)){
        fprintf(stderr, "Failed to add child\n");
        return;
    }
    parent->children[childCount]=makeNode(childData);
    parent->childCount++;
}

void Tree:: addChildren(TreeNode* parent, void** childData, int addedChildCount){
    if(!expand(parent, childData)){
        fprintf(stderr, "Failed to add children\n");
        return;
    }
    int currentChildCount=parent->childCount;
    for(int i=0;i<addedChildCount;i++){
        parent->children[i+currentChildCount]=makeNode(childData[i]);
    }
    parent->childCount+=addedChildCount;
}

void Tree::addChild(TreeNode* parent, TreeNode* child{
    if(!expand(parent)){
        fprintf(stderr, "Failed to add child\n");
        return;
    }
    parent->children[childCount]=child;
    parent->childCount++;
}

void Tree:: addChildren(TreeNode* parent, TreeNode** children, int addedChildCount){
    if(!expand(parent, childData)){
        fprintf(stderr, "Failed to add children\n");
        return;
    }
    int currentChildCount=parent->childCount;
    for(int i=0;i<addedChildCount;i++){
        parent->children[i+currentChildCount]=children[i];
    }
    parent->childCount+=addedChildCount;
}

bool Tree::expand(TreeNode* parent){
    return expand(parent, 1);
}
bool Tree::expand(TreeNode* parent, int growth){
    TreeNode** tmp=new TreeNode*[childCount+growth];
    if(tmp==NULL)
        return false;
    for(int i=0;i<childCount;i++)
        tmp[i]=parent->children[i];
    delete[] parent->children;
    parent->children=tmp;
    return true;
}

TreeNode* Tree::makeNode(void* data){
    TreeNode* node=new TreeNode;
    node->data=data;
    node->children=NULL;
    node->childCount=0;
    return node;
}

Tree::deleteNode(TreeNode* node){
    del(data, delArgs);
    for(int i=0, j=node->childCount;i<j;i++){
        deleteNode(node->children[i]);
    }
    delete node;
}
