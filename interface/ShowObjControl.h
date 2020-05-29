#pragma once
class AFX_CLASS_EXPORT ShowObjControl
{
public:
	ShowObjControl(HWND hView, HWND hWnd);
	~ShowObjControl();

	void Show();

	int GetWidth();
	int GetHeight();

	HWND GetHWND();
private:
	HWND m_hWnd;
	HWND m_hView;
	HWND hwndWPF;
};

