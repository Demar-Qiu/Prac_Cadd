#include<string>
#include"MyArray.h"
using namespace std;

/* 类模板
      定义类模板MyArray,成员函数：构造、析构和display函数
                        数据成员：m_pArr

*/

int main()
{
    MyArray<int, 5, 6>arr;  //形成了一个模板类 并实例化
    arr.Display();

    return 0;
}