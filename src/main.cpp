#include"BaseIncluder.h"
#include"EditorWindow/EditorWindow.h"

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{
	EditorWindow window;

	window.Init(hInstance, nShowCmd);

	int lresult = window.Update();

	window.Release();

	return lresult;
}