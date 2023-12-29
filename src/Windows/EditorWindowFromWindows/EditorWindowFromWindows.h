#pragma once

#include"../../EditorWindow/EditorWindow.h"

class EditorWindowFromWindows : public EditorWindow
{
public:

	void Init()override;

	int Update()override;

	void Release()override;


private:

	void InitWindows();

	void InitDirectX();

	void InitWindowsMenu();

	void UpdateFunction();

	void DrawFunction();

	ChPtr::Shared<ChSystem::BaseSystem> wind = nullptr;

	std::vector<ChPtr::Shared<ChCpp::ModelObject>>modelList;

	std::vector<ChPtr::Shared<ChD3D11::TextureBase11>>textureList;

	ChINTPOINT displaySize;

	HMENU menu = nullptr;
	ChWin::WindClassObject windClass;

	ChD3D11::DirectX3D11 d3d11;

	ChD3D11::Shader::BaseDrawMesh11 drawMeshShader;

	ChD3D11::Shader::BaseDrawSprite11 drawSpriteShader;

	ChD3D11::Shader::BaseDrawPolygonBoard11 drawPolygonShader;

	ChD3D11::Shader::BaseDrawPolygonBoard11 drawGridShader;
};