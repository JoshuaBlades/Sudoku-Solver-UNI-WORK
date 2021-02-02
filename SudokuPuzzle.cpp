#pragma once 
#include "SudokuPuzzle.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <Windows.h>
#include <vector>

using namespace std;

SudokuPuzzle::SudokuPuzzle(void)
{
}

SudokuPuzzle::~SudokuPuzzle(void)
{
}

//This method is to break up the large initialise
//grid method.
void SudokuPuzzle::InitialiseBlockGrid()
{
	//Start by declaring the variables I want to use
	//The limit variables are to make sure we're 
	//correctly limiting the row and the column because
	//we only want a 3x3 grid, not the full 9x9.
	int rowLimit = 3;
	int colLimit = 3;

	//These variables are pointers to the row and 
	//the column within this 3x3 block. 
	int rowptr = 0;
	int colptr = 0;

	//The counter which is the index for setting 
	//the cell. 
	int counter = 0;

	//Now we loop round for 9 because that's how many blocks
	//we want in total.
	for (int blockCounter = 0; blockCounter < 9; ++blockCounter)
	{
		//If the block counter is three then we
		//need to move along one block to start the next
		//block of 3x3.
		if (blockCounter == 3)
		{
			colptr = 3;
			rowptr = 0;
			rowLimit = 3;
			colLimit = 6;
		}

		//Same again, once it reaches the bottom of the second 
		//set of blocks we move along and make a 3rd row of blocks.
		if (blockCounter == 6)
		{
			colptr = 6;
			rowptr = 0;
			rowLimit = 3;
			colLimit = 9;
		}

		//This is the main double for loop which will iterate 
		//round for the entire 81 blocks and make us the 
		//9 blocks. 
		for (; rowptr < rowLimit; ++rowptr)
		{
			for (; colptr < colLimit; ++colptr)
			{
				m_gridBlock[blockCounter].SetCell(counter, m_gridColumns[colptr].GetCell(rowptr));
				++counter;
			}
			//Minus the column pointer to go back to 
			//0 so we can scan another 3 columns.
			colptr -= 3;
		}
		rowLimit += 3;
		counter = 0;
	}
}

//This is the main method for reading in the grid.
//Here, the data will be inputted and placed onto the
//board filling in values and candidate numbers.
void SudokuPuzzle::ReadInGrid()
{
	ifstream file("sudoku_puzzle.txt");
	if (file.is_open())
	{
		//Double for loop which takes us around
		//each cell of the 81.
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				//Read in the cell value.
				int cellValue;
				file >> cellValue;
				bool given = false;
				vector<int> canList;
				//This checks to see if the cell was derived from
				//the text file.
				if (cellValue != 0)
				{
					given = true;
				}
				//Adds values to the different grid elements (grid and row)
				//which are from the text file.
				m_gridRows[row].SetCell(column, new Cell(cellValue, given, canList));
				m_gridColumns[column].SetCell(row, m_gridRows[row].GetCell(column));
			}
		}
		//This method called is above.
		InitialiseBlockGrid();
	}
	file.close();
}

