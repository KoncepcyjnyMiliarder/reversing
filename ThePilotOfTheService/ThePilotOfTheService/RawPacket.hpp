#pragma once
#include <string>

class RawPacket
{
public:
	RawPacket(unsigned short packetId, const char* rawData) = delete;
	explicit RawPacket(unsigned short packetId, const std::string&& rawData)
		: packetId(packetId), rawData(std::move(rawData)) {}
	const unsigned short packetId;
	const std::string rawData;
	const std::string toString() const;
	static const unsigned short headerSize = 4;
};