#include "BoundingBox.hpp"
#include "Maths.hpp"

void BoundingBox::Reset(std::vector<XYPair>&& polygonxyPairs, unsigned int newHeightDifference)
{
	maxHeightDifference = newHeightDifference;
	xyPairs = std::move(polygonxyPairs);
}

bool BoundingBox::isInsideBox(int x, int y, unsigned int heightDifference)
{
	if (xyPairs.size() < 3) return true; // polygon is not complete, so like whole area right?
	if (heightDifference > maxHeightDifference) return false;
	int sgn = Maths::sgn(Maths::determinant(
		xyPairs[0].x - xyPairs[xyPairs.size() - 1].x,
		xyPairs[0].y - xyPairs[xyPairs.size() - 1].y,
		x - xyPairs[xyPairs.size() - 1].x,
		y - xyPairs[xyPairs.size() - 1].y)
	);
	for (size_t i = 0; i < xyPairs.size() - 1; ++i)
	{
		int tempSgn = Maths::sgn(Maths::determinant(
			xyPairs[i + 1].x - xyPairs[i].x,
			xyPairs[i + 1].y - xyPairs[i].y,
			x - xyPairs[i].x,
			y - xyPairs[i].y)
		);
		if (tempSgn != sgn) return false;
	}
	return true;
}

void BoundingBox::Reset(size_t numVertices, XYPair&& center, unsigned int radius, unsigned int newHeightDifference)
{
	xyPairs.clear();
	maxHeightDifference = newHeightDifference;
	double fi = 2 * 3.1415 / numVertices;
	for (size_t i = 0; i < numVertices; i++)
	{
		xyPairs.push_back({ static_cast<int>(center.x + cos(fi * i) * radius), static_cast<int>(center.y + sin(fi * i) * radius) });
	}
}