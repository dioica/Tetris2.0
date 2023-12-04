#include "game.h"
#include <random>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

bool flag = true;

Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
}

// �ܧѧاէ�� �ҧݧ�� ��� 1 ��ѧ٧�, �٧ѧ�֧� ���ӧ���ڧ��
Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;

}

std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw()
{
	grid.Draw();
	currentBlock.Draw();
	//std::cout << currentBlock.GetCellPosition()[0].row << "/n";
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		Reset();
	}

	switch (keyPressed)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_DOWN:
		MoveBlockDown();
		break;
	case KEY_UP:
		RotateBlock();
		break;
	}
}

void Game::MoveBlockLeft()
{
	if (!gameOver)
	{
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, 1);
		}
	}
}

void Game::MoveBlockRight()
{
	if (!gameOver)
	{
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, -1);
		}
	}
}

void Game::MoveBlockDown()
{
	if (!gameOver)
	{
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

int Game::AutoTetris()
{



	//currentBlock.Move(currentBlock.GetCellPosition()[0].row, 0);

	// ����ӧ֧�ڧ�� ��֧�ܧ�
	//currentBlock.id 

	// �էݧ� ���ڧ�ܧ� ������� ���֧ۧܧ�
	//std::pair<int, int> p = grid.Search(); // �ӧ֧�ߧ���� ��ڧ�֧�ܧ�

	//std::cout << "i" << p.first << "\n";
	// ���ާ֧��ڧ�� �ҧݧ��

	std::pair<int, int> p;

	std::vector<std::vector<int>> vectorWithEmptyCells = grid.Search();

	std::cout << "vectorWithEmptyCells " << vectorWithEmptyCells[0].size() << "\n";
	std::cout << "vectorWithEmptyCells " << vectorWithEmptyCells[1].size() << "\n";

	int moving;
	int minCountEmptyCells = 100;
	int bestPositionColumn = 0;
	int bestRotation = 0;
	int countEmptyCells;
	int firstEmptyRowWithEmptyCell = grid.SearchRowWithEmptyCell();


	for (int i = 0; i < vectorWithEmptyCells.size(); i++)
	{
		for (int j = 0; j < vectorWithEmptyCells[i].size(); j++)
		{
			//moving = currentBlock.GetCellPosition()[0].column - vectorWithEmptyCells[i][j]; 

			for (int rotate = 0; rotate < currentBlock.cells.size(); rotate++)
			{
				if (rotate != 0)
					RotateBlock();

				if (currentBlock.rotationState != rotate)
				{
					if (currentBlock.id == 3) {
						MoveBlockDown();
					}

					if (currentBlock.GetCellPosition()[0].column > 4)
					{
						MoveBlockLeft();
						MoveBlockLeft();
						MoveBlockLeft();
						RotateBlock();
					}

					else
					{
						MoveBlockRight();
						MoveBlockRight();
						MoveBlockRight();
						RotateBlock();
					}
				}



				int rrr = currentBlock.rotationState;
				int ooo = currentBlock.GetCellPosition()[0].column;
				moving = currentBlock.GetCellPosition()[0].column - vectorWithEmptyCells[i][j];

				if (vectorWithEmptyCells[i][j] < currentBlock.GetCellPosition()[0].column) // ��ާ֧�֧ߧڧ� �ӧݧ֧ӧ�
				{
					//int q = currentBlock.fixedPoint[currentBlock.rotationState];
					for (int x = 0; x <= currentBlock.GetCellPosition()[0].column - vectorWithEmptyCells[i][j]; x++) //2
					{
						MoveBlockLeft();
						std::cout << "�ӧݧ֧ӧ� " << "\n";
					}
				}
				else if (vectorWithEmptyCells[i][j] > currentBlock.GetCellPosition()[0].column) // ��ާ֧�֧ߧڧ� �ӧ��ѧӧ�
				{
					for (int x = 0; x <= vectorWithEmptyCells[i][j] - currentBlock.GetCellPosition()[0].column; x++) //2
					{
						MoveBlockRight();
						std::cout << "�ӧ��ѧӧ�" << "\n";
					}
				}

				int em = currentBlock.GetCellPosition()[0].column;
				countEmptyCells = CountingEmptyCellsUnderBlock(firstEmptyRowWithEmptyCell - i, vectorWithEmptyCells[i][j]);

				if (countEmptyCells == 0)
				{
					int yyyy = currentBlock.GetCellPosition()[0].column;
					std::cout << "currentBlock.GetCellPosition()[0].column" << currentBlock.GetCellPosition()[0].column << "\n";
					return (0);
					// ��֧�֧ۧ�� �� ��ݧ֧է���֧ާ� �ҧݧ�ܧ�, �٧ѧܧ�ߧ�ڧ�� ���� ���ߧܧ�ڧ�
					//bestPositionColumn = vectorWithEmptyCells[i][j];// �ҧ�է֧� �ݧ� ��ѧ� ��ѧҧ��ѧ��
					//break;
				}
				else if (countEmptyCells < minCountEmptyCells)
				{
					minCountEmptyCells = countEmptyCells;
					bestPositionColumn = vectorWithEmptyCells[i][j];
					bestRotation = currentBlock.rotationState;
					std::cout << "bestPositionColumn" << bestPositionColumn << "\n";
				}

				// ��էӧڧߧ��� �ҧݧ�� ��ҧ�ѧ�ߧ�
				// ���ѧէ�?????????????????
			}
		}
	}


	//moving = currentBlock.GetCellPosition()[0].column - bestPositionColumn;

	if (currentBlock.rotationState != bestRotation)
	{
		if (currentBlock.GetCellPosition()[0].column > 4)
		{
			MoveBlockLeft();
			MoveBlockLeft();
			RotateBlock();
		}

		else
		{
			MoveBlockRight();
			MoveBlockRight();
			RotateBlock();
		}
	}

	while (currentBlock.rotationState != bestRotation)
	{
		RotateBlock();
	}

	if (bestPositionColumn <= currentBlock.GetCellPosition()[0].column)
	{
		for (int x = 0; x < currentBlock.GetCellPosition()[0].column - bestPositionColumn; x++)
		{
			MoveBlockLeft();
			std::cout << "�ӧݧ֧ӧ� " << "\n";
		}
	}
	else if (bestPositionColumn > currentBlock.GetCellPosition()[0].column)
	{
		for (int x = 0; x <= bestPositionColumn - currentBlock.GetCellPosition()[0].column; x++)
		{
			MoveBlockRight();
			std::cout << "�ӧ��ѧӧ�" << "\n";
		}
	}
	return (0);
}


//std::cout << "���ѧ�ѧݧ�ߧѧ� ���٧ڧ�ڧ� " << currentBlock.GetCellPosition()[0].column << "\n";
//std::cout << "������ѧ� �ܧݧ֧�ܧ� " << p.second << "\n";
//std::cout << "��ާ֧�֧ߧڧ�? " << currentBlock.GetCellPosition()[0].column - p.second << "\n";
//int moving = currentBlock.GetCellPosition()[0].column - p.second;

//currentBlock.Move(0, -(currentBlock.GetCellPosition()[0].column - p.second));

/*switch (currentBlock.id)
{
	case 1:

		if (moving - 2 > 0)
		{
			for (int i = 0; i < moving - 2; i++)
			{
				MoveBlockLeft();
				std::cout << "�ӧݧ֧ӧ� " << "\n";
			}
		}
		else
		{
			for (int i = 0; i < -(moving - 2); i++)
			{
				MoveBlockRight();
				std::cout << "�ӧ��ѧӧ�" << "\n";
			}
		}

		break;
}*/

/*if (currentBlock.id == 1)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving - 2; i++)
	{
		MoveBlockLeft();
		std::cout << "�ӧݧ֧ӧ� " <<  "\n";
	}

	int fallRow = FallPosition(3, 2, 2);
	std::cout << " !!!!FalRow" << fallRow << currentBlock.id << "\n";

	int min = 10 * 20;
	int minId = -1;
	for (int i = 0; i < 4; i++)
	{
		int countOfEmptyCell = CountingEmptyCellsUnderBlock(fallRow, p.first, p.second);
		if (countOfEmptyCell < min)
		{
			min = countOfEmptyCell;
			minId = currentBlock.id;
		}
		currentBlock.Rotate();
	}

	while (currentBlock.rotationState != minId)
	{
		currentBlock.Rotate();
	}



	std::cout << "currentBlock.rotationState " << currentBlock.rotationState << "\n";
	if (currentBlock.rotationState == 1 || currentBlock.rotationState == 3)
	{
		MoveBlockLeft();
		std::cout << "currentBlock.rotationState �� �ӧݧ֧ӧ�" << currentBlock.rotationState << "\n";
	}
}
else if (currentBlock.id == 2)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving; i++)
	{
		MoveBlockLeft();
		std::cout << "�ӧݧ֧ӧ� " <<  "\n";
	}



	// ����ӧ֧�ڧ�� ���է��էڧ� �ݧ�, ����ѧߧ���� �ݧ� �ҧݧ�ܧ� �����ߧ�� �ӧߧڧ٧�
	if (grid.IsCellEmpty(p.first, p.second)) // �֧�ݧ� �ߧѧۧէ֧ߧߧѧ� �ܧݧ֧�ܧ� ����ѧݧѧ�� �������
		// ���ާ֧ߧڧ�� ��֧�֧ާ֧�֧ߧڧ�, ������ҧ�ӧѧ�� �է��ԧ�� �������
	{
		std::cout << "����ѧݧѧ�� �����ѧ� �ܧݧ֧�ܧ�" << "\n";
	}

	int fallRow = FallPosition(3, 2, 0);
	std::cout << " !!!!FalRow" << fallRow << currentBlock.id << "\n";
}
else if (currentBlock.id == 3)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving; i++)
	{
		MoveBlockLeft();
		std::cout << "�ӧݧ֧ӧ� " << "\n";
	}

	// ����ӧ֧�ڧ�� ���է��էڧ� �ݧ�, ����ѧߧ���� �ݧ� �ҧݧ�ܧ� �����ߧ�� �ӧߧڧ٧�
	if (grid.IsCellEmpty(p.first, p.second)) // �֧�ݧ� �ߧѧۧէ֧ߧߧѧ� �ܧݧ֧�ܧ� ����ѧݧѧ�� �������
		// ���ާ֧ߧڧ�� ��֧�֧ާ֧�֧ߧڧ�, ������ҧ�ӧѧ�� �է��ԧ�� �������
	{
		std::cout << "����ѧݧѧ�� �����ѧ� �ܧݧ֧�ܧ�" << "\n";
	}
}
else if (currentBlock.id == 4)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving; i++)
	{
		MoveBlockLeft();
		std::cout << "�ӧݧ֧ӧ� " << "\n";
	}
}
else if (currentBlock.id == 5)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving - 1; i++)
	{
		MoveBlockLeft();
		std::cout << "�ӧݧ֧ӧ� " <<  "\n";
	}
}
else if (currentBlock.id == 6)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving - 1; i++)
	{
		MoveBlockLeft();
		std::cout << "�ӧݧ֧ӧ� " <<  "\n";
	}
}
else if (currentBlock.id == 7)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving; i++)
	{
		MoveBlockLeft();
		std::cout << "�ӧݧ֧ӧ� " << p.second << "\n";
	}
}
*/

//std::cout << "�����ݧ� ��ާ֧�֧ߧڧ� " << currentBlock.GetCellPosition()[0].column << "\n";
//std::cout << "-------------------------------- " << "\n";

//std::this_thread::sleep_for(std::chrono::seconds(10));
//std::this_thread::sleep_for(std::chrono::nanoseconds(10));
//std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));





void Game::AutoMoving(int x)
{

}

int Game::FallPosition() {
	// ���ڧ��ӧѧ֧��� �� �էݧڧߧ�, �� �ԧէ� �ߧѧ��էڧ��� ����ܧ� ���ӧ�����
	// ��ѧܧا� �ߧѧէ� ���֧��� �ܧ�է� ��ާ֧�ѧ�� ���ߧ�� ����ܧ� ���ӧ����� (��� �ԧ��ڧ٧�ߧ�ѧݧ� �ڧݧ� ��� �ӧ֧��ڧܧѧݧ�)??????
	std::cout << "FallPosition" << "\n";

	// �էݧ� L (0)
	int blockLength = currentBlock.length[currentBlock.rotationState]; //3
	int blockHeight = currentBlock.height[currentBlock.rotationState]; //2
	//int fixedPoint = currentBlock.fixedPoint[currentBlock.rotationState]; //2


	for (int i = currentBlock.GetCellPosition()[0].row; i < 20; i++) // 20 - �ܧ��-�ӧ� ������ 
	{
		for (int j = 0; j < blockLength; j++)
		{
			int q1 = i;
			int q2 = currentBlock.GetCellPosition()[0].column + j;

			//int rr1 = currentBlock.rotationState

			int r1 = i + currentBlock.irregularities[currentBlock.rotationState][j];
			int r2 = currentBlock.GetCellPosition()[0].column - currentBlock.leftOffset[currentBlock.rotationState] + j;
			int r3 = currentBlock.leftOffset[currentBlock.rotationState];

			// ��էӧڧ� �ӧݧ֧ӧ�, �����ҧ� ����ߧ� �ߧѧ�ѧ�� �� �ߧѧ�ѧݧ� �ҧݧ�ܧ�
			if (!grid.IsCellEmpty(i + currentBlock.irregularities[currentBlock.rotationState][j],
				currentBlock.GetCellPosition()[0].column - currentBlock.leftOffset[currentBlock.rotationState] + j))
			{
				std::cout << "����٧ڧ�ڧ� ��ѧէ֧ߧڧ�" << i - 1 << "\n";
				return(i - 1); // �ӧ�٧ӧ�ѧ�ѧ֧� �����ܧ�, �ܧ������ �٧ѧۧާ֧� �ҧݧ��
			}
		}
	}
	std::cout << "����٧ڧ�ڧ� ��ѧէ֧ߧڧ�" << 19 << "\n";
	return (19);
}

int Game::CountingEmptyCellsUnderBlock(int emptyCellRow, int emptyCellColumn)
{
	// ���� �է֧ݧѧ�� �� �ߧ֧��ӧߧ�ާ� ��ڧԧ��ѧާ� ?????
	int x = 0; //�էݧ� �ߧ֧��ӧߧ�� ��ڧԧ��, ��ܧ�ݧ�ܧ� �ߧѧէ� �֧�� �ܧݧ֧��� �����ڧ�ѧ�� �ߧѧӧӧ֧��
	int lengnt = 3; //�էݧڧߧ� ��ڧԧ���
	int count = 0; //���֧��ڧ� ������� �ܧݧ֧���

	int stopRow = FallPosition();

	/*if (currentBlock.rotationState == 1 || currentBlock.rotationState == 3)
	{
		lengnt = 2;
		//MoveBlockLeft();
	}*/


	// �ܧݧ֧�ܧ� �ߧѧ�ѧݧ� �ҧݧ�ܧ�
	int ttt = currentBlock.GetCellPosition()[0].column;
	int cellBegin = currentBlock.GetCellPosition()[0].column - currentBlock.leftOffset[currentBlock.rotationState];

	if (emptyCellColumn != currentBlock.GetCellPosition()[0].column)
	{
		if (emptyCellColumn < currentBlock.leftOffset[currentBlock.rotationState]) // �էݧ� �ݧ֧ӧ�ԧ� �ܧ�ѧ�
		{
			cellBegin = 0;
		}
		else if (emptyCellColumn < currentBlock.GetCellPosition()[0].column + currentBlock.rightOffset[currentBlock.rotationState]) // �էݧ� ���ѧӧ�ԧ� �ܧ�ѧ�
		{
			cellBegin = grid.numCols - 1 - currentBlock.rightOffset[currentBlock.rotationState];
		}
	}

	for (int i = emptyCellRow; i > stopRow + x; i--)
	{
		for (int j = cellBegin;
			j < cellBegin + currentBlock.length[currentBlock.rotationState]; j++)
		{
			if (grid.IsCellEmpty(i, j) && i < grid.numRows && j < grid.numCols)
			{
				count++;
			}
		}
	}

	for (int i = 0; i < currentBlock.irregularities[currentBlock.rotationState].size(); i++)
	{
		count = count - currentBlock.irregularities[currentBlock.rotationState][i];
	}


	/*if (currentBlock.id == 1)
	{
		if (currentBlock.rotationState == 2)
		{
			count = count - 1;
		}
		else if (currentBlock.rotationState == 3)
		{
			count = count - 2;
		}
	}*/

	return(count);
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.column))
		{
			return true;
		}
	}
	return false;
}

void Game::RotateBlock()
{
	if (!gameOver)
	{
		currentBlock.Rotate();
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.UndoRotation();
		}
	}
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
	}
	nextBlock = GetRandomBlock();
	grid.ClearFullRows();


	//std::cout << "Sleeping for 1 second.." << std::endl;
	//std::this_thread::sleep_for(std::chrono::milliseconds(2000));    // sleep for 1 second
	//std::cout << "1 second elapsed.." << std::endl;
	int y = AutoTetris();
}


bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (grid.IsCellEmpty(item.row, item.column) == false)
		{
			return false;
		}
	}
	return true;
}

void Game::Reset()
{
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
}
