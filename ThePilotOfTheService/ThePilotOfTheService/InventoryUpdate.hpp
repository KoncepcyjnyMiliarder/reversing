#pragma once
#include "LineagePacket.hpp"
#include <vector>
#include "Item.hpp"

//21=InventoryUpdate:h(count:Loop.01.0025)h(1add 2mod 3remove)d(ObjectID)d(ItemID:Get.F0)d(Slot)q(Count)h(ItemType2)h(CustomType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(CustType2)d(AugmID:Get.F1)d(Mana)d(remainTime)h(AttackElem)h(AttackElemVal)h(DefAttrFire)h(DefAttrWater)h(DefAttrWind)h(DefAttrEarth)h(DefAttrHoly)h(DefAttrUnholy)h(EnchEff1)h(enchEff2)h(enchEff3)
//27=InventoryUpdate:h(count:For.0013)h(1add2mod3remove)h(itemType1)d(ObjectId)d(ItemId:Get.Func01)d(Count)h(itemType2)h(cusType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(cusType2)d(AugId)d(Shadowtime)

class InventoryUpdate : public LineagePacket
{
public:
	InventoryUpdate(const char packet[], size_t length);
	virtual void HandlePacket() override;
private:
	struct InvUpdate
	{
		short action;
		unsigned int objectId;
		unsigned int typeId;
		unsigned int ammount;
	};
	std::vector<InvUpdate> updates;
};
