#pragma once
#pragma once
#include <vector>
#include <raylib.h>

class Grid {
public:
	Grid();
	void Initialize();
	//void Search(); // §æ§å§ß§Ü§è§Ú§ñ §Õ§Ý§ñ§á§à§Ú§ã§Ü§Ñ
	std::vector<std::vector<int>> Search();
	int SearchRowWithEmptyCell(); // §æ§å§ß§Ü§è§Ú§ñ §Õ§Ý§ñ§á§à§Ú§ã§Ü§Ñ §ã§Ñ§Þ§à§Û §ß§Ú§Ø§ß§Ö§Û §ã§ä§â§à§Ü§Ú §ã §á§å§ã§ä§à§Û §Ü§Ý§Ö§ä§Ü§à§Û
	void Print();
	void Draw(); // §ã§à§Ù§Õ§Ñ§ß§Ú§Ö §ã§Ö§ä§Ü§Ú §Ó §ã§à§à§ä§Ó§Ö§ä§ã§Ó§Ú§Ú §ã §è§Ó§Ö§ä§Ñ§Þ§Ú
	bool IsCellOutside(int row, int column);
	bool IsCellEmpty(int row, int column);
	int ClearFullRows();

	//std::vector<std::vector<int> > grid(20, std::vector<int>(10, 0)); // §Õ§Ó§Ñ §â§Ñ§Ù§Þ§Ö§â§Ñ
	//std::vector<std::vector<int>> grid;
	int grid[20][10];
	int numRows;
	int numCols;

private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int cellSize; // §â§Ñ§Ù§Þ§Ö§â §Ü§Ý§Ö§ä§Ü§Ú §Ó §á§Ú§Ü§ã§Ú§Ý§ñ§ç
	std::vector<Color> colors; // §è§Ó§Ö§ä §Ü§Ý§Ö§ä§à§Ü

};