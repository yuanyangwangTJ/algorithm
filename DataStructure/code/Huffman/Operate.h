#ifndef OPERATE_H
#define OPERATE_H
#include <fstream>

using namespace std;

void Compress(ifstream &fin, ofstream &fout);
void DisCompress(ifstream& fin, ofstream& fout);

#endif