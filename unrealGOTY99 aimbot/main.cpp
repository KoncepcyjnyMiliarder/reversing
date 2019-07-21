#include<Windows.h>
#include<stdio.h>
#include<vector>

LPVOID HookE8E9(LPVOID Adres, LPVOID MojaFunkcja)
{
    DWORD q;
    DWORD prawdziwaFunkcja = (DWORD)Adres + *(DWORD*)((DWORD)Adres + 1) + 5;
    if (VirtualProtect(Adres, 5, PAGE_EXECUTE_READWRITE, &q))
    {
        *(DWORD*)((DWORD)Adres + 1) = (DWORD)MojaFunkcja - (DWORD)Adres - 5;
    }
    else return NULL;
    return (LPVOID)prawdziwaFunkcja;
}

struct punkt
{
    float x;
    float y;
    float z;
};

punkt operator-(punkt& a, punkt& b)
{
    return punkt{ a.x - b.x,a.y - b.y,a.z - b.z };
}

float Wyznacznik(const punkt& a, const punkt& b)
{
    return a.x*b.y - a.y*b.x;
}

float Skalarny(const punkt& a, const punkt& b)
{
    return a.x*b.x + a.y*b.y;
}

float Dlugosc2D(const punkt& a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}

float Dlugosc3D(const punkt& a)
{
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

float KatDoAimbotaX(const punkt& ZZV, const char Direction, const punkt& gracz, const punkt& przeciwnik)
{
    float obrot;
    punkt wektor;
    wektor.x = przeciwnik.x - gracz.x;
    wektor.y = przeciwnik.y - gracz.y;
    obrot = (acos(Skalarny(ZZV, wektor) / Dlugosc2D(wektor)) / 3.141592f)*180.0f;
    if (Wyznacznik(ZZV, wektor) < 0) obrot = 360.0f - obrot;
    if (Direction == -1) obrot = 360.0f - obrot;
    return obrot;
}

float KatDoAimbotaY(const punkt& gracz, const punkt& przeciwnik)
{
    float obrot;
    punkt wektor;
    wektor.x = przeciwnik.x - gracz.x;
    wektor.y = przeciwnik.y - gracz.y;
    wektor.z = przeciwnik.z - gracz.z;
    obrot = (asin((przeciwnik.z - gracz.z) / Dlugosc3D(wektor)) / 3.141592f)*180.0f;
    return obrot;
}

#pragma pack (push)
#pragma pack (1)

struct PawnData
{
    BYTE unk[0x234];
    DWORD team;
};

struct APawn
{
    void* vftable;
    BYTE unk1[0xCC];
    punkt xyz; //+0xD0
    //+0xDC
    BYTE unk2[0x158];
    DWORD unkPOMYLKAxDD; //0x234
    BYTE unk3[0x34];
    float movSpeed;//0x26c
    BYTE unk4[0xC];
    float jumpHeight; //+0x27c
    BYTE unk5[0x54];
    int targetY; //+0x2d4
    int targetX; //+0x2d8
    BYTE unk6[0x40];
    int hp; //+0x31C
    BYTE unk7[0x12C];
    PawnData* pawndata; //+0x44C
};

struct APlayerPawn
{
    void* vftable;
    BYTE unk1[0xCC];
    punkt xyz; //+0xD0
    //+0xDC
    BYTE unk2[0x158];
    DWORD unkPOMYLKAxDD; //0x234
    BYTE unk3[0x34];
    float movSpeed;//0x26c
    BYTE unk4[0xC];
    float jumpHeight; //+0x27c
    BYTE unk5[0x50];
    int targetY; //+0x2d0
    int targetX; //+0x2d4
    BYTE unk6[0x44];
    int hp; //+0x31C
    BYTE unk7[0x12C];
    PawnData* pawndata; //+0x44C
};

struct Name
{
    DWORD id;
    DWORD flags;
    DWORD unk;
    wchar_t text[1];
};

struct NamesArray
{
    Name** names;
    DWORD maxNames;
};

NamesArray* strings = (NamesArray*)GetProcAddress(GetModuleHandleA("Core.dll"), "?Names@FName@@0V?$TArray@PAUFNameEntry@@@@A");

#pragma pack(pop)
namespace
{
    std::vector<APawn*> pawns;
    APlayerPawn* player = nullptr;
}

APawn*(__fastcall* realAPawnConstructor)(APawn* This);
APawn*(__fastcall* realAPawnCopyConstructor)(APawn* This, void* dummyEdx, APawn* toCopy);
APawn*(__fastcall* realAPawnDestructor)(APawn* This);

APawn*__fastcall myAPawnConstructor(APawn* This)
{
    printf(__FUNCTION__ " called! This: %X\n", This);
    pawns.push_back(This);
    return realAPawnConstructor(This);
}

APawn*__fastcall myAPawnCopyConstructor(APawn* This, void* dummyEdx, APawn* toCopy)
{
    printf(__FUNCTION__ " called! This: %X\n", This);
    pawns.push_back(This);
    return realAPawnCopyConstructor(This, dummyEdx, toCopy);
}

APawn*__fastcall myAPawnDestructor(APawn* This)
{
    printf(__FUNCTION__ " called! This: %X\n", This);
    auto position = std::find(pawns.begin(), pawns.end(), This);
    if (position != pawns.end()) pawns.erase(position);
    return realAPawnDestructor(This);
}

APlayerPawn*(__fastcall* realAPlayerPawnConstructor)(APlayerPawn* This);
APlayerPawn*(__fastcall* realAPlayerPawnDestructor)(APlayerPawn* This);

APlayerPawn*__fastcall myAPlayerPawnConstructor(APlayerPawn* This)
{
    printf(__FUNCTION__ " called! This: %X\n", This);
    player = This;
    return realAPlayerPawnConstructor(This);
}

APlayerPawn*__fastcall myAPlayerPawnDestructor(APlayerPawn* This)
{
    printf(__FUNCTION__ " called! This: %X\n", This);
    player = nullptr;
    return realAPlayerPawnDestructor(This);
}

bool(__fastcall* LineOfSightTo)(APlayerPawn* player, void* dummyEdx, APawn* toActor, bool choleraGoWie) = (bool(__fastcall*)(APlayerPawn*, void*, APawn*, bool))GetProcAddress(GetModuleHandleA("Engine.dll"), "?LineOfSightTo@APawn@@QAEKPAVAActor@@H@Z");

//public: unsigned long __thiscall APawn::LineOfSightTo(class AActor *,int)
//"?LineOfSightTo@APawn@@QAEKPAVAActor@@H@Z"
void QQThread()
{
    realAPawnConstructor = (APawn*(__fastcall*)(APawn*))HookE8E9(GetProcAddress(GetModuleHandleA("Engine.dll"), "??0APawn@@QAE@XZ"), myAPawnConstructor);
    realAPawnCopyConstructor = (APawn*(__fastcall*)(APawn*, void*, APawn*))HookE8E9(GetProcAddress(GetModuleHandleA("Engine.dll"), "??0APawn@@QAE@ABV0@@Z"), myAPawnCopyConstructor);
    realAPawnDestructor = (APawn*(__fastcall*)(APawn*))HookE8E9(GetProcAddress(GetModuleHandleA("Engine.dll"), "??1APawn@@UAE@XZ"), myAPawnDestructor);
    realAPlayerPawnConstructor = (APlayerPawn*(__fastcall*)(APlayerPawn*))HookE8E9(GetProcAddress(GetModuleHandleA("Engine.dll"), "??0APlayerPawn@@QAE@XZ"), myAPlayerPawnConstructor);
    realAPlayerPawnDestructor = (APlayerPawn*(__fastcall*)(APlayerPawn*))HookE8E9(GetProcAddress(GetModuleHandleA("Engine.dll"), "??1APlayerPawn@@UAE@XZ"), myAPlayerPawnDestructor);

    for (;;)
    {
		
        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            printf("---------------------------PAWNS\n");
            for (size_t i = 0; i < pawns.size(); ++i)
            {
                printf("Pawn %X team %d ( %f , %f , %f ) HP: %u\n", pawns[i], pawns[i]->pawndata->team, pawns[i]->xyz.x, pawns[i]->xyz.y, pawns[i]->xyz.z, pawns[i]->hp);
            }
            printf("--------------------------------\n\n");
        }

        if (GetAsyncKeyState(VK_END) & 1)
        {
            if (!player)
            {
                printf("nullptr ; O\n");
                continue;
            }
            printf("PlayerPawn %X team %d ( %f , %f , %f ) HP: %u\nTarget %d %d\n", player, player->pawndata->team, player->xyz.x, player->xyz.y, player->xyz.z, player->hp, player->targetY, player->targetX);
        }

        if (GetAsyncKeyState(VK_RBUTTON))
        {
            APawn* closest = nullptr;
            float minDistSquare = 0;
            for (size_t i = 0; i < pawns.size(); ++i)
            {
                if (pawns[i]->pawndata != nullptr && pawns[i]->pawndata->team != player->pawndata->team && pawns[i]->hp > 0 && LineOfSightTo(player, 0, pawns[i], 0))
                {
                    float dist = Dlugosc3D(player->xyz - pawns[i]->xyz);
                    if (closest == nullptr)
                    {
                        minDistSquare = dist;
                        closest = pawns[i];
                        continue;
                    }

                    if (dist < minDistSquare)
                    {
                        minDistSquare = dist;
                        closest = pawns[i];
                    }

                }

            }
            if (closest != nullptr)
            {
                //stary kod, TO SMIERDZI BONKIEM NA KJILOMETER!! refaktor nided veri badli

                player->targetX = (DWORD)((KatDoAimbotaX({ 1,0,0 }, 1, player->xyz, closest->xyz) / 360.0f)*65535.0f);
                player->targetY = (DWORD)((KatDoAimbotaY(player->xyz, closest->xyz) / 360.0f)*65535.0f);

            }
            //else printf("No attackable!\n");
        }

        if (GetAsyncKeyState(VK_NUMPAD0) & 1)
        {
            for (size_t i = 0; i < strings->maxNames; i++)
            {
				if (strings->names[i] && wcsstr(strings->names[i]->text, L"QQCHAMP")) printf("%d %ws\n", strings->names[i]->id, strings->names[i]->text);
            }
        }



    }
}

//??1APawn@@UAE@XZ destr
//??0APawn@@QAE@XZ def constr
//??0APawn@@QAE@ABV0@@Z copy constr

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID q)
{
    UNREFERENCED_PARAMETER(q);
    UNREFERENCED_PARAMETER(hInst);
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        AllocConsole();
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        //wazne zmienne
        /*ZZVector.x = 1;
        ZZVector.y = 0;
        Dir = 1;*/
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)QQThread, 0, 0, 0);
        break;
    }
    return 1;
}