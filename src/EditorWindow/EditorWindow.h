#pragma once

class ControlManager;

class EditorWindow : public ChCp::Initializer
{
public://子ウィンドウ//




public:

	void Init()
	{
		InitBase();

#ifdef _WINDOWS

		InitWindows();

		InitDirectX();
#else

#endif
		SetInitFlg(true);
	}


	int Update()
	{
		int res = 0;


		while (wind->IsUpdate())
		{

#ifdef _WIN32

			res = UpdateWindows();

#endif


		}

		return res;
	}

	void Release();

private:

	void InitBase();

private:

	void InitWindows();

	void InitDirectX();

	void InitWindowsMenu();

	int UpdateWindows();

	void DrawWindows();


	void ReleaseWindows();

	ChLMat viewMatrix;

	//透視投影射影行列//
	ChLMat projectionMatrixPerspective;
	
	//直行射影行列//
	ChLMat projectionMatrixOrthographic;

	ControlManager* controlManager = nullptr;

	ChPtr::Shared<ChSystem::BaseSystem> wind = nullptr;

	std::vector<ChPtr::Shared<ChCpp::ModelObject>>modelList;

	std::vector<ChPtr::Shared<
#ifdef WIN32
		ChD3D11::TextureBase11
#endif
		>>textureList;

#ifdef WIN32

	ChINTPOINT displaySize;

	HMENU menu = nullptr;
	ChWin::WindClassObject windClass;

	ChD3D11::DirectX3D11 d3d11;

	ChD3D11::Shader::BaseDrawMesh11 drawMeshShader;

	ChD3D11::Shader::BaseDrawSprite11 drawSpriteShader;

	ChD3D11::Shader::BaseDrawPolygonBoard11 drawPolygonShader;

	bool checkTestFlg = false;

#else 


#endif


};