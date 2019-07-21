#include "CharSelected.hpp"
#include "BotBrain.hpp"

//0B=CharSelected:s(Name)d(CharID)s(Title)d(SessionID)d(ClanID)d(0)d(Sex)d(Race)d(ClassID:Get.ClassID)d(active)d(X)d(Y)d(Z)f(curHP)f(curMP)d(SP)q(EXP)d(Level)d(karma)d(pkKills)d(INT)d(STR)d(CON)d(MEN)d(DEX)d(WIT)d(gameTime)d(0)d(ClassID:Get.ClassID)z(0016)z(0064)d(0)

//nafixuj unique id, a moze to brac z pamieci?

CharSelected::CharSelected(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	name = std::wstring(serializer.ReadS());
	objectId = serializer.ReadD();
	serializer.ReadS();
	serializer.ReadD();
	serializer.ReadD();
	serializer.ReadD();
	sex = serializer.ReadD();
	race = serializer.ReadD();
	classID = serializer.ReadD();
	serializer.ReadD();
	x = serializer.ReadD();
	y = serializer.ReadD();
	z = serializer.ReadD();
	serializer.ReadD();
	serializer.ReadD();
	serializer.ReadD();
	serializer.ReadD();
	serializer.ReadD();
	exp = serializer.ReadD();
	unsigned long long tmp = serializer.ReadD();
	exp |= tmp << 32;
	level = serializer.ReadD();
}
#include <Windows.h>

void CharSelected::HandlePacket()
{
	BotBrain::GetInstance().GetWorld().HandleCharacterSelected(PlayerCharacter(
		objectId, x, y, z, name, race, sex, classID, level, exp, 1, 1, 1, 1));
	BotBrain::GetInstance().GetWorld().HandleWorldEnter();
}
