#include"BaseIncluder.h"
#include"ControlManager.h"


void ControlManager::InitializeShortcutKeyMaps()
{
	shortcutKeyMap[ShortcutKeyType::ChangeTheProjectionMatrixType] = { VK_SHIFT,'V' };
}

ChPtr::Shared<ChCpp::JsonObject> ControlManager::Serialize()
{
	auto&& res = ChPtr::Make_S<ChCpp::JsonObject>();

	res->SetObject("Camera Look Angle Radian", ChCpp::JsonNumber::CreateObject(cameraLookAngleRadian));

	res->SetObject("Use Orthographic From Projection Matrix", ChCpp::JsonBoolean::CreateObject(useProjectionMatrixOrthographicFlg));

	auto&& shortcutKeyMapObject = ChPtr::Make_S<ChCpp::JsonObject>();
	
	for (auto&& shortcutKeyValue : shortcutKeyMap)
	{
		auto&& shortcutKeyArray = ChCpp::JsonArray::CreateObject(shortcutKeyValue.second);

		shortcutKeyMapObject->SetObject(std::to_string(ChStd::EnumCast(shortcutKeyValue.first)), shortcutKeyArray);
	}

	res->SetObject("Shortcut Key Mapping", shortcutKeyMapObject);

	return res;
}

void ControlManager::Deserialize(const ChPtr::Shared<ChCpp::JsonObject>& _json)
{
	if (_json == nullptr)return;

	cameraLookAngleRadian = GetJsonNumber("Camera Look Angle Radian", _json, cameraLookAngleRadian);

	useProjectionMatrixOrthographicFlg = GetJsonBoolean("Use Orthographic From Projection Matrix", _json, useProjectionMatrixOrthographicFlg);

	auto&& shortcutKeyMapObject = _json->GetJsonObject("Shortcut Key Mapping");

	if (shortcutKeyMapObject != nullptr)
	{
		auto&& shortcutKeyMapParameters = shortcutKeyMapObject->GetParameterNames();

		for (auto&& parameterName : shortcutKeyMapParameters)
		{
			auto&& shortcutKeys = shortcutKeyMapObject->GetJsonArray(parameterName);

			if (shortcutKeys == nullptr)continue;

			std::vector<unsigned long>keyList;

			for (unsigned long i = 0; i < shortcutKeys->GetCount(); i++)
			{
				auto&& keyObject = shortcutKeys->GetJsonNumber(i);

				if (keyObject == nullptr)continue;

				keyList.push_back(*keyObject);
			}

			if (keyList.empty())continue;

			auto&& shortcutKeyType = static_cast<ShortcutKeyType>(ChStr::GetIntegialFromText<unsigned short>(parameterName));

			shortcutKeyMap[shortcutKeyType] = keyList;
		}

	}

}
