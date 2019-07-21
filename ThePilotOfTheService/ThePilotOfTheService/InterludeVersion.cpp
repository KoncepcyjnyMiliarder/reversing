#include "InterludeVersion.hpp"

InterludeVersion::InterludeVersion()
{
	engineEcxBase = Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?GL2Console@@3PAVUL2ConsoleWnd@@A") - 8;
}

unsigned int InterludeVersion::GetEngineEcx()
{
	unsigned int engineEcx = *(unsigned int*)engineEcxBase;
	engineEcx = *(unsigned int*)(engineEcx + 0x60);
	return engineEcx;
}

PacketEnum InterludeVersion::OpcodeToPacket(unsigned char opcode)
{
	return static_cast<PacketEnum>(opcode);
}

Version InterludeVersion::GetGameVersion()
{
	return L2_IL;
}
