// CellGroup is the  

#include <iostream>
#include <vector>
#include "CellGroup.h"

using namespace std;



CellGroup::CellGroup(void)
{
	for (int i = 0; i < 9; ++i)
	{
		m_cells[i] = nullptr;
	}
}


CellGroup::~CellGroup(void)
{
}

void CellGroup::SetCell(int index, Cell *cell)
{
	m_cells[index] = cell;
}

Cell* CellGroup::GetCell(int index) const
{
	return m_cells[index];
}


