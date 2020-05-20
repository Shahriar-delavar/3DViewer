#pragma once

class AFX_CLASS_EXPORT RemoveTooth
{
public:
	RemoveTooth(HWND hView, HWND hWnd);
	~RemoveTooth();

	BOOL Is_Show;
	void Show();
	void Hide();

	int GetWidth();
	int GetHeight();

	HWND GetHWND();
	void SetPosition(int x, int y);
private:
	HWND m_hWnd;
	HWND m_hView;
	HWND hwndWPF;
};

