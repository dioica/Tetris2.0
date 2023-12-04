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

	// §à§á§â§Ö§Õ§Ö§Ý§ñ§Ö§ä§ã§ñ §á§à§Ù§Ú§è§Ú§ñ §á§à§ã§Ý§Ö §á§Ñ§Õ§Ö§ß§Ú§ñ §á§â§Ú §ä§Ö§Ü§å§ë§Ö§Þ §á§à§Ý§à§Ø§Ö§ß§Ú§Ú §Ò§Ý§à§Ü§Ñ
	// §Õ§à§Ý§Ø§ß§Ñ §Ó§Ö§â§ß§å§ä§î §ã§ä§â§à§Ü§å §Ó §Ü§à§ä§à§â§à§Û §Ò§Ý§à§Ü §à§ã§ä§Ñ§ß§à§Ó§Ú§ä§ã§ñ
	int FallPosition();

	// §á§à§Õ§ã§é§Ú§ä§í§Ó§Ñ§Ö§ä §Ü§à§Ý§Ú§é§Ö§ã§ä§Ó§à §á§å§ã§ä§í§ç §Ü§Ý§Ö§ä§à§Ü §á§à§Õ §Ò§Ý§à§Ü§à§Þ, §á§à§ã§Ý§Ö §Ö§Ô§à §á§Ñ§Õ§Ö§ß§Ú§ñ
	// §ã§ä§à§Ü§Ñ, §Ô§Õ§Ö §Ò§Ý§à§Ü §à§ã§ä§Ñ§ß§à§Ó§Ú§ä§ã§ñ; §ã§ä§â§Ü§Ñ §Ú §ã§ä§à§Ý§Ò§Ö§è §Ü§Ý§Ö§ä§Ü§Ú, §Ó §Ü§à§ä§à§â§à§Û §Õ§à§Ý§Ø§Ö§ß §Ò§í§Ý §à§Ü§Ñ§Ù§Ñ§ä§î§ã§ñ §Ò§Ý§à§Ü
	int CountingEmptyCellsUnderBlock(int emptyCellRow, int emptyCellColumn);


private:
	bool IsBlockOutside();
	void RotateBlock();
	void LockBlock();
	bool BlockFits(); // §ß§Ñ§ç§à§Õ§Ú§ä§ã§ñ §Ý§Ú §Ò§Ý§à§Ü §á§à §Ó§Ó§Ö§â§ç §á§å§ã§ä§à§Û §ñ§é§Ö§Û§Ü§Ú §ã§Ö§ä§Ü§Ú
	void Reset();
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;

};