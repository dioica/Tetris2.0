#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "color.h"


class Block
{
public:
	Block();
	void Draw();
	void Move(int rows, int columns);
	std::vector<Position> GetCellPosition();
	void Rotate();
	void UndoRotation();
	int id;
	std::vector<std::vector<int>> irregularities;
	std::vector<int> height;
	std::vector<int> length;
	std::vector<int> leftOffset;
	std::vector<int> rightOffset;

	// ���ݧ�ا֧ߧڧ� �ܧѧاէ�� ���֧ۧܧ� ��֧�ܧ�
	std::map<int, std::vector<Position>> cells;
	int rotationState;


private:
	int cellSize;
	std::vector<Color> colors;
	int rowOffset; // ��ާ֧�֧ߧڧ� 
	int columnOffset; // ��ާ֧�֧ߧڧ�

};