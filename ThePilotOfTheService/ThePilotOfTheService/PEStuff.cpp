#include "PEStuff.hpp"

typedef struct LDR_DATA_ENTRY {
	LIST_ENTRY              InMemoryOrderModuleList;
	DWORD                   BaseAddress;
	PVOID                   EntryPoint;
	ULONG                   SizeOfImage;
	UNICODE_STRING          FullDllName;
	UNICODE_STRING          BaseDllName;
	ULONG                   Flags;
	SHORT                   LoadCount;
	SHORT                   TlsIndex;
	LIST_ENTRY              HashTableEntry;
	ULONG                   TimeDateStamp;
} LDR_DATA_ENTRY, *PLDR_DATA_ENTRY;

struct EKSPORTY
{
	int zsyf[3];
	DWORD offsetDllname;
	DWORD zjedynka;
	DWORD zsyf2; // tu tez jest licznik ale ponad prawdziwa ilosc ; O WAT DA FAK
	DWORD ilsocFunkcji; // to prawdziwe!
	DWORD offsetProcAddresses;
	DWORD offsetProcNames;
	DWORD offsetOrdinals;
};

void* Utils::Hook(void* functionToHook, void* myFunction, size_t size)
{
	DWORD old;
	LPVOID oldInstructions = malloc(5 + size);
	VirtualProtect(oldInstructions, size + 5, PAGE_EXECUTE_READWRITE, &old);
	memcpy(oldInstructions, functionToHook, size);
	*(BYTE*)((DWORD)oldInstructions + size) = 0xE9;
	*(DWORD*)((DWORD)oldInstructions + size + 1) = (DWORD)((DWORD)functionToHook + size) - (DWORD)((DWORD)oldInstructions + size) - 5;
	VirtualProtect(functionToHook, 5, PAGE_EXECUTE_READWRITE, &old);
	*(BYTE*)functionToHook = 0xE9;
	*(DWORD*)((DWORD)functionToHook + 1) = (DWORD)myFunction - (DWORD)functionToHook - 5;
	return oldInstructions;
}

unsigned int Utils::sdbm(const char str[])
{
	unsigned int hash = 0;
	DWORD c;

	while ((c = *str++) != NULL); //assignment within conditional expression T_T
	hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}

EKSPORTY* FindExportTable(DWORD Base)
{
	return (*(DWORD*)((*(DWORD*)(Base + 0x3C)) + Base + 0x78)) == 0 ? 0 : (EKSPORTY*)((*(DWORD*)((*(DWORD*)(Base + 0x3C)) + Base + 0x78)) + Base);
}

WORD NameIndexToOrdinal(DWORD Base, DWORD indeks)
{
	EKSPORTY* eks = FindExportTable(Base);
	WORD* tablicaOrdinal = (WORD*)(eks->offsetOrdinals + Base);
	return tablicaOrdinal[indeks];
}

unsigned int Utils::FindExport(unsigned int Base, const char ProcName[])
{
	EKSPORTY* eks = FindExportTable(Base);
	//return (DWORD)GetProcAddress((HMODULE)Base, ProcName);
	for (DWORD i = 0; i < eks->ilsocFunkcji; i++)
	{
		if (!strcmp((char*)(*(DWORD*)(eks->offsetProcNames + Base + 4 * i)) + Base, ProcName))
		{
			DWORD* tablicaFunkcji = (DWORD*)(eks->offsetProcAddresses + Base);
			return tablicaFunkcji[NameIndexToOrdinal(Base, i)] + Base;
		}
	}
	return 0;
}

PLDR_DATA_ENTRY firstLdrDataEntry()
{
	PLDR_DATA_ENTRY result;
	__asm
	{
		mov eax, fs:[0x30]  // PEB
		mov eax, [eax + 0x0C] // PEB_LDR_DATA
		mov eax, [eax + 0x1C] // InInitializationOrderModuleList
		mov[result], eax
	}
	
}

unsigned int Utils::LdrGetModuleHandle(const wchar_t ModuleName[])
{
	PLDR_DATA_ENTRY cursor = firstLdrDataEntry();
	while (cursor->BaseAddress)
	{
		if (!_wcsicmp(ModuleName, cursor->BaseDllName.Buffer))
		{
			return (DWORD)cursor->BaseAddress;
		}
		cursor = (PLDR_DATA_ENTRY)cursor->InMemoryOrderModuleList.Flink;
	}

	return 0;
}

unsigned int Utils::GetCurrentThreadId()
{
	return *(unsigned int*)(__readfsdword(0x18) + 0x24);
}

bool PatternMatches(const char pattern[], const char* sample, int size, BYTE ignoredDigit)
{
	for (int i = 0; i < size; i++)
	{
		if (pattern[i] != ignoredDigit && pattern[i] != sample[i]) return false;
	}
	return true;
}

bool PatternMatches(const char pattern[], const char* sample, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (pattern[i] != sample[i]) return false;
	}
	return true;
}

PIMAGE_OPTIONAL_HEADER Utils::GetPEHeader(unsigned int moduleBase)
{
	return (PIMAGE_OPTIONAL_HEADER)(moduleBase + *(DWORD*)(moduleBase + 0x3C) + 0x18);
}

void* Utils::FindBytePattern(const char pattern[], size_t patternLength, const char* start, const char* end)
{
	for (const char* i = start; i < end; i++)
	{
		if (PatternMatches(pattern, i, patternLength)) return (LPVOID)i;
	}
	return 0;
}

LPVOID Utils::FindBytePattern(const char pattern[], size_t patternLength, const char* start, const char* end, char ignoredDigit)
{
	for (const char* i = start; i < end; i++)
	{
		if (PatternMatches(pattern, i, patternLength, ignoredDigit)) return (LPVOID)i;
	}
	return 0;
}

unsigned int Utils::resolveJump(unsigned int E9addr)
{
	return E9addr + *(unsigned int*)(E9addr + 1) + 5;
}
