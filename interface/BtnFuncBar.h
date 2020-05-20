#pragma once

class AFX_CLASS_EXPORT BtnFuncBar
{
public:
	BtnFuncBar(HWND hView, HWND hWnd);
	~BtnFuncBar();

	void Show();

	int GetWidth();
	int GetHeight();

	HWND GetHWND();
private:
	HWND m_hWnd;
	HWND m_hView;
	HWND hwndWPF;
	
};

