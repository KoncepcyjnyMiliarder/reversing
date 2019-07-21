#include <windows.h>
#include <stdio.h>

//proof of concept simple fishbot for Lineage2 Interlude version

class L2ParamStack
{
    char unk[0x14];

  public:
    void* Top();
    L2ParamStack(int);
    ~L2ParamStack(void);
    int PushBack(void*);
};

int engineBase = (int)LoadLibraryA("Engine.dll");

namespace native
{

int get_my_id()
{
  return *(int*)(engineBase + 0x81F530);
}

class u_network_handler
{
    char unk[100];

  public:

    u_network_handler() = delete;
    u_network_handler(const u_network_handler&) = delete;
    u_network_handler(u_network_handler&&) = delete;
    u_network_handler& operator =(const u_network_handler&) = delete;
    u_network_handler& operator =(u_network_handler&&) = delete;

    static u_network_handler* native_instance()
    {
      return (u_network_handler*) * (int*)((*(int*)(engineBase + 0x951044)) + 0x60);
    }

    void use_skill(int skillID, bool shift = false, bool ctrl = false)
    {
      static auto nativeCall = (void(__thiscall*)(u_network_handler&, L2ParamStack&))(engineBase + 0x6C1C);
      L2ParamStack params(10);
      params.PushBack((void*)skillID);
      params.PushBack((void*)shift);
      params.PushBack((void*)ctrl);
      nativeCall(*this, params);
    }
};
}

//10300000
//standard packets MOV EAX,DWORD PTR DS:[ECX+0x10A57310]
//extended packets MOV EAX,DWORD PTR DS:[ECX+0x10A67610]
struct networkTableEntry
{
  int(__cdecl* handler)(void* unk, char packet[]);
  const wchar_t packetName[128];
};
static_assert(sizeof(networkTableEntry) == 0x104, "INTERLUDE networkTableEntry has to be 0x104 in size!");

bool fishing = false;

enum fishingState
{
  inactive,
  bait_set,
  fight,
};

fishingState currentFishingState = inactive;
bool shouldReel;

//FE13=ExFishingStart:h(subID)d(charObjID)d(fishType)d(X)d(Y)d(Z)c(isNightLure)c(c)
int(__cdecl* realFishingStart)(void* unk, char packet[]);
int __cdecl myFishingStart(void* unk, char packet[])
{
  struct FishingStart
  {
    int objid;
    int fishtype;
    int x, y, z;
  };

  FishingStart* data = (FishingStart*)packet;
  if (data->objid == native::get_my_id())
  {
    currentFishingState = bait_set;
    printf("Fishing start obj %X finshtype %d xyz %d %d %d\n", data->objid, data->fishtype, data->x, data->y, data->z);
  }
  return realFishingStart(unk, packet);
}

//FE14=ExFishingEnd:h(subID)d(charObjectId)c(isWin)
int(__cdecl* realFishingEnd)(void* unk, char packet[]);
int __cdecl myFishingEnd(void* unk, char packet[])
{
  struct FishingEnd
  {
    int charid;
    bool iswin;
  };

  FishingEnd* data = (FishingEnd*)packet;
  if (data->charid == native::get_my_id())
  {
    currentFishingState = inactive;
    //printf("Fishing end %X win? %d\n", data->charid, data->iswin);
  }
  return realFishingEnd(unk, packet);
}

//FE15=ExFishingStartCombat:h(subID)d(charObjID)d(time)d(HP)c(Fighting)c(LureType)c(isFishDeceptive)
int(__cdecl* realFishingStartCombat)(void* unk, char packet[]);
int __cdecl myFishingStartCombat(void* unk, char packet[])
{
  struct FishingCombat
  {
    int objid;
    int time;
    int hp;
    char mode;
    char luretype;
    char deceptivemode;
  };

  FishingCombat* data = (FishingCombat*)packet;
  if (data->objid == native::get_my_id())
  {
    currentFishingState = fight;
    shouldReel = data->mode ? true : false;
    //printf("Fishing combat %X time %d mode %d\n", data->objid, data->time, data->mode);
  }
  return realFishingStartCombat(unk, packet);
}