void SudokuPuzzle::CheckRow() const
{
	//Initialise my variables
	//Two Cell variables to get certain data
	//from the cell.
	Cell * currCell;
	Cell * checkCell;
	//Used to store the values from both the cells. 
	int value;
	int checkCellValue;


	//Double for loop to iterate round all of the cells.
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			//Get the current cell.
			currCell = m_gridRows[row].GetCell(column);
			//Get the value of that cell.
			value = currCell->GetValue();

			//If the value is 0, then we need to 
			//populate the candidate lists.
			if (value == 0)
			{
				//Two new vectors to hold candidate lists from the 
				//current cell and the one we're going to get.
				vector<int> valueList;
				vector<int>RowValues;

				//Loop round for each row
				for (int checkRow = 0; checkRow < 9; ++checkRow)
				{
					//Get the value of the row
					checkCell = m_gridRows[row].GetCell(checkRow);
					checkCellValue = checkCell->GetValue();

					//If it is not 0, put them into the RowValues vector.
					//This is a list of the numbers which cannot go in 
					//the candidate list of the current cell.
					if (checkCellValue != 0)
					{
						RowValues.push_back(checkCellValue);
					}
				}

				//Set a value checker of 1 to 9, we will see if the number 
				//is in the row value list, if not add it to a list which
				//we will push into a list to go into the candiate list.
				for (int valueChecker = 1; valueChecker < 10; ++valueChecker)
				{
					if (find(RowValues.begin(), RowValues.end(), valueChecker) == RowValues.end())
					{
						valueList.push_back(valueChecker);
					}
				}
				//Add the candidate list to the cell.
				//and clear the cell.
				currCell->SetList(valueList);
				valueList.clear();
			}
		}
	}
}
void SudokuPuzzle::CheckColumn() const
{
	//Initialise my variables
	//Two Cell variables to get certain data
	//from the cell.
	Cell * currCell;
	Cell * checkCell;
	Cell * getRowList;
	//Used to store the values from both the cells. 
	int value;
	int checkCellValue;
	//Checking number from row candidate lists.
	int check;

	vector<int>rowChecker;

	//Double for loop to iterate round all of the cells.
	for (int column = 0; column < 9; ++column)
	{
		for (int row = 0; row < 9; ++row)
		{
			//Get the current cell.
			currCell = m_gridColumns[column].GetCell(row);
			//Get the value of that cell.
			value = currCell->GetValue();

			//If the value is 0, then we need to 
			//populate the candidate lists.
			if (value == 0)
			{
				//Two new vectors to hold candidate lists from the 
				//current cell and the one we're going to get.
				vector<int> valueList;
				vector<int> ColumnValues;

				//Loop round for each column.
				for (int checkCol = 0; checkCol < 9; ++checkCol)
				{
					//Get the value of the column.
					checkCell = m_gridColumns[column].GetCell(checkCol);
					checkCellValue = checkCell->GetValue();

					//If it is not 0, put them into the ColumnValues vector.
					//This is a list of the numbers which cannot go in 
					//the candidate list of the current cell.
					if (checkCellValue != 0)
					{
						ColumnValues.push_back(checkCellValue);
					}
				}

				//Set a value checker of 1 to 9, we will see if the number 
				//is in the column value list, if not add it to a list which
				//we will push into a list to go into the candiate list.
				for (int valueChecker = 1; valueChecker < 10; ++valueChecker)
				{
					if (find(ColumnValues.begin(), ColumnValues.end(), valueChecker) == ColumnValues.end())
					{
						valueList.push_back(valueChecker);
					}
				}

				//Now we need to check it against the row lists.
				getRowList = m_gridRows[row].GetCell(column);
				rowChecker = getRowList->GetList();
				//Sort the lists.
				sort(rowChecker.begin(), rowChecker.end());
				sort(valueList.begin(), valueList.end());
				//Make a new values list.
				vector<int> newValueList;

				//Get the value of the row list.
				check = valueList.size();

				//Loop round for the size.
				for (int i = 0; i < check; ++i)
				{
					//Get each value of the row list.
					int valueChecker = valueList[i];

					//If row checker contains the value, remove it else put it into a list
					//which will be pushed into the cell as the candidate list.
					if (find(rowChecker.begin(), rowChecker.end(), valueChecker) == rowChecker.end())
					{
						rowChecker.erase(remove(rowChecker.begin(), rowChecker.end(), valueChecker), rowChecker.end());
					}
					else if (find(rowChecker.begin(), rowChecker.end(), valueChecker) != rowChecker.end())
					{
						newValueList.push_back(valueChecker);
					}
				}
				//Add the candidate list into the cell
				//and clear all of the other vectors
				//ready for the next cell.
				currCell->SetList(newValueList);
				rowChecker.clear();
				newValueList.clear();
				valueList.clear();
			}
		}
	}
}

void SudokuPuzzle::CheckBlock() const
{
	//Initialise my variables
	//Two Cell variables to get certain data
	//from the cell.
	Cell * currCell;
	Cell * checkCell;
	Cell * getCurrList;
	//Used to store the values from both the cells. 
	int value;
	int checkCellValue;
	//Checking number from row candidate lists.
	int check;

	vector<int>getBlockChecker;

	//Double for loop to iterate round all of the cells.
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			//Get the current cell.
			currCell = m_gridBlock[row].GetCell(column);
			//Get the value of that cell.
			value = currCell->GetValue();

			//If the value is 0, then we need to 
			//populate the candidate lists.
			if (value == 0)
			{
				//Two new vectors to hold candidate lists from the 
				//current cell and the one we're going to get.
				vector<int> valueList;
				vector<int> BlockValues;

				//Loop round for each block.
				for (int checkCol = 0; checkCol < 9; ++checkCol)
				{
					//Get the value of the column.
					checkCell = m_gridBlock[row].GetCell(checkCol);
					checkCellValue = checkCell->GetValue();

					//If it is not 0, put them into the BlockValues vector.
					//This is a list of the numbers which cannot go in 
					//the candidate list of the current cell.
					if (checkCellValue != 0)
					{
						BlockValues.push_back(checkCellValue);
					}
				}

				//Set a value checker of 1 to 9, we will see if the number 
				//is in the block value list, if not add it to a list which
				//we will push into a list to go into the candidate list.
				for (int valueChecker = 1; valueChecker < 10; ++valueChecker)
				{
					if (find(BlockValues.begin(), BlockValues.end(), valueChecker) == BlockValues.end())
					{
						valueList.push_back(valueChecker);
					}
				}
				//Now we need to check it against the column lists.
				getCurrList = m_gridBlock[row].GetCell(column);
				getBlockChecker = getCurrList->GetList();
				//Sort the lists.
				sort(getBlockChecker.begin(), getBlockChecker.end());
				sort(valueList.begin(), valueList.end());
				//Make a new values list.
				vector<int> newValueList;
				//Get the value of the row list.
				check = valueList.size();
				//Loop round for the size.
				for (int i = 0; i < check; ++i)
				{
					//Get each value of the row list.
					int valueChecker = valueList[i];

					//If column checker contains the value, remove it else put it into a list
					//which will be pushed into the cell as the candidate list.
					if (find(getBlockChecker.begin(), getBlockChecker.end(), valueChecker) == getBlockChecker.end())
					{
						getBlockChecker.erase(remove(getBlockChecker.begin(), getBlockChecker.end(), valueChecker), getBlockChecker.end());
					}
					else if (find(getBlockChecker.begin(), getBlockChecker.end(), valueChecker) != getBlockChecker.end())
					{
						newValueList.push_back(valueChecker);
					}
				}
				//Add the candidate list into the cell
				//and clear all of the other vectors
				//ready for the next cell.
				currCell->SetList(newValueList);
				getBlockChecker.clear();
				newValueList.clear();
				valueList.clear();
			}
		}
	}
}

