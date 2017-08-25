#pragma once
#include <list>

struct binary_tree 
{
public:
    binary_tree(int key)
        : m_key(key)
        , m_lChild(NULL)
        , m_rChild(NULL)
    {

    }
    ~binary_tree(){};

    binary_tree* m_lChild;
    binary_tree* m_rChild;
    int m_key;
};

class CBinaryTree
{
public:
    CBinaryTree();
    ~CBinaryTree();

private:
    binary_tree* m_pRoot;

private:
    //Recursion
    void InsertNodeRecursion(binary_tree* pNode,int key);
    void preTraverseRecursion(binary_tree* pNode,std::list<int>& lstValue);
    void midTraverseRecursion(binary_tree* pNode, std::list<int>& lstValue);
    void postTraverseRecursion(binary_tree* pNode, std::list<int>& lstValue);
    int GetTreeDepthRecursion(binary_tree* pNode);
    //non-recursion
    void InsertNonRecursion(binary_tree* pNode,int key);
    void preTraverseNonRecursion(binary_tree* pNode, std::list<int>& lstValue);
    void midTraverseNonRecursion(binary_tree* pNode, std::list<int>& lstValue);
    void postTraverseNonRecursion(binary_tree* pNode, std::list<int>& lstValue);

public:
    bool IsEmpty(){ return m_pRoot == NULL; }
    binary_tree* GetTreeRoot();

    void InsertNode(int key);
    void preTraverse(std::list<int>& lstValue);
    void midTraverse(std::list<int>& lstValue);
    void postTraverse(std::list<int>& lstValue);

    void preTraverseR(std::list<int>& lstValue);
    void midTraverseR(std::list<int>& lstValue);
    void postTraverseR(std::list<int>& lstValue);

    int GetTreeDepthR();

    void LevelTraverse();
};
