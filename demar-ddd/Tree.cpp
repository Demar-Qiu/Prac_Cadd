#include<iostream>
#include"Tree.h"
using namespace std;


Tree::Tree(int size, int* pRoot)
{
	m_iSize = size;
	m_pTree = new int[size];
	for (int i = 0; i < size; i++)
	{
		m_pTree[i] = 0;
	}
	m_pTree[0] = *pRoot;
}


Tree::~Tree()
{
	delete[]m_pTree;
	m_pTree = NULL;

}


int* Tree::SearchNode(int nodeIndex)
{
	if (nodeIndex < 0 || nodeIndex >= m_iSize)
	{
		return NULL;
	}
	if (m_pTree[nodeIndex] == 0)  //用0表示当前不存在节点
	{
		return NULL;
	}
	return &m_pTree[nodeIndex];
}


bool Tree::AddNode(int nodeIndex, int direction, int* pNode)
{
	if (nodeIndex < 0 || nodeIndex >= m_iSize)
	{
		return false;
	}
	if (m_pTree[nodeIndex] == 0)
	{
		return false;
	}
	if (direction == 0)  //往左边插入
	{
		if (nodeIndex * 2 + 1 >= m_iSize)
		{
			return false;
		}
		if (m_pTree[nodeIndex * 2 + 1] != 0)
		{
			return false;
		}
		m_pTree[nodeIndex * 2 + 1] = *pNode;
	}

	if (direction == 1)    // 表示往右边插入
	{
		if (nodeIndex * 2 + 2 >= m_iSize)
		{
			return false;
		}
		if (m_pTree[nodeIndex * 2 + 2] != 0)  //不为0表示此时有结点所以不能插入
		{
			return false;
		}
		m_pTree[nodeIndex * 2 + 2] = *pNode;  //插入右节点
	}
	return true;
	
}


bool Tree::DeleteNode(int nodeIndex, int* pNode)
{
	if (nodeIndex < 0 || nodeIndex >= m_iSize)
	{
		return false;
	}
	if (m_pTree[nodeIndex] == 0)  //用0表示当前不存在结点
	{
		return false;
	}
	*pNode = m_pTree[nodeIndex];
	m_pTree[nodeIndex] = 0;                     
	return true;
}



void Tree::TreeTraverse()
{
	for (int i = 0; i < m_iSize; i++)
	{
		cout << m_pTree[i] << ",";
	}
}










