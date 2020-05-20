#pragma once
class AFX_CLASS_EXPORT AlignWin
{
public:
	AlignWin(HWND hView, HWND hWnd);
	~AlignWin();

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

