//Huffman 类
#include <iostream>
#include <queue>
#include <algorithm>
#include <fstream>
#include <bitset>
#include <string>
#include <cstring>
#include <ctime>
#include <conio.h>

#define OVERFLOW -2

using namespace std;

typedef string *HuffCode; //Huffman编码存储

typedef struct {
    char sym;   //字符
    int freq;   //出现的频率
    int parent, lchild, rchild;
    int sub;    //数组下标
} HTNode, *HuffTree;

struct cmp {
    bool operator()(HTNode& a, HTNode& b) {
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

void Compress(ifstream &fin, ofstream &fout)
{
    //huffman压缩
    int _countMap[257] = {0};
    int *countMap = &_countMap[128];
    countMap[128] = 1;
    char buffer[1024];

    cout << "Reading frequence of word......" << endl;
    while (fin && !fin.eof()) {
        fin.read(buffer, 1024);
        int readNum = fin.gcount();
        for (int i = 0; i < readNum; i++) {
            countMap[int(buffer[i])]++;
        }
    }// 这里完成统计字符的任务
    cout << "Creating Huffman tree......" << endl;
    Huffman HF(countMap);

    fout.write((char*)&HF.num, sizeof(int));
    for (int i = -128; i < 128; i++) {
        if (countMap[i]) {
            char sym = char(i);
            fout.write((char*)&sym, sizeof(char));
            fout.write((char*)&countMap[i], sizeof(int));
        }
    }// 写入数据方便生成Huffman表解码

    cout << "Compressing......" << endl;
    fin.clear();    fin.seekg(ios::beg);

    string huffStr = "";
    while (fin && !fin.eof()) {
        fin.read(buffer, 1024);
        int readNum = fin.gcount();
        for (int i = 0; i < readNum; i++) {
            huffStr.append(HF.HC[int(buffer[i])]);
        }
        
        while (huffStr.length() >= 8) {
            string str = huffStr.substr(0, 8);
            bitset<8> bts(str);
            fout.write((char*)&bts, sizeof(char));
            huffStr = huffStr.erase(0, 8);
        }
    }
    huffStr.append(HF.HC[int(buffer[128])]);    //加入自建的EOF
    while (huffStr.length() >= 8) {
        string str = huffStr.substr(0, 8);
        bitset<8> bts(str);
        fout.write((char*)&bts, sizeof(char));
        huffStr = huffStr.erase(0, 8);
    }

    int len = huffStr.length();
    if (len) {
        for (int i = 0; i < 8-len; i++) {
            huffStr += '0';
        }
        bitset<8> bts(huffStr);
        fout.write((char*)&bts, sizeof(char));
    }

    fin.clear();
    fin.seekg(0, ios::end);
    streampos origin, current;
    origin = fin.tellg();
    current = fout.tellp();

    cout<<"Finish!"<<endl;
    cout<<"Compression ratio is : "<< double(current)/origin*100 << "%" <<endl;
}


void DisCompress(ifstream& fin, ofstream& fout)
{
    cout << "Reading frequence of word......" << endl;
    int _countMap[257] = {0};
    int *countMap = &_countMap[128];
    countMap[128] = 1;
    int num;
    fin.read((char*)&num, sizeof(int));
    for (int i = 0; i < num - 1; i++) {
        char sym;
        fin.read((char*)&sym, sizeof(char));
        fin.read((char*)&countMap[int(sym)], sizeof(int));
    }

    cout << "Creating Huffman tree......" << endl;
    Huffman HF(countMap);
    
    cout << "Discompressing......" << endl;
    
    string huffstr = "";
    int temp = HF.tot;
    bitset<8> buffer;

    while (fin && !fin.eof()) {
        int readEnd = 0;
        fin.read ((char*)&buffer, sizeof(char));
        huffstr = buffer.to_string();
        
        int len = huffstr.length();
        for (int i = 0; i < len; i++) {
            if (huffstr[i] == '0') {
                temp = HF.HT[temp].lchild;
            } else {
                temp = HF.HT[temp].rchild;
            }
        
            if (temp < HF.num) {    //到达叶子节点
                if (temp == HF.num - 1) {
                    readEnd = 1;
                    break;
                }
                char symbol = HF.HT[temp].sym;
                fout << symbol;
                temp = HF.tot;
            }
        }
        if (readEnd) break;
        huffstr = "";
    }

    cout << "Discompress Finish!" << endl;
}

void menu() 
{
    cout << "Author: Yuanyang Wang" << endl;
    cout << "******Huffman Compress/DisCompress******\n";

    cout << "Please choose what you want to do: \n";
    cout << "------------------------------\n";
    cout << "1. compress    2.discompress\n";
    cout << "------------------------------\n";
}

void GetFile(ifstream& fin, ofstream& fout) 
{
    char formerName[30], laterName[30];
    cout << "Next please input file absolute path \n";
    cout << "Please input operated file and store file: \n";
    cin >> formerName >> laterName;
    fin.open(formerName, ios::binary);
    fout.open(laterName, ios::binary);
}

int main()
{
    clock_t start, end;
    
    ifstream fin;
    ofstream fout;

    menu();
    char order = getch();
    GetFile(fin, fout);

    start = clock();
    switch (order) {
        case '1':{
            Compress(fin,fout);
            break;
        }
        case '2':{
            DisCompress(fin, fout);
            break;
        }
        default: {
            cout << "Error, please quit and input again!\n";
        }
    }

    fin.close(); fout.close();

    end = clock();
    printf("Time costs %d ms.\n", int(end-start));
    return 0;
}