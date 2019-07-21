#include "UserInfo.hpp"
#include "BotBrain.hpp"

//04=UserInfo:d(X)d(Y)d(Z)d(Heading)d(ObjectID)s(Name)
//d(Race)d(Sex)d(ClassID:Get.ClassID)d(Level)q(Exp)d(STR)d(DEX)d(CON)d(INT)d(WIT)d(MEN)
//d(MaxHP)d(CurHP)d(MaxMP)d(CurMP)d(SP)d(CurLoad)d(MaxLoad)d(d)d(DHair)d(Rear)d(Lear)d(Neck)d(RFinger)d(LFinger)d(Head)d(RHand)d(LHand)d(Gloves)d(Chest)d(Legs)d(Feet)d(Back)d(LRHand)d(Hair)d(Face)d(DHair:Get.Func01)d(Rear:Get.Func01)d(Lear:Get.Func01)d(Neck:Get.Func01)d(RFinger:Get.Func01)d(LFinger:Get.Func01)d(Head:Get.Func01)d(RHand:Get.Func01)d(LHand:Get.Func01)d(Gloves:Get.Func01)d(Chest:Get.Func01)d(Legs:Get.Func01)d(Feet:Get.Func01)d(Back:Get.Func01)d(LRHand:Get.Func01)d(Hair:Get.Func01)d(Face)z(0068)d(Patk)d(Paspd)d(Pdef)d(evasion)d(accur)d(crithit)d(Matk)d(Maspd)d(Paspd)d(Mdef)d(PvpFlag)d(Karma)d(runSpd)d(walkSpd)d(swimRSpd)d(swimWSpd)d(flRSpd)d(flWSpd)d(flyRSpd)d(flyWSpd)f(MoveMul)f(aspdMul)f(collisRadius)f(collisHeight)d(HairStyle)d(HairColor:Get.FCol)d(Face)d(AccessLvl)s(Title)d(clanID)d(clanCrestId)d(AllyID)d(AllyCrestId)d(ClanLeader)c(Mount)c(shop)c(DwarfCraft)d(PKkills)d(PVPkills)h(cubics:For.0001)h(cubID)c(findparty)d(abnEffects)c(c)d(clanPrivil)h(RecomLeft)h(RecomHave)d(d)h(InventLimit)d(classId:Get.ClassID)d(sEff)d(maxCP)d(curCP)c(Mount)c(Team)d(clanBigCrestId)c(Noble)c(Hero)c(Fishing)d(fishX)d(fishY)d(fishZ)d(NameColor:Get.FCol)c(isRun)d(PledgeClass)d(d)d(TitleColor:Get.FCol)d(d)d(CurseWeap)

