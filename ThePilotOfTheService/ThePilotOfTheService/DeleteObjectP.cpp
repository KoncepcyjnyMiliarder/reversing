#include "DeleteObjectP.hpp"
#include "BotBrain.hpp"

//12=DeleteObject:d(objectId)d(d)

DeleteObjectP::DeleteObjectP(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	objectId = serializer.ReadD();
}

void DeleteObjectP::HandlePacket()
{
	BotBrain::GetInstance().GetWorld().RemoveObject(objectId);
}