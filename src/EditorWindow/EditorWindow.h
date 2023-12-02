#pragma once

class ControlManager;

class EditorWindow:public ChCp::Initializer
{
public:

	
	virtual void Init();

	virtual int Update() = 0;

	virtual void Release();

protected:

	ChLMat viewMatrix;

	//透視投影射影行列//
	ChLMat projectionMatrixPerspective;

	//直行射影行列//
	ChLMat projectionMatrixOrthographic;

	ControlManager* controlManager = nullptr;

	ChCpp::JsonObject saveData;

	bool checkTestFlg = false;

};