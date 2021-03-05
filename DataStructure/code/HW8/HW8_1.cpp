// 折半查找
#include <iostream>

using namespace std;

typedef bool Status;
typedef int KeyType;

typedef struct {
    KeyType key;    // 关键字域
} SElemType;

typedef struct {
    SElemType *elem;    //数据元素存储基址
    int length;         //表的长度
} SSTable;

// 相等判断
Status EQ (KeyType k1, KeyType k2)
{
    return k1 == k2 ? true : false;
}// EQ

// 相等判断
Status LT (KeyType k1, KeyType k2)
{
    return k1 < k2 ? true : false;
}// LT

// 二分查找
void CreatTable (SSTable &ST, int n)
{
    ST.elem = new SElemType [n];
    ST.length = n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &ST.elem[i].key);
    }
}// CreatTable

// 二分查找
int Search_Bin (SSTable ST, KeyType key)
{
    ST.elem[0].key = key;   //设置哨兵
    int low, high, mid;
    low = 1; high = ST.length;
    while (low <= high) {
        mid = (low + high) / 2;
        if (EQ(key, ST.elem[mid].key)) break;
        else if (LT(key, ST.elem[mid].key)) high = mid - 1;
        else low = mid + 1;
    }// while

    // 二分查找相同元素的处理方案
    int pos = mid;
    while (EQ(key, ST.elem[pos].key) && pos > 0) {
        --pos;
    }

    if (EQ(key, ST.elem[pos + 1].key)) return pos;
    
    return -1;
}// Search_Bin

int main()
{
    int n, m;
    KeyType key;
    SSTable ST;
    scanf("%d", &n);
    CreatTable(ST, n);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &key);
        int pos = Search_Bin(ST, key);
        printf("%d\n", pos);
    }

    return 0;
}