#pragma once

class EditorWindow
{
public:

	void Init(HINSTANCE _hInstance, int _nShowCmd);

	int Update();



private:

	ChSystem::Windows* windows = nullptr;

};