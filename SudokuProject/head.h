#ifndef HEAD_HPP

#define HEAD_HPP

#define mysize 9
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

#endif