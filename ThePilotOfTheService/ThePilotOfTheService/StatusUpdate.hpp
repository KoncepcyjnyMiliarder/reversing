#pragma once
#include "LineagePacket.hpp"
#include "Resources.hpp"
#include <vector>

class StatusUpdate : public LineagePacket
{
public:
	StatusUpdate(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:	
	unsigned int objectId;
	std::vector<std::pair<StatusEnum, int>> attributes;

};
