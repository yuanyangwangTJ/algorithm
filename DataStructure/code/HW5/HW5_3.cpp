//根据中序遍历的入栈顺序构造二叉树
#include <iostream>
#include <stack>

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

//根据中序遍历的入栈顺序构造二叉树
void CreatBiTree (BiTree &T, int n) {
    stack<BiTree> Tstack;
    int count = 0, flag = 0;    //flag为标志位置，为0说明连接左孩子，为1连接右孩子
    string order;   TElemType ch;
    BiTree p = NULL, q = NULL; T = NULL;

    if (n) {                //非空为头结点
        cin >> order >> ch;
        count++;
        p = new(nothrow) BiTNode;
        if (!p) exit (OVERFLOW);
        p->data = ch; p->lchild = p->rchild = NULL;
        T = q = p;
        Tstack.push(p);
    }

    while (count < n || Tstack.empty() == false) {
        cin >> order;
        if (order == "push") {
            count++;
            cin >> ch;
            p = new(nothrow) BiTNode;
            p->data = ch; p->lchild = p->rchild = NULL;
            if (!flag) {
                q->lchild = p; q = p;
            } else {
                q->rchild = p; q = p;
            }
            Tstack.push(p);
            flag = 0;
        } else if (order == "pop") {
            p = Tstack.top();   Tstack.pop();
            q = p;
            flag = 1;
        }
    }

}// CreatBiTree

//输出函数
Status PrintElement (TElemType e) {
    cout << e;
    return OK;
}// PrintElement

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


int main()
{
    BiTree T; int n;
    cin >> n;
    CreatBiTree (T, n);
    PostOrderTraverse (T, PrintElement);

    return 0;
}