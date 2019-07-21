#pragma once
#include "LineagePacket.hpp"
#include <memory>

class LineagePacketFactory
{
public:
	std::unique_ptr<LineagePacket> Construct(const char packet[], size_t length);
};