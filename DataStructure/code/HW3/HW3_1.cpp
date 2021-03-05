#include <iostream>
#include <cstring>
 
#define STACKINCREMENT  10
#define OK              1
#define ERROR           0
#define OVERFLOW        -2
 
using namespace std;
 
typedef int Status;
typedef int SElemType;
typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

//初始化栈
Status InitStack (SqStack &S, int n) {
    S.base = (SElemType *)malloc(n * sizeof(SElemType));
    if (!S.base) exit (OVERFLOW);
    S.top = S.base;
    S.stacksize = n;
    return OK;
}   //InitStack
 
//push操作
Status Push(SqStack &S, SElemType e) {
    if (S.top - S.base >= S.stacksize) {//栈满
        cout << "Stack is Full" << endl;
        return ERROR;
        // S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        // if (!S.base) exit (OVERFLOW);
        // S.top = S.base + S.stacksize;
        // S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}   //push
 
//pop操作
Status Pop(SqStack &S, SElemType &e) {
    if (S.top == S.base) {
        cout << "Stack is Empty" << endl;
        return ERROR;
    }
    e = * --S.top;
    return OK;
}   //pop
 
//输出栈内元素
Status PrintStack(SqStack S) {
    for (int i = 1; i <= (S.top - S.base); i++) {
        cout << *(S.top - i) << " ";
    }
    cout << endl;
    return OK;
}   //print
 
int main()
{
    SqStack S;
    int n, e;
    string command;
    cin >> n;
    InitStack(S, n);
 
    do {
        cin >> command;
        if (command == "pop") {
            if (Pop(S, e)) cout << e << endl;
        } else if (command == "push") {
            cin >> e;
            Push(S, e);
        }
    } while (command != "quit");
    PrintStack(S);
 
    return 0;
}