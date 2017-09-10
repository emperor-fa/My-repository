#include<iostream>
#include <fstream>
#include<ctime>
#include"head.h"
using namespace std;


int main(int argc, char *argv[])
{
	int n,i;
	if (sscanf_s(argv[2],"%d", &n) == 0)
	{
		cout << "请输入一个数字：" << endl;
		return 0;
	}
	srand((int)time(0));
	ofstream fout("sudoku.txt", ios::trunc);      //清空文本
	for (i = 0; i < n; i++)
	{
		Sudoku sudoku;
		if (sudoku.setnum(0, 1))
			sudoku.display();
	}
}