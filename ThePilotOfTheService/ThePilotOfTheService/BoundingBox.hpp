#pragma once
#include <vector>

struct XYPair
{
	int x;
	int y;
};

class BoundingBox
{
public:
	BoundingBox()
		:maxHeightDifference(0) {}
	void Reset(std::vector<XYPair>&& polygonxyPairs, unsigned int maxHeightDifference);
	void Reset(size_t numVertices, XYPair&& center, unsigned int radius, unsigned int maxHeightDifference);
	void Clear() { xyPairs.clear(); }
	bool isInsideBox(int x, int y, unsigned int heightDifference);
	const std::vector<XYPair>& getPolygon() { return xyPairs; }
private:
	unsigned int maxHeightDifference;
	std::vector<XYPair> xyPairs;
};