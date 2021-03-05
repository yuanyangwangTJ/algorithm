//���еĻ�������
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
    QueuePtr front;     //��ͷָ��
    QueuePtr rear;      //��βָ��
    int length;         //�ӵĳ���
} LinkQueue;

//���г�ʼ��
Status InitQueue (LinkQueue &Q) {
    //����һ���ն���Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front) exit(OVERFLOW);
    Q.front->next = NULL;
    Q.length = 0;
    return OK;
}

//����Ԫ���ڶ�β
Status EnQueue (LinkQueue &Q, QElemType e) {
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) exit(OVERFLOW);
    p->data = e; p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    Q.length++;
    return OK;
}

//ɾ����ͷԪ��
Status DeQueue (LinkQueue &Q, QElemType &e) {
    //�п�
    if (Q.front == Q.rear) return ERROR;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;
    free (p);
    Q.length--;
    return OK;
}

//��ӡ����Ԫ��
Status PrintQueue (LinkQueue Q) {
    QueuePtr p = Q.front->next;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
    return OK;
}

//�ж��Ƿ����
Status QueueFull (LinkQueue Q, int n) {
    return Q.length >= n ? TRUE : FALSE;
}

//�ж��Ƿ�ӿ�
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