#include "TargetUnselected.hpp"
#include "BotBrain.hpp"
//2A = TargetUnselected:d(TargetID)d(X)d(Y)d(Z)d(d)
TargetUnselected::TargetUnselected(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	targetID = serializer.ReadD();
	x = serializer.ReadD();
	y = serializer.ReadD();
	z = serializer.ReadD();
}

void TargetUnselected::HandlePacket()
{
	BotBrain::GetInstance().GetWorld().HandleTargetSwitch(targetID, 0);
}
