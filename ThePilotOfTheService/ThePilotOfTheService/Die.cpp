#include "Die.hpp"
#include "BotBrain.hpp"

////06 = Die:d(CharID)d(d)d(HAsHideout)d(HasCastle)d(flags)d(sweepable)d(access)
Die::Die(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	objectId = serializer.ReadD();
	for (int i = 0; i < 4; ++i) serializer.ReadD();
	sweepable = serializer.ReadD();
}

void Die::HandlePacket()
{
	BotBrain::GetInstance().GetWorld().HandleObjectDeath(objectId);
}
