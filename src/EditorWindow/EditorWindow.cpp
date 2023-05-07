#include"../BaseIncluder.h"
#include"EditorWindow.h"

#define POSITION_X 5
#define POSITION_Y 5

void EditorWindow::Init(HINSTANCE _hInstance, int _nShowCmd)
{
	windows = ChSystem::SysManager().Init<ChSystem::Windows>();

	ChWin::WindCreater creater = ChWin::WindCreater(_hInstance);

	auto displaySize = ChWin::GetScreenSize();

	creater.SetInitPosition(POSITION_X, POSITION_Y);
	creater.SetInitSize(displaySize.w - (POSITION_X * 2), displaySize.h - (POSITION_Y * 2));

	ChWin::WindStyle style;
	style.AddOverlappedWindow();
	style.AddClipChildren();
	style.AddSizeBox();
	style.AddVisible();

	creater.SetWindStyle(&style);

	windows->Init(creater, "ChFileEditorFor3D", "ChEditor", _hInstance, _nShowCmd);
}

int EditorWindow::Update()
{

	while (ChSystem::SysManager().IsUpdate())
	{
		
	}

	return 0;
}
