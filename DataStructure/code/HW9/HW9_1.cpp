// 排序
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

// 打印输出顺序表
void PrintSqList (SqList L)
{
    for (int i = 1; i <= L.length; i++)
        printf("%d ", L.r[i].key);
    printf("\n");
}

// 直接插入排序
void InsertSort (SqList &L) 
{
    int i, j;
    for (i = 2; i <= L.length; ++i) {
        if (L.r[i].key < L.r[i - 1].key) {
            L.r[0] = L.r[i];
            L.r[i] = L.r[i - 1];
            for (j = i - 2; L.r[0].key < L.r[j].key; --j)
                L.r[j + 1] = L.r[j];
            L.r[j + 1] = L.r[0];
        }
    }
}// InsertSort

// 选择排序
void SelectSort (SqList &L)
{
    int i, j;
    for (i = 1; i < L.length; ++i) {
        int k = i;
        for (j = i + 1; j <= L.length; ++j) {
            if (L.r[k].key > L.r[j].key) k = j;
        }
        if (i != k) {
            L.r[0] = L.r[i];
            L.r[i] = L.r[k];
            L.r[k] = L.r[0];
        }
    }
}// SelectSort

// 希尔排序
void ShellSort(SqList &L) 
{
    int gap, i, j;
    for (gap = L.length >> 1; gap > 0; gap >>= 1)
        for (i = gap + 1; i <= L.length; i++) {
            L.r[0] = L.r[i];
            for (j = i - gap; j >= 1 && L.r[j].key > L.r[0].key; j -= gap)
                    L.r[j + gap] = L.r[j];
            L.r[j + gap] = L.r[0];
        }
}// ShellSort

// 起泡排序（冒泡排序）
void BubbleSort (SqList &L)
{
    bool change = true;
    for (int i = L.length; i > 1 && change; --i) {
        change = false;
        for (int j = 1; j < i; ++j) {
            if (L.r[j+1].key < L.r[j].key) {
                L.r[0] = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = L.r[0];
                change = true;
            }
        }
    }
}// BubbleSort

// 快速排序
// 交换顺序子表r[low..high]记录
int Partition (SqList &L, int low, int high)
{
    L.r[0] = L.r[low];
    KeyType pivotkey = L.r[low].key;    // 枢轴记录关键字
    while (low < high) {
        while (low < high && L.r[high].key >= pivotkey) --high;
        L.r[low] = L.r[high];
        while (low < high && L.r[low].key <= pivotkey) ++low;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];
    return low;
}// Partition

// QuickSort
void QuickSort (SqList &L, int low, int high)
{
    if (low < high) {
        int pivot = Partition(L, low, high);
        QuickSort(L, low, pivot - 1);
        QuickSort(L, pivot + 1, high);
    }
}// QuickSort

/**********************************
// 归并排序
**********************************/
void Merge (RcdType SR[], int first, int mid, int last, RcdType temp[])
{
    // 将SR[first..mid]和SR[mid+1..last]归并
    int i = first, j = mid + 1;
    int m = mid, n = last;
    int k = 0;
    while (i <= m && j <= n) {
        if (SR[i].key <= SR[j].key)
            temp[k++] = SR[i++];
        else 
            temp[k++] = SR[j++];
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
void MSort (RcdType SR[], int first, int last, RcdType temp[])
{
    // 将SR[first..last]归并排序
    if (first < last) {
        int mid = (first + last) / 2;
        MSort(SR, first, mid, temp);
        MSort(SR, mid + 1, last, temp);
        Merge(SR, first, mid, last, temp);
    }
    
}// MSort

// 归并排序（迭代）
void MergeSort (SqList &L)
{
    RcdType *temp = new RcdType[L.length + 1];
    MSort(L.r, 1, L.length, temp);
}// MergeSort

/******************************************
 * 堆排序
 * ***************************************/

typedef SqList HeapType;

void HeapAdjust (HeapType &H, int start, int end)
{
    // int parent = start;
    // int child = parent * 2 + 1;
    // while (child <= parent) {
    //     if (child + 1 <= end && H.r[child].key < H.r[child + 1].key)
    //         child++;
    //     if (H.r[parent].key > H.r[child].key)
    //         return ;
    //     else {
    //         // 交换元素
    //         RcdType temp = H.r[parent];
    //         H.r[parent] = H.r[child];
    //         H.r[child] = temp;

    //         parent = child;
    //         child = parent * 2 + 1;
    //     }
    // }
    // 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，
    // 本函数调整H.r[s]的关键字，使H.r[s..m]成为一个大顶堆
    int s = start, m = end, j;
    RcdType rc = H.r[s];
    for (j = 2*s; j <= m; j *= 2) {
        if (j < m && (H.r[j].key <= H.r[j+1].key))
            ++j;
        if (rc.key > H.r[j].key) break;
        H.r[s] = H.r[j];    s = j;
    }
    H.r[s] = rc;

}// HeapAdjust

void HeapSort (HeapType &H)
{
    int len = H.length;
    for (int i = len/2; i > 0; i--)
        HeapAdjust(H, i, len);
    
    for (int i = len; i > 1; i--) {
        RcdType temp = H.r[1];
        H.r[1] = H.r[i];
        H.r[i] = temp;

        HeapAdjust(H, 1, i - 1);
    }
}// HeapSort


int main()
{
    SqList L;
    cin >> L.length;
    CreatSqList(L);
    
    // InsertSort (L);
    // SelectSort(L);
    // BubbleSort(L);
    // QuickSort(L, 1, L.length);
    MergeSort(L);
    // ShellSort(L);
    // HeapSort(L);
    PrintSqList(L);

    return 0;
}