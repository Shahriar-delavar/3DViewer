#pragma once
class AFX_CLASS_EXPORT ModelControl
{
public:
	ModelControl(HWND hView, HWND hWnd);
	~ModelControl();

	void Show();

	int GetWidth();
	int GetHeight();

	HWND GetHWND();
private:
	HWND m_hWnd;
	HWND m_hView;
	HWND hwndWPF;
};

