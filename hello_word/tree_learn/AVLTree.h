#pragma once
#include <string>
struct avl_tree_node
{
    avl_tree_node* m_lChild;
    avl_tree_node* m_rChild;
    avl_tree_node* m_rParent;
    
    int m_nHeight;
    int m_nbf;
    int m_key;

    avl_tree_node()
        :m_lChild(NULL)
        , m_rChild(NULL)
        , m_rParent(NULL)
        , m_nHeight(0)
        , m_nbf(0)
        , m_key(0){}
    

    avl_tree_node(int key)
        :m_lChild(NULL)
        , m_rChild(NULL)
        , m_rParent(NULL)
        , m_nHeight(0)
        , m_nbf(0)
        , m_key(key){}

    ~avl_tree_node(){}
};
class CAVLTree
{
public:
    CAVLTree();
    ~CAVLTree();
private:
    avl_tree_node* m_pRoot;

private:
    int GetDepth(avl_tree_node* pNode);
public:
    void InsertNode(int key);
    int GetDepth(){return GetDepth(m_pRoot);};
    void PrintTree();
    void PrintTree(avl_tree_node* pNode, bool left, std::string str);
};

