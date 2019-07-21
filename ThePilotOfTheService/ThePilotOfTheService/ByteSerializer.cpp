#include "ByteSerializer.hpp"
#include <stdexcept>

ByteSerializer::ByteSerializer(const char data[], size_t bytesToSkip, size_t len)
{
	currPtr = data + bytesToSkip;
	currentPos = bytesToSkip;
	maxPos = len;
}

ByteSerializer::ByteSerializer(const RawPacket& data)
	:ByteSerializer(data.rawData.c_str(), 0, data.rawData.size())
{
}

int ByteSerializer::ReadD()
{
	if (currentPos + sizeof(int) > maxPos) throw std::underflow_error("Received packet is too small " __FILE__ " " __FUNCTION__);
	currentPos += sizeof(int);
	int val = *reinterpret_cast<const int*>(currPtr);
	currPtr += sizeof(int);
	return val;
}

char ByteSerializer::ReadC()
{
	if (currentPos + sizeof(char) > maxPos) throw std::underflow_error("Received packet is too small " __FILE__ " " __FUNCTION__);
	currentPos += sizeof(char);
	return *currPtr++;
}

short ByteSerializer::ReadH()
{
	if (currentPos + sizeof(short) > maxPos) throw std::underflow_error("Received packet is too small " __FILE__ " " __FUNCTION__);
	currentPos += sizeof(short);
	short val = *reinterpret_cast<const short*>(currPtr);
	currPtr += sizeof(short);
	return val;
}

const wchar_t * ByteSerializer::ReadS()
{
	const wchar_t* stringStart = reinterpret_cast<const wchar_t*>(currPtr);
	const wchar_t* currentStringPos = stringStart;
	do
	{
		currentPos += sizeof(wchar_t);
		currPtr += sizeof(wchar_t);
	} while (*currentStringPos++);
	if (currentPos > maxPos) throw std::underflow_error("Received packet is too small " __FILE__ " " __FUNCTION__);
	return stringStart;
}
