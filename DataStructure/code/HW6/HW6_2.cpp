// 先序遍历线索二叉树
#include <iostream>

#define OVERFLOW -2
#define OK      1
#define ERROR   0

using namespace std;

typedef int Status;
typedef enum{Link, Thread} PointerTag;
//  Link = 0:指针，指向孩子结点
//  Thread = 1:线索，指向前驱或后继结点
typedef char TElemType;

typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;

//使用先序遍历创建二叉树
void BuildBiTree (BiThrTree &T) {
    TElemType ch;
    cin >> ch;
    if (ch == '#')  T = NULL;
    else {
        T = new(nothrow) BiThrNode;
        if (!T) exit(OVERFLOW);
        T->data = ch;
        BuildBiTree (T->lchild);
        BuildBiTree (T->rchild);
    }
}// BuildBiTree

//先序线索化
void InThreading (BiThrTree &P, BiThrTree &pre)
{
    if (P) {
        InThreading(P->lchild, pre);
        if (!P->lchild) {
            P->LTag = Thread;   P->lchild = pre;
        } else P->LTag = Link;

        if (!P->rchild) P->RTag = Thread;
        else P->RTag = Link;

        if (pre && pre->rchild == NULL) {
            pre->rchild = P;    pre->RTag = Thread;
        }
        pre = P;
        InThreading(P->rchild, pre);
    }
}// PreThreading

//创建先序线索化二叉树
void CreatInThread (BiThrTree &T)
{
    BiThrTree pre = NULL;
    if (T != NULL) {
        InThreading(T, pre);
    }
}// CreatInThread

//输出元素
void PrintElement (TElemType e) {
    cout << e;
    return;
}// PrintElement

//中序遍历线索化二叉树
void InOrderTraverse (BiThrTree T, void (*Visit)(TElemType)) 
{
    BiThrTree p = T;
    while (p->LTag == Link) p = p->lchild;
    Visit(p->data);
    while (p->rchild) {
        if (p->RTag == Link) {
            p = p->rchild;
            while (p->LTag == Link) p = p->lchild;
        } 
        else p = p->rchild;
        Visit(p->data);
    }
    cout << endl;
}// InOrderTraverse

//比较元素
Status Compare (BiThrTree p, TElemType e)
{
    if (p->data == e) {
        BiThrTree q = p;            //方便寻找前驱结点
        cout << "succ is ";     //输出后续结点
        if (p->RTag == Thread) {
            if (p->rchild) {
                cout << p->rchild->data << p->rchild->RTag << endl;
            } else cout << "NULL" << endl;
        } else {
            p = p->rchild;
            while (p->LTag == Link) p = p->lchild;
            cout << p->data << p->RTag << endl;
        }

        cout << "prev is ";     //输出前驱结点
        if (q->LTag == Thread) {
            if (q->lchild) {
                cout << q->lchild->data << q->lchild->LTag << endl;
            } else cout << "NULL" << endl;
        } else {
            q = q->lchild;
            while (q->RTag == Link) q = q->rchild;
            cout << q->data << q->LTag << endl;
        }
        return OK;
    }
    return ERROR;
}// Compare

//查找元素e
Status SearchElem (BiThrTree T, TElemType e)
{
    BiThrTree p = T;
    while (p->LTag == Link) p = p->lchild;
    if (Compare(p, e)) return OK;

    while (p->rchild) {
        if (p->RTag == Link) {
            p = p->rchild;
            while (p->LTag == Link) p = p->lchild;
        } 
        else p = p->rchild;
        if (Compare(p, e)) return OK;
    }

    return ERROR;
}// SearchElem

int main()
{
    BiThrTree P;
    TElemType e;
    BuildBiTree(P);
    cin >> e;
    CreatInThread(P);
    InOrderTraverse(P, PrintElement);
    if (!SearchElem(P, e)) cout << "Not found" << endl;

    return 0;
}