#pragma once
#include "World.hpp"
#include "BoundingBox.hpp"

struct BotSkill
{
  unsigned int skillId;
  unsigned int reuse;
  unsigned int mana;
  unsigned int hp;
  bool reqTarget;
  unsigned int lastUse = 0;
};

struct BotItem
{
  unsigned int itemId;
  unsigned int reuse;
  unsigned int manaMin;
  unsigned int manaMax;
  unsigned int hpMin;
  unsigned int hpMax;
  bool reqTarget;
  unsigned int lastUse = 0;
};

class BotBrain
{
  public:
    static BotBrain& GetInstance()
    {
      static BotBrain ziemniak;
      return ziemniak;
    }
    //get world
    //get player
    //bot?
    bool botactive = false;
    bool autotarget = false;
    bool autoattack = false;
    BoundingBox polygon;
    std::vector<BotSkill> skills;
    std::vector<BotItem> items;
    Inventory backpack;
    World& GetWorld()
    {
      return world;
    }
    std::vector<unsigned> to_enchant;
    unsigned enchant_id;
  private:
    World world;
};