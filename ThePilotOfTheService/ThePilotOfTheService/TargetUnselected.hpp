#pragma once
#include "LineagePacket.hpp"

class TargetUnselected : public LineagePacket
{
public:
	TargetUnselected(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	TargetUnselected();
	unsigned int targetID;
	int x;
	int y;
	int z;

};