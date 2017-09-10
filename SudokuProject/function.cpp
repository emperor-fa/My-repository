#include "head.h"
#include<vector>
#include <iostream>
#include <fstream>
using namespace std;
//using std::cout;
//
//using std::endl;
Sudoku::Sudoku()
{
	memset(mysudoku, 0, sizeof(mysudoku));
	mysudoku[0][0] = 6;
}
void Sudoku::display()
{
	ofstream fout("sudoku.txt", ios::app);     //输出到文本
	for (int i = 0; i < mysize; i++)
	{
		for (int j = 0; j < mysize; j++)
		{
			//cout << mysudoku[i][j] << " ";
			fout << mysudoku[i][j] << " ";
		}
		fout << endl;
		//cout << endl;
	}
	fout << endl;
	//cout << endl;
}
bool Sudoku::judge(int row, int col)    //判断
{
	int num = mysudoku[row][col];
	int i, j;
	for (j = 0; j < col; j++)      //判断本行该格之前是否有相同的数
		if (mysudoku[row][j] == num)
			return false;
	for (i = 0; i < row; i++)      //判断本列该格之上是否有相同的数
		if (mysudoku[i][col] == num)
			return false;
	//接下来比较九宫格内
	int row_start = row / 3 * 3;  //获得本九宫的第一格的行坐标
	int col_start = col / 3 * 3;   //获得本九宫的第一格的行坐标
	i = row_start, j = col_start;      //设置变量
	while (i < row || j < col)
	{
		if (mysudoku[i][j] == num)      //存在一样的数
			return false;
		if (j == col_start + 2)     //当在该小九宫格最右列
		{
			i = i + 1;                  //则到下一行
			j = col_start;
		}
		else
			j++;
	}
	return true;
}
bool Sudoku::setnum(int row, int col)   //填数
{
	vector<int> num;      //创建一个从1-9的数组用于填充
	for (int i = 0; i <mysize; i++)
		num.emplace_back(i + 1);
	while (!num.empty())
	{
		int randindex = rand() % num.size();     //生成一个随机序号
		int randnum = num[randindex];         //取得数组内随机序号的值
		num.erase(num.begin() + randindex);     //删除掉所取值
		mysudoku[row][col] = randnum;         //赋值
		if (judge(row, col) == false)         //判断是否符合
			continue;                           //不符合则重新选数
		if (row == mysize - 1 && col == mysize - 1)    //是否整个九宫格赋值完成
			return true;
		int nextrow, nextcol;
		if (col == mysize - 1)      //下一格
		{
			nextrow = row + 1;
			nextcol = 0;
		}
		else
		{
			nextrow = row;
			nextcol = col + 1;
		}
		bool nextset = setnum(nextrow, nextcol);      //深度搜索
		if (nextset)
			return true;
	}
	if (num.empty())           //无解
	{
		mysudoku[row][col] = -1;
		return false;
	}
}