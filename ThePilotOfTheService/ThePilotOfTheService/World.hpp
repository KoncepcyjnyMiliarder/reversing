#pragma once
#include <map>
#include "Npc.hpp"
#include "PlayerCharacter.hpp"
#include <memory>
#include <mutex>
#include <vector>
#include "Resources.hpp"

class World
{
  public:

    World()
      : ingame(false) {}

    World(const World&) = delete;

    std::map<unsigned int, Npc>& GetNpcs()
    {
      return npcs;
    }
    void InsertNpc(unsigned int objectId, Npc&& npc);

    std::map<unsigned int, Character>& GetCharacters()
    {
      return chars;
    }
    void InsertCharacter(unsigned int objectId, Character&& character);

    void HandleStatusUpdate(unsigned int objectId, std::vector<std::pair<StatusEnum, int>>& attributes);
    void HandleMoveToLocation(unsigned int objectId, int x, int y, int z);
    void HandleTargetSwitch(unsigned int whoId, unsigned int targetId);
    void HandleObjectDeath(unsigned int objectId);
    void RemoveObject(unsigned int objectId);

    PlayerCharacter& GetPlayer()
    {
      return *player;
    }
    WorldObject& GetObject(unsigned int objectId);
    void HandleCharacterSelected(PlayerCharacter&& newPlayer)
    {
      player.reset(new PlayerCharacter(std::move(newPlayer)));
    }
    void HandleWorldLeave()
    {
      ingame = false;
      currentTargetId = 0;
    }
    void HandleWorldEnter()
    {
      ingame = true;
      currentTargetId = 0;
    }

    bool IsIngame()
    {
      return ingame;
    }

    //object orgy ftw. who the fuck messes this var?
    unsigned currentTargetId;

  private:

    std::mutex worldMutex; // cos tym, jakos wymusic
    bool ingame;
    std::map<unsigned int, Npc> npcs;
    std::map<unsigned int, Character> chars;
    std::unique_ptr<PlayerCharacter> player;
};