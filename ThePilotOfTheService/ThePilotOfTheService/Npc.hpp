#pragma once
#include "WorldObject.hpp"

class Npc : public WorldObject
{
public:
	//typeId(typeId), isAttackable(isAttackable), x(x), y(y), z(z), isAlive(1), currHP(1), maxHP(1), currMP(0)
	Npc(int typeId, bool isAttackable, bool isDead, int x, int y, int z)
		:WorldObject(x, y, z), typeId(typeId), isAttackable(isAttackable), isAlive(!isDead), currHP(1), maxHP(1), currMP(0) {}

	/*Npc(const Npc& rhs)
		:WorldObject(rhs), typeId(rhs.typeId), isAttackable(rhs.isAttackable),
		isAlive(rhs.isAlive), currHP(rhs.currHP), maxHP(rhs.maxHP), currMP(rhs.currMP) {}

	Npc(Npc&& rhs)
		:WorldObject(std::move(rhs)), typeId(rhs.typeId), isAttackable(rhs.isAttackable), 
		isAlive(rhs.isAlive), currHP(rhs.currHP), maxHP(rhs.maxHP), currMP(rhs.currMP) {}
		*/
	int typeId;
	bool isAttackable;
	bool isAlive;
	int currHP, maxHP;
	int currMP;
	//d(Heading)d(d)d(Maspd)d(Paspd)
	//d(runSpd)d(walkSpd)d(swimRSpd)d(swimWSpd)d(flRSpd)d(flWSpd)d(FlyRSpd)d(FlyWSpd)f(ProperMul)f(Paspd)
	//f(CollisRadius)f(CollisHeight)d(RHand:Get.Func01)d(d)d(LHand:Get.Func01)c(nameabove)c(isRun)c(isInFight)
	//c(isAlikeDead)c(isSummoned)s(Name)s(Title)d(d)d(PvpFlag)d(karma?)h(abnEffect)h(d)d(d)d(d)d(d)d(d)c(c)c(Team)f(collisRadius)f(collisHeight)d(d)
};