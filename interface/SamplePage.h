#pragma once

class AFX_CLASS_EXPORT SamplePage
{
public:
	SamplePage(HWND hView, HWND hWnd);
	~SamplePage();

	void Show(BOOL _show);

	float GetTestValue();
	HWND m_hWnd;
	HWND m_hView;
};

