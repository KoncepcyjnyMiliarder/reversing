#include "H5Version.hpp"

H5Version::H5Version()
{
	engineEcxBase = Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?GGlobalTempObjects@@3PAVUGlobalTempObjects@@A") - 0x7C;
}

unsigned int H5Version::GetEngineEcx()
{
	return *(unsigned int*)engineEcxBase;
}

PacketEnum H5Version::OpcodeToPacket(unsigned char opcode)
{
	switch (opcode)
	{
	case 0xFA:
		return shortBuffStatusUpdate;
	case 0xB9:
		return myTargetSelected;
	case 0x5F:
		return skillList;
	case 0x2F:
		return moveToLocation;
	case 0x31:
		return charInfo;
	case 0x32:
		return userInfo;
	case 0x0:
		return die;
	case 0x18:
		return statusUpdate;
	case 0x8:
		return deleteObject;
	case 0xC:
		return npcInfo;
	case 0x23:
		return targetSelected;
	case 0x24:
		return targetUnselected;
	case 0x0B:
		return charSelected;
	case 0x11:
		return itemList;
	case 0x21:
		return inventoryUpdate;
	}
	return error;
}

Version H5Version::GetGameVersion()
{
	return L2_H5;
}
