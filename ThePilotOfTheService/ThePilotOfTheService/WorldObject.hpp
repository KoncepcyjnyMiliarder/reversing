#pragma once

struct WorldObject
{
	
	int x, y, z;

protected:

	WorldObject(int x, int y, int z)
		:x(x), y(y), z(z) {}
	virtual ~WorldObject() = default;
};