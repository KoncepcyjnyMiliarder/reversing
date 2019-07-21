#pragma once
#include "ByteSerializer.hpp"

class Packet
{
protected:
	virtual ~Packet() = default;
	Packet(const char data[], size_t bytesToSkip, size_t len)
		:serializer(data, bytesToSkip, len) {}
	ByteSerializer serializer;
};