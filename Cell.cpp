#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Cell.h"

using namespace std;

Cell::Cell(int value, bool given, const vector<int>& list)
{
	SetValue(value);
	SetGiven(given);
	SetList(list);
}

Cell::~Cell(void)
{

}

int Cell::GetValue() const
{
	return m_value;
}

void Cell::SetValue(int value)
{
	m_value = value;
}

void Cell::SetGiven(bool given)
{
	m_given = given;
}

bool Cell::GetGiven() const
{
	return m_given;
}

const void Cell::SetList(const vector<int>& list)
{
	m_candidateList = list;
}

const vector<int>& Cell::GetList() const
{
	return m_candidateList;
}