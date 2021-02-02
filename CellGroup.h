#pragma once

#include <iostream>
#include <fstream>
#include "Cell.h"

using namespace std;

class CellGroup
{
public:

	CellGroup(void);
	~CellGroup(void);


	void SetCell(int index, Cell* cell);
	Cell* GetCell(int index) const;

private:
	Cell* m_cells[9];
};
