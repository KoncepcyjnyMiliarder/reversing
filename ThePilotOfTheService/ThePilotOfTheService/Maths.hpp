#pragma once

namespace Maths
{

	unsigned int abs(int val); // problem. no bo roznica moze byc ujemna a abs nigdy

	template<typename T>
	T abs(T val)
	{
		return val < 0 ? -val : val;
	}

	template<typename T>
	int sgn(T val)
	{
		return val == 0 ? 0 : val < 0 ? -1 : 1;
	}

	int determinant(int ax, int ay, int bx, int by);
}