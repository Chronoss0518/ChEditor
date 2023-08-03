#include"BaseIncluder.h"
#include"EditorWindow/EditorWindow.h"

int main()
{
	EditorWindow window;

	window.Init();

	int lresult = window.Update();

	window.Release();

	return lresult;
}