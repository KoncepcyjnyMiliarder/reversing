#include "LineagePacketFactory.hpp"
#include "VersionInfo.hpp"
#include "CharInfo.hpp"
#include "CharSelected.hpp"
#include "DeleteObjectP.hpp"
#include "Die.hpp"
#include "MoveToLocation.hpp"
#include "MyTargetSelected.hpp"
#include "NpcInfo.hpp"
#include "SkillList.hpp"
#include "StatusUpdate.hpp"
#include "TargetSelected.hpp"
#include "TargetUnselected.hpp"
#include "UserInfo.hpp"
#include "ItemList.hpp"
#include "InventoryUpdate.hpp"
#include "ShortBuffStatusUpdate.hpp"
std::unique_ptr<LineagePacket> LineagePacketFactory::Construct(const char packet[], size_t length)
{
	switch (VersionInfo::getInstance().OpcodeToPacket((unsigned char)packet[0]))
	{
		//case keyInit:
	case charSelected:
		return std::unique_ptr<LineagePacket>(new CharSelected(packet, length));
	case moveToLocation:
		return std::unique_ptr<LineagePacket>(new MoveToLocation(packet, length));
		//case npcSay:
	case charInfo:
		return std::unique_ptr<LineagePacket>(new CharInfo(packet, length));
	case userInfo:
		return std::unique_ptr<LineagePacket>(new UserInfo(packet, length));
		//case attack:
	case die:
		return std::unique_ptr<LineagePacket>(new Die(packet, length));
	case deleteObject:
		return std::unique_ptr<LineagePacket>(new DeleteObjectP(packet, length));
		//case revive:
		//case attackOutOfRange:
		//case attackinCoolTime:

		//case attackDeadTarget:
	case statusUpdate:
		return std::unique_ptr<LineagePacket>(new StatusUpdate(packet, length));
	case npcInfo:
		return std::unique_ptr<LineagePacket>(new NpcInfo(packet, length));
	case targetSelected:
		return std::unique_ptr<LineagePacket>(new TargetSelected(packet, length));
	case targetUnselected:
		return std::unique_ptr<LineagePacket>(new TargetUnselected(packet, length));
	case myTargetSelected:
		return std::unique_ptr<LineagePacket>(new MyTargetSelected(packet, length));
	case skillList:
		return std::unique_ptr<LineagePacket>(new SkillList(packet, length));
	case itemList:
		return std::unique_ptr<LineagePacket>(new ItemList(packet, length));
	case inventoryUpdate:
		return std::unique_ptr<LineagePacket>(new InventoryUpdate(packet, length));
	case shortBuffStatusUpdate:
		return std::unique_ptr<LineagePacket>(new ShortBuffStatusUpdate(packet, length));
		
	default:
		return nullptr;
	}
}
