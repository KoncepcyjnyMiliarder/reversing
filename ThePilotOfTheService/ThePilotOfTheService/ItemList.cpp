#include "ItemList.hpp"
#include "VersionInfo.hpp"
#include "BotBrain.hpp"

//1B=ItemListPacket:h(window)h(ListCount:For.0012)h(itemType1)d(ObjectId)d(ItemID:Get.Func01)d(count)h(itemType2)h(CustType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(CustType2)d(AugId)d(Shadowtime)
//11=ItemList:h(ShowWindow)h(count:Loop.01.0024)d(ObjectID)d(ItemID:Get.F0)d(LocationSlot)q(Count)h(ItemType2)h(CustomType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(CustType2)d(AugmentID:Get.F1)d(Mana)d(remainTime)h(AttackElem)h(AttackElemVal)h(DefAttrFire)h(DefAttrWater)h(DefAttrWind)h(DefAttrEarth)h(DefAttrHoly)h(DefAttrUnholy)h(EnchEff1)h(enchEff2)h(enchEff3)h(blockedItems:Loop.02.0001)c(blockMode)d(blockItem)

/*

d(ObjectID)d(ItemID:Get.F0)d(LocationSlot)q(Count)h(ItemType2			6 skip
h(CustomType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(CustType2)		12
d(AugmentID:Get.F1)d(Mana)d(remainTime)h(AttackElem)h(AttackElemVal)	16
h(DefAttrFire)h(DefAttrWater)h(DefAttrWind)h(DefAttrEarth)				8
h(DefAttrHoly)h(DefAttrUnholy)h(EnchEff1)h(enchEff2)h(enchEff3)			10
h(blockedItems:Loop.02.0001)c(blockMode)d(blockItem)					//to jest chyba poza glowna petla

*/
ItemList::ItemList(const char packet[], size_t length)
	:LineagePacket(packet, 1, length)
{
	auto ver = VersionInfo::getInstance().GetVersion();
	if (ver == L2_IL) return; // interlude qq
	serializer.ReadH();
	short count = serializer.ReadH();
	for (short i = 0; i < count; ++i)
	{
		unsigned int objectId = serializer.ReadD();
		unsigned int typeId = serializer.ReadD();
		serializer.ReadD();
		unsigned int count = serializer.ReadD();
		serializer.Skip(6 + 12 + 16 + 8 + 10);
		inv.emplace(objectId, Item(typeId, count));
		////printf("Cziki briki %X %X %d\n", objectId, typeId, count);
	}

}

void ItemList::HandlePacket()
{
	BotBrain::GetInstance().backpack.Clear();
	BotBrain::GetInstance().backpack.Set(std::move(inv));
}
