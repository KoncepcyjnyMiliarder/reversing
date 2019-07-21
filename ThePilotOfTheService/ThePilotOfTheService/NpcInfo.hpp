#pragma once
#include "LineagePacket.hpp"

class NpcInfo : public LineagePacket
{
public:
	NpcInfo(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	NpcInfo();
	unsigned int objectId;
	int typeId;
	int isAttackable;
	int x, y, z;
	char isDead;
};