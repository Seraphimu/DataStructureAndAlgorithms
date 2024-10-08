#include <iostream>
#include <cstdlib>

using namespace std;

typedef int DataType;

//链表节点
typedef struct Node {
    DataType A;
    struct Node * Prev;
    struct Node * Next;
}Node;

class DoubleLinkedList {
private:
    Node * Head;
public:
    //尾插
    void PushBack(DataType X);
    //头插
    void PushFront(DataType X);
    //在第Pos个位置插入，若不存在该位置报错
    void InsertThisPos(int Pos, DataType X);

    //尾删
    void PopBack();
    //头删
    void PopFront();
    //删除第Pos位元素，若无该位置，则返回错误
    void DeleteThisPos(int Pos);
    // 把链表置为空表
    void MakeEmpty();
    
    //查找值为 Target的元素，若不存在，则返回空指针，存在则返回节点指针
    Node * SearchByValue(DataType Target);
    void ModifyByValue(DataType Value, DataType NewValue);

    //创建一个空表
    void Init();
    //判空，若空，则返回true，反之返回false
    bool IsEmpty();
    //打印链表
    void Print();
    //分配空间，根据参数X分配空间，分配成功则返回该节点的指针
    Node * BuyNode(DataType X);
};