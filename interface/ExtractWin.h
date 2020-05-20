#pragma once
class AFX_CLASS_EXPORT ExtractWin
{
public:
	ExtractWin(HWND hView, HWND hWnd);
	~ExtractWin();

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