//32=UserInfo:d(X)d(Y)d(Z)d(isInAirShip)d(ObjectID)s(Name)
//d(Race)d(Sex)d(ClassID:Get.ClassID)d(Level)q(Exp)d(Str)d(Dex)d(Con)d(Int)d(Wit)d(Men)
//d(MaxHP)d(CurHP)d(MaxMP)d(CurMP)d(Sp)d(CurLoad)d(MaxLoad)d(isWeapEquip 40yes)d(Under)d(REar)d(LEar)d(Neck)d(RRing)d(LRing)d(Head)d(RHand)d(LHand)d(Gloves)d(Chest)d(Legs)d(Feet)d(Back)d(LRHand)d(Hair)d(Hair2)d(RBrace)d(LBrace)d(DEC1)d(DEC2)d(DEC3)d(DEC4)d(DEC5)d(DEC6)d(Belt)d(Under:Get.F0)d(REar:Get.F0)d(LEar:Get.F0)d(Neck:Get.F0)d(RRing:Get.F0)d(LRing:Get.F0)d(Head:Get.F0)d(RHand:Get.F0)d(LHand:Get.F0)d(Gloves:Get.F0)d(Chest:Get.F0)d(Legs:Get.F0)d(Feet:Get.F0)d(Back:Get.F0)d(LRHand:Get.F0)d(Hair:Get.F0)d(Hair2:Get.F0)d(RBrace:Get.F0)d(LBrace:Get.F0)d(DEC1:Get.F0)d(DEC2:Get.F0)d(DEC3:Get.F0)d(DEC4:Get.F0)d(DEC5:Get.F0)d(DEC6:Get.F0)d(Belt:Get.F0)d(AUnder:Get.F1)d(AREar:Get.F1)d(ALEar:Get.F1)d(ANeck:Get.F1)d(ARRing:Get.F1)d(ALRing:Get.F1)d(AHead:Get.F1)d(ARHand:Get.F1)d(ALHand:Get.F1)d(AGloves:Get.F1)d(AChest:Get.F1)d(ALegs:Get.F1)d(AFeet:Get.F1)d(ABack:Get.F1)d(ALRHand:Get.F1)d(AHair:Get.F1)d(AHair2:Get.F1)d(ARBrace:Get.F1)d(ALBrace:Get.F1)d(ADEC1:Get.F1)d(ADEC2:Get.F1)d(ADEC3:Get.F1)d(ADEC4:Get.F1)d(ADEC5:Get.F1)d(ADEC6:Get.F1)d(ABelt:Get.F1)d(talismanSlots)d(cloakStatus)d(Patk)d(PatkSpd)d(Pdef)d(EvasionRate)d(Accuracy)d(CriticalHit)d(Matk)d(MatkSpd)d(PatkSpd)d(Mdef)d(PvPFlag)d(Karma)d(RunSpd)d(WalkSpd)d(SwimRunSpd)d(SwimWalkSpd)d(0)d(0)d(FlyRunSpd)d(FlyWalkSpd)f(MoveMul)f(AtkSpeedMul)f(ColRadius)f(ColHeight)d(HairStyle)d(HairColor)d(Face)d(isGM)s(Title)d(ClanID)d(ClanCrestID)d(AllyID)d(AllyCrestID)d(Relation)c(mountType)c(privateStoreType)c(isDwarvenCraft)d(pkKills)d(pvpKills)h(cubicsSize:Loop.01.0001)h(cubicID)c(findParty)d(abnormalEffect)c(isFlyingMounted)d(clanPrivs)h(recomLeft)h(recomHave)d(mountNpcID:Get.NpcId)h(inventoryLimit)d(ClassID:Get.ClassID)d(specEffects)d(MaxCP)d(CurCP)c(isMounted)c(Team)d(clanCrestLargeID)c(isNoble)c(isHero)c(isFishing)d(fishX)d(fishY)d(fishZ)d(nameColor:Get.FCol)c(isRunning)d(PledgeClass)d(PledgeType)d(titleColor:Get.FCol)d(cursedWeap:Get.F0)d(Transformation)h(AttackElem)h(AttackElemPower)h(DefFire)h(DefWater)h(DefWind)h(DefEarth)h(DefHoly)h(DefUnholy)d(AgathionId)d(Fame)d(mmapAllowed)d(Vitality)d(specEffects)

UserInfo::UserInfo(const char packet[], size_t length)
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
	level = serializer.ReadD();
	exp = serializer.ReadD();
	unsigned long long tmp = serializer.ReadD();
	exp |= tmp << 32;
	serializer.Skip(24);
	//MAGIC! skp 8 znikad
	serializer.Skip(8);
	maxHP = serializer.ReadD();
	currHP = serializer.ReadD();
	maxMP = serializer.ReadD();
	currMP = serializer.ReadD();
}

void UserInfo::HandlePacket()
{
	BotBrain::GetInstance().GetWorld().HandleCharacterSelected(PlayerCharacter(objectId,
		x, y, z, name, race, sex, classID, level, exp, maxHP, currHP, maxMP, currMP));
}
