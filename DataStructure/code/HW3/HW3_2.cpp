#include <cstring>
#include <iostream>

#define STACK_INIT_SIZE 10
#define STACKINCREMENT 5
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

using namespace std;

typedef int Status;
typedef char OperatorType;
typedef int OperandType;

template <typename T>
struct SqStack {
    T* base;
    T* top;
    int stacksize;
};

//初始化栈
template <typename T>
Status InitStack(SqStack<T>& S) {
    S.base = (T*)malloc(STACK_INIT_SIZE * sizeof(T));
    if (!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
} //InitStack

//push操作
template <typename T>
Status Push(SqStack<T>& S, T e) {
    if (S.top - S.base >= S.stacksize) { //栈满
        S.base = (T*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(T));
        if (!S.base)
            exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
} //push

//pop操作
template <typename T>
Status Pop(SqStack<T>& S, T& e) {
    if (S.top == S.base) {  //错误判断
        cout << "ERROR" << endl;
        exit (ERROR);
    }
    e = *--S.top;
    return OK;
} //pop

//判断是否为空栈
template <typename T>
Status StackEmpty(SqStack<T> S) {
    return S.top == S.base ? OK : ERROR;
}

//获取栈顶元素
template <typename T>
T GetTop(SqStack<T> S) {
    if (S.base == S.top) {          //错误判断
        cout << "ERROR" << endl;
        exit (ERROR);
    }
    return *(S.top - 1);
} //GetTop

//非法输入
void Invalid() {
    cout << "ERROR" << endl;
    exit(ERROR);
}

//判断输入是否为运算符
Status In(char e) {
    switch (e) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '#':
        return TRUE;
    default:
        return FALSE;
    }
} //In

//判断优先级
OperatorType Precede(OperatorType o1, OperatorType o2) {
    OperatorType relation;

    switch (o2) {
    case '+':
    case '-':
        if (o1 == '(' || o1 == '#')
            relation = '<';
        else
            relation = '>';
        break;

    case '*':
    case '/':
        if (o1 == '*' || o1 == '/' || o1 == ')')
            relation = '>';
        else
            relation = '<';
        break;

    case '(':
        if (o1 == ')') {
            Invalid();
        } else
            relation = '<';
        break;

    case ')':
        switch (o1) {
        case '(':
            relation = '=';
            break;
        case '#':
            Invalid();
        default:
            relation = '>';
        }
        break;

    case '#':
        switch (o1) {
        case '#':
            relation = '=';
            break;
        case '(':
            Invalid();
        default:
            relation = '>';
        }
    }

    return relation;
}   //Precede

//运算
OperandType Operate(OperandType a, OperatorType theta, OperandType b) {
    OperandType r;
    switch(theta) {
		case '+':
			r = a + b;
			break;
		case '-': 
			r = a - b;
			break;
		case '*':
			r = a * b;
			break;
		case '/':
            if (b == 0) {
                cout << "ERROR" << endl;
                exit(ERROR);
            }
			r = a / b;
			break;
	}
    return r;
}// Operate

//算符优先算法
OperandType EvaluateExpression(SqStack<OperatorType> OPTR, SqStack<OperandType> OPND) {
    InitStack(OPTR);    Push(OPTR, '#');    //'#'压栈
    InitStack(OPND);    Push(OPND, 0);
    OperatorType c = cin.peek();
    OperatorType x, theta;
    OperandType oprd, a, b;
    
    if (c == '=') c = '#';          //题目专属定制 '#' = '='
    while (c != '#' || GetTop(OPTR) != '#') {
        
        if (!In(c)) {       //不是运算符
            if (!isdigit(c)) {  //不是运算符又不是数字，异常退出
                Invalid();
            }
            cin >> oprd;    Push(OPND, oprd);
            c = cin.peek();
        } else {

            switch (Precede(GetTop(OPTR), c)) {
                case '<':   //栈顶元素优先级低
                    c = cin.get();
                    Push(OPTR, c);  c = cin.peek();
                    break;
                case '=':   //脱括号并接收下一字符
                    c = cin.get();
                    Pop(OPTR, x);   c = cin.peek();
                    break;
                case '>':   //退栈并将运算结果入栈
                    Pop(OPTR, theta);
                    Pop(OPND, b);   Pop(OPND, a);
                    Push(OPND, Operate(a, theta, b));
                    break;
            }// switch
        }// else
        if (c == '=') c = '#';
    }// while
    if (GetTop(OPTR) != '#') {
        Invalid();
    }// 错误判断

    return GetTop(OPND);
} //EvaluateExpression

int main()
{
    SqStack<OperatorType> OPTR;
    SqStack<OperandType> OPND;
    OperandType result = EvaluateExpression(OPTR, OPND);
    cout << result << endl;

    return 0;
}