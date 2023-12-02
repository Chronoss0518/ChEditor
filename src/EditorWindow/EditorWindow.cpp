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

	ChCpp::File<char> file;
	file.FileOpen("ControlManagerFile.setting");
	auto&& jsonObject = ChPtr::SharedSafeCast<ChCpp::JsonObject>(ChCpp::JsonBaseType::GetParameter(file.FileReadText()));
	controlManager->Deserialize(jsonObject);
	if (jsonObject == nullptr)controlManager->InitializeShortcutKeyMaps();
	file.FileClose();

	SetInitFlg(true);
}

void EditorWindow::Release()
{
	if (!IsInit())return;

	ChCpp::File<char> file;
	file.FileOpen("ControlManagerFile.setting");
	file.FileWriteText(controlManager->Serialize()->GetRawData());
	file.FileClose();

	if (ChPtr::NotNullCheck(controlManager))
	{
		delete controlManager;
		controlManager = nullptr;
	}

	SetInitFlg(false);
}

