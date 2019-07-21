#pragma once
#include "LineagePacket.hpp"

class MyTargetSelected : public LineagePacket
{
public:
	MyTargetSelected(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	MyTargetSelected();
	unsigned int targetID;
};