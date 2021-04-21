#pragma once
#include"Node.h"

class List
{
public:
	List();    //无需size参数，因为增加一个节点时可临时申请堆中内存
	~List();
	void ClearList();
	int ListLength();
	bool ListEmpty();
	bool GetElem(int i, Node *pNode);
	int LocateElem(Node *pNode);
	bool PriorElem(Node *pCurrentNode, Node *pPreNode);
	bool NextElem(Node *pCurrentNode, Node *pNextNode);
	void ListTraverse();
	bool ListInsert(int i, Node *pNode); //插入节点
	bool ListDelete(int i, Node *pNode); //删除节点
	bool ListInsertHead(int i, Node *pNode);  //从头插入节点
	bool ListInsertTail(int i, Node *pNode);  //从尾插入节点

private:
	Node *m_pList;
	int m_iLength;
};