#pragma once
#include "LineagePacket.hpp"

class MoveToLocation : public LineagePacket
{
public:
	MoveToLocation(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	unsigned int objectId;
	int toX, toY, toZ;
	int fromX, fromY, fromZ;
};