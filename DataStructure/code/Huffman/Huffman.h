#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <queue>

using namespace std;
typedef string *HuffCode; //Huffman编码存储

typedef struct {
    char sym;   //字符
    int freq;   //出现的频率
    int parent, lchild, rchild;
    int sub;    //数组下标
} HTNode, *HuffTree;

struct cmp {
    bool operator()(HTNode a, HTNode b) {
        return a.freq > b.freq;
    }
};

class Huffman {
public:
    HuffCode HC;
    HuffTree HT;
    int tot;        //Huffman树的结点
    int num;        //叶子节点的数目
    Huffman (int *);
    ~Huffman();
private: 
    HuffCode _HC;
    priority_queue<HTNode, vector<HTNode>, cmp> huffQueue;
    void GetNum (int *);
    void CreatNode (int, int);
    void CreatTree (int *);
    void GetCode ();
};

#endif