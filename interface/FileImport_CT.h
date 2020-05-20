#pragma once
#include <string>
using namespace std;
class AFX_CLASS_EXPORT  FileImport_CT
{
public:
	FileImport_CT(HWND hView, HWND hWnd);
	~FileImport_CT();

	BOOL Is_Show;
	void Show();
	void Hide();

	int GetWidth();
	int GetHeight();

	HWND GetHWND();
	void SetPosition(int x, int y);

	string GetCTFolderPath();
private:
	HWND m_hWnd;
	HWND m_hView;
	HWND hwndWPF;
};

