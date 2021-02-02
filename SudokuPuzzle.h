#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "CellGroup.h"
using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void Solve();

private:
	void ReadInGrid();
	void CheckRow() const;
	void CheckColumn() const;
	void CheckBlock() const;
	void NakedSingles() const;
	void HiddenSingles() const;
	void InitialiseBlockGrid();

	CellGroup m_gridRows[9];
	CellGroup m_gridColumns[9];
	CellGroup m_gridBlock[9];
	void Output() const;
};

