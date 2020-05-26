#pragma once
class AFX_CLASS_EXPORT InfoSetting
{
public:
	InfoSetting(HWND hView, HWND hWnd);
	~InfoSetting();

	void Show();

	int GetWidth();
	int GetHeight();

	HWND GetHWND();
private:
	HWND m_hWnd;
	HWND m_hView;
	HWND hwndWPF;
};

