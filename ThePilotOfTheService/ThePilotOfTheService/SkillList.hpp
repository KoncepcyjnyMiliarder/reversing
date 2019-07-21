#pragma once
#include "LineagePacket.hpp"
//#include "Skill.hpp"
#include <vector>

class SkillList : public LineagePacket
{
public:
	SkillList(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	//std::vector<Skill> skills;
};