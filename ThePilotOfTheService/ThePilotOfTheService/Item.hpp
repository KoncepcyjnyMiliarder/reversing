#pragma once
#include "WorldObject.hpp"
#include <string>

struct Item : public WorldObject
{
	Item(unsigned int typeID, unsigned int ammount)
		:WorldObject(0, 0, 0), typeID(typeID), ammount(ammount){}

	/*Character(const Character& rhs)
	:WorldObject(rhs), name(name), race(race), sex(sex), classID(classID) {}

	Character(Character&& rhs)
	:WorldObject(std::move(rhs)), name(std::move(rhs.name)), race(rhs.race), sex(rhs.sex), classID(rhs.classID) {}
	*/
	std::wstring name;
	unsigned int typeID;
	unsigned int ammount;
};