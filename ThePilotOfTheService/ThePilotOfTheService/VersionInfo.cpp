#include "VersionInfo.hpp"
#include "InterludeVersion.hpp"
#include "H5Version.hpp"
#include <stdio.h>

VersionInfo& VersionInfo::getInstance()
{
	static VersionInfo instance;
	return instance;
}

unsigned int VersionInfo::GetEngineEcx()
{
	return ver->GetEngineEcx();
}

PacketEnum VersionInfo::OpcodeToPacket(char opcode)
{
	return ver->OpcodeToPacket(opcode);
}

Version VersionInfo::GetVersion()
{
	return ver->GetGameVersion();
}

VersionInfo::VersionInfo()
{
	unsigned int addr = Utils::FindExport(Utils::LdrGetModuleHandle(L"Core.dll"), "?PushBack@L2ParamStack@@QAEHPAX@Z");
	////printf("adres pushbacka to %X\n", addr);
	if (addr) ver = new InterludeVersion;
	else ver = new H5Version;
}