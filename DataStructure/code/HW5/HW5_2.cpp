//判断二叉树是否为同构
#include <iostream>

#define OVERFLOW    -2
#define TRUE    1
#define FALSE   0
#define null    -1
using namespace std;

typedef int Tree;
typedef int Status;
typedef char TElemType;
typedef struct TNode {
    TElemType data;
    Tree lchild, rchild;
}TNode;

typedef struct {
    TNode *node;
    int root, n;        //根的位置和结点
} BiTree;

void CreatBiTree (BiTree &T) {
    char lc, rc;
    cin >> T.n;
    T.node = new(nothrow) TNode[T.n];
    if (!T.node) exit(OVERFLOW);

    int *Root = new(nothrow) int[T.n];  //寻找根结点
    if (!Root)   exit(OVERFLOW);
    for (int i = 0; i < T.n; i++)   Root[i] = 1;

    for (int i = 0; i < T.n; i++) {
        cin >> T.node[i].data >> lc >> rc;
        if (lc == '-') T.node[i].lchild = null;
        else {
            T.node[i].lchild = lc - '0';
            Root[lc - '0'] = 0;
        }

        if (rc == '-') T.node[i].rchild = null;
        else {
            T.node[i].rchild = rc - '0';
            Root[rc - '0'] = 0;
        }
    }
    for (int i = 0; i < T.n; i++) {
        if (Root[i]) {
            T.root = i; break;
        }
    }
    if (!T.n)   T.root = null;
}

Status Isomorphism(BiTree Ta, BiTree Tb, Tree Ra, Tree Rb) {
    TNode t1 = Ta.node[Ra], t2 = Tb.node[Rb];
    if (Ra == null && Rb == null)   return TRUE;    //两树为空——相同
    if ((Ra == null && Rb != null) || (Ra != null && Rb == null)) 
        return FALSE;           //各有一空——不同
    if (t1.data != t2.data)
        return FALSE;           //根元素不同——不同
    if (t1.lchild == null && t2.lchild == null)     //左子树为空，看右子树
        return Isomorphism(Ta, Tb, t1.rchild, t2.rchild);
    
    if ((t1.lchild != null && t2.lchild != null) && Ta.node[t1.lchild].data == Tb.node[t2.lchild].data)
        return (Isomorphism(Ta, Tb, t1.lchild, t2.lchild) && 
        Isomorphism(Ta, Tb, t1.rchild, t2.rchild));
    //两树左子树均存在且左子树节点相同时，同时判断两树左右树是否相同
    else    //如果左子树节点不同——则左右交换，判断
        return (Isomorphism(Ta, Tb, t1.lchild, t2.rchild) && 
        Isomorphism(Ta, Tb, t1.rchild, t2.lchild));
}// Isomorphism

//树的深度计算
int Depth (BiTree T, Tree tr) {
    int depl, depr;
    if (tr != null) {
        depl = Depth (T, T.node[tr].lchild);
        depr = Depth (T, T.node[tr].rchild);
        if (depl >= depr)  return (depl + 1);
        else return (depr + 1);
    }
    return 0;
}// Depth

int main()
{
    BiTree Ta, Tb;
    CreatBiTree (Ta);
    CreatBiTree (Tb);
    if (Isomorphism (Ta, Tb, Ta.root, Tb.root)) {
        cout << "Yes" << endl;
    } else cout << "No" << endl;

    cout << Depth (Ta, Ta.root) << endl;
    cout << Depth (Tb, Tb.root) << endl;

    return 0;
}