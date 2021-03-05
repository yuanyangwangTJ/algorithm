// 字典树
#include <iostream>
#include <cstring>

using namespace std;

const int SIZE = 26;
typedef struct Trie {
    int count;      // 记录前缀出现的次数
    bool isEnd;     // 是否为字符串
    struct Trie* next[SIZE];
} Trie;

// 动态申请的初始化
Trie* InitNew (struct Trie* r) {
    r = new Trie;
    r->count = 0;
    r->isEnd = false;
    for (int i = 0; i < SIZE; i++) {
        r->next[i] = NULL;
    }
    return r;
}// InitNew

// 插入单词字符串
void Insert (struct Trie* Root, string s)
{
    int len = s.length();
    int id;
    struct Trie* root = Root;
    for (int i = 0; i < len; i++) {
        id = s[i] - 'a';
        if (root->next[id] == NULL) {
            root->next[id] = InitNew(root->next[id]);
        }
        root = root->next[id];
        root->count++;
    }
    root->isEnd = true;
}// Insert

// 查找单词字符串
int Search (struct Trie* Root, string s)
{
    int len = s.length();
    int id;
    struct Trie* root = Root;
    for (int i = 0; i < len; i++) {
        id = s[i] - 'a';
        if (root->next[id] == NULL) return 0;
        else root = root->next[id];
    }
    return root->count;
}// Search

int main()
{
    struct Trie* Root = NULL;
    Root = InitNew(Root);
    int n, m;
    string str;
    cin >> n >> m;
    for (int u = 0; u < n; u++) {
        cin >> str;
        Insert(Root, str);
    }

    for (int v = 0; v < m; v++) {
        cin >> str;
        int count = Search(Root, str);
        cout << count << endl;
    }

    return 0;
}