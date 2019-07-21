#include "ExceptionBasedSniffer.hpp"
#include "VersionInfo.hpp"
#include <windows.h>
#include "PEStuff.hpp"

namespace
{
	void(*packetCallback)(const char packet[], size_t len);
}
#include <stdio.h>
LONG WINAPI ExceptionHandler(PEXCEPTION_POINTERS exception)
{
	//if (exception->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT) printf("O KURCZE address %X code %X byte %02X\n", exception->ExceptionRecord->ExceptionAddress, exception->ExceptionRecord->ExceptionCode, *(BYTE*)(exception->ContextRecord->Eip));
	if (exception->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP && *(BYTE*)(exception->ContextRecord->Eip - 1) == 0xF1 && *(BYTE*)(exception->ContextRecord->Eip) == 0x90)
	{
		//printf("okej2\n");
		//printf(__FUNCTION__ "TAK %X\n", exception->ExceptionRecord->ExceptionAddress);
		packetCallback((const char*)(exception->ContextRecord->Esi + 0x852), *(WORD*)(exception->ContextRecord->Esi + 0x850));
		switch (VersionInfo::getInstance().GetVersion())
		{
		case L2_H5:
			exception->ContextRecord->Eax = *(DWORD*)(exception->ContextRecord->Esp + 0x14);
			break;
		case L2_IL:
			exception->ContextRecord->Eax = 0;
			break;
		}

		exception->ContextRecord->Dr6 = 0;
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	//printf(__FUNCTION__ " unhandled address %X code %X\n", exception->ExceptionRecord->ExceptionAddress, exception->ExceptionRecord->ExceptionCode);
	//printf("Ja tylko umjem HWBPm nie obsluguje %X %X :( Szukam dalej\n", exception->ExceptionRecord->ExceptionCode, exception->ExceptionRecord->ExceptionAddress);
	return EXCEPTION_CONTINUE_SEARCH;
}

#include <stdio.h>

void ExceptionBasedSniffer::SetupNotification(void(*packetRecvCallback)(const char packet[], size_t len))
{
	packetCallback = packetRecvCallback;
	AddVectoredExceptionHandler(2, ExceptionHandler);
	unsigned int engineBase = Utils::LdrGetModuleHandle(L"Engine.dll");
	size_t sizeOfCode = (Utils::GetPEHeader(engineBase))->SizeOfCode;
	const char patternIL[] = "\x33\xC0\x89\x86\xE8\x5B\x00\x00\x89\x86\xEC\x5B\x00\x00\x89\x86\xF0\x5B\x00\x00";
	const char patternH5[] = "\x8B\x44\x24\x14\x8B\x4C\x24\x1C\xC7\x00\x00\x00\x00\x00\xC7\x03\x00\x00\x00\x00\xC7\x01\x00\x00\x00\x00";
	//H5 4 bajty MOV EAX,DWORD PTR SS:[ESP+0x14]
	//8B 44 24 14 8B 4C 24 1C C7 00 00 00 00 00 C7 03 00 00 00 00 C7 01 00 00 00 00
	char* addr;
	DWORD old;
	switch (VersionInfo::getInstance().GetVersion())
	{
	case L2_H5:
		addr = (char*)Utils::FindBytePattern(patternH5, sizeof(patternH5) - 1, (const char*)engineBase, (const char*)engineBase + sizeOfCode);
		VirtualProtect(addr, sizeof(patternH5) - 1, PAGE_EXECUTE_READWRITE, &old);
		*addr++ = '\xF1';
		*addr++ = '\x90';
		*addr++ = '\x90';
		*addr = '\x90';
		break;
	case L2_IL:
		addr = (char*)Utils::FindBytePattern(patternIL, sizeof(patternIL) - 1, (const char*)engineBase, (const char*)engineBase + sizeOfCode);
		VirtualProtect(addr, sizeof(patternIL) - 1, PAGE_EXECUTE_READWRITE, &old);
		*addr++ = '\xF1';
		*addr++ = '\x90';
		break;
	}
}
