#ifndef TREE
#define TREE

#ifndef DELETE_FUNC
#define REMOVE_FUNC
typedef void (*DeleteFunc)(void*, void*);
#endif
typedef struct TreeNode{
    void* data;
    TreeNode** children;
    int childCount;
} TreeNode;

class Tree {
public:
    Tree(DeleteFunc deleteVoid, void* deleteArgs);
    Tree(DeleteFunc deleteVoid, void* deleteArgs, void* rootData);
   ~Tree();
    TreeNode* getRoot();
    int getChildCount(TreeNode* parent);
    TreeNode** getChildren(TreeNode* parent);
    TreeNode* getChild(TreeNode* parent, int childID);
    void* getData(TreeNode* node);
    void setData(TreeNode* node, void* data);
    void addChild(TreeNode* parent, void* childData);
    void addChildren(TreeNode* parent, void** childData, int childCount);
    void addChild(TreeNode* parent, TreeNode* child);
    void addChildren(TreeNode* parent, TreeNode** children, int childCount);
private:
    TreeNode* root;
    DeleteFunc del;
    void* delArgs;
    bool expand(TreeNode* parent);
    bool expand(TreeNode* parent, int growth);
    TreeNode* makeNode(void* data);
    void deleteNode(TreeNode* node);
};

#endif