#pragma once
#include "GameVersion.hpp"
#include "PEStuff.hpp"

class H5Version : public GameVersion
{
public:
	H5Version();
	virtual unsigned int GetEngineEcx() override;
	virtual PacketEnum OpcodeToPacket(unsigned char opcode) override;
	virtual Version GetGameVersion() override;
private:
	unsigned int engineEcxBase;
};