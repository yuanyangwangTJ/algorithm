// 二叉排序树
#include <iostream>
#include <stack>

using namespace std;

typedef int KeyType;

typedef struct {
    KeyType key;        // 关键字域
    int count;          // 元素个数
} ElemType;

typedef struct BiTNode{
    ElemType data;      //数据元素
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 初始化
void InitBST (BiTree &T) {
    T = new BiTNode;
    T->rchild = NULL;
    T->lchild = NULL;
    T->data.count = 1;
}

// 查找元素的个数
int SearchBST (BiTree T, KeyType key)
{
    BiTree p = T;
    while (p) {
        if (key == p->data.key) {
            return p->data.count;
        } else if (p->data.key > key) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    // 寻找前驱结点

    return 0;
}

// 二叉树排序树插入结点
void InsertBST (BiTree &T, KeyType key)
{
    int flag = 0;   //表示key值是否已经存在
    BiTree p, q;
    BiTree S;
    InitBST(S);
    S->data.key = key;

    if (!T) T = S;
    else {
        p = T;
        while (p) {
            q = p;
            if (S->data.key == p->data.key) {
                p->data.count++;
                delete S;    // key值已经存在，无需删除
                flag = 1; break;
            } else if (S->data.key < p->data.key) {
                p = p->lchild;
            } else {
                p = p->rchild;
            }
        }
        if (!flag) {
            if (S->data.key < q->data.key) q->lchild = S;
            else q->rchild = S;
        }
    }
    return ;
}// InsertBST

// 二叉排序树删除结点
void delNode (BiTree &T, BiTree p, BiTree f)
{
    BiTree s, q;
    int tag = 0;    // tag == 0表示左右孩子至少有一个为空
    if (p->data.count > 1) {
        (p->data.count)--;
    }// 有重复元素，删除一个即可
    else {
        if (!p->lchild) s = p->rchild;
        else if (!p->rchild) s = p->lchild;
        else {
            q = p; s = p->lchild;   // q是s的双亲
            while (s->rchild) {
                q = s; s = s->rchild;
            }
            p->data = s->data;
            if (q == p) q->lchild = s->lchild;
            else q->rchild = s->lchild;
            delete s;
            tag = 1;    //左右孩子都存在，删除s
        }
        if (!tag) {
            if (!f) T = s;  // p是根结点
            else if (f->lchild == p) f->lchild = s;
            else f->rchild = s;
            delete s;
        }
    }
    
    return ;
}// delNode

// 二叉树排序树的删除操作
int DeleteBST (BiTree &T, KeyType key)
{
    BiTree p, f;
    int findFlag = 0;
    p = T; f = NULL;
    while (p) {
        if (p->data.key == key) {
            delNode (T, p, f);
            findFlag = 1;
            break;
        } else if (p->data.key > key) {
            f = p; p = p->lchild;
        } else {
            f = p; p = p->rchild;
        }
    }
    return findFlag;
}// DeleteBST

// 寻找最小值，这里树非空
KeyType FindMin (BiTree T) 
{
    BiTree p = T;
    while (p->lchild) {
        p = p->lchild;
    }
    return p->data.key;
}// FindMin

// 寻找前驱结点
BiTree FrontBST (BiTree T, KeyType key)
{
    BiTree p, q = NULL, pre = NULL;
    stack<BiTree> S;
    p = T;
    do {
        while (p) {
            S.push(p); p = p->lchild;
        }
        if (!S.empty()) {
            p = S.top(); S.pop();   // 出栈
            if (p->data.key >= key) {
                pre = q;
                break;
            }
            q = p;                  // 记录结点
            p = p->rchild;
        }
    } while (!S.empty() || p);
    if (q && q->data.key < key) pre = q;
    
    return pre;
}// FrontBST

void OperatorBST (BiTree &T)
{
    int op;
    KeyType key;
    BiTree pre; //前驱结点
    cin >> op;
    switch (op) {
    case 1: {// 插入元素
        cin >> key;
        InsertBST(T, key);
        break;
    }
    case 2: {// 删除元素
        cin >> key;
        if (DeleteBST(T, key)) ;
        else cout << "None" << endl;
        break;
    }
    case 3: {// 查询
        cin >> key;
        int cnt = SearchBST(T, key);
        cout << cnt << endl;
        break;
    }
    case 4: {// 最小元素
        if (T) {
            KeyType min = FindMin(T);
            cout << min << endl;
        }
        break;
    }
    case 5: {// 前驱结点
        cin >> key;
        pre = FrontBST(T, key);
        if (pre) cout << pre->data.key << endl;
        else cout << "None" << endl;
        break;
    }
    default: ;
    }
}

int main()
{
    int n;
    BiTree T = NULL;
    cin >> n;
    for (int i = 0; i < n; i++) {
        OperatorBST(T);
    }

    return 0;
}