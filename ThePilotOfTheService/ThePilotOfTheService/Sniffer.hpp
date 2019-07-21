#pragma once

class Sniffer
{
public:
	virtual void SetupNotification(void(*packetRecvCallback)(const char packet[], size_t len)) = 0;
	virtual ~Sniffer() = default;
};