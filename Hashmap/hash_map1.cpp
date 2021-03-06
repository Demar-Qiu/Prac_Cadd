#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <malloc.h>
using namespace std;

/* 哈希表 */

//散列函数采用除留余数法: f(key)=key mod p(p一般取素数)
//冲突解决采用链表法: 将相应位置上冲突的所有关键词存储在同一个单链表中。
               // 每一个Entry对象通过next指针指向它的下一个Entry节点。
               //当新来的Entry映射到与之冲突的数组位置时，只需要插入到对应的链表中即可。


#define MAXTABLESIZE 10000 //允许开辟的最大散列表长度
#define KEYLENGTH 100      //关键字的最大长度

typedef int ElementType;
struct LNode
{
    ElementType data;
    LNode* next;
};
typedef LNode* PtrToNode;
typedef PtrToNode LinkList; //存储指向节点的指针列表
struct TblNode
{
    int tablesize;  //散列表的最大长度
    LinkList heads; //存放散列单元数据的数组
};
typedef struct TblNode* HashTable;

/*返回大于n且不超过MAXTABLESIZE的最小素数*/
int NextPrime(int n)
{
    int p = (n % 2) ? n + 2 : n + 1; //从大于n的下一个奇数开始
    int i;
    while (p <= MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--)  //素数的判断
        {
            if ((p % i) == 0)
                break;
        }
        if (i == 2)
            break; //说明是素数，结束
        else
            p += 2;
    }
    return p;
}

/*创建新的哈希表*/
HashTable CreateTable(int table_size)
{
    HashTable h = (HashTable)malloc(sizeof(TblNode));   //注意做内存分配检查
    h->tablesize = NextPrime(table_size);
    h->heads = (LinkList)malloc(h->tablesize * sizeof(LNode)); //散列单元数据的单链表
    //初始化表头结点
    for (int i = 0; i < h->tablesize; i++)
    {
        h->heads[i].next = NULL;
    }
    return h;
   
}

/*哈希函数 查找数据的初始位置*/
int Hash(ElementType key, int n)
{
    //这里只针对大小写
    return key % 11;  //这里哈希函数设为此
    //return key % n;
}

/*根据key查找元素位置*/
LinkList Find(HashTable h, ElementType key)
{
    int pos;

    pos = Hash(key, h->tablesize); //初始散列地址

    LinkList p = h->heads[pos].next; //从链表的第一个节点开始
    while (p && key != p->data)  //发生冲突，转向下一个节点
    {
        p = p->next;
    }

    return p;
}

/*插入新的元素*/
bool Insert(HashTable h, ElementType key)
{
    LinkList p = Find(h, key); //先查找key是否存在
    if (!p)
    {
        //关键词key未找到，可以插入
        LinkList new_cell = (LinkList)malloc(sizeof(LNode));  //注意做内存分配检查
        new_cell->data = key; //key先赋值给节点值
        int pos = Hash(key, h->tablesize); //获取散列地址
        new_cell->next = h->heads[pos].next;  //将散列地址所在的节点next赋值
        h->heads[pos].next = new_cell;
        return true;
    }
    else
    {
        cout << "键值已存在！" << endl;
        return false;
    }
}

/*销毁链表*/
void DestroyTable(HashTable h)
{
    int i;
    LinkList p, tmp;
    //释放每个节点
    for (i = 0; i < h->tablesize; i++)
    {
        p = h->heads[i].next; //链表头结点所指向的下一个节点
        while (p)   //若存在，将下一节点赋值给p,删除该节点
        {
            tmp = p->next;
            free(p);
            p = tmp;
        }
    }
    //直到所有单链表都删除完，最后删除节点链表和哈希表
    free(h->heads);  
    free(h);
}

int main(int argc, char const* argv[])
{
    int a[] = { 47, 7, 29,29, 11, 16, 92, 22, 8, 3, 50, 37, 89, 94, 21 };
    int n = 15;
    HashTable h = CreateTable(n);
    for (int i = 0; i < n; i++)
    {
        Insert(h, a[i]); //插入元素
    }
    for (int i = 0; i < h->tablesize; i++)
    {
        LinkList p = h->heads[i].next;
        while (p)
        {
            cout << p->data << " "; //打印哈希表元素
            p = p->next;
        }
        cout << endl;
    }
    return 0;
}