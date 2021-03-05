#include <iostream>
    
#define OK      1
#define ERROR   0
#define OVERFLOW  -2
    
using namespace std;
    
typedef int Status;
typedef int ElemType;
    
//定义链表
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
    
//初始化创建链表
Status InitList(LinkList &L) {
    L = (LinkList) malloc(sizeof(LNode));
    if (!L) {
        exit(OVERFLOW);
    }
    
    L->next = NULL;
    return OK;
}
    
//输出整个链表
Status ListDisplay_L(LinkList &L) {
    LinkList p = L->next;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
    return OK;
}
    
//反转链表
Status ListReverse(LinkList &L, int begin, int end) {
    int i, j;
    LinkList p, pstart, pnext, pend;
    p = L;
    
    for (i = 1; p && (i < begin); i++) {
        p = p->next;
    }
    pstart = p;                                 //定位reverse的开始位置
    
    p = p->next;
    for (j = i; p->next && (j < end); j++) {   
        p = p->next;                            //定位reverse的末尾位置
    }
    
    if (i != begin || j != end || i > j) {
        cout << ERROR << endl;
        return ERROR;
    }
    
    pend = p;
    p = pstart->next;
    for (i = 0; i < end - begin; i++) {
        pnext = p->next;
        p->next = pend->next;
        pend->next = p;
        p = pnext;
    }
    pstart->next = pend;
    ListDisplay_L(L);
    
    return OK;
}
    
//销毁链表
Status ClearList(LinkList &L) {
    LinkList p, q;
    p = L->next;
    while (p) {
        q = p->next;
        free (p);
        p = q;
    }
    L->next = NULL;
    return OK;
}
    
int main()
{
    int n, k;
    LinkList L, node, last;
    
    InitList(L);        //初始化链表
    last = L;
    
    cin >> n;           //输入链表的初始元素个数
    for (int i = 0; i < n; i++) {
        node = (LinkList) malloc(sizeof(LNode));
        if (!node) exit(OVERFLOW);
        cin >> node->data;
        last->next = node;
        last = node;
    }
    last->next = NULL;
    
    cin >> k;
    int begin, end;
    for (int i = 0; i < k; i++) {
        cin >> begin >> end;
        ListReverse(L, begin, end);   
    }
    
    ClearList(L);
    return 0;
}