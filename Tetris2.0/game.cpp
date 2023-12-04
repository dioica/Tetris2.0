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

// §Ü§Ñ§Ø§Õ§í§Û §Ò§Ý§à§Ü §á§à 1 §â§Ñ§Ù§å, §Ù§Ñ§ä§Ö§Þ §á§à§Ó§ä§à§â§Ú§ä§î
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

	// §á§â§à§Ó§Ö§â§Ú§ä§î §ã§Ö§ä§Ü§å
	//currentBlock.id 

	// §Õ§Ý§ñ §á§à§Ú§ã§Ü§Ñ §á§å§ã§ä§à§Û §ñ§é§Ö§Û§Ü§Ú
	//std::pair<int, int> p = grid.Search(); // §Ó§Ö§â§ß§å§ä§ã§ñ §è§Ú§æ§Ö§â§Ü§Ú

	//std::cout << "i" << p.first << "\n";
	// §á§à§Þ§Ö§ã§ä§Ú§ä§î §Ò§Ý§à§Ü

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

				if (vectorWithEmptyCells[i][j] < currentBlock.GetCellPosition()[0].column) // §ã§Þ§Ö§ë§Ö§ß§Ú§Ö §Ó§Ý§Ö§Ó§à
				{
					//int q = currentBlock.fixedPoint[currentBlock.rotationState];
					for (int x = 0; x <= currentBlock.GetCellPosition()[0].column - vectorWithEmptyCells[i][j]; x++) //2
					{
						MoveBlockLeft();
						std::cout << "§Ó§Ý§Ö§Ó§à " << "\n";
					}
				}
				else if (vectorWithEmptyCells[i][j] > currentBlock.GetCellPosition()[0].column) // §ã§Þ§Ö§ë§Ö§ß§Ú§Ö §Ó§á§â§Ñ§Ó§à
				{
					for (int x = 0; x <= vectorWithEmptyCells[i][j] - currentBlock.GetCellPosition()[0].column; x++) //2
					{
						MoveBlockRight();
						std::cout << "§Ó§á§â§Ñ§Ó§à" << "\n";
					}
				}

				int em = currentBlock.GetCellPosition()[0].column;
				countEmptyCells = CountingEmptyCellsUnderBlock(firstEmptyRowWithEmptyCell - i, vectorWithEmptyCells[i][j]);

				if (countEmptyCells == 0)
				{
					int yyyy = currentBlock.GetCellPosition()[0].column;
					std::cout << "currentBlock.GetCellPosition()[0].column" << currentBlock.GetCellPosition()[0].column << "\n";
					return (0);
					// §á§Ö§â§Ö§Û§ä§Ú §Ü §ã§Ý§Ö§Õ§å§ð§ë§Ö§Þ§å §Ò§Ý§à§Ü§å, §Ù§Ñ§Ü§à§ß§é§Ú§ä§î §ï§ä§å §æ§å§ß§Ü§è§Ú§ð
					//bestPositionColumn = vectorWithEmptyCells[i][j];// §Ò§å§Õ§Ö§ä §Ý§Ú §ä§Ñ§Ü §â§Ñ§Ò§à§ä§Ñ§ä§î
					//break;
				}
				else if (countEmptyCells < minCountEmptyCells)
				{
					minCountEmptyCells = countEmptyCells;
					bestPositionColumn = vectorWithEmptyCells[i][j];
					bestRotation = currentBlock.rotationState;
					std::cout << "bestPositionColumn" << bestPositionColumn << "\n";
				}

				// §ã§Õ§Ó§Ú§ß§å§ä§î §Ò§Ý§à§Ü §à§Ò§â§Ñ§ä§ß§à
				// §¯§Ñ§Õ§à?????????????????
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
			std::cout << "§Ó§Ý§Ö§Ó§à " << "\n";
		}
	}
	else if (bestPositionColumn > currentBlock.GetCellPosition()[0].column)
	{
		for (int x = 0; x <= bestPositionColumn - currentBlock.GetCellPosition()[0].column; x++)
		{
			MoveBlockRight();
			std::cout << "§Ó§á§â§Ñ§Ó§à" << "\n";
		}
	}
	return (0);
}


