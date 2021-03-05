// 使用归并排序求逆序对数
#include <iostream>

using namespace std;

typedef int KeyType;        // 定义关键字类型为整数类型
typedef struct {
    KeyType key;            // 关键字项
    //InfoType otherinfo;   // 其他数据项
} RcdType;

typedef struct {
    RcdType *r;     // r[0]闲置或者用作哨兵
    int length;     // 顺序表长度
} SqList;           // 顺序表类型

// 创建顺序表
void CreatSqList (SqList &L)
{
    L.r = new RcdType[L.length + 1];
    for (int i = 1; i <= L.length; ++i) {
        scanf("%d", &L.r[i].key);
    }
}// CreatSqList

// 删除顺序表
void DeleteSqList (SqList &L)
{
    delete[] L.r;
}

/**********************************
// 归并排序
**********************************/
void Merge (RcdType SR[], int first, int mid, int last, RcdType temp[], int& count)
{
    // 将SR[first..mid]和SR[mid+1..last]归并
    int i = first, j = mid + 1;
    int m = mid, n = last;
    int k = 0;
    while (i <= m && j <= n) {
        if (SR[i].key <= SR[j].key)
            temp[k++] = SR[i++];
        else {
            temp[k++] = SR[j++];
            count += mid - i + 1;
        }
    }

    while (i <= m)
        temp[k++] = SR[i++];

    while (j <= n)
        temp[k++] = SR[j++];

    for (i = 0; i < k; i++)
        SR[first + i] = temp[i];
}// Merge

// 迭代的归并排序
// TR2为辅助数组
void MSort (RcdType SR[], int first, int last, RcdType temp[], int& count)
{
    // 将SR[first..last]归并排序
    if (first < last) {
        int mid = (first + last) / 2;
        MSort(SR, first, mid, temp, count);
        MSort(SR, mid + 1, last, temp, count);
        Merge(SR, first, mid, last, temp, count);
    }
    
}// MSort

// 归并排序（迭代）
void MergeSort (SqList &L)
{
    int count = 0;
    RcdType *temp = new RcdType[L.length + 1];
    MSort(L.r, 1, L.length, temp, count);
    cout << count << endl;
}// MergeSort

int main()
{
    SqList L;
    cin >> L.length;
    while (L.length > 0) {
        CreatSqList(L);
        MergeSort(L);
        DeleteSqList(L);
        cin >> L.length;
    }
    
    return 0;
}