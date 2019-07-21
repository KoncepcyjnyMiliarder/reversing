#pragma once
#include "LineagePacket.hpp"
#include <map>
#include "Item.hpp"

class ItemList : public LineagePacket
{
public:
	ItemList(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	std::map<unsigned int, Item> inv;
};
