//队列的基本操作
#include <iostream>
#include <cstring>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define OVERFLOW -2

using namespace std;

typedef int Status;
typedef int QElemType;

typedef struct QNode {
    QElemType     data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;     //队头指针
    QueuePtr rear;      //队尾指针
    int length;         //队的长度
} LinkQueue;

//队列初始化
Status InitQueue (LinkQueue &Q) {
    //构造一个空队列Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front) exit(OVERFLOW);
    Q.front->next = NULL;
    Q.length = 0;
    return OK;
}

//插入元素在队尾
Status EnQueue (LinkQueue &Q, QElemType e) {
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) exit(OVERFLOW);
    p->data = e; p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    Q.length++;
    return OK;
}

//删除队头元素
Status DeQueue (LinkQueue &Q, QElemType &e) {
    //判空
    if (Q.front == Q.rear) return ERROR;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;
    free (p);
    Q.length--;
    return OK;
}

//打印队列元素
Status PrintQueue (LinkQueue Q) {
    QueuePtr p = Q.front->next;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
    return OK;
}

//判断是否队满
Status QueueFull (LinkQueue Q, int n) {
    return Q.length >= n ? TRUE : FALSE;
}

//判断是否队空
Status QueueEmpty (LinkQueue Q) {
    return Q.front == Q.rear? TRUE : FALSE; 
}

int main()
{
    int n;
    string command;
    LinkQueue Q;    InitQueue(Q);
    QElemType e;
    cin >> n;
    while (1) {
        cin >> command;
        if (command == "dequeue") {
            if (DeQueue(Q, e)) cout << e << endl;
            else cout << "Queue is Empty" << endl;
        } else if (command == "enqueue") {
            cin >> e;
            if (QueueFull(Q, n)) cout << "Queue is Full" << endl;
            else EnQueue(Q, e);
        } else if (command == "quit") {
            PrintQueue(Q);
            break;
        }
    }

    return 0;
}