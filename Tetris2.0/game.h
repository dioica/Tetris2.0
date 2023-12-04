#pragma once
#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void Draw();
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	Grid grid;
	bool gameOver;
	// 
	int AutoTetris();

	void AutoMoving(int x);

	// ����֧է֧ݧ�֧��� ���٧ڧ�ڧ� ����ݧ� ��ѧէ֧ߧڧ� ���� ��֧ܧ��֧� ���ݧ�ا֧ߧڧ� �ҧݧ�ܧ�
	// �է�ݧاߧ� �ӧ֧�ߧ��� �����ܧ� �� �ܧ������ �ҧݧ�� ����ѧߧ�ӧڧ���
	int FallPosition();

	// ���է��ڧ��ӧѧ֧� �ܧ�ݧڧ�֧��ӧ� ������� �ܧݧ֧��� ���� �ҧݧ�ܧ��, ����ݧ� �֧ԧ� ��ѧէ֧ߧڧ�
	// ����ܧ�, �ԧէ� �ҧݧ�� ����ѧߧ�ӧڧ���; ����ܧ� �� ����ݧҧ֧� �ܧݧ֧�ܧ�, �� �ܧ������ �է�ݧا֧� �ҧ�� ��ܧѧ٧ѧ���� �ҧݧ��
	int CountingEmptyCellsUnderBlock(int emptyCellRow, int emptyCellColumn);


private:
	bool IsBlockOutside();
	void RotateBlock();
	void LockBlock();
	bool BlockFits(); // �ߧѧ��էڧ��� �ݧ� �ҧݧ�� ��� �ӧӧ֧�� ������� ���֧ۧܧ� ��֧�ܧ�
	void Reset();
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;

};