#pragma once
#include "LineagePacket.hpp"

class Die : public LineagePacket
{
public:
	Die(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	unsigned int objectId;
	int sweepable;
};