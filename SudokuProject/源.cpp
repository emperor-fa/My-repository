#include<iostream>
#include<vector>
#include <fstream>
#define mysize 9
using namespace std;
class Sudoku
{
public:
	Sudoku();
	void display();    //打印
	bool judge(int row, int col);   //判断所填格的行列，九宫是否有一样的数
	bool setnum(int row, int col);   //从左往右，从上往下置数
private:
	int mysodoku[mysize][mysize];
};
Sudoku::Sudoku()
{
	memset(mysodoku, 0, sizeof(mysodoku));
	mysodoku[0][0] = 6;
}
void Sudoku::display()
{
	ofstream fout("sudoku.txt",ios::app);     //输出到文本
	for (int i = 0; i < mysize; i++)
	{
		for (int j = 0; j < mysize; j++)
		{
			cout << mysodoku[i][j] << " ";   
			fout << mysodoku[i][j] << "  ";
		}
		fout << endl;
		cout << endl;
	}
	fout << endl;
	cout << endl;
}
bool Sudoku::judge(int row, int col)
{
	int num = mysodoku[row][col];
	int i, j;
	for (j = 0; j < col; j++)      //判断该行该格之前是否有相同的数
		if (mysodoku[row][j] == num)
			return false;
	for (i = 0; i < row; i++)      //判断该列该格之上是否有相同的数
		if (mysodoku[i][col] == num)
			return false;
	//接下来比较九宫格内
	int row_start = row / 3;
	row_start *= 3;      //获得该小九宫格最小行号
	int col_start = col / 3;
	col_start *= 3;      //获得该小九宫格最小列号
	int col_end = col_start + 2;      //获得该小九宫格最大列号
	i = row_start, j = col_start;      //设置变量
	while (i < row || j < col)
	{
		if (mysodoku[i][j] == num)      //存在一样的数
			return false;
		if (j == col_end)     //当在该小九宫格最右列
		{
			i = i + 1;
			j = col_start;
		}
		else
			j++;
	}
	return true;
}
bool Sudoku::setnum(int row, int col)
{
	vector<int> num;      //创建一个从1-9的数组用于填充
	for (int i = 0; i <mysize; i++)
		num.emplace_back(i + 1);
	while (!num.empty())
	{
		int randindex = rand() % num.size();     //生成一个随机序号
		int randnum = num[randindex];         //取得数组内随机序号的值
		num.erase(num.begin() + randindex);     //删除掉所取值
		mysodoku[row][col] = randnum;         //赋值
		if (judge(row, col) == false)         //判断
			continue;
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
		mysodoku[row][col] = -1;
		return false;
	}
}
int main()
{
	int n, i;
	cin >> n;
	ofstream fout("sudoku.txt", ios::trunc);      //清空文本
	for (i = 0; i < n; i++)
	{
		Sudoku sudoku;
		if (sudoku.setnum(0, 1))
			sudoku.display();
		//delete sudoku;
	}
	system("pause");
}