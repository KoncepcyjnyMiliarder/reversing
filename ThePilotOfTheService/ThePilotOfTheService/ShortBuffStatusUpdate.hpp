#pragma once
#include "LineagePacket.hpp"

//FA=ShortBuffStatusUpdate:d(SkillID:Get.Skill)d(SkillLevel)d(Duration)

class ShortBuffStatusUpdate : public LineagePacket
{
public:
	ShortBuffStatusUpdate(const char packet[], size_t length);
	virtual void HandlePacket() override;

private:

	unsigned int skillId;
	unsigned int skillLevel;
	unsigned int duration;
};
