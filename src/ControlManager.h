#pragma once

class ControlManager
{
public:

	enum class ControlType : unsigned short
	{
		ChangeTheProjectionMatrixType,None
	};

public:

	void InitializeShortcutKeyMaps();

	ChPtr::Shared<ChCpp::JsonObject> Serialize();

	void Deserialize(const ChPtr::Shared<ChCpp::JsonObject>& _json);

	inline void SetCameraLookAngleRadian(float _radian)
	{
		if (_radian < 1.0f)return;
		if (_radian >= 180.0f)return;
		cameraLookAngleRadian = _radian;
	}

	inline float GetCameraLookAngleRadian()
	{
		return cameraLookAngleRadian;
	}

	inline void SetUseProjectionMatrixOrthographicFlg(bool _flg)
	{
		useProjectionMatrixOrthographicFlg = _flg;
	}

	inline bool IsUseProjectionMatrixOrthographicFlg() 
	{
		return useProjectionMatrixOrthographicFlg; 
	}

	std::vector<ControlManager::ControlType> GetShortcut(ChPtr::Shared<ChSystem::BaseSystem> _windSystem);

private:

	std::string ControlTypeToString(ControlManager::ControlType _type);

	ControlManager::ControlType StringToControlType(const std::string& _str);
	
	float cameraLookAngleRadian = 60.0f;

	bool useProjectionMatrixOrthographicFlg = false;

	std::map<ControlType, std::vector<unsigned long>>shortcutKeyMap;

};