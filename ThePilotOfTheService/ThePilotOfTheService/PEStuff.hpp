#pragma once
#include "ntdll.h"

namespace Utils
{
	void* Hook(void* functionToHook, void* myFunction, size_t size);
	unsigned int sdbm(const char str[]);
	unsigned int FindExport(unsigned int base, const char procName[]);
	unsigned int LdrGetModuleHandle(const wchar_t moduleName[]);
	unsigned int GetCurrentThreadId();
	//PIMAGE_OPTIONAL_HEADER GetPEHeader(DWORD moduleBase);
	//void Hookshark();
	//LPVOID SafeCall(LPVOID Funkcja, DWORD dlugosc);
	//LPVOID SafeCallCustomBytes(LPVOID Funkcja, BYTE* in, int bufsize);
	//void SetHWBPs(DWORD a, DWORD b = 0, DWORD c = 0, DWORD d = 0);
	PIMAGE_OPTIONAL_HEADER GetPEHeader(unsigned int moduleBase);
	void* FindBytePattern(const char pattern[], size_t patternLength, const char* start, const char* end);
	void* FindBytePattern(const char pattern[], size_t patternLength, const char* start, const char* end, char ignoredDigit);
	unsigned int resolveJump(unsigned int E9addr);
}
