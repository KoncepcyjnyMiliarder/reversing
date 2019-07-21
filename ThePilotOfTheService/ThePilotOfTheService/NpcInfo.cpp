#include "NpcInfo.hpp"
#include "BotBrain.hpp"
//NpcInfo:d(objectId)d(NpcTypeId : Get.NpcId)d(IsAttackable)d(X)d(Y)d(Z)d(Heading)d(d)d(Maspd)d(Paspd)
//d(runSpd)d(walkSpd)d(swimRSpd)d(swimWSpd)d(flRSpd)d(flWSpd)d(FlyRSpd)d(FlyWSpd)f(ProperMul)f(Paspd)
//f(CollisRadius)f(CollisHeight)d(RHand : Get.Func01)d(d)d(LHand : Get.Func01)c(nameabove)c(isRun)
//c(isInFight)c(isAlikeDead)c(isSummoned)s(Name)s(Title)d(d)d(PvpFlag)d(karma ? )h(abnEffect)
//h(d)d(d)d(d)d(d)d(d)c(c)c(Team)f(collisRadius)f(collisHeight)d(d)
NpcInfo::NpcInfo(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	objectId = serializer.ReadD();
	typeId = serializer.ReadD();
	isAttackable = serializer.ReadD();
	x = serializer.ReadD();
	y = serializer.ReadD();
	z = serializer.ReadD();
	//15 4 3b
	serializer.Skip(15 * 4 + 4 * 8 + 3);
	isDead = serializer.ReadC();
}

void NpcInfo::HandlePacket()
{
	BotBrain::GetInstance().GetWorld().InsertNpc(objectId, Npc(typeId, isAttackable ? true : false, isDead, x, y, z));
}
