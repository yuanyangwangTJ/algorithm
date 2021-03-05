//二叉树的创建与遍历
#include <iostream>
#include <stack>
#include <queue>

#define OK      1
#define ERROR   0
#define OVERFLOW -2

using namespace std;

typedef int Status;
typedef char TElemType;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//使用先序遍历创建二叉树
Status CreatBiTree (BiTree &T) {
    TElemType ch;
    cin >> ch;
    if (ch == '#')  T = NULL;
    else {
        T = new(nothrow) BiTNode;
        if (!T) exit(OVERFLOW);
        T->data = ch;
        CreatBiTree (T->lchild);
        CreatBiTree (T->rchild);
    }
    return OK;
}// CreatBiTree

//输出函数
Status PrintElement (TElemType e) {
    cout << e;
    return OK;
}// PrintElement


//先序遍历二叉树的递归算法
Status PreOrderTraverse (BiTree T, Status (*Visit)(TElemType)) {
    if (T) {
        if (Visit(T->data))
            if (PreOrderTraverse(T->lchild, Visit))
                if (PreOrderTraverse(T->rchild, Visit))
                    return OK;
        return ERROR;
    } else return OK;
}// PreOrderTraverse

//中序遍历二叉树的递归算法
Status InOrderTraverse (BiTree T, Status (*Visit)(TElemType)) {
    if (T) {
        if (InOrderTraverse(T->lchild, Visit))
            if (Visit(T->data))
                if (InOrderTraverse(T->rchild, Visit))
            return OK;
        return ERROR;
    } else return OK;
}// InOrderTraverse

//后序遍历二叉树的非递归算法
void PostOrderTraverse (BiTree T, Status (*Visit)(TElemType)) {
    BiTree p = T, q = NULL;
    stack<BiTree> S;
    S.push(p);
    while (!S.empty()) {
        if (p && p != q) {
            S.push(p);  p = p->lchild;
        } else {
            p = S.top();    S.pop();
            if (!S.empty()) {
                if (p->rchild && p->rchild != q) {
                    S.push(p);  p = p->rchild;
                } else {
                    Visit(p->data);     q = p;
                }
            }
        }
    }
}// PostOrderTraverse

//层次遍历二叉树的算法
void LevelOrderTraverse (BiTree T, Status (*Visit)(TElemType)) {
    BiTree p = T;
    queue<BiTree> Q;
    Q.push(p);
    while (!Q.empty()) {
        p = Q.front();   Q.pop();
        Visit (p->data);
        if (p->lchild)  Q.push(p->lchild);
        if (p->rchild)  Q.push(p->rchild);
    }
}// LevelOrderTraverse

//输出二叉树的树型图(逆时针旋转90度)
void PrintBiTree (BiTree T, int n) {
    int i;  char ch = ' ';
    if (T) {
        PrintBiTree (T->rchild, n + 1);
        for (i = 1; i <= n; i++) printf("%5c", ch);
        cout << T->data << endl;
        PrintBiTree (T->lchild, n + 1);
    }
}// PrintBiTree


int main()
{
    BiTree T;
    CreatBiTree (T);
    PreOrderTraverse(T, PrintElement);  cout << endl;
    InOrderTraverse(T, PrintElement);   cout << endl;
    PostOrderTraverse(T, PrintElement); cout << endl;
    LevelOrderTraverse(T, PrintElement);cout << endl;
    PrintBiTree(T, 0);

    return 0;
}