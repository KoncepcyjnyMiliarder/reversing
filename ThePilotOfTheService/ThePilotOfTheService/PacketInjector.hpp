#pragma once
#include "Injector.hpp"

class PacketInjector : public Injector
{
public:
	virtual void Action(unsigned int objectId, int origX, int origY, int origZ, bool shift) override;
	virtual void MagicSkillUse(int skillID, bool shift, bool ctrl) override;
	virtual void Say2(wchar_t* text, int channel, wchar_t* targetNamePM = nullptr) override;
private:
	PacketInjector(); // deprecated
	void(__cdecl* DataSend)(int q, const char* format, ...);
	int firstParam;
};