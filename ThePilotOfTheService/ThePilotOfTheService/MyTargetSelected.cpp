#include "MyTargetSelected.hpp"
#include "BotBrain.hpp"

//A6=MyTargetSelected:d(objectId)h(color)

MyTargetSelected::MyTargetSelected(const char packet[], size_t length)
  : LineagePacket(packet, 1, length)
{
  targetID = serializer.ReadD();
}

void MyTargetSelected::HandlePacket()
{
  auto myId = BotBrain::GetInstance().GetWorld().GetPlayer().objectId;
  //printf(__FUNCSIG__ "who %X targeted %X\n", myId, targetID);
  BotBrain::GetInstance().GetWorld().HandleTargetSwitch(myId, targetID);
}
