#pragma once
#pragma once
#include <vector>
#include <raylib.h>

class Grid {
public:
	Grid();
	void Initialize();
	//void Search(); // ���ߧܧ�ڧ� �էݧ���ڧ�ܧ�
	std::vector<std::vector<int>> Search();
	int SearchRowWithEmptyCell(); // ���ߧܧ�ڧ� �էݧ���ڧ�ܧ� ��ѧާ�� �ߧڧاߧ֧� �����ܧ� �� ������� �ܧݧ֧�ܧ��
	void Print();
	void Draw(); // ���٧էѧߧڧ� ��֧�ܧ� �� �����ӧ֧��ӧڧ� �� ��ӧ֧�ѧާ�
	bool IsCellOutside(int row, int column);
	bool IsCellEmpty(int row, int column);
	int ClearFullRows();

	//std::vector<std::vector<int> > grid(20, std::vector<int>(10, 0)); // �էӧ� ��ѧ٧ާ֧��
	//std::vector<std::vector<int>> grid;
	int grid[20][10];
	int numRows;
	int numCols;

private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int cellSize; // ��ѧ٧ާ֧� �ܧݧ֧�ܧ� �� ��ڧܧ�ڧݧ��
	std::vector<Color> colors; // ��ӧ֧� �ܧݧ֧���

};