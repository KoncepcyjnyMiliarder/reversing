#pragma once
#include "Sniffer.hpp"

class ExceptionBasedSniffer : public Sniffer
{
public:
	virtual void SetupNotification(void(*packetRecvCallback)(const char packet[], size_t len)) override;
};