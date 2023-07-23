#include"BaseIncluder.h"
#include"ControlManager.h"


ChPtr::Shared<ChCpp::JsonObject> ControlManager::Serialize()
{
	auto&& res = ChPtr::Make_S<ChCpp::JsonObject>();

	return res;
}

void ControlManager::Deserialize(const ChPtr::Shared<ChCpp::JsonObject>& _json)
{
	if (_json == nullptr)return;
}