void SudokuPuzzle::NakedSingles() const
{
	//In here is the code for the naked singles algorithm.
	//This one first scans all of the cells to form a list for each cell.
	//Cycle through until every one of the cell list only contains number.
	//This is the value for that cell. 

	Cell * currCell;
	vector<int> List;
	int counter = 0;
	int hasValue;

	//While the counter is not 81, this means we still
	//have unsorted cells, so we go round again until they're
	//all solved. 
	while (counter != 81)
	{
		//Loop round to visit each cell.
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				//Get the current value.
				currCell = m_gridBlock[row].GetCell(column);
				hasValue = currCell->GetValue();
				//If it's not 0, it has been solved so we increment
				//the counter.
				if (hasValue != 0)
				{
					++counter;
				}
				//Else we get the list.
				else
				{
					List = currCell->GetList();
					//If it has a size of one, we make the value of the
					//cell this the candidate. We set the candidate 
					//list to 0. This cell is now solved. 
					if (List.size() == 1)
					{
						currCell->SetValue(List[0]);
						List.clear();
						currCell->SetList(List);
						CheckRow();
						CheckColumn();
						CheckBlock();
					}
				}
			}
		}
		//If counter is not 81, reset the counter
		//and scan all the cells again.
		if (counter != 81)
		{
			counter = 0;
		}
	}
}


//This is the unfinished code for the hidden singles algorithm. 
//Unfortunatly, I didn't manage to get it working but this is left
//to show how I tried to do it and if I ever come back to it.

void SudokuPuzzle::HiddenSingles() const
{
	//THIS ONE SCANS THE ROW, COLUMN & BLOCK AND IF THE VALUE ONLY APPEARS 
	//IN **ONE** OF THE CELLS IT MUST BE THAT CELL. 
	vector<int> blockValues;
	vector<int> fullList;
	vector<int> singleOcc;
	vector<int> values;
	int valueChecker;
	bool solved = false;
	int counter = 0;
	int hasValue;

	while (solved == false)
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				if (hasValue != 0)
				{
					++counter;
				}

				// here



			}

			if (counter == 81)
			{
				solved = true;
			}
			else
			{
				counter = 0;
			}
		}

	}
}


	void SudokuPuzzle::Solve()
	{
		LARGE_INTEGER start, end, frequency;
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&start);

		// Solve the puzzle
		ReadInGrid();
		CheckRow();
		CheckColumn();
		CheckBlock();
		NakedSingles();
		//HiddenSingles();
		QueryPerformanceCounter(&end);
		float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
		// Output the solved puzzle
		Output();
		// Output the time it takes
		cout << time << endl;
	}


	void SudokuPuzzle::Output() const
	{
		Cell * currCell;
		int out;
		ofstream fout("sudoku_solution.txt");
		if (fout.is_open())
		{
			//Loop round for all cells.
			for (int y = 0; y < 9; ++y)
			{
				for (int x = 0; x < 9; ++x)
				{
					//Get the value and output it.
					currCell = m_gridRows[y].GetCell(x);
					out = currCell->GetValue();
					cout << out << " ";
					fout << out << " ";
				}
				cout << endl;
				fout << endl;
			}
			fout.close();
		}
	}
