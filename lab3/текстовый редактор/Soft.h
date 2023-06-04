#pragma once

#define OnOpenFile			1
#define OnSaveFile			2
#define OnSaveFileAs		3
#define OnExitSoftware		4
#define OnCopying			5
#define OnInserting			6
#define OnCutting			7
#define Properties			8

#define TextBufferSize		256

char Buffer[TextBufferSize];


HWND hEditControl;

char filename[260];
OPENFILENAMEA ofn;

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SetOpenFileParams(HWND hWnd);
void SaveData(LPCSTR path);
void LoadData(LPCSTR path);
