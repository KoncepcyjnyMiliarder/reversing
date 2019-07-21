#pragma once

class Injector
{
  public:
    virtual void Action(unsigned int objectId, int origX, int origY, int origZ, bool shift) = 0;
    virtual void MagicSkillUse(int skillID, bool shift, bool ctrl) = 0;
    virtual void Say2(wchar_t* text, int channel, wchar_t* targetNamePM = nullptr) = 0;
    virtual void UseItem(unsigned int itemId, bool control) = 0;
    virtual void EnchantItem(unsigned itemId, unsigned enchant_id) = 0;
    virtual ~Injector() = default;
};