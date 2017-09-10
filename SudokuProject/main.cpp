#include<iostream>
#include<vector>
#include <fstream>
#include<ctime>
#define mysize 9
using namespace std;
class Sudoku
{
public:
	Sudoku();
	void display();    //��ӡ
	bool judge(int row, int col);   //�ж����������У��Ź��Ƿ���һ������
	bool setnum(int row, int col);   //�������ң�������������
private:
	int mysudoku[mysize][mysize];
};
Sudoku::Sudoku()
{
	memset(mysudoku, 0, sizeof(mysudoku));
	mysudoku[0][0] = 6;
}
void Sudoku::display()
{
	ofstream fout("sudoku.txt", ios::app);     //������ı�
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
bool Sudoku::judge(int row, int col)    //�ж�
{
	int num = mysudoku[row][col];
	int i, j;
	for (j = 0; j < col; j++)      //�жϱ��иø�֮ǰ�Ƿ�����ͬ����
		if (mysudoku[row][j] == num)
			return false;
	for (i = 0; i < row; i++)      //�жϱ��иø�֮���Ƿ�����ͬ����
		if (mysudoku[i][col] == num)
			return false;
	//�������ȽϾŹ�����
	int row_start = row / 3 * 3;  //��ñ��Ź��ĵ�һ���������
	int col_start = col / 3 * 3;   //��ñ��Ź��ĵ�һ���������
	i = row_start, j = col_start;      //���ñ���
	while (i < row || j < col)
	{
		if (mysudoku[i][j] == num)      //����һ������
			return false;
		if (j == col_start + 2)     //���ڸ�С�Ź���������
		{
			i = i + 1;                  //����һ��
			j = col_start;
		}
		else
			j++;
	}
	return true;
}
bool Sudoku::setnum(int row, int col)   //����
{
	vector<int> num;      //����һ����1-9�������������
	for (int i = 0; i <mysize; i++)
		num.emplace_back(i + 1);
	while (!num.empty())
	{
		int randindex = rand() % num.size();     //����һ��������
		int randnum = num[randindex];         //ȡ�������������ŵ�ֵ
		num.erase(num.begin() + randindex);     //ɾ������ȡֵ
		mysudoku[row][col] = randnum;         //��ֵ
		if (judge(row, col) == false)         //�ж��Ƿ����
			continue;                           //������������ѡ��
		if (row == mysize - 1 && col == mysize - 1)    //�Ƿ������Ź���ֵ���
			return true;
		int nextrow, nextcol;
		if (col == mysize - 1)      //��һ��
		{
			nextrow = row + 1;
			nextcol = 0;
		}
		else
		{
			nextrow = row;
			nextcol = col + 1;
		}
		bool nextset = setnum(nextrow, nextcol);      //�������
		if (nextset)
			return true;
	}
	if (num.empty())           //�޽�
	{
		mysudoku[row][col] = -1;
		return false;
	}
}
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