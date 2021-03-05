//用栈来模拟递归
#include <iostream>
#include <stack>
#include <time.h>

#define TESTCOUNT 10000000
#define INTMAX 998244353    //  测试使用

using namespace std;

typedef long long int LONGINT;
typedef struct{
    int n;              //函数的输入参数
    //int returnAddress;
    //函数的返回地址，但是因为栈的顺序相当于地址，此处不设置
} Data;

//递归实现
LONGINT Recursion(int n) {
    if (n == 1) return 1;      //停止调用
    return n * Recursion(n-1);  //调用自身
}

//栈实现
LONGINT StackCompute(int n) {
    LONGINT result = 1;
    stack<Data> mystack;
    Data d;
    do {
        d.n = n;
        mystack.push(d);
        n = n - 1;
    } while (n >= 1);
    while (!mystack.empty()) {
        result = result * (mystack.top()).n;
        mystack.pop();
    }
    return result;
}

//迭代实现
LONGINT iteration(int n) 
{
    LONGINT result = 1;
    for (int i = n; i >= 1; i--) {
        result *= i;
    }
    return result;
}
int main()
{
    int n;
    clock_t start, end;     //计算时间
    cout << "Simulate Recursion with Stack." << endl;
    cout << "Now we will compute the n!, "
         << "please input the num n: " << endl;
    cin >> n;

    //test iteration
    start = clock();
    for (int i = 0; i < TESTCOUNT; i++)  iteration(n);
    cout << "The result using iteration is: " << iteration(n) << endl;
    end = clock();
    cout <<"Time : " << (end-start) << endl;
    
    //test recursion
    start = clock();
    for (int i = 0; i < TESTCOUNT; i++)  Recursion(n);
    cout << "The result using recursion is: " << Recursion(n) << endl;
    end = clock();
    cout <<"Time : " << (end-start) << endl;

    //test stack
    start = clock();
    for (int i = 0; i < TESTCOUNT; i++)  StackCompute(n);
    cout << "The result using stack is :    " << StackCompute(n) << endl;
    end = clock();
    cout <<"Time : " << (end-start) << endl;

    return 0;
}