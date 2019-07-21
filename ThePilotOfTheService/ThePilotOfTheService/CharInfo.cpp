#include "CharInfo.hpp"
#include "BotBrain.hpp"

//03=CharInfo:d(X)d(Y)d(Z)d(Heading)d(objectId)s(Name)d(Race)d(Sex)d(ClassID:Get.ClassID)d(DHair)d(Head:Get.Func01)d(RHand:Get.Func01)d(LHand:Get.Func01)d(Gloves:Get.Func01)d(Chest:Get.Func01)d(Legs:Get.Func01)d(Feet:Get.Func01)d(Back:Get.Func01)d(LRHand:Get.Func01)d(Hair:Get.Func01)d(Face)z(0048)d(PvpFlag)d(Karma)d(MSpeed)d(PSpeed)d(PvpFlag)d(Karma)d(runSpd)d(walkSpd)d(swimRSpd)d(swimWSpd)d(flRunSpd)d(flWalkSpd)d(flyRSpd)d(flyWSpd)f(SpdMul)f(ASpdMul)f(collisRadius)f(collisHeight)d(HairStyle)d(HairColor:Get.FCol)d(Face)s(Title)d(clanID)d(clanCrest)d(allyID)d(allyCrest)d(siegeFlag)c(isStand)c(isRun)c(isInFight)c(isAlikeDead)c(Invis)c(Mount)c(shop)h(cubics:For.0001)h(cubID)c(findparty)d(abnEffects)c(RecomLeft)h(RecomHave)d(classID:Get.ClassID)d(maxCP)d(curCP)c(isMounted)c(Team)d(clanBigCrestId)c(isNoble)c(isHero)c(isFishing)d(fishX)d(fishY)d(fishZ)d(NameColor:Get.FCol)d(isRun)d(PledgeClass)d(PledgeColor:Get.FCol)d(TitleColor:Get.FCol)d(d)d(Cursed)

CharInfo::CharInfo(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	x = serializer.ReadD();
	y = serializer.ReadD();
	z = serializer.ReadD();
	serializer.ReadD();
	objectId = serializer.ReadD();
	name = std::wstring(serializer.ReadS());
	race = serializer.ReadD();
	sex = serializer.ReadD();
	classID = serializer.ReadD();
}

void CharInfo::HandlePacket()
{
	BotBrain::GetInstance().GetWorld().InsertCharacter(objectId, Character(x, y, z, name, race, sex, classID));
}
