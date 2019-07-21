#pragma once
#include "GameVersion.hpp"

class InterludeVersion : public GameVersion
{
public:
	InterludeVersion();
	virtual unsigned int GetEngineEcx() override;
	virtual PacketEnum OpcodeToPacket(unsigned char opcode) override;
	virtual Version GetGameVersion() override;
private:
	unsigned int engineEcxBase;
};