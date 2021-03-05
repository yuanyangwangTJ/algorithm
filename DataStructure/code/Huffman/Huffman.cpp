//Huffman 类
#include "Huffman.h"
#include <iostream>
#include <queue>
#include <algorithm>

#define OVERFLOW -2

// typedef string *HuffCode; //Huffman编码存储

// typedef struct {
//     char sym;   //字符
//     int freq;   //出现的频率
//     int parent, lchild, rchild;
//     int sub;    //数组下标
// } HTNode, *HuffTree;

// struct cmp {
//     bool operator()(HTNode& a, HTNode& b) {
//         return a.freq > b.freq;
//     }
// };

// class Huffman {
// public:
//     HuffCode HC;
//     HuffTree HT;
//     int tot;        //Huffman树的结点
//     int num;        //叶子节点的数目
//     Huffman (int *);
//     ~Huffman();
// private:
//     HuffCode _HC;
//     priority_queue<HTNode, vector<HTNode>, cmp> huffQueue;
//     void GetNum (int *);
//     void CreatNode (int, int);
//     void CreatTree (int *);
//     void GetCode ();
// };


void Huffman::GetNum(int *countMap)
{
    for (int i = -128; i <= 128; i++) {
        if (countMap[i]) ++num;
    }
}


Huffman::Huffman(int *countMap)
{
    tot = num = 0;
    GetNum (countMap);
    _HC = new(nothrow) string[257];
    if (!_HC) exit(OVERFLOW);
    HC = &_HC[128];

    if (num <= 1)   return;
    HT = new(nothrow) HTNode[num*2 - 1];
    CreatTree (countMap);
    GetCode ();
}

Huffman::~Huffman()
{
    //释放空间
    delete[] HT;
    delete[] _HC;
}

void Huffman::CreatNode (int l, int r) 
{
    //根据左右结点建立Huffman树的一个新结点
    HT[l].parent = HT[r].parent = tot;
    HT[tot].lchild = l; HT[tot].rchild = r;
    HT[tot].freq = HT[l].freq + HT[r].freq;
    HT[tot].sub = tot;
}

void Huffman::CreatTree (int *countMap) 
{
    //创建Huffman树
    for (int i = -128; i <= 128; i++) {
        if (countMap[i]) {
            HT[tot].sym = (char)i;
            HT[tot].freq = countMap[i];
            HT[tot].lchild = HT[tot].rchild = -1;
            HT[tot].sub = tot;
            huffQueue.push(HT[tot]);    //结点加入优先队列
            ++tot;
        }
    }
    while (!huffQueue.empty()) {
        if (huffQueue.size() == 1) {
            break;      //只剩一个结点，说明建树完成
        }
        int l = huffQueue.top().sub;
        huffQueue.pop();
        int r = huffQueue.top().sub;
        huffQueue.pop();
        CreatNode(l, r);
        huffQueue.push(HT[tot]);
        ++tot;
    }
    HT[--tot].parent = -1;      
}

void Huffman::GetCode ()
{
    //huffman编码生成
    for (int i = 0; i < num; i++) {
        int sub = HT[i].sym;    //编码数组的下标
        HC[sub] = "";
        int temp = i;       
        while (HT[temp].parent != -1) {     // 左孩子为0
            if (HT[HT[temp].parent].lchild == temp) {
                HC[sub] += '0';
            } else {                        // 右孩子为1
                HC[sub] += '1';
            }
            temp = HT[temp].parent;
        }

        reverse (HC[sub].begin(), HC[sub].end());
    }
}