#include "MoveToLocation.hpp"
#include "BotBrain.hpp"
//01=MoveToLocation:d(objectId)d(ToX)d(ToY)d(ToZ)d(OrigX)d(OrigY)d(OrigZ)

MoveToLocation::MoveToLocation(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	objectId = serializer.ReadD();
	toX = serializer.ReadD();
	toY = serializer.ReadD();
	toZ = serializer.ReadD();
	fromX = serializer.ReadD();
	fromY = serializer.ReadD();
	fromZ = serializer.ReadD();
}

void MoveToLocation::HandlePacket()
{
	BotBrain::GetInstance().GetWorld().HandleMoveToLocation(objectId, toX, toY, toZ);
}
