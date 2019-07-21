#include "FunctionCaller.hpp"
#include "PEStuff.hpp"
#include "VersionInfo.hpp"

FunctionCaller::FunctionCaller()
{
  //?Action@UNetworkHandler@@UAEXHVFVector@@H@Z
  ActionCall = (void(__fastcall*)(unsigned int ecx, void* dummy, unsigned int objectId, float origX, float origY, float origZ, bool shift))Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?Action@UNetworkHandler@@UAEXHVFVector@@H@Z");
  //?RequestMagicSkillUse@UNetworkHandler@@UAEXAAVL2ParamStack@@@Z
  MagicSkillUseCall = (void(__fastcall*)(unsigned int ecx, void* dummy, L2ParamStack & stack))Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?RequestMagicSkillUse@UNetworkHandler@@UAEXAAVL2ParamStack@@@Z");
  //?Say2@UNetworkHandler@@UAEXAAVL2ParamStack@@@Z // channel, msg, do kogo,
  Say2Call = (void(__fastcall*)(unsigned int ecx, void* dummy, L2ParamStack & stack))Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?Say2@UNetworkHandler@@UAEXAAVL2ParamStack@@@Z");
  //?RequestUseItem@UNetworkHandler@@UAEHAAVL2ParamStack@@@Z
  UseItemCall = (void(__fastcall*)(unsigned int ecx, void* dummy, L2ParamStack & stack))Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?RequestUseItem@UNetworkHandler@@UAEHAAVL2ParamStack@@@Z");
  //?RequestEnchantItem@UNetworkHandler@@UAEHHH@Z
  EnchantItemCall = (void(__fastcall* )(unsigned int ecx, void* dummy, unsigned itemId, unsigned enchant_id))Utils::FindExport(Utils::LdrGetModuleHandle(L"Engine.dll"), "?RequestEnchantItem@UNetworkHandler@@UAEHHH@Z");
}

void FunctionCaller::Action(unsigned int objectId, int origX, int origY, int origZ, bool shift)
{
  ActionCall(VersionInfo::getInstance().GetEngineEcx(), 0, objectId, static_cast<float>(origX), static_cast<float>(origY), static_cast<float>(origZ), shift);
}

void FunctionCaller::MagicSkillUse(int skillID, bool shift, bool ctrl)
{
  L2ParamStackWrapper params;
  params.PushBack(skillID);
  params.PushBack(shift);
  params.PushBack(ctrl);
  MagicSkillUseCall(VersionInfo::getInstance().GetEngineEcx(), 0, params.Get());
}

void FunctionCaller::Say2(wchar_t* text, int channel, wchar_t* targetNamePM)
{
  L2ParamStackWrapper params;
  params.PushBack(channel);
  params.PushBack(text);
  if (targetNamePM) params.PushBack(targetNamePM);
  Say2Call(VersionInfo::getInstance().GetEngineEcx(), 0, params.Get());
}

void FunctionCaller::UseItem(unsigned int itemId, bool control)
{
  L2ParamStackWrapper params;
  params.PushBack(itemId);
  params.PushBack(control);
  UseItemCall(VersionInfo::getInstance().GetEngineEcx(), 0, params.Get());
}

void FunctionCaller::EnchantItem(unsigned itemId, unsigned enchant_id)
{
  EnchantItemCall(VersionInfo::getInstance().GetEngineEcx(), 0, itemId, enchant_id);
}
