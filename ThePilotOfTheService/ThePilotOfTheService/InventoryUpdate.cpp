#include "InventoryUpdate.hpp"
#include "VersionInfo.hpp"
#include "BotBrain.hpp"

//21=InventoryUpdate:h(count:Loop.01.0025)h(1add 2mod 3remove)d(ObjectID)d(ItemID:Get.F0)d(Slot)q(Count)h(ItemType2)h(CustomType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(CustType2)d(AugmID:Get.F1)d(Mana)d(remainTime)h(AttackElem)h(AttackElemVal)h(DefAttrFire)h(DefAttrWater)h(DefAttrWind)h(DefAttrEarth)h(DefAttrHoly)h(DefAttrUnholy)h(EnchEff1)h(enchEff2)h(enchEff3)
//27=InventoryUpdate:h(count:For.0013)h(1add2mod3remove)h(itemType1)d(ObjectId)d(ItemId:Get.Func01)d(Count)h(itemType2)h(cusType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(cusType2)d(AugId)d(Shadowtime)

/*21=InventoryUpdate:h(count:Loop.01.0025)
h(1add 2mod 3remove)d(ObjectID)d(ItemID:Get.F0)d(Slot)q(Count)h(ItemType2)						6
h(CustomType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(CustType2)d(AugmID:Get.F1)				16
d(Mana)d(remainTime)h(AttackElem)h(AttackElemVal)h(DefAttrFire)h(DefAttrWater)					16
h(DefAttrWind)h(DefAttrEarth)h(DefAttrHoly)h(DefAttrUnholy)h(EnchEff1)h(enchEff2)h(enchEff3)	14

*/
InventoryUpdate::InventoryUpdate(const char packet[], size_t length)
	:LineagePacket(packet, 1, length)
{
	auto ver = VersionInfo::getInstance().GetVersion();
	if (ver == L2_IL) return; // interlude qq
	short count = serializer.ReadH();
	for (short i = 0; i < count; ++i)
	{
		InvUpdate temp;
		temp.action = serializer.ReadH();
		temp.objectId = serializer.ReadD();
		temp.typeId = serializer.ReadD();
		serializer.Skip(4);
		temp.ammount = serializer.ReadD();
		serializer.Skip(6 + 16 + 16 + 14);
		////printf("Update! %d %X %X %d\n", temp.action, temp.objectId, temp.typeId, temp.ammount);
		updates.push_back(temp);
	}
}

void InventoryUpdate::HandlePacket()
{
	Inventory& inv = BotBrain::GetInstance().backpack;
	for (const auto& update : updates)
	{
		switch (update.action)
		{
		case 1:
			return inv.InsertItem(update.objectId, Item(update.typeId, update.ammount));
		case 2:
			return inv.UpdateAmmount(update.objectId, update.ammount);
		case 3:
			return inv.UpdateAmmount(update.objectId, 0);
		}
		
	}
}

