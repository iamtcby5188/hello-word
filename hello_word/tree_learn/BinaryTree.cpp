#include "stdafx.h"
#include "BinaryTree.h"
#include <stack>
CBinaryTree::CBinaryTree()
    :m_pRoot(NULL)
{
}

CBinaryTree::~CBinaryTree()
{
}


binary_tree* CBinaryTree::GetTreeRoot()
{
    return m_pRoot;
}

void CBinaryTree::InsertNode(int key)
{
    if (m_pRoot == NULL)
    {
        m_pRoot = new binary_tree(key);
    }
    else
    {
        InsertNodeRecursion(m_pRoot, key);
    }
}


void CBinaryTree::InsertNodeRecursion(binary_tree* pNode, int key)
{
    if (pNode == NULL || pNode->m_key == key) return;

    if (pNode->m_key < key)
    {
        if (pNode->m_rChild == NULL)
        {
            pNode->m_rChild = new binary_tree(key);
        }
        else
        {
            InsertNodeRecursion(pNode->m_rChild, key);
        }
    }
    else if (pNode->m_key > key)
    {
        if (pNode->m_lChild == NULL) 
        {
            pNode->m_lChild = new binary_tree(key);
        }
        else
        {
            InsertNodeRecursion(pNode->m_lChild, key);
        }
    }
    
}

void CBinaryTree::preTraverseRecursion(binary_tree* pNode, std::list<int>& lstValue)
{
    if (pNode != NULL)
    {
        lstValue.push_back(pNode->m_key);
        preTraverseRecursion(pNode->m_lChild, lstValue);
        preTraverseRecursion(pNode->m_rChild, lstValue);
    }
}

void CBinaryTree::midTraverseRecursion(binary_tree* pNode, std::list<int>& lstValue)
{
    if (pNode != NULL)
    {
        midTraverseRecursion(pNode->m_lChild, lstValue);
        lstValue.push_back(pNode->m_key);
        midTraverseRecursion(pNode->m_rChild, lstValue);
    }
}

void CBinaryTree::postTraverseRecursion(binary_tree* pNode, std::list<int>& lstValue)
{
    if (pNode != NULL)
    {
        postTraverseRecursion(pNode->m_lChild, lstValue);
        postTraverseRecursion(pNode->m_rChild, lstValue);
        lstValue.push_back(pNode->m_key);
    }
}

void CBinaryTree::preTraverseR(std::list<int>& lstValue)
{
    preTraverseRecursion(m_pRoot, lstValue);
}

void CBinaryTree::midTraverseR(std::list<int>& lstValue)
{
    midTraverseRecursion(m_pRoot, lstValue);
}

void CBinaryTree::postTraverseR(std::list<int>& lstValue)
{
    postTraverseRecursion(m_pRoot, lstValue);
}


void CBinaryTree::preTraverse(std::list<int>& lstValue)
{
    preTraverseNonRecursion(m_pRoot, lstValue);
}

void CBinaryTree::midTraverse(std::list<int>& lstValue)
{
    midTraverseNonRecursion(m_pRoot, lstValue);
}

void CBinaryTree::postTraverse(std::list<int>& lstValue)
{
    postTraverseNonRecursion(m_pRoot, lstValue);
}

void CBinaryTree::preTraverseNonRecursion(binary_tree* pNode, std::list<int>& lstValue)
{
    if (pNode == NULL)
    {
        return;
    }

    std::stack<binary_tree*> stNode;
    stNode.push(pNode);
    while (!stNode.empty())
    {
        binary_tree* pTmp = stNode.top();
        stNode.pop();
        if (pTmp->m_rChild != NULL)
        {
            stNode.push(pTmp->m_rChild);
        }

        if (pTmp->m_lChild != NULL)
        {
            stNode.push(pTmp->m_lChild);
        }

        lstValue.push_back(pTmp->m_key);
    }
}

void CBinaryTree::midTraverseNonRecursion(binary_tree* pNode, std::list<int>& lstValue)
{
    if (pNode == NULL)
    {
        return;
    }
    std::stack<binary_tree*> stNode;
    stNode.push(pNode);
    binary_tree* pTmp = pNode;

    while (pTmp->m_lChild != NULL)
    {
        stNode.push(pTmp->m_lChild);
        pTmp = pTmp->m_lChild;
    }

    while (!stNode.empty())
    {
        pTmp = stNode.top();
        stNode.pop();
        lstValue.push_back(pTmp->m_key);
        if (pTmp->m_rChild != NULL)
        {
            stNode.push(pTmp->m_rChild);
            pTmp = pTmp->m_rChild;
            while (pTmp->m_lChild != NULL)
            {
                stNode.push(pTmp->m_lChild);
                pTmp = pTmp->m_lChild;
            }
        }
    }
}

void CBinaryTree::postTraverseNonRecursion(binary_tree* pNode, std::list<int>& lstValue)
{
    if (pNode == NULL)
    {
        return;
    }

    std::stack<binary_tree*> stNode;
    binary_tree* pCur = pNode;
    binary_tree* pPre = NULL;
    while (pCur != NULL || !stNode.empty())
    {
        while (pCur != NULL)
        {
            stNode.push(pCur);
            pCur = pCur->m_lChild;
        }

        pCur = stNode.top();
        if (pCur->m_rChild == NULL || pCur->m_rChild == pPre)
        {
            lstValue.push_back(pCur->m_key);
            pPre = pCur;
            stNode.pop();
            pCur = NULL;
        }
        else
        {
            pCur = pCur->m_rChild;
        }
    }
}
