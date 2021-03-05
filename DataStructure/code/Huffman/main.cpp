#include "Operate.h"
#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

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
    char order = _getch();
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