//顺序表实现队列
//循环牺牲一个元素空间
#include <iostream>
#include <conio.h>

#define MAXQSIZE 100    //最大队列长度
#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0
#define OVERFLOW -2

using namespace std;

typedef int QElemType;
typedef int Status;

typedef struct {
    QElemType *base; //存储元素信息
    int front; //队头
    int rear; //队尾
} SqQueue;

//构造空队列
Status InitQueue (SqQueue &Q) {
    Q.base = new(nothrow) QElemType[MAXQSIZE];
    if (!Q.base) exit(OVERFLOW);

    Q.front = Q.rear = 0;
    return OK;
}// InitQueue

//返回队列的元素个数
int QueueLength (SqQueue Q) {
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}// QueueLength

//插入元素e为Q的新的队尾元素
Status EnQueue (SqQueue &Q, QElemType e) {
    if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;   //队列满
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}// EnQueue

//删除队列的队头元素
Status DeQueue (SqQueue &Q, QElemType &e) {
    if (Q.front == Q.rear) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}// DeQueue

//判空
Status QueueEmpty (SqQueue Q) {
    if (Q.front == Q.rear) return TRUE;
    return FALSE;
}// QueueEmpty

//清空队列
Status ClearQueue (SqQueue &Q) {
    Q.front = Q.rear = 0;
    return OK;
}// ClearQueue

//销毁队列
Status DestroyQueue (SqQueue &Q) {
    delete [] Q.base;
    return OK;
}// DestroyQueue

//输出元素
Status PrintQueue (SqQueue &Q) {
    for (int i = Q.front; i != Q.rear; i = (i + 1) % MAXQSIZE)
    {
        cout << Q.base[i] << " ";
    }
    cout << endl;
    return OK;
}// PrintQueue

void Menu() {
    cout << "********************************\n";
    cout << "*This is Static Queue.         *\n";
    cout << "*The order is following:       *\n";
    cout << "* 1. Add element;              *\n";
    cout << "* 2. Delete head element;      *\n";
    cout << "* 3. The queue is empty?;      *\n";
    cout << "* 4. The length of Queue;      *\n";
    cout << "* 5. Print the Queue;          *\n";
    cout << "* 6. Clear Queue;              *\n";
    cout << "* 7. Destroy Queue;            *\n";
    cout << "* 8. Quit;                     *\n";
    cout << "********************************\n";
}

int main()
{
    SqQueue Q;
    InitQueue(Q);
    char order;
    QElemType e;
    while (1) {
        Menu();
        int quit_flag = 0;
        cout << "Please input your order(the number): \n";
        cin >> order;
        switch (order) {
            case '1': {
                cout << "cout the element what you add: ";
                cin >> e;
                if (EnQueue(Q, e)) {
                    cout << "Operate successfully!" << endl;
                } else cout << "Failure!" << endl;
                break;
            }
            case '2': {
                if (DeQueue(Q, e)) {
                    cout << "Operate successfully!" << endl;
                    cout << e << " has been deleted!" << endl;
                } else cout << "Failure!" << endl;
                break;
            }
            case '3': {
                if (QueueEmpty(Q)) cout << "Yes!" << endl;
                else cout << "No" << endl;
                break;
            }
            case '4': {
                cout << "Length is " << QueueLength(Q) << endl;
                break;
            }
            case '5': {
                cout << "The all elements are fllowing: " << endl;
                PrintQueue(Q);
                break;
            }
            case '6': {
                if (ClearQueue(Q)) {
                    cout << "Operate successfully!" << endl;
                } else cout << "Failure!" << endl;
                break;
            }
            case '7': {
                if (DestroyQueue(Q)) {
                    cout << "Operate successfully!" << endl;
                } else cout << "Failure!" << endl;
                break;
            }
            case '8': {
                quit_flag = 1;
                break;
            }
            default: cout << "Error order!" << endl; break;
        }

        if (quit_flag) break;
        cout << "press any key to continue... " << endl;
        getch();
        system("cls");
    }
    cout << "Thanks your use!" << endl;

    return 0;
}