#include "Element.h"

Element::Element()
{
	number = 0;
	possible[0] = false;
	count = 9;
	for (int i = 1; i < 10; i++)
		possible[i] = true;
}

Element::Element(int num)
{
	if (num == 0)
	{
		number = 0;
		count = 9;
		for (int i = 1; i < 10; i++)
			possible[i] = true;
	}
	else
	{
		setNum(num);
	}
}

void Element::setNum(int num)
{
	number = num;
}

int Element::getNum()
{
	return number;
}

bool Element::getKnown()
{
	if (number > 0)
		return true;
	return false;
}

bool Element::setFalse(int n)
{
	if (number > 0)
		return false;
	if (possible[n])
	{
		count--;
		possible[n] = false;
		if (count == 1)
		{
			for (int i = 1; i <= 9; i++)
			{
				if (possible[i])
				{
					setNum(i);
					return true;
				}
			}
		}
	}
	return false;
}

bool Element::getPossible(int n)
{
	if (number > 0)
		return false;
	return possible[n];
}

bool Element::canGuess()
{
	if (count == 2)
		return true;
	return false;
}
