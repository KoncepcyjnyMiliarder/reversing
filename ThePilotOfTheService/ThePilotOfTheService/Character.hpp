#pragma once
#include "WorldObject.hpp"
#include <string>

struct Character : public WorldObject
{
	Character(int x, int y, int z, const std::wstring& name, int race, int sex, int classID)
		:WorldObject(x, y, z), name(name), race(race), sex(sex), classID(classID) {}

	/*Character(const Character& rhs)
		:WorldObject(rhs), name(name), race(race), sex(sex), classID(classID) {}

	Character(Character&& rhs)
		:WorldObject(std::move(rhs)), name(std::move(rhs.name)), race(rhs.race), sex(rhs.sex), classID(rhs.classID) {}
		*/
	std::wstring name;
	int race;
	int sex;
	int classID;
};