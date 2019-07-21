#include <Windows.h>
#include "VersionInfo.hpp"
#include "ExceptionBasedSniffer.hpp"
#include "FunctionCaller.hpp"
#include <memory>
#include <stdexcept>
#include "LineagePacketFactory.hpp"
#include "BotBrain.hpp"
#include "Maths.hpp"
#include "GUI.hpp"

//#define WIELKIE_QQ(text) MessageBoxA(0, text, "qq", 0);
#define WIELKIE_QQ(text) (text);//printf(text "\n");
/*
85=MagicEffectIcons:h(ListCount:Loop.01.0003)d(skillID:Get.Skill)h(SkillLevel)d(Duration)


85 29 00 8B 5A 00 00 01 00 86 0A 00 00 75 05 00 00 03 00 1D 18 00 00 9E
04 00 00 03 00 1D 18 00 00 A5 04 00 00 03 00 1D 18 00 00 A7 04 00 00 03
00 1D 18 00 00 70 05 00 00 03 00 1D 18 00 00 71 05 00 00 03 00 1D 18 00
00 48 05 00 00 01 00 1D 18 00 00 49 05 00 00 01 00 1D 18 00 00 4A 05 00
00 01 00 1D 18 00 00 EB 04 00 00 04 00 1D 18 00 00 0B 04 00 00 04 00 1D
18 00 00 36 04 00 00 06 00 1D 18 00 00 B5 05 00 00 01 00 1D 18 00 00 17
05 00 00 02 00 1D 18 00 00 3E 03 00 00 01 00 1D 18 00 00 6D 05 00 00 03
00 1D 18 00 00 26 04 00 00 02 00 1D 18 00 00 5F 12 00 00 0D 00 1D 18 00
00 3D 04 00 00 03 00 1D 18 00 00 DD 05 00 00 01 00 1D 18 00 00 DC 05 00
00 01 00 1D 18 00 00 DB 05 00 00 01 00 1D 18 00 00 E0 05 00 00 01 00 1D
18 00 00 85 05 00 00 01 00 1D 18 00 00 06 06 00 00 01 00 1D 18 00 00 07
05 00 00 01 00 4A 02 00 00 B1 05 00 00 01 00 AF 04 00 00 6B 01 00 00 01
00 1D 18 00 00 34 01 00 00 01 00 1D 18 00 00 12 02 00 00 01 00 1D 18 00
00 11 02 00 00 01 00 1D 18 00 00 5D 01 00 00 01 00 1D 18 00 00 0C 01 00
00 01 00 1D 18 00 00 0B 01 00 00 01 00 1D 18 00 00 30 01 00 00 01 00 1D
18 00 00 08 01 00 00 01 00 1D 18 00 00 6D 01 00 00 01 00 1D 18 00 00 11
01 00 00 01 00 1D 18 00 00 14 01 00 00 01 00 1D 18 00 00 93 03 00 00 01
00 1D 18 00 00 00 00

F4=PartySpelled:d(isSummon)d(ObjecID)d(EffectSize:Loop.01.0003)d(skillID:Get.Skill)h(SkillLevel)d(Duration)

F4 00 00 00 00 AA AA 29 10 29 00 00 00 8B 5A 00 00 01 00 40 0A 00 00 75
05 00 00 03 00 D7 17 00 00 9E 04 00 00 03 00 D7 17 00 00 A5 04 00 00 03
00 D7 17 00 00 A7 04 00 00 03 00 D7 17 00 00 70 05 00 00 03 00 D7 17 00
00 71 05 00 00 03 00 D7 17 00 00 48 05 00 00 01 00 D7 17 00 00 49 05 00
00 01 00 D7 17 00 00 4A 05 00 00 01 00 D7 17 00 00 EB 04 00 00 04 00 D7
17 00 00 0B 04 00 00 04 00 D7 17 00 00 36 04 00 00 06 00 D7 17 00 00 B5
05 00 00 01 00 D7 17 00 00 17 05 00 00 02 00 D7 17 00 00 3E 03 00 00 01
00 D7 17 00 00 6D 05 00 00 03 00 D7 17 00 00 26 04 00 00 02 00 D7 17 00
00 5F 12 00 00 0D 00 D7 17 00 00 3D 04 00 00 03 00 D7 17 00 00 DD 05 00
00 01 00 D7 17 00 00 DC 05 00 00 01 00 D7 17 00 00 DB 05 00 00 01 00 D7
17 00 00 E0 05 00 00 01 00 D7 17 00 00 85 05 00 00 01 00 D7 17 00 00 06
06 00 00 01 00 D8 17 00 00 07 05 00 00 01 00 53 02 00 00 B1 05 00 00 01
00 AF 04 00 00 6B 01 00 00 01 00 D8 17 00 00 34 01 00 00 01 00 D8 17 00
00 12 02 00 00 01 00 D8 17 00 00 11 02 00 00 01 00 D8 17 00 00 5D 01 00
00 01 00 D8 17 00 00 0C 01 00 00 01 00 D8 17 00 00 0B 01 00 00 01 00 D8
17 00 00 30 01 00 00 01 00 D8 17 00 00 08 01 00 00 01 00 D8 17 00 00 6D
01 00 00 01 00 D8 17 00 00 11 01 00 00 01 00 D8 17 00 00 14 01 00 00 01
00 D8 17 00 00 93 03 00 00 01 00 D8 17 00 00 00 00

*/
//to wszystko trzeba opakowac w klasy - im fuckin dead right now

