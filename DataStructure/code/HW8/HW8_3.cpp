// 哈希表
#include <iostream>
#include <cstring>
#include <cmath>

#define SUCCESS     1
#define UNSUCCESS   0
#define NULLKEY     -1
#define KEY         1

using namespace std;

// 此处哈希表不存储字符串数据
typedef int Status;
typedef int KeyType;
typedef struct {
    KeyType key;        // 键
    int num;            // 散列次数
} ElemType;

typedef struct {
    ElemType *elem;     // 数据元素存储基址
    int count;          // 当前数据元素个数
    int M;              // 模数以及实际长度
    int sizeindex;      // 关键字总数
} HashTable;

// 素数判断函数
bool isPrime (int n) {
    int i, k = sqrt(n);
    for (i = 2; i <= k; i++) {
        if (n%i == 0) break;
    }
    return i > k? true : false;
}// isPrime

// 哈希表创建
void CreatHash (HashTable &H)
{
    int N, P;
    scanf("%d%d", &N, &P);
    H.sizeindex = N;
    while (!isPrime(P)) {
        P++;
    }
    H.M = P;
    H.count = 0;
    H.elem = new ElemType[H.M];
    for (int i = 0; i < H.M; i++) {
        H.elem[i].key = NULLKEY;
    }
}// CreatHash

// 哈希查找
Status SearchHash (HashTable H, int hash)
{
    if (H.elem[hash].key == NULLKEY) return UNSUCCESS;
    return SUCCESS;
}// SearchHash

// hash值生成和插入
Status Hash (HashTable &H, string str, int &hash)
{
    int length = str.length();
    int Insertflag = 0;
    hash = 0;
    char *pkey = (char *)str.c_str();
    for (int i = 0; i < length; i++) {
        hash = (hash * 37 % H.M + int(pkey[i])) % H.M;
    }
    if (H.elem[hash].key == NULLKEY) {
        H.elem[hash].key = KEY;
        H.count++;
        Insertflag = 1;
        H.elem[hash].num = 0;
    } else {
        int cnt = 0;        // 探测次数
        int flag = 1;       // 散列数的符号
		int hashvalue = hash;
        while (cnt < H.M) {
            hashvalue = ((hash + flag * cnt * cnt) % H.M + H.M) % H.M;
            flag = - flag;

            if (H.elem[hashvalue].key == NULLKEY) { //插入成功
                H.elem[hashvalue].key = KEY;
                H.count++;
                Insertflag = 1;
                H.elem[hashvalue].num = cnt;
                break;
            }

			hashvalue = ((hash + flag * cnt * cnt) % H.M + H.M) % H.M;
            flag = - flag;

            if (H.elem[hashvalue].key == NULLKEY) { //插入成功
                H.elem[hashvalue].key = KEY;
                H.count++;
                Insertflag = 1;
                H.elem[hashvalue].num = cnt;
                break;
            }
            ++cnt;
        }
    }
    if (Insertflag) return SUCCESS;
    return UNSUCCESS;
}

int main()
{
    HashTable H;
	string str;
    int hash;
    CreatHash(H);
    for (int i = 0; i < H.sizeindex; i++) {
        cin >> str;
        if(Hash(H, str, hash)) printf("%d", hash);
        else printf("-");
		if (i < H.sizeindex - 1) printf(" ");
    }
    printf("\n");

    return 0;
}