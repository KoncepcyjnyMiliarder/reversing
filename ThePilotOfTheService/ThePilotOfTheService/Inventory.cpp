#include "Inventory.hpp"

void Inventory::InsertItem(unsigned int objectId, Item&& item)
{
	std::lock_guard<std::mutex> lock(invMutex);
	if (backpack.count(objectId) == 1)
		backpack.at(objectId) = std::forward<Item>(item);
	else backpack.emplace(objectId, std::forward<Item>(item));
}

void Inventory::UpdateAmmount(unsigned int objectId, unsigned int ammount)
{
	std::lock_guard<std::mutex> lock(invMutex);
	if (backpack.count(objectId) == 1)
	{
		if (ammount == 0) backpack.erase(objectId);
		else backpack.at(objectId).ammount = ammount;
	}
}

unsigned int Inventory::TemplateIdToObjectId(unsigned int templateId)
{
	for (const auto& item : backpack)
	{
		if (item.second.typeID == templateId) return item.first;
	}
	return 0;
}