void UstawiaczBota(HINSTANCE hInst)
{
  auto KeyPressed = [](int key)->bool
  {
    if (!(GetAsyncKeyState(key) & 0x8000) || !(GetAsyncKeyState(VK_CONTROL) & 0x8000)) return false;
    DWORD pid;
    GetWindowThreadProcessId(GetForegroundWindow(), &pid);
    return pid == GetCurrentProcessId();
  };

  while (1)
  {
    if (KeyPressed(VK_F1))
      BlockingGUI().Spawn(hInst);
    Sleep(156);
  }
}

void Bot()
{
  static Injector* injector = new FunctionCaller; // memory leak 4Head
  static unsigned int pause = GetTickCount();
  BotBrain& brain = BotBrain::GetInstance();
  World& world = brain.GetWorld();
  if (pause > GetTickCount()) return;
  if (!world.IsIngame() || !brain.botactive)
  {
    //MessageBoxA(0, "7", "asd", 0);
    //printf("[%02d:%02d:%02d]\tNie w grze albo pauza\n", pause / 3600000, (pause / 60000) % 60, (pause / 1000) % 60);
    pause = GetTickCount() + 1000;
    //MessageBoxA(0, "8", "asd", 0);
    return;
  }
  auto& player = world.GetPlayer();
  auto& npcs = world.GetNpcs();
  static unsigned int targwtPause = GetTickCount();
  static unsigned int enchantPause = GetTickCount();

  if (brain.to_enchant.size() && enchantPause < GetTickCount())
  {
    enchantPause = GetTickCount() + 123;
    injector->UseItem(brain.enchant_id, 0);
    injector->EnchantItem(brain.to_enchant.back(), brain.enchant_id);
    //visual bug in l2. says item goes from 0 to +++ but in fact every item foes +1+1+1+1
    //MessageBoxA(0, std::to_string(brain.to_enchant.back()).c_str(), "enchant status", 0);
    brain.to_enchant.pop_back();
  }

  if (brain.autotarget && targwtPause < GetTickCount())
  {
    targwtPause = GetTickCount() + 564;
    bool target = false;
    if (world.currentTargetId != 0)
    {
      //MessageBoxA(0, "you arlready have target", "1", 0);
      if (npcs.count(world.currentTargetId) == 1 && npcs.at(world.currentTargetId).isAlive)
      {
        //MessageBoxA(0, "and target is alive", "1", 0);
      }
      else
      {
        //MessageBoxA(0, "and target is DEAD", "1", 0);
        target = true;
      }
    }
    else
    {
      //MessageBoxA(0, "you do not have target", "1", 0);
      target = true;
    }

    if (target)
    {
      //MessageBoxA(0, "tryin to target!!", "2", 0);
      unsigned int closestNpc = 0;
      int maxDistance = 13371337;
      for (auto& it : npcs)
      {
        auto& npc = it.second;
        if (!npc.isAttackable || !npc.isAlive) continue;
        if (!brain.polygon.isInsideBox(npc.x, npc.y, Maths::abs(player.z - npc.z))) continue;
        int distSquare = (player.x - npc.x) * (player.x - npc.x) + (player.y - npc.y) * (player.y - npc.y);
        if (distSquare < maxDistance)
        {
          maxDistance = distSquare;
          closestNpc = it.first;
        }
      }
      if (closestNpc)
      {
        //MessageBoxA(0, "tryin to target", "3", 0);
        ////printf("Targetuje najblizszego %X czy zywy? %d!\n", closestNpc, npcs.at(closestNpc).isAlive);
        injector->Action(closestNpc, player.x, player.y, player.z, 0);
      }
      else
      {
        ////printf("Nikogo w okolicy!\n");
      }
    }
  }

  static unsigned int actionPause = GetTickCount();

  if (brain.autoattack && actionPause < GetTickCount())
  {
    actionPause = GetTickCount() + 456;
    if (world.currentTargetId != 0)
    {
      if (npcs.count(world.currentTargetId) == 1 && npcs.at(world.currentTargetId).isAlive)
      {
        if (!npcs.at(world.currentTargetId).isAttackable)
        {
          ////printf("Twoj target nie jest atakowalny\n");
        }
        else
        {
          ////printf("DO ATAKUUUUU! %X\n", world.currentTargetId);
          actionPause = GetTickCount() + 789;
          injector->Action(world.currentTargetId, player.x, player.y, player.z, false);
        }
      }
      else
      {
        ////printf("Autoatk - twoj target jest martwy ; O\n");
      }
    }
    else
    {
      ////printf("Nie masz targetu na autoatak!\n");
    }

  }

  std::vector<BotSkill*> wanted;

  for (auto& skill : brain.skills)
  {
    //czemu uzywa tylko 1szego? ; O
    //moze niech wybiera sobie losowy z dostepnych?
    if (skill.lastUse + skill.reuse < GetTickCount())
    {
      if (skill.reqTarget && world.currentTargetId == 0) continue;
      if ((player.currMP * 100) / player.maxMP < skill.mana) continue;
      if ((player.currHP * 100) / player.maxHP < skill.hp) continue;
      wanted.push_back(&skill);
      //break; // niech nie spami miliard naraz tylko w kolejnym ticku
    }
  }

  if (wanted.size())
  {
    auto skill = wanted[rand() % wanted.size()];
    skill->lastUse = GetTickCount();
    injector->MagicSkillUse(skill->skillId, 0, 0);
  }
  for (auto& item : brain.items)
  {
    ////printf("Przelatuje itemy %d %d %d %d %d %d\n", player.currHP, player.maxHP, player.currMP, player.maxMP, item.lastUse, item.reuse);
    if (item.lastUse + item.reuse < GetTickCount())
    {
      if (item.reqTarget && world.currentTargetId == 0) continue;
      if ((100 * player.currHP) / player.maxHP > item.hpMax) continue;
      if ((100 * player.currHP) / player.maxHP < item.hpMin) continue;
      if ((100 * player.currMP) / player.maxMP > item.manaMax) continue;
      if ((100 * player.currMP) / player.maxMP < item.manaMin) continue;
      auto qq = brain.backpack.TemplateIdToObjectId(item.itemId);
      if (!qq) continue;
      ////printf("WIOOOO ITEM %X -> %X\n", item.itemId, qq);
      injector->UseItem(qq, 0);
      item.lastUse = GetTickCount();
      //break;
      //injector->
      //skill.lastUse = GetTickCount();
      //injector->MagicSkillUse(skill.skillId, 0, 0);
      //break; // niech nie spami miliard naraz tylko w kolejnym ticku
    }
  }
}

