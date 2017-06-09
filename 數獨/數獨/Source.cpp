#include <iostream>
#include <string>

using namespace std;

bool FindUnassignedLocation(int grid[9][9], int &row, int &col);
bool Promising(int grid[9][9], int row, int col, int num);

/* BackTrack遞迴函式*/
bool BckTrck(int array[9][9])
{
	int row, col;
	if (!FindUnassignedLocation(array, row, col))
		return true;
	for (int num = 1; num <= 9; num++)
	{
		if (Promising(array, row, col, num))
		{
			array[row][col] = num;
			if (BckTrck(array))
				return true;
			array[row][col] = 0;
		}
	}
	return false;
}

/* 檢查row是否符合規定 */
bool UsedInRow(int array[9][9], int row, int num)
{
	for (int col = 0; col < 9; col++)
		if (array[row][col] == num)
			return true;
	return false;
}

/* 找有無空的格子 */
bool FindUnassignedLocation(int array[9][9], int &row, int &col)
{
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (array[row][col] == 0)
				return true;
	return false;
}

/*檢查column是否符合規定 */
bool UsedInCol(int array[9][9], int col, int num)
{
	for (int row = 0; row < 9; row++)
		if (array[row][col] == num)
			return true;
	return false;
}

/*把數獨陣列劃為9個3*3陣列*/
bool UsedInBox(int array[9][9], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (array[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}

//檢查陣列中每一格是否符合數獨規定
bool Promising(int array[9][9], int row, int col, int num)
{
	return !UsedInRow(array, row, num) && !UsedInCol(array, col, num) &&
		!UsedInBox(array, row - row % 3, col - col % 3, num);
}

/* 印出結果  */
void PrintAnswer(int array[9][9])
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
			cout << array[row][col] << "  ";
		cout << endl;
	}
}

/* Main */
int main()
{
	string input;
	cout << "請輸入數字(輸入exit結束):";
	cin >> input;

	while (input!="exit"&&input!="EXIT") {
		int array[9][9] = { {0} };
		int n = 0;
		for (int i = 0; i < 9; i++) {		//把值放入9*9數獨陣列中
			for (int j = 0; j < 9; j++) {
				array[i][j] = input[n] - 48;
				n++;
			}
		}
		if (BckTrck(array) == true) {	//進入backtrack函式，有解則印出答案
			PrintAnswer(array);
		}
		else {
			cout << "No solution exists" << endl;
		}
		cout << endl << endl << "請輸入數字(輸入exit結束):";
		cin >> input;
	}
	return 0;
}