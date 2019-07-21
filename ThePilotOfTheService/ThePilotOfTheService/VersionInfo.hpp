#pragma once
#include "GameVersion.hpp"

class VersionInfo
{
public:
	static VersionInfo& getInstance();
	unsigned int GetEngineEcx();
	PacketEnum OpcodeToPacket(char opcode);
	Version GetVersion();
private:
	VersionInfo();
	GameVersion* ver;
};