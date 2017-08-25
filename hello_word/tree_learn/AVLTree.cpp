#include "stdafx.h"
#include "AVLTree.h"
#include "iostream"
using namespace std;

CAVLTree::CAVLTree()
    :m_pRoot(NULL)
{
}


CAVLTree::~CAVLTree()
{
}

void CAVLTree::InsertNode(int key)
{
    if (m_pRoot == NULL)
    {
        m_pRoot = new avl_tree_node(key);
        return;
    }

    avl_tree_node* pInsert = new avl_tree_node(key);
    avl_tree_node* pCur = m_pRoot;

    while (true)
    {
        if (pCur->m_key < key)
        {
            if (pCur->m_rChild == NULL)
            {
                pCur->m_rChild = pInsert;
                break;
            }
            else
            {
                pCur = pCur->m_rChild;
            }
        }
        else if (pCur->m_key > key)
        {
            if (pCur->m_lChild == NULL)
            {
                pCur->m_lChild = pInsert;
                break;
            }
            else
            {
                pCur = pCur->m_lChild;
            }
        }
        else
        {
            return;
        }
               
    }

    
}
void CAVLTree::PrintTree(avl_tree_node* pNode, bool left, std::string str)
{
    if (pNode->m_rChild != NULL)
    {
        PrintTree(pNode->m_rChild, false, (str + (left ? "|     " : "      ")));
    }
    cout << str;
    cout << (left ? '\\' : '/');

    cout << "----";
    cout << pNode->m_key << endl;
    
    if (pNode->m_lChild != NULL)
    {
        PrintTree(pNode->m_lChild, true, (str + (left ? "      " : "|     ")));
    }
}

void CAVLTree::PrintTree()
{
    if (m_pRoot->m_rChild != NULL)
    {
        PrintTree(m_pRoot->m_rChild, false, "");
    }

    cout << m_pRoot->m_key << endl;
    if (m_pRoot->m_lChild != NULL)
    {
        PrintTree(m_pRoot->m_lChild, true, "");
    }
}

int CAVLTree::GetDepth(avl_tree_node* pNode)
{
    if (pNode == NULL)
    {
        return 0;
    }

    int lDep = GetDepth(pNode->m_lChild);
    int rDep = GetDepth(pNode->m_rChild);

    return lDep > rDep ? (lDep + 1) : (rDep + 1);
}
