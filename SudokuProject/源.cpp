#include<iostream>
#include<vector>
#include <fstream>
#define mysize 9
using namespace std;
class Sodoku
{
public:
	Sodoku();
	void display();    //��ӡ
	bool judge(int row, int col);   //�ж����������У��Ź��Ƿ���һ������
	bool setnum(int row, int col);   //�������ң�������������
private:
	int mysodoku[mysize][mysize];
};
Sodoku::Sodoku()
{
	memset(mysodoku, 0, sizeof(mysodoku));
	mysodoku[0][0] = 6;
}
void Sodoku::display()
{
	ofstream fout("sodoku.txt",ios::app);     //������ı�
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
bool Sodoku::judge(int row, int col)
{
	int num = mysodoku[row][col];
	int i, j;
	for (j = 0; j < col; j++)      //�жϸ��иø�֮ǰ�Ƿ�����ͬ����
		if (mysodoku[row][j] == num)
			return false;
	for (i = 0; i < row; i++)      //�жϸ��иø�֮���Ƿ�����ͬ����
		if (mysodoku[i][col] == num)
			return false;
	//�������ȽϾŹ�����
	int row_start = row / 3;
	row_start *= 3;      //��ø�С�Ź�����С�к�
	int col_start = col / 3;
	col_start *= 3;      //��ø�С�Ź�����С�к�
	int col_end = col_start + 2;      //��ø�С�Ź�������к�
	i = row_start, j = col_start;      //���ñ���
	while (i < row || j < col)
	{
		if (mysodoku[i][j] == num)      //����һ������
			return false;
		if (j == col_end)     //���ڸ�С�Ź���������
		{
			i = i + 1;
			j = col_start;
		}
		else
			j++;
	}
	return true;
}
bool Sodoku::setnum(int row, int col)
{
	vector<int> num;      //����һ����1-9�������������
	for (int i = 0; i <mysize; i++)
		num.emplace_back(i + 1);
	while (!num.empty())
	{
		int randindex = rand() % num.size();     //����һ��������
		int randnum = num[randindex];         //ȡ�������������ŵ�ֵ
		num.erase(num.begin() + randindex);     //ɾ������ȡֵ
		mysodoku[row][col] = randnum;         //��ֵ
		if (judge(row, col) == false)         //�ж�
			continue;
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
		mysodoku[row][col] = -1;
		return false;
	}
}
int main()
{
	int n, i;
	cin >> n;
	ofstream fout("sodoku.txt", ios::trunc);      //����ı�
	for (i = 0; i < n; i++)
	{
		Sodoku sodoku;
		if (sodoku.setnum(0, 1))
			sodoku.display();
		//delete sodoku;
	}
	system("pause");
}