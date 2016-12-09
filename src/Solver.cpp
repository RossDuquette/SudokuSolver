#include "Solver.h"
#include <vector>
#include <iostream>
#include <fstream>

int main()
{	
	//initialize
	Element* cell = new Element[81];
	read(cell, "2");
	
	bool solved = solve(cell);

	//output
	cout << (solved ? "Successfully solved puzzle" : "Could not solve puzzle") << endl;
	write(cell, "2", solved);
	delete[] cell;
	return 0;
}

bool check(Element* cell, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9)
{
	bool ret = false, exists;
	vector<Element*> known, unknown;
	known.clear();
	unknown.clear();
	int num, counter;
	
	if (cell[n1].getKnown()) known.push_back(&cell[n1]); else unknown.push_back(&cell[n1]);
	if (cell[n2].getKnown()) known.push_back(&cell[n2]); else unknown.push_back(&cell[n2]);
	if (cell[n3].getKnown()) known.push_back(&cell[n3]); else unknown.push_back(&cell[n3]);	
	if (cell[n4].getKnown()) known.push_back(&cell[n4]); else unknown.push_back(&cell[n4]);	
	if (cell[n5].getKnown()) known.push_back(&cell[n5]); else unknown.push_back(&cell[n5]);	
	if (cell[n6].getKnown()) known.push_back(&cell[n6]); else unknown.push_back(&cell[n6]);	
	if (cell[n7].getKnown()) known.push_back(&cell[n7]); else unknown.push_back(&cell[n7]);	
	if (cell[n8].getKnown()) known.push_back(&cell[n8]); else unknown.push_back(&cell[n8]);	
	if (cell[n9].getKnown()) known.push_back(&cell[n9]); else unknown.push_back(&cell[n9]);
	
	//set possibilities based on known values in set
	for (int i = 0; i < known.size(); i++)
	{
		num = (*known[i]).getNum();
		for (int j = 0; j < unknown.size(); j++)
		{
			bool update = (*unknown[j]).setFalse(num);
			if (update)
			{
				known.push_back(unknown[j]);
				unknown.erase(unknown.begin() + j);
				j--;
				ret = true;
			}
		}
	}
	
	//check if only one element can be a missing number
	for (num = 1; num <= 9; num++)
	{
		counter = 0;
		exists = false;

		for (int i = 0; i < known.size(); i++)
		{
			if ((*known[i]).getNum() == num)
			{
				exists = true;
				break;
			}
		}

		if (exists)
			continue;
		
		for (int i = 0; i < unknown.size(); i++)
		{
			if ((*unknown[i]).getPossible(num))
				counter++;
		}
		
		//only possible element
		if (counter == 1)
		{
			for (int i = 0; i < unknown.size(); i++)
			{
				if ((*unknown[i]).getPossible(num))
				{
					(*unknown[i]).setNum(num);
					known.push_back(unknown[i]);
					unknown.erase(unknown.begin()+i);
					i--;
					ret = true;
					break;	
				}
			}
		}
	}
	return ret;
}

void read(Element* cell, string name)
{
	int num;
	name = "./Puzzles/Problem_" + name + ".txt";
	ifstream fin;
	fin.open(name.c_str());
	if (fin.is_open())
	{
		for (int i = 0; i < 81 && !fin.eof(); i++)
		{
			fin >> num;
			cell[i].setNum(num);
		}
	}
	fin.close();
}

void write(Element* cell, string name, bool done)
{
	name = "./Puzzles/Solution_" + name + ".txt";
	ofstream fout;
	fout.open(name.c_str());
	if (fout.is_open())
	{
		if (!done)
		{
			fout << "Solution could not be found \n";
		}
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (j == 3 || j == 6)
					fout << "| ";
				if (cell[i*9+j].getKnown())
					fout << cell[i*9+j].getNum() << " ";
				else
					fout << 0 << " ";
			}
			fout << endl;
			if (i == 2 || i == 5)
				fout << "---------------------\n";
		}
	}
	fout.close();
}

bool solve(Element* cell)
{
	bool changed = true;
	while (changed)
	{
		changed = false;
		//iterate through rows
		for (int i = 0; i < 9; i++)
			changed = check(cell, 9 * i, 9 * i + 1, 9 * i + 2, 9 * i + 3, 9 * i + 4, 9 * i + 5, 9 * i + 6, 9 * i + 7, 9 * i + 8) || changed;

		//iterate through columns
		for (int i = 0; i < 9; i++)
			changed = check(cell, i, 9 + i, 18 + i, 27 + i, 36 + i, 45 + i, 54 + i, 63 + i, 72 + i) || changed;

		//iterate through boxes
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				changed = check(cell, i * 27 + j * 3, i * 27 + j * 3 + 1, i * 27 + j * 3 + 2, i * 27 + j * 3 + 9, i * 27 + j * 3 + 10, i * 27 + j * 3 + 11, i * 27 + j * 3 + 18, i * 27 + j * 3 + 19, i * 27 + j * 3 + 20) || changed;
			}
		}
	}

	//check if done
	if (!finished(cell)) //try guessing
	{
		for (int i = 0; i < 81; i++)
		{
			if (cell[i].canGuess())
			{
				//get possible guesses
				int guess1=0, guess2=0;
				for (int j = 1; j <= 9; j++)
				{
					if (guess1 == 0 && cell[i].getPossible(j))
						guess1 = j;
					else if (guess1 != 0 && cell[i].getPossible(j))
					{
						guess2 = j;
						break;
					}
				}

				Element* cellGuess = new Element[81];
				memcpy(cellGuess, cell, sizeof(Element)*81);
				cellGuess[i].setNum(guess1);
				
				if (solve(cellGuess))
				{
					memcpy(cell, cellGuess, sizeof(Element)*81);
					delete[] cellGuess;
					return true;
				}
				else
				{
					memcpy(cellGuess, cell, sizeof(Element)*81);
					cellGuess[i].setNum(guess2);
					if (solve(cellGuess))
					{
						memcpy(cell, cellGuess, sizeof(Element)*81);
						delete[] cellGuess;
						return true;
					}
					else
					{
						delete[] cellGuess;
						return false;
					}
				}
			}
		}
	}
	else
		return true;
}

bool finished(Element* cell)
{
	for (int i = 0; i < 81; i++)
	{
		if (!(cell[i].getKnown()))
		{
			return false;
		}
	}
	return true;
}
