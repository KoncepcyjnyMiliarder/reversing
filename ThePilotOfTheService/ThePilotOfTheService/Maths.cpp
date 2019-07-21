#include "Maths.hpp"

unsigned int Maths::abs(int val)   // problem. no bo roznica moze byc ujemna a abs nigdy
{
	return val < 0 ? -val : val;
}

int Maths::determinant(int ax, int ay, int bx, int by)
{
	return ax*by - ay*bx;
}
