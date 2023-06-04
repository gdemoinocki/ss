#include <Windows.h>
#include "resource1.h"
#include "Soft.h"



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevinst, LPSTR args, int nomdshow)
{
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }

	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"Текстовый редактор", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 250, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;

}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;
	
	return NWC;
}
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case OnOpenFile: {
			if (GetSaveFileNameA(&ofn)) { LoadData(filename); }
			break; }

		case OnSaveFile: {
			MessageBoxA(hWnd, "Сохранено", "Menu 2", MB_OK);
			break; }

		case OnSaveFileAs: {
			//SaveData("C:\\s\\text.txt");
			if (GetSaveFileNameA(&ofn)) { SaveData(filename); }
			break; }

		case OnExitSoftware:{
			PostQuitMessage(0);
			break; }

		case OnCopying: {
			MessageBoxA(hWnd, " Копировать ", "Menu 5", MB_OK);
			break; }

		case OnInserting: {
			MessageBoxA(hWnd, " Вставить ", "Menu 6", MB_OK);
			break; }

		case OnCutting: {
			MessageBoxA(hWnd, " Вырезать ", "Menu 7", MB_OK);
			break; }

		case Properties: {
			MessageBoxA(hWnd, " Инфа ", "Menu 8", MB_OK);
			break; }


		default: break;
		}
		break;

	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		SetOpenFileParams(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu1 = CreateMenu();
	HMENU SubMenu2 = CreateMenu();
	HMENU SubMenu3 = CreateMenu();

	//1 Меню
	AppendMenu(SubMenu1, MF_STRING, OnOpenFile, L"Открыть...");//Создание подменю
	AppendMenu(SubMenu1, MF_STRING, OnSaveFile, L"Сохранить");
	AppendMenu(SubMenu1, MF_STRING, OnSaveFileAs, L"Сохранить как...");
	AppendMenu(SubMenu1, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu1, MF_STRING, OnExitSoftware, L"Выход");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu1, L"Файл");//Создание меню

	//2 Меню
	AppendMenu(SubMenu2, MF_STRING, OnCopying, L"Копировать");
	AppendMenu(SubMenu2, MF_STRING, OnInserting, L"Вставить");
	AppendMenu(SubMenu2, MF_STRING, OnCutting, L"Вырезать");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu2, L"Правка");

	//3 Меню
	AppendMenu(SubMenu3, MF_STRING, Properties, L"О программе");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu3, L"Справка");

	SetMenu(hWnd, RootMenu);

}

void MainWndAddWidgets(HWND hWnd) 
{
	hEditControl = CreateWindowA("edit","", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 5, 2, 480, 180, hWnd, NULL, NULL, NULL);
}

void SaveData(LPCSTR path)
{
	HANDLE FileToSave = CreateFileA(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	int saveLenth = GetWindowTextLength(hEditControl) + 1;
	char* data = new char[saveLenth];

	saveLenth = GetWindowTextA(hEditControl, data, saveLenth);

	DWORD bytesIterated;
	WriteFile(FileToSave, data, saveLenth, &bytesIterated, NULL);

	CloseHandle(FileToSave);
	delete[] data;

}

void LoadData(LPCSTR path)
{
	HANDLE FileToLoad = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD bytesIterated;
	ReadFile(FileToLoad, Buffer, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hEditControl, Buffer);

	CloseHandle(FileToLoad);
}

void SetOpenFileParams(HWND hWnd){

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = "*.txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "C:/s";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}
