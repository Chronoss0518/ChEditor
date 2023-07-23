#include"../BaseIncluder.h"
#include"EditorWindow.h"
#include"../../resource.h"
#include"../ControlManager.h"

#define POSITION_X 5
#define POSITION_Y 5

#define BASE_DISPLAY_SIZE_WIDTH 1280
#define BASE_DISPLAY_SIZE_HEIGHT 720


#define CHAST_FLOAT(val) static_cast<float>(val)

void EditorWindow::Init()
{
	controlManager = new ControlManager();

	SetInitFlg(true);
}

void EditorWindow::InitWindows(HINSTANCE _hInstance, int _nShowCmd)
{
#ifdef _WIN32
	windClass.Init();

	{
		ChWin::WindClassStyle style;
		style.AddSaveBits();

		windClass.SetStyle(&style);
		windClass.RegistClass(L"ChEditor");
	}


	ChWin::WindCreater creater = ChWin::WindCreater(_hInstance);

	displaySize = ChWin::GetScreenSize();

	displaySize.w = displaySize.w - (POSITION_X * 2);
	displaySize.h = displaySize.h - (POSITION_Y * 2);

	creater.SetInitPosition(POSITION_X, POSITION_Y);
	creater.SetInitSize(displaySize.w, displaySize.h);

	{
		ChWin::WindStyle style;
		style.AddOverlappedWindow();
		style.AddClipChildren();
		style.AddSizeBox();
		style.AddVisible();

		creater.SetWindStyle(&style);
	}

	creater.Create(&windows, L"ChFileEditorFor3D", windClass.GetWindClassName(), _nShowCmd);

	menu = LoadMenu(_hInstance, TO_STRING(MENU_FILE));
	SetMenu(windows.GethWnd(), menu);

	InitWindowsMenu();

	ChMat_11 tmpMat;

	tmpMat.CreateProjectionMat(60.0f, TO_FLOATING(displaySize.w), TO_FLOATING(displaySize.h), 0.01f, 10000.0f);

	projectionMatrixPerspective = tmpMat;

	tmpMat.CreateProjectionMat(TO_FLOATING(displaySize.w), TO_FLOATING(displaySize.h), 0.01f, 10000.0f);

	projectionMatrixOrthographic = tmpMat;

#endif
}

void EditorWindow::InitDirectX()
{
#ifdef _WIN32
	d3d11.Init(windows.GethWnd(), false, displaySize.w, displaySize.h);

	ChD3D11::Shader11().Init(d3d11, CHAST_FLOAT(displaySize.w), CHAST_FLOAT(displaySize.h));
#endif
}

void EditorWindow::InitWindowsMenu()
{

#ifdef _WIN32

	windows.SetWindProcedure(APP_EXIT, [&](HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)->LRESULT {
		ChWin::MsgBox msgBox;
		msgBox.ClearDisplayButtonType();
		msgBox.AddDisplayButtonType(ChWin::MsgBox::DisplayButtonType::YesNo);

		if (msgBox.Display(_hWnd, L"終了確認", L"アプリケーションを終了しますか") == ChWin::MsgBox::PushButtonType::Yes)
		{
			PostQuitMessage(0);
		}
		return 0;
	});

	windows.SetWindProcedure(FILE_CLOSE, [&](HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)->LRESULT {
		ChWin::MsgBox msgBox;
	msgBox.SetDefaultButtonType(ChWin::MsgBox::DefaultButtonType::Button1);
	msgBox.Display(_hWnd, L"File Close Test", L"you select a file close in menu");
	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
		});

	windows.SetWindProcedure(WINDOW_OPEN_PROPATY, [&](HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)->LRESULT {

		checkTestFlg = !checkTestFlg;
		CheckMenuItem(menu, WINDOW_OPEN_PROPATY, checkTestFlg ? MF_CHECKED : MF_UNCHECKED);

		return 0;
		});
#endif
}

int EditorWindow::UpdateWindows()
{
#ifdef _WIN32


	while (windows.Update())
	{




		ChLMat projectionMat = projectionMatrixPerspective;

		if (controlManager->IsUseProjectionMatrixOrthographicFlg())projectionMat = projectionMatrixOrthographic;

	}

	return (int)windows.GetReturnMassage();
#endif
}

int EditorWindow::Update()
{
	int res = 0;

#ifdef _WIN32

	res = UpdateWindows();

#endif

	return res;
}

void EditorWindow::Release()
{
	if (!IsInit())return;
	
	ReleaseWindows();

	SetInitFlg(false);
}

void EditorWindow::ReleaseWindows()
{
#ifdef _WIN32

	ChD3D11::Shader11().Release();

	d3d11.Release();

	windows.Release();

	windClass.Release();

	if (ChPtr::NotNullCheck(controlManager))
	{
		delete controlManager;
		controlManager = nullptr;
	}


#endif

}
