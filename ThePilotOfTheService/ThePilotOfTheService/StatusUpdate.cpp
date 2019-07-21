#include "StatusUpdate.hpp"
#include "BotBrain.hpp"

//0E=StatusUpdate:d(objectId)d(AttribCount:For.0002)d(AttrID:Get.FSup)d(AttrValue)

StatusUpdate::StatusUpdate(const char packet[], size_t length)
	: LineagePacket(packet, 1, length)
{
	objectId = serializer.ReadD();
	size_t size = serializer.ReadD();
	for (size_t i = 0; i < size; ++i)
	{
		StatusEnum attr = static_cast<StatusEnum>(serializer.ReadD());
		int val = serializer.ReadD();
		attributes.push_back({ attr, val });
	}
}

void StatusUpdate::HandlePacket()
{
	BotBrain::GetInstance().GetWorld().HandleStatusUpdate(objectId, attributes);
}