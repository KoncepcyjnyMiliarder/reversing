#include "TargetSelected.hpp"
#include "BotBrain.hpp"
//29 = TargetSelected:d(objectId)d(TargetID)d(X)d(Y)d(Z)
TargetSelected::TargetSelected(const char packet[], size_t length)
  : LineagePacket(packet, 1, length)
{
  objectId = serializer.ReadD();
  targetID = serializer.ReadD();
  x = serializer.ReadD();
  y = serializer.ReadD();
  z = serializer.ReadD();
}

void TargetSelected::HandlePacket()
{
  BotBrain::GetInstance().GetWorld().HandleMoveToLocation(targetID, x, y, z);
  //printf(__FUNCSIG__ "who %X targeted %X\n", objectId, targetID);
  BotBrain::GetInstance().GetWorld().HandleTargetSwitch(objectId, targetID);
}
