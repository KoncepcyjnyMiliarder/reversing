#pragma once
#include "RawPacket.hpp"

class ByteSerializer
{
public:
	ByteSerializer(const char data[], size_t bytesToSkip, size_t len);
	ByteSerializer(const RawPacket& data);
	int ReadD();
	char ReadC();
	short ReadH();
	const wchar_t* ReadS();
	void Skip(size_t count) { currPtr += count; }
private:
	const char* currPtr;
	size_t currentPos, maxPos;
};