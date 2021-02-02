#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Cell
{
public:
	Cell(int, bool, const vector<int>&);
	~Cell(void);

	void SetValue(int val);

	void SetGiven(bool given);

	const void SetList(const vector<int>& List);

	int GetValue() const;

	bool GetGiven() const;

	const vector<int>& GetList() const;


private:
	vector<int> m_candidateList;
	int m_value;
	bool m_given;

};


