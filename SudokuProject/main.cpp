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
		cout << "������һ�����֣�" << endl;
		return 0;
	}
	srand((int)time(0));
	ofstream fout("sudoku.txt", ios::trunc);      //����ı�
	for (i = 0; i < n; i++)
	{
		Sudoku sudoku;
		if (sudoku.setnum(0, 1))
			sudoku.display();
	}
}