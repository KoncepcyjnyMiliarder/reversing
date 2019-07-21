#pragma once
#include "Character.hpp"
#include "Inventory.hpp"
#include <vector>
#include "Buff.hpp"

struct PlayerCharacter : public Character
{
  public:
    PlayerCharacter(unsigned int objectId, int x, int y, int z, const std::wstring& name, int race,
                    int sex, int classID, int level, unsigned long long exp, int maxHP, int currHP, int maxMP, int currMP)
      : Character(x, y, z, name, race, sex, classID), objectId(objectId), level(level),
        exp(exp), maxHP(maxHP), currHP(currHP), maxMP(maxMP), currMP(currMP) {}

    //PlayerCharacter(const PlayerCharacter&) = delete;

    /*PlayerCharacter(PlayerCharacter&& rhs)
      : Character(std::move(rhs)), objectId(rhs.objectId), level(rhs.level), exp(rhs.exp), maxHP(rhs.maxHP),
      currHP(rhs.currHP), maxMP(rhs.maxMP), currMP(rhs.currMP), targetId(rhs.targetId) {}
      */
    unsigned int objectId;
    int level;
    unsigned long long exp;
    unsigned int maxHP, currHP;
    unsigned int maxMP, currMP;
    std::vector<Buff> buffs;
    //std::vector<Skill> skills;
};