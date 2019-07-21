#include "World.hpp"
#include <algorithm>

void World::InsertNpc(unsigned int objectId, Npc&& npc)
{
  std::lock_guard<std::mutex> lock(worldMutex);
  if (npcs.count(objectId) == 1)
    npcs.at(objectId) = std::forward<Npc>(npc);
  else npcs.emplace(objectId, std::forward<Npc>(npc));
}

void World::InsertCharacter(unsigned int objectId, Character&& character)
{
  std::lock_guard<std::mutex> lock(worldMutex);
  if (chars.count(objectId) == 1)
    chars.at(objectId) = std::forward<Character>(character);
  else chars.emplace(objectId, std::forward<Character>(character));
}

void World::HandleStatusUpdate(unsigned int objectId, std::vector<std::pair<StatusEnum, int>>& attributes)
{
  std::lock_guard<std::mutex> lock(worldMutex);
  if (objectId == player->objectId)
  {
    for (size_t i = 0; i < attributes.size(); ++i)
    {
      switch (attributes[i].first)
      {
        case level:
          player->level = attributes[i].second;
          break;
        case expPts: // nie wiem czy to wysyla exp za moba czy calkowity? chyba za jednego moba skoro to int a nie ULL
          player->exp += attributes[i].second;
          break;
        case currHP:
          player->currHP = attributes[i].second;
          break;
        case maxHP:
          player->maxHP = attributes[i].second;
          break;
        case currMP:
          player->currMP = attributes[i].second;
          break;
        case maxMP:
          player->maxMP = attributes[i].second;
          break;
          /*
          currCP = 0x21,
          maxCP = 0x22,
          */
      }

    }
    return;
  }
}

void World::HandleMoveToLocation(unsigned int objectId, int x, int y, int z)
{
  std::lock_guard<std::mutex> lock(worldMutex);
  if (objectId == player->objectId)
  {
    //printf("Ruszyles sie na %d %d %d\n", x, y, z);
    player->x = x;
    player->y = y;
    player->z = z;
    return;
  }
  if (npcs.count(objectId) == 1)
  {
    //printf("NPC %X ruszyl sie sie na %d %d %d\n", objectId, x, y, z);
    auto& npc = npcs.at(objectId);
    npc.x = x;
    npc.y = y;
    npc.z = z;
    return;
  }
  //printf("No zglupialem. Niby sie ktos ruszyl ale go nie mam w danych ; OOOOOOOOOOO\n");
}

void World::HandleTargetSwitch(unsigned int whoId, unsigned int targetId)
{
  std::lock_guard<std::mutex> lock(worldMutex);
  if (whoId == player->objectId)
    currentTargetId = targetId;
}

void World::HandleObjectDeath(unsigned int objectId)
{
  std::lock_guard<std::mutex> lock(worldMutex);

  if (npcs.count(objectId) == 1)
  {
    //printf("Obiektowi %X sie umarlo\n", objectId);
    npcs.at(objectId).isAlive = false;
    return;
  }

  /*if (chars.count(objectId) == 1) // char narazie nie ma czy alive ; O
  {
    chars[objectId].isAlive = false;
    return;
  }*/
}

void World::RemoveObject(unsigned int objectId)
{
  //printf("Usuwam %X\n", objectId);
  std::lock_guard<std::mutex> lock(worldMutex);
  npcs.erase(objectId) || chars.erase(objectId); // HACK
}
