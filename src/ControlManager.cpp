#include"BaseIncluder.h"
#include"ControlManager.h"

constexpr char const* controlTypeStr[] = { "Change The Projection Matrix Type","None" };

void ControlManager::InitializeShortcutKeyMaps()
{
	shortcutKeyMap[ControlType::ChangeTheProjectionMatrixType] = { VK_SHIFT,'V' };
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

		shortcutKeyMapObject->SetObject(ControlTypeToString(shortcutKeyValue.first), shortcutKeyArray);
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

			auto&& shortcutKeyType = StringToControlType(parameterName);

			if (shortcutKeyType == ControlType::None)continue;

			shortcutKeyMap[shortcutKeyType] = keyList;
		}
	}
}

std::vector<ControlManager::ControlType> ControlManager::GetShortcut(ChPtr::Shared<ChSystem::BaseSystem> _windSystem)
{
	unsigned long pushKey = 0;

	std::vector<ControlManager::ControlType> res;

	bool isPush = true;

	for (auto&& controlType : shortcutKeyMap)
	{
		isPush = true;

		for (auto&& shortcutKey : controlType.second)
		{
			if (_windSystem->IsPushKey(shortcutKey))continue;
			isPush = false;
		}

		if (!isPush)continue;
		res.push_back(controlType.first);
	}

	return res;
}



std::string ControlManager::ControlTypeToString(ControlManager::ControlType _type)
{
	return controlTypeStr[ChStd::EnumCast(_type)];
}

ControlManager::ControlType ControlManager::StringToControlType(const std::string& _str)
{
	for (typename std::underlying_type<ControlType>::type i = 0; i < 1; i++)
	{
		if (_str == controlTypeStr[i])return static_cast<ControlType>(i);
	}

	return ControlType::None;
}
