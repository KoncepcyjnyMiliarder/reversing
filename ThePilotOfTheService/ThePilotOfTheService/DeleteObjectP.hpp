#pragma once
#include "LineagePacket.hpp"

class DeleteObjectP : public LineagePacket
{
public:
	DeleteObjectP(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	unsigned int objectId;
};