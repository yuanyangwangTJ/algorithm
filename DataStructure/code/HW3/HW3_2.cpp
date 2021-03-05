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

//��ʼ��ջ
template <typename T>
Status InitStack(SqStack<T>& S) {
    S.base = (T*)malloc(STACK_INIT_SIZE * sizeof(T));
    if (!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
} //InitStack

//push����
template <typename T>
Status Push(SqStack<T>& S, T e) {
    if (S.top - S.base >= S.stacksize) { //ջ��
        S.base = (T*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(T));
        if (!S.base)
            exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
} //push

//pop����
template <typename T>
Status Pop(SqStack<T>& S, T& e) {
    if (S.top == S.base) {  //�����ж�
        cout << "ERROR" << endl;
        exit (ERROR);
    }
    e = *--S.top;
    return OK;
} //pop

//�ж��Ƿ�Ϊ��ջ
template <typename T>
Status StackEmpty(SqStack<T> S) {
    return S.top == S.base ? OK : ERROR;
}

//��ȡջ��Ԫ��
template <typename T>
T GetTop(SqStack<T> S) {
    if (S.base == S.top) {          //�����ж�
        cout << "ERROR" << endl;
        exit (ERROR);
    }
    return *(S.top - 1);
} //GetTop

//�Ƿ�����
void Invalid() {
    cout << "ERROR" << endl;
    exit(ERROR);
}

//�ж������Ƿ�Ϊ�����
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

//�ж����ȼ�
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

//����
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

//��������㷨
OperandType EvaluateExpression(SqStack<OperatorType> OPTR, SqStack<OperandType> OPND) {
    InitStack(OPTR);    Push(OPTR, '#');    //'#'ѹջ
    InitStack(OPND);    Push(OPND, 0);
    OperatorType c = cin.peek();
    OperatorType x, theta;
    OperandType oprd, a, b;
    
    if (c == '=') c = '#';          //��Ŀר������ '#' = '='
    while (c != '#' || GetTop(OPTR) != '#') {
        
        if (!In(c)) {       //���������
            if (!isdigit(c)) {  //����������ֲ������֣��쳣�˳�
                Invalid();
            }
            cin >> oprd;    Push(OPND, oprd);
            c = cin.peek();
        } else {

            switch (Precede(GetTop(OPTR), c)) {
                case '<':   //ջ��Ԫ�����ȼ���
                    c = cin.get();
                    Push(OPTR, c);  c = cin.peek();
                    break;
                case '=':   //�����Ų�������һ�ַ�
                    c = cin.get();
                    Pop(OPTR, x);   c = cin.peek();
                    break;
                case '>':   //��ջ������������ջ
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
    }// �����ж�

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