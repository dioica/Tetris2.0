#include "grid.h"
#include <iostream>
#include "color.h"
#include <algorithm>
#include <vector>

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30; // §â§Ñ§Ù§Þ§Ö§â §ñ§é§Ö§Û§Ü§Ú
	Initialize();
	colors = GetCellColors();
}

void Grid::Initialize()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			grid[row][column] = 0;
		}
	}
}

// §é§ä§à §Õ§à§Ý§Ø§ß§à §Ó§à§Ù§â§Ñ§ë§Ñ§ä§î ????
// §ß§å§Ø§ß§í§Û §Ý§Ú §á§à§â§ñ§Õ§à§Ü? §ß§Ñ§Õ§à §ß§Ñ§é§Ú§ß§Ñ§ä§î §ã§ß§Ú§Ù§å
std::vector<std::vector<int>> Grid::Search() {

	int rowWithFirstEmptyCell = SearchRowWithEmptyCell();
	std::vector<std::vector<int>> v;

	// §ß§Ñ§Û§ä§Ú §á§å§ã§ä§ß§í§Ö §Ü§Ý§Ö§ä§Ü§Ú §Ú§Ù §Õ§Ó§å§ç §ß§Ú§Ø§ß§Ú§ç §ã§ä§â§à§Ü §ã §á§å§ã§ä§í§Þ§Ú §Ü§Ý§Ö§ä§Ü§Ñ§Þ§Ú
	for (int row = rowWithFirstEmptyCell; row >= rowWithFirstEmptyCell - 1; row--)
	{
		std::vector<int > v0;
		v.push_back(v0);

		for (int column = 0; column < numCols; column++)
		{
			if (IsCellEmpty(row, column))
			{
				std::cout << "§±§å§ã§ä§Ñ§ñ §Ü§Ý§Ö§ä§Ü§Ñ" << row << " " << column << "\n";
				bool flag = true;
				for (int i = row; i > 0; i--)
				{
					if (!IsCellEmpty(i, column))
					{
						flag = false;
						break;
					}
				}

				if (flag == true) {
					if (row == rowWithFirstEmptyCell)
					{
						v[0].push_back(column);
					}
					else if (!std::binary_search(v[0].begin(), v[0].end(), column)) // §ß§Ö§ä §ã§Þ§í§ã§Ý§Ñ §Ù§Ñ§á§Ú§ã§Ó§Ñ§ä§î §á§å§ã§ä§å§ð §Ü§Ý§Ö§ä§Ü§å §ß§Ñ§Õ §á§å§ã§ä§à§Û §Ü§Ý§Ö§ä§Ü§à§Û §Ú§Ù §á§â§ê§Ý§à§Û §ã§ä§â§à§Ü§Ú
					{
						v[1].push_back(column);
					}

					//return (std::make_pair(row, column));
				}
			}
		}
	}
	return (v);
}

// §ß§Ñ§Û§ä§Ú §ã§Ñ§Þ§å§ð §ß§Ú§Ø§ß§ð§ð §ã§ä§â§à§Ü§å §ã §á§å§ã§ä§à§Û §Ü§Ý§Ö§ä§Ü§à§Û
int Grid::SearchRowWithEmptyCell() {

	for (int row = numRows - 1; row >= 0; row--)
	{
		for (int column = 0; column < numCols; column++)
		{
			if (IsCellEmpty(row, column))
			{
				bool flag = true;
				for (int i = row; i > 0; i--)
				{
					if (!IsCellEmpty(i, column))
					{
						flag = false;
						break;
					}
				}

				if (flag == true) {
					return (row);
				}
			}
		}
	}
}

void Grid::Print()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			std::cout << grid[row][column] << " ";
		}
		std::cout << std::endl;
	}
}


void Grid::Draw()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			int cellValue = grid[row][column];
			DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
		}
	}
}

bool Grid::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < numRows && column >= 0 && column < numCols)
	{
		return false;
	}
	return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
	{
		return true;
	}
	return false;
}

int Grid::ClearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row, completed);
		}
	}
	return completed;
}

bool Grid::IsRowFull(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		if (grid[row][column] == 0)
		{
			return false;
		}
	}
	return true;
}

void Grid::ClearRow(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row][column] = 0;
	}
}

void Grid::MoveRowDown(int row, int numRows)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row + numRows][column] = grid[row][column];
		grid[row][column] = 0;
	}
}