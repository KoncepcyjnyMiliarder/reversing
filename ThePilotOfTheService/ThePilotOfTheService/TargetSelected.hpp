#pragma once
#include "LineagePacket.hpp"

class TargetSelected : public LineagePacket
{
public:
	TargetSelected(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	TargetSelected();
	unsigned int objectId;
	int targetID;
	int x;
	int y;
	int z;
};