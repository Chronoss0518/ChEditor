#pragma once

class ControlManager;

class EditorWindow : public ChCp::Initializer
{
public://子ウィンドウ//



public:

	void Init(HINSTANCE _hInstance, int _nShowCmd)
	{
		Init();

#ifdef _WINDOWS

		InitWindows(_hInstance, _nShowCmd);

		InitDirectX();
#else

#endif
	}

	void Init();

	int Update();

	void Release();

private:

	void InitWindows(HINSTANCE _hInstance, int _nShowCmd);

	void InitDirectX();

	void InitWindowsMenu();

	int UpdateWindows();

	void ReleaseWindows();

	ChLMat viewMatrix;

	//透視投影射影行列//
	ChLMat projectionMatrixPerspective;
	
	//直行射影行列//
	ChLMat projectionMatrixOrthographic;

	ControlManager* controlManager = nullptr;

#ifdef WIN32 || WIN64

	ChINTPOINT displaySize;

	ChWin::WindObject windows;
	HMENU menu = nullptr;
	ChWin::WindClassObject windClass;

	ChD3D11::DirectX3D11 d3d11;

	bool checkTestFlg = false;

#else

#endif


};