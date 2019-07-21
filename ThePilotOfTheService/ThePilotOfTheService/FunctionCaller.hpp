#pragma once
#include "Injector.hpp"
#include "L2ParamStackWrapper.hpp"

class FunctionCaller : public Injector
{
  public:
    FunctionCaller();
    virtual void Action(unsigned int objectId, int origX, int origY, int origZ, bool shift) override;
    virtual void MagicSkillUse(int skillID, bool shift, bool ctrl) override;
    virtual void Say2(wchar_t* text, int channel, wchar_t* targetNamePM = nullptr) override;
    virtual void UseItem(unsigned int itemId, bool control) override;
    virtual void EnchantItem(unsigned itemId, unsigned enchant_id) override;

  private:
    //?Action@UNetworkHandler@@UAEXHVFVector@@H@Z
    void(__fastcall* ActionCall)(unsigned int ecx, void* dummy, unsigned int objectId, float origX, float origY, float origZ, bool shift);
    //?RequestMagicSkillUse@UNetworkHandler@@UAEXAAVL2ParamStack@@@Z
    void(__fastcall* MagicSkillUseCall)(unsigned int ecx, void* dummy, L2ParamStack& stack);
    //?Say2@UNetworkHandler@@UAEXAAVL2ParamStack@@@Z // channel, msg, do kogo,
    void(__fastcall* Say2Call)(unsigned int ecx, void* dummy, L2ParamStack& stack);
    void(__fastcall* UseItemCall)(unsigned int ecx, void* dummy, L2ParamStack& stack);
    //?RequestEnchantItem@UNetworkHandler@@UAEHHH@Z
    void(__fastcall* EnchantItemCall)(unsigned int ecx, void* dummy, unsigned itemId, unsigned enchant_id);
};