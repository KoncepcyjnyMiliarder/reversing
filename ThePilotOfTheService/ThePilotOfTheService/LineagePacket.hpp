#pragma once
#include "Packet.hpp"

class LineagePacket : public Packet
{
public:
	LineagePacket(const char data[], size_t bytesToSkip, size_t len)
		:Packet(data, bytesToSkip, len) {}
	virtual void HandlePacket() = 0;
	virtual ~LineagePacket() = default;
};