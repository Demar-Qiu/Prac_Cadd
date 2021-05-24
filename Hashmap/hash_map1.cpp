#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <malloc.h>
using namespace std;

/* ��ϣ�� */

//ɢ�к������ó���������: f(key)=key mod p(pһ��ȡ����)
//��ͻ�������������: ����Ӧλ���ϳ�ͻ�����йؼ��ʴ洢��ͬһ���������С�
               // ÿһ��Entry����ͨ��nextָ��ָ��������һ��Entry�ڵ㡣
               //��������Entryӳ�䵽��֮��ͻ������λ��ʱ��ֻ��Ҫ���뵽��Ӧ�������м��ɡ�


#define MAXTABLESIZE 10000 //�������ٵ����ɢ�б�����
#define KEYLENGTH 100      //�ؼ��ֵ���󳤶�

typedef int ElementType;
struct LNode
{
    ElementType data;
    LNode* next;
};
typedef LNode* PtrToNode;
typedef PtrToNode LinkList; //�洢ָ��ڵ��ָ���б�
struct TblNode
{
    int tablesize;  //ɢ�б�����󳤶�
    LinkList heads; //���ɢ�е�Ԫ���ݵ�����
};
typedef struct TblNode* HashTable;

/*���ش���n�Ҳ�����MAXTABLESIZE����С����*/
int NextPrime(int n)
{
    int p = (n % 2) ? n + 2 : n + 1; //�Ӵ���n����һ��������ʼ
    int i;
    while (p <= MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--)  //�������ж�
        {
            if ((p % i) == 0)
                break;
        }
        if (i == 2)
            break; //˵��������������
        else
            p += 2;
    }
    return p;
}

/*�����µĹ�ϣ��*/
HashTable CreateTable(int table_size)
{
    HashTable h = (HashTable)malloc(sizeof(TblNode));   //ע�����ڴ������
    h->tablesize = NextPrime(table_size);
    h->heads = (LinkList)malloc(h->tablesize * sizeof(LNode)); //ɢ�е�Ԫ���ݵĵ�����
    //��ʼ����ͷ���
    for (int i = 0; i < h->tablesize; i++)
    {
        h->heads[i].next = NULL;
    }
    return h;
   
}

/*��ϣ���� �������ݵĳ�ʼλ��*/
int Hash(ElementType key, int n)
{
    //����ֻ��Դ�Сд
    return key % 11;  //�����ϣ������Ϊ��
    //return key % n;
}

/*����key����Ԫ��λ��*/
LinkList Find(HashTable h, ElementType key)
{
    int pos;

    pos = Hash(key, h->tablesize); //��ʼɢ�е�ַ

    LinkList p = h->heads[pos].next; //�������ĵ�һ���ڵ㿪ʼ
    while (p && key != p->data)  //������ͻ��ת����һ���ڵ�
    {
        p = p->next;
    }

    return p;
}

/*�����µ�Ԫ��*/
bool Insert(HashTable h, ElementType key)
{
    LinkList p = Find(h, key); //�Ȳ���key�Ƿ����
    if (!p)
    {
        //�ؼ���keyδ�ҵ������Բ���
        LinkList new_cell = (LinkList)malloc(sizeof(LNode));  //ע�����ڴ������
        new_cell->data = key; //key�ȸ�ֵ���ڵ�ֵ
        int pos = Hash(key, h->tablesize); //��ȡɢ�е�ַ
        new_cell->next = h->heads[pos].next;  //��ɢ�е�ַ���ڵĽڵ�next��ֵ
        h->heads[pos].next = new_cell;
        return true;
    }
    else
    {
        cout << "��ֵ�Ѵ��ڣ�" << endl;
        return false;
    }
}

/*��������*/
void DestroyTable(HashTable h)
{
    int i;
    LinkList p, tmp;
    //�ͷ�ÿ���ڵ�
    for (i = 0; i < h->tablesize; i++)
    {
        p = h->heads[i].next; //����ͷ�����ָ�����һ���ڵ�
        while (p)   //�����ڣ�����һ�ڵ㸳ֵ��p,ɾ���ýڵ�
        {
            tmp = p->next;
            free(p);
            p = tmp;
        }
    }
    //ֱ�����е�������ɾ���꣬���ɾ���ڵ������͹�ϣ��
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
        Insert(h, a[i]); //����Ԫ��
    }
    for (int i = 0; i < h->tablesize; i++)
    {
        LinkList p = h->heads[i].next;
        while (p)
        {
            cout << p->data << " "; //��ӡ��ϣ��Ԫ��
            p = p->next;
        }
        cout << endl;
    }
    return 0;
}