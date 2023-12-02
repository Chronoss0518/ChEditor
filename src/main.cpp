#include"BaseIncluder.h"
#include"EditorWindow/EditorWindow.h"
#include"Windows/EditorWindowFromWindows/EditorWindowFromWindows.h"

int main()
{
	ChPtr::Unique<EditorWindow> window = nullptr;

#ifdef _WINDOWS
	window = ChPtr::Make_U<EditorWindowFromWindows>();
#endif

	window->Init();

	int lresult = window->Update();

	window->Release();

	return lresult;
}