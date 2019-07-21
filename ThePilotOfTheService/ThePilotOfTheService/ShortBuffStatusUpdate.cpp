#include "ShortBuffStatusUpdate.hpp"
#include "BotBrain.hpp"
#include <Windows.h>

//FA=ShortBuffStatusUpdate:d(SkillID:Get.Skill)d(SkillLevel)d(Duration)

ShortBuffStatusUpdate::ShortBuffStatusUpdate(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	skillId = serializer.ReadD();
	skillLevel = serializer.ReadD();
	duration = serializer.ReadD();
}

void ShortBuffStatusUpdate::HandlePacket()
{
	//MessageBoxA(0, std::to_string(skillId).c_str(), "", 0);
	//BotBrain::GetInstance().GetWorld().GetPlayer().buffs.push_back({ skillId,skillLevel,GetTickCount() + duration });
}

