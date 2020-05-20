#pragma once

class AFX_CLASS_EXPORT FileProcessWin
{
public:
	FileProcessWin(HWND hView, HWND hWnd);
	~FileProcessWin();

	BOOL Is_Show;
	void Show();
	void Hide();

	int GetWidth();
	int GetHeight();

	HWND GetHWND();
	void SetPosition(int x, int y);
	void Setparaent(HWND mother);
private:
	HWND m_hWnd;
	HWND m_hView;
	HWND hwndWPF;
private:
	static bool isCreate;
};

