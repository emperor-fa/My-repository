#ifndef HEAD_HPP

#define HEAD_HPP

#define mysize 9
class Sudoku
{
public:
	Sudoku();
	void display();    //打印
	bool judge(int row, int col);   //判断所填格的行列，九宫是否有一样的数
	bool setnum(int row, int col);   //从左往右，从上往下置数
private:
	int mysudoku[mysize][mysize];
};

#endif