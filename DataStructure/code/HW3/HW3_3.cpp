#include <iostream>
#include <cstring>
 
#define STACK_INIT_SIZE 10
#define STACKINCREMENT  5
#define OK              1
#define ERROR           0
#define OVERFLOW        -2
 
using namespace std;
 
typedef int Status;
typedef char SElemType;
 
typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

//初始化栈
Status InitStack (SqStack &S) {
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base) exit (OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}   //InitStack
 
//push操作
Status Push(SqStack &S, SElemType e) {
    if (S.top - S.base >= S.stacksize) {//栈满
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base) exit (OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}   //push
 
//pop操作
Status Pop(SqStack &S, SElemType &e) {
    if (S.top == S.base) {
        return ERROR;
    }
    e = * --S.top;
    return OK;
}   //pop
 
//判断是否为空栈
Status StackEmpty(SqStack S) {
    return S.top == S.base ? OK : ERROR;
}
 
//判断是否可以按顺序通过
Status Pass(SqStack S, string out, string in) {
    int length = out.length();
    int i, j = 0;
    for (i = 0; i < length; i++) {
        //列车出站的序列
        int top_flag = 0;               //判断列车是否在栈顶
        int in_flag = 0;                //判断列车是否在未进入行列
 
        if ((!StackEmpty(S)) && *(S.top - 1) == out[i]) { //列车在栈顶
            Pop(S, out[i]);
            top_flag = 1;
        } else {                    //列车未进入或者在下面
            for (; j < length; j++) {
                if (out[i] == in[j]) {
                    in_flag = 1;
                    j++;
                    break;
                }
                Push(S, in[j]);
            }
        }
 
        if (!top_flag && !in_flag) {
            return ERROR;           //不在栈顶也不在未进入行列
        }
    }
    return OK;
}
 
int main()
{
    SqStack S;
    InitStack(S);
    string in, out;
 
    cin >> in;
    
    while (cin >> out) {
        if (Pass(S, out, in)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
 
    return 0;
}