DWORD GlobalAddr;

LONG WINAPI TickHookHandler(PEXCEPTION_POINTERS exception)
{
  if (exception->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT && exception->ExceptionRecord->ExceptionAddress == (PVOID)GlobalAddr)
  {
    Bot();
    exception->ContextRecord->Eip++;
    exception->ContextRecord->Dr6 = 0;
    return EXCEPTION_CONTINUE_EXECUTION;
  }
  //DbgPrint("Ja tylko umjem STI nie obsluguje %X :( Szukam dalej\n", exception->ExceptionRecord->ExceptionCode);
  return EXCEPTION_CONTINUE_SEARCH;
}

void InstallTickHook()
{
  //printf("zaczynam\n");
  WIELKIE_QQ("1");
  Version cv = VersionInfo::getInstance().GetVersion();
  WIELKIE_QQ("2");
  DWORD HookAddr = 0;
  switch (cv)
  {
    case L2_H5:
      ////printf("L2 H5\n");
      /*switch (rand() % 4)
      {
      case 0:*/
      HookAddr = Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?SpecialViewTick@ALineagePlayerController@@QAEXM@Z") + 0x30;
      GlobalAddr = HookAddr;
      if(!HookAddr) MessageBoxA(0, "RIP IN PEPPERS", "1", 0);
      /*break;
      case 1:
      HookAddr = Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?UpdateShakeState@ALineagePlayerController@@QAEXM@Z") + 0x2B;
      break;
      case 2:
      HookAddr = Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?ElasticCameraTick@ALineagePlayerController@@QAEXM@Z") + 0x28;
      break;
      case 3:
      HookAddr = Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?Tick@ULevel@@UAEXW4ELevelTick@@M@Z") + 0x33;
      break;
      }*/
      break;
    case L2_IL:
      ////printf("L2 IL\n");
      /*switch (rand() % 3)
      {
      case 0:
      HookAddr = Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?SpecialViewTick@ALineagePlayerController@@QAEXM@Z");
      if (!HookAddr) MessageBoxA(0, "RIP IN PEPPERS", "2", 0);
      HookAddr = Utils::resolveJump(HookAddr) + 0x4F;

      break;
      case 1:
      HookAddr = Utils::resolveJump(Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?UpdateShakeState@ALineagePlayerController@@QAEXM@Z")) + 0x28;
      break;
      case 2:
      */
      HookAddr = Utils::resolveJump(Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?Tick@ULevel@@UAEXW4ELevelTick@@M@Z")) + 0x33;
      GlobalAddr = HookAddr;
      break;
    //}
    //break;
    default:
      MessageBoxA(0, "Failed to detect game version! MAGIC ; O\n", "", 0);
      return;

  }
  WIELKIE_QQ("3");
  ////printf("adresik to %X\n", HookAddr);
  DWORD old, old2;
  auto result = VirtualProtect((LPVOID)HookAddr, 1, PAGE_EXECUTE_READWRITE, &old);
  WIELKIE_QQ("4");
  if (!result) MessageBoxA(0, (std::string("RIP IN PEPPERS") + std::to_string(*(int*)VirtualProtect) + " " + std::to_string(*(int*)NtProtectVirtualMemory)).c_str(), "3", 0);
  *(BYTE*)HookAddr = 0xCC;
  WIELKIE_QQ("5");
  if (*(BYTE*)HookAddr != 0xCC) MessageBoxA(0, "RIP IN PEPPERS", "4", 0);
  result = VirtualProtect((LPVOID)HookAddr, 1, old, &old2);
  WIELKIE_QQ("6");
  if (!result) MessageBoxA(0, (std::string("RIP IN PEPPERS") + std::to_string(*(int*)VirtualProtect) + " " + std::to_string(*(int*)NtProtectVirtualMemory)).c_str(), "3", 0);
  auto veh = AddVectoredExceptionHandler(1, TickHookHandler);
  WIELKIE_QQ("7");
  if (!veh) MessageBoxA(0, "RIP IN PEPPERS", "6", 0);
  //std::unique_ptr<Sniffer> sniffer(new ExceptionBasedSniffer/*HookBasedSniffer*/());
  auto sniffer(std::make_unique<ExceptionBasedSniffer>());
  WIELKIE_QQ("8");
  sniffer->SetupNotification([](const char packet[], size_t length)->void
  {
    //printf("\n[Recv]");
    /*for (size_t i = 0; i < length; ++i)
    {
        if (i % 24 == 0) putchar('\n');
        printf("%02X ", (unsigned int)packet[i] & 0xFF);
    }*/
    try
    {
      auto pp = LineagePacketFactory().Construct(packet, length);
      if (pp) pp->HandlePacket();
    }
    catch (std::runtime_error& e)
    {
      MessageBoxA(0, e.what(), "SZAKA BOT - EXCEPTION", 0);
    }

  });
  //printf("supermoc\n");
  WIELKIE_QQ("done");
}


BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID q)
{
  UNREFERENCED_PARAMETER(hInst);
  UNREFERENCED_PARAMETER(q);
  switch (reason)
  {
    case DLL_PROCESS_ATTACH:

      //wazne: bot wezmie adres z ktorego zostal wywolany i na jego podstawie cos tam porobi //0xE58B5B5E
      //zagwarantuej to ladowanie wylacznie z mojego payloadu
      //
      //do tego getmodulehandle czy nie jestem recznie zaladowany
      //niewidzialny watek antysuspend
      //l2 lubi sie osiedlac na chyba 10900000
      //aha i loaddll.exe xD
      //jakis timer na kazda wersje ze miesiac 2 max
      //przelec ldr czy hinstance instnieje
      //usun reloakcje loaderem?
      //no pisz wiecej pomyslow misiaczku ; O
      /*AllocConsole();
      freopen("CONOUT$", "w", stdout);
      printf("dzialam\n");*/
      //UltraSecretConfirmation - TOP SECRET U_U
      /*
      002200DF    5F              POP EDI
      002200E0    5E              POP ESI
      002200E1    5B              POP EBX
      002200E2    8BE5            MOV ESP,EBP
      */
      /*DWORD* stackptr = (DWORD*)&hInst;
      if (stackptr < (DWORD*)0x120000) return 0; // main thread stack - NEVER
      if (*(DWORD*)*(stackptr + 0x50 / 4) != 0x8B5B5E5F) return 0; // nie moje bajty loadera
      if (GetModuleHandleA("loaddll.exe")) return 0; // ; OOO
      if ((DWORD)GetModuleHandleA(0) == 0x400000) return 0;*/


      //printf("Okej misiaczki %X %X", *(stackptr + 0x50 / 4), *(DWORD*)*(stackptr + 0x50 / 4));
      InstallTickHook();

      CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UstawiaczBota, hInst, 0, 0);
      break;
  }
  return 1;
}