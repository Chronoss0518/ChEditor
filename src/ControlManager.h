#pragma once

class ControlManager
{
public:

	enum class ControlType
	{
		CHANGE_PROJECT_MATRIX_TYPE
	};

public:

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

private:

	float cameraLookAngleRadian = 60.0f;

	bool useProjectionMatrixOrthographicFlg = false;

	std::map<ControlType, std::vector<unsigned long>>shortcutKeyMap;

};