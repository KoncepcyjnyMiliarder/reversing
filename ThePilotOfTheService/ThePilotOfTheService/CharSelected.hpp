#pragma once
#include "LineagePacket.hpp"

class CharSelected : public LineagePacket
{
public:
	CharSelected(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	int x, y, z;
	unsigned int objectId;
	std::wstring name;
	int race;
	int sex;
	int classID;
	int level;
	unsigned long long exp;
	int maxHP, currHP;
	int maxMP, currMP;
};