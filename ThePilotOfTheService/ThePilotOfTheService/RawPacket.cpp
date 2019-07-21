#include "RawPacket.hpp"

const std::string RawPacket::toString() const
{
	char header[4];
	*(unsigned short*)header = (unsigned short)rawData.size() + headerSize;
	*(unsigned short*)(header + 2) = packetId;
	std::string result(header, headerSize);
	result.append(rawData);
	return result;
}
