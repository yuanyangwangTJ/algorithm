#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

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