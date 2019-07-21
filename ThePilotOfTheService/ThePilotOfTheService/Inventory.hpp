#pragma once
#include "Item.hpp"
#include <map>
#include <mutex>

class Inventory
{
public:

	void Set(std::map<unsigned int, Item>&& newInv) { backpack = std::move(newInv); }
	void InsertItem(unsigned int objectId, Item&& item);
	void UpdateAmmount(unsigned int objectId, unsigned int ammount); // if 0, remove
	const std::map<unsigned int, Item>& GetInv() { return backpack; }
	void Clear() { backpack.clear(); }
	unsigned int TemplateIdToObjectId(unsigned int templateId);

private:

	std::mutex invMutex;
	std::map<unsigned int, Item> backpack;
};