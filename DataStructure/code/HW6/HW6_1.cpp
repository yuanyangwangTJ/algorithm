// 先序遍历线索二叉树
#include <iostream>

#define OVERFLOW -2

using namespace std;

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
void PreThreading (BiThrTree &P, BiThrTree &pre)
{
    if (P) {
        if (!P->lchild) {
            P->LTag = Thread;   P->lchild = pre;
        } else {
            P->LTag = Link;
        }
        if (!P->rchild) {
            P->RTag = Thread;
        } else {
            P->RTag = Link;
        }

        if (pre && pre->rchild == NULL) {
            pre->rchild = P;
        }
        pre = P;
        if (P->LTag == Link) PreThreading(P->lchild, pre);
        if (P->RTag == Link) PreThreading(P->rchild, pre);
    }
}// PreThreading

//创建先序线索化二叉树
void CreatPreThread (BiThrTree &T)
{
    BiThrTree pre = NULL;
    if (T != NULL) {
        PreThreading(T, pre);
        pre->rchild = NULL;
        pre->RTag = Thread;
    }
}

//输出二叉树的树型图(逆时针旋转90度)
void PrintBiTree (BiThrTree T, int n) {
    int i;  char ch = ' ';
    if (T) {
        if (T->RTag == Link) PrintBiTree (T->rchild, n + 1);
        for (i = 1; i <= n; i++) printf("%5c", ch);
        cout << T->data << T->LTag << T->RTag << endl;
        if (T->LTag == Link) PrintBiTree (T->lchild, n + 1);
    }
}// PrintBiTree


void PrintElement (TElemType e) {
    cout << e;
    return;
}// PrintElement

//先序遍历二叉树
void PreOrderTraverse (BiThrTree T, void (*Visit)(TElemType)) {
    if (T) {
        Visit(T->data);
        if (T->LTag == Link) PreOrderTraverse(T->lchild, Visit);
        if (T->RTag == Link) PreOrderTraverse(T->rchild, Visit);
    }
}// PreOrderTraverse


int main()
{
    BiThrTree P;
    BuildBiTree(P);
    CreatPreThread(P);
    PrintBiTree(P, 0);
    PreOrderTraverse(P, PrintElement);

    return 0;
}