//std::cout << "§¯§Ñ§é§Ñ§Ý§î§ß§Ñ§ñ §á§à§Ù§Ú§è§Ú§ñ " << currentBlock.GetCellPosition()[0].column << "\n";
//std::cout << "§±§å§ã§ä§Ñ§ñ §Ü§Ý§Ö§ä§Ü§Ñ " << p.second << "\n";
//std::cout << "§ã§Þ§Ö§ë§Ö§ß§Ú§Ö? " << currentBlock.GetCellPosition()[0].column - p.second << "\n";
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
				std::cout << "§Ó§Ý§Ö§Ó§à " << "\n";
			}
		}
		else
		{
			for (int i = 0; i < -(moving - 2); i++)
			{
				MoveBlockRight();
				std::cout << "§Ó§á§â§Ñ§Ó§à" << "\n";
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
		std::cout << "§Ó§Ý§Ö§Ó§à " <<  "\n";
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
		std::cout << "currentBlock.rotationState §ª §Ó§Ý§Ö§Ó§à" << currentBlock.rotationState << "\n";
	}
}
else if (currentBlock.id == 2)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving; i++)
	{
		MoveBlockLeft();
		std::cout << "§Ó§Ý§Ö§Ó§à " <<  "\n";
	}



	// §á§â§à§Ó§Ö§â§Ú§ä§î §á§à§Õ§ç§à§Õ§Ú§ä §Ý§Ú, §à§ã§ä§Ñ§ß§å§ä§ã§ñ §Ý§Ú §Ò§Ý§à§Ü§Ú §á§å§ã§ä§ß§í§Ö §Ó§ß§Ú§Ù§å
	if (grid.IsCellEmpty(p.first, p.second)) // §Ö§ã§Ý§Ú §ß§Ñ§Û§Õ§Ö§ß§ß§Ñ§ñ §Ü§Ý§Ö§ä§Ü§Ñ §à§ã§ä§Ñ§Ý§Ñ§ã§î §á§å§ã§ä§à§Û
		// §à§ä§Þ§Ö§ß§Ú§ä§î §á§Ö§â§Ö§Þ§Ö§ë§Ö§ß§Ú§Ö, §á§à§á§â§à§Ò§í§Ó§Ñ§ä§î §Õ§â§å§Ô§à§Û §ã§á§à§ã§à§Ò
	{
		std::cout << "§à§ã§ä§Ñ§Ý§Ñ§ã§î §á§å§ã§ä§Ñ§ñ §Ü§Ý§Ö§ä§Ü§Ñ" << "\n";
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
		std::cout << "§Ó§Ý§Ö§Ó§à " << "\n";
	}

	// §á§â§à§Ó§Ö§â§Ú§ä§î §á§à§Õ§ç§à§Õ§Ú§ä §Ý§Ú, §à§ã§ä§Ñ§ß§å§ä§ã§ñ §Ý§Ú §Ò§Ý§à§Ü§Ú §á§å§ã§ä§ß§í§Ö §Ó§ß§Ú§Ù§å
	if (grid.IsCellEmpty(p.first, p.second)) // §Ö§ã§Ý§Ú §ß§Ñ§Û§Õ§Ö§ß§ß§Ñ§ñ §Ü§Ý§Ö§ä§Ü§Ñ §à§ã§ä§Ñ§Ý§Ñ§ã§î §á§å§ã§ä§à§Û
		// §à§ä§Þ§Ö§ß§Ú§ä§î §á§Ö§â§Ö§Þ§Ö§ë§Ö§ß§Ú§Ö, §á§à§á§â§à§Ò§í§Ó§Ñ§ä§î §Õ§â§å§Ô§à§Û §ã§á§à§ã§à§Ò
	{
		std::cout << "§à§ã§ä§Ñ§Ý§Ñ§ã§î §á§å§ã§ä§Ñ§ñ §Ü§Ý§Ö§ä§Ü§Ñ" << "\n";
	}
}
else if (currentBlock.id == 4)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving; i++)
	{
		MoveBlockLeft();
		std::cout << "§Ó§Ý§Ö§Ó§à " << "\n";
	}
}
else if (currentBlock.id == 5)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving - 1; i++)
	{
		MoveBlockLeft();
		std::cout << "§Ó§Ý§Ö§Ó§à " <<  "\n";
	}
}
else if (currentBlock.id == 6)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving - 1; i++)
	{
		MoveBlockLeft();
		std::cout << "§Ó§Ý§Ö§Ó§à " <<  "\n";
	}
}
else if (currentBlock.id == 7)
{
	std::cout << "id " << currentBlock.id << "\n";
	for (int i = 0; i < moving; i++)
	{
		MoveBlockLeft();
		std::cout << "§Ó§Ý§Ö§Ó§à " << p.second << "\n";
	}
}
*/

//std::cout << "§±§à§ã§Ý§Ö §ã§Þ§Ö§ë§Ö§ß§Ú§ñ " << currentBlock.GetCellPosition()[0].column << "\n";
//std::cout << "-------------------------------- " << "\n";

//std::this_thread::sleep_for(std::chrono::seconds(10));
//std::this_thread::sleep_for(std::chrono::nanoseconds(10));
//std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));





void Game::AutoMoving(int x)
{

}

int Game::FallPosition() {
	// §å§é§Ú§ä§í§Ó§Ñ§Ö§ä§ã§ñ §ª §Õ§Ý§Ú§ß§Ñ, §Ú §Ô§Õ§Ö §ß§Ñ§ç§à§Õ§Ú§ä§ã§ñ §ä§à§é§Ü§Ñ §á§à§Ó§à§â§à§ä§Ñ
	// §ä§Ñ§Ü§Ø§Ö §ß§Ñ§Õ§à §å§é§Ö§ã§ä§î §Ü§å§Õ§Ñ §ã§Þ§Ö§ë§Ñ§ä§î §à§ä§ß§à§ã §ä§à§é§Ü§Ú §á§à§Ó§à§â§à§ä§Ñ (§á§à §Ô§à§â§Ú§Ù§à§ß§ä§Ñ§Ý§Ú §Ú§Ý§Ú §á§à §Ó§Ö§â§ä§Ú§Ü§Ñ§Ý§Ú)??????
	std::cout << "FallPosition" << "\n";

	// §Õ§Ý§ñ L (0)
	int blockLength = currentBlock.length[currentBlock.rotationState]; //3
	int blockHeight = currentBlock.height[currentBlock.rotationState]; //2
	//int fixedPoint = currentBlock.fixedPoint[currentBlock.rotationState]; //2


	for (int i = currentBlock.GetCellPosition()[0].row; i < 20; i++) // 20 - §Ü§à§Ý-§Ó§à §ã§ä§â§à§Ü 
	{
		for (int j = 0; j < blockLength; j++)
		{
			int q1 = i;
			int q2 = currentBlock.GetCellPosition()[0].column + j;

			//int rr1 = currentBlock.rotationState

			int r1 = i + currentBlock.irregularities[currentBlock.rotationState][j];
			int r2 = currentBlock.GetCellPosition()[0].column - currentBlock.leftOffset[currentBlock.rotationState] + j;
			int r3 = currentBlock.leftOffset[currentBlock.rotationState];

			// §ã§Õ§Ó§Ú§Ô §Ó§Ý§Ö§Ó§à, §é§ä§ä§à§Ò§í §ä§à§é§ß§à §ß§Ñ§é§Ñ§ä§î §ã §ß§Ñ§é§Ñ§Ý§Ñ §Ò§Ý§à§Ü§Ñ
			if (!grid.IsCellEmpty(i + currentBlock.irregularities[currentBlock.rotationState][j],
				currentBlock.GetCellPosition()[0].column - currentBlock.leftOffset[currentBlock.rotationState] + j))
			{
				std::cout << "§±§à§Ù§Ú§è§Ú§ñ §á§Ñ§Õ§Ö§ß§Ú§ñ" << i - 1 << "\n";
				return(i - 1); // §Ó§à§Ù§Ó§â§Ñ§ë§Ñ§Ö§ä §ã§ä§â§à§Ü§å, §Ü§à§ä§à§â§å§ð §Ù§Ñ§Û§Þ§Ö§ä §Ò§Ý§à§Ü
			}
		}
	}
	std::cout << "§±§à§Ù§Ú§è§Ú§ñ §á§Ñ§Õ§Ö§ß§Ú§ñ" << 19 << "\n";
	return (19);
}

int Game::CountingEmptyCellsUnderBlock(int emptyCellRow, int emptyCellColumn)
{
	// §é§ä§à §Õ§Ö§Ý§Ñ§ä§î §ã §ß§Ö§â§à§Ó§ß§í§Þ§Ú §æ§Ú§Ô§å§â§Ñ§Þ§Ú ?????
	int x = 0; //§Õ§Ý§ñ §ß§Ö§â§à§Ó§ß§í§ç §æ§Ú§Ô§å§â, §ã§Ü§à§Ý§î§Ü§à §ß§Ñ§Õ§à §Ö§ë§× §Ü§Ý§Ö§ä§à§Ü §á§à§ã§é§Ú§ä§Ñ§ä§î §ß§Ñ§Ó§Ó§Ö§â§ç
	int lengnt = 3; //§Õ§Ý§Ú§ß§Ñ §æ§Ú§Ô§å§â§í
	int count = 0; //§ã§é§Ö§ä§é§Ú§Ü §á§å§ã§ä§í§ç §Ü§Ý§Ö§ä§à§Ü

	int stopRow = FallPosition();

	/*if (currentBlock.rotationState == 1 || currentBlock.rotationState == 3)
	{
		lengnt = 2;
		//MoveBlockLeft();
	}*/


	// §Ü§Ý§Ö§ä§Ü§Ñ §ß§Ñ§é§Ñ§Ý§Ñ §Ò§Ý§à§Ü§Ñ
	int ttt = currentBlock.GetCellPosition()[0].column;
	int cellBegin = currentBlock.GetCellPosition()[0].column - currentBlock.leftOffset[currentBlock.rotationState];

	if (emptyCellColumn != currentBlock.GetCellPosition()[0].column)
	{
		if (emptyCellColumn < currentBlock.leftOffset[currentBlock.rotationState]) // §Õ§Ý§ñ §Ý§Ö§Ó§à§Ô§à §Ü§â§Ñ§ñ
		{
			cellBegin = 0;
		}
		else if (emptyCellColumn < currentBlock.GetCellPosition()[0].column + currentBlock.rightOffset[currentBlock.rotationState]) // §Õ§Ý§ñ §á§â§Ñ§Ó§à§Ô§à §Ü§â§Ñ§ñ
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
