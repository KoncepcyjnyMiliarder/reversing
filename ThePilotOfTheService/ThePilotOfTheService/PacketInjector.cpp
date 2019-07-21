#include "PacketInjector.hpp"

void PacketInjector::Action(unsigned int objectId, int origX, int origY, int origZ, bool shift)
{
	DataSend(firstParam, "cddddc", 0x4, objectId, origX, origY, origZ, shift);
}

void PacketInjector::MagicSkillUse(int skillID, bool shift, bool ctrl)
{
	DataSend(firstParam, "cddc", 0x2F, skillID, shift, ctrl);
}

void PacketInjector::Say2(wchar_t * text, int channel, wchar_t * targetNamePM)
{
	targetNamePM ? DataSend(firstParam, "cSdS", 0x38, text, channel, targetNamePM) : DataSend(firstParam, "cSd", 0x38, text, channel);
}
