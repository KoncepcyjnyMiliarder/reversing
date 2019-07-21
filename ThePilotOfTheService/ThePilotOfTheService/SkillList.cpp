#include "SkillList.hpp"
#include "World.hpp"
//58=SkillList:d(ListCount:For.0004)d(isPassive)d(lvl)d(SkillID:Get.Skill)c(c)

SkillList::SkillList(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	/*size_t size = serializer.ReadD();
	for (size_t i = 0; i < size; ++i)
	{
		bool isPassive = serializer.ReadD();
		DWORD level = ReadD();
		DWORD skillID = ReadD();
		ReadC();
		if (world.version->GetVersion() == VersionInfo::L2_H5) ReadC();
		skills.push_back({ skillID,isPassive,level });
	}*/
}

void SkillList::HandlePacket()
{
	/*World& world = World::GetInstance();
	for (size_t i = 0; i < skills.size(); ++i)
	{
		DbgPrint("Skill %X %X %X\n", skills[i].skillID, skills[i].skillLevel, skills[i].isPassive);
	}

	world.player->skills = skills;*/
}
