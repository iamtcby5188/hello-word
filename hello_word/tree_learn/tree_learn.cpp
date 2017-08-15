// tree_learn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "BinaryTree.h"

//普通二叉树test
void BinaryTreeNormal()
{
    CBinaryTree tree;
    std::list<int> lstValue;
    for (int n = 0; n < 10;)
    {
        int num = rand() % 100;
        if (std::find(lstValue.begin(), lstValue.end(), num) == lstValue.end())
        {
            lstValue.push_back(num);
            n++;
        }
    }

    std::cout << "origin data is:";
    for (auto iter = lstValue.begin(); iter != lstValue.end(); iter++)
    {
        std::cout << *iter << ",";
    }
    std::cout << std::endl << std::endl;

    std::cout << "begin build tree...." << std::endl;
    for (auto iter = lstValue.begin(); iter != lstValue.end(); iter++)
    {
        tree.InsertNode(*iter);
    }
    std::cout << "end build tree...." << std::endl << std::endl;


    std::cout << "begin preTraverse tree...." << std::endl;
    lstValue.clear();
    tree.preTraverse(lstValue);
    std::cout << "end preTraverse tree...." << std::endl;
    std::cout << "preTraverse data is:";
    for (auto iter = lstValue.begin(); iter != lstValue.end(); iter++)
    {
        std::cout << *iter << ",";
    }

    std::cout << std::endl;
    lstValue.clear();
    tree.preTraverseR(lstValue);
    std::cout << "end preTraverse Recursion tree...." << std::endl;
    std::cout << "preTraverse data is:";
    for (auto iter = lstValue.begin(); iter != lstValue.end(); iter++)
    {
        std::cout << *iter << ",";
    }

    std::cout << std::endl << std::endl;


    std::cout << "begin midTraverse tree...." << std::endl;
    lstValue.clear();
    tree.midTraverse(lstValue);
    std::cout << "end midTraverse tree...." << std::endl;
    std::cout << "midTraverse data is:";
    for (auto iter = lstValue.begin(); iter != lstValue.end(); iter++)
    {
        std::cout << *iter << ",";
    }

    std::cout << std::endl;
    lstValue.clear();
    tree.midTraverseR(lstValue);
    std::cout << "end midTraverse Recursion tree...." << std::endl;
    std::cout << "midTraverse data is:";
    for (auto iter = lstValue.begin(); iter != lstValue.end(); iter++)
    {
        std::cout << *iter << ",";
    }

    std::cout << std::endl << std::endl;


    std::cout << "begin postTraverse tree...." << std::endl;
    lstValue.clear();
    tree.postTraverse(lstValue);
    std::cout << "end postTraverse tree...." << std::endl;
    std::cout << "postTraverse data is:";
    for (auto iter = lstValue.begin(); iter != lstValue.end(); iter++)
    {
        std::cout << *iter << ",";
    }

    std::cout << std::endl;
    lstValue.clear();
    tree.postTraverseR(lstValue);
    std::cout << "end postTraverse Recursion tree...." << std::endl;
    std::cout << "postTraverse data is:";
    for (auto iter = lstValue.begin(); iter != lstValue.end(); iter++)
    {
        std::cout << *iter << ",";
    }

    std::cout << std::endl << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    BinaryTreeNormal();


	return 0;
}