//FE16=ExFishingHpRegen:h(subID)d(charObjID)d(time)d(fish_HP)c(HPstop/rise)c(GoodUse)c(anim)d(penalty)c(BarColor)
int(__cdecl* realFishingHPRegen)(void* unk, char packet[]);
int __cdecl myFishingHPRegen(void* unk, char packet[])
{
  struct FishingHpRegen
  {
    int objid;
    int time;
    int fishhp;
    char isHpRaising;
  };

  FishingHpRegen* data = (FishingHpRegen*)packet;
  if (data->objid == native::get_my_id())
  {
    currentFishingState = fight;
    shouldReel = data->isHpRaising ? true : false;
    //printf("Fishing regen %X time %d stopraise %d hp %d\n", data->objid, data->time, data->isHpRaising, data->fishhp);
  }
  return realFishingHPRegen(unk, packet);
}

void controller()
{
  while (1)
  {
    Sleep(55);
    auto KeyPressed = [](int key)->bool
    {
      if (!(GetAsyncKeyState(key) & 0x8000)) return false;
      DWORD pid;
      GetWindowThreadProcessId(GetForegroundWindow(), &pid);
      return pid == GetCurrentProcessId();
    };

    if (KeyPressed(VK_END))
    {
      fishing = !fishing;
      printf(fishing ? "fishing RUNNING\n" : "fishing PAUSED\n");
      Sleep(500);
    }

  }
}

void implant()
{
  static auto timer = GetTickCount();
  if (fishing)
  {
    if (timer + 888 < GetTickCount())
    {
      timer = GetTickCount();
      //printf("FISHING TICK\n");
      /*
      1312    Fishing
      1313   Pumping
      1314   Reeling
      */
      switch (currentFishingState)
      {
        case inactive:
          native::u_network_handler::native_instance()->use_skill(1312);
          break;
        case bait_set:
          break;
        case fight:
          native::u_network_handler::native_instance()->use_skill(shouldReel ? 1314 : 1313);
          break;
      }
    }
  }

}

__declspec(naked) void trampolinka()
{
  __asm
  {
    XOR EBX, EBX
    MOV DWORD PTR SS : [EBP - 0x4], EBX
    PUSHAD
    CALL implant
    POPAD
    RET
  }
}

template<typename Func>
void hookHandler(unsigned index, Func realFunc, Func myFunc, networkTableEntry* packet_table)
{
  realFunc = packet_table[index].handler;
  packet_table[index].handler = myFunc;
}

DWORD WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID q)
{
  switch (reason)
  {
    case DLL_PROCESS_ATTACH:
      AllocConsole();
      freopen("CONOUT$", "w", stdout);
      printf("Hello Kappa\n");
      //tu call 2D544B
      DWORD old, old2;
      VirtualProtect((void*)(engineBase + 0x2D544B), 5, PAGE_EXECUTE_READWRITE, &old);
      *(char*)(engineBase + 0x2D544B) = '\xE8';
      *(int*)(engineBase + 0x2D544B + 1) = (int)trampolinka - (engineBase + 0x2D544B) - 5;
      VirtualProtect((void*)(engineBase + 0x2D544B), 5, old, &old2);
      networkTableEntry* standardPackets = (networkTableEntry*)(engineBase + 0x757310);
      networkTableEntry* exPackets = (networkTableEntry*)(engineBase + 0x767610);

      hookHandler(0x13, realFishingStart, myFishingStart, exPackets);
      hookHandler(0x14, realFishingEnd, myFishingEnd, exPackets);
      hookHandler(0x15, realFishingStartCombat, myFishingStartCombat, exPackets);
      hookHandler(0x16, realFishingHPRegen, myFishingHPRegen, exPackets);

      CreateThread(0, 0, (LPTHREAD_START_ROUTINE)controller, 0, 0, 0);
      break;
  }
  return 1;
}