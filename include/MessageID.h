#ifndef __MESSAGEID_H__
#define __MESSAGEID_H__

#define	WM_WPFUI_BTNFUNCBAR					WM_USER+100
#define	WM_WPFUI_TEST						WM_USER +101
#define	WM_WPFUI_PROCESSBAR					WM_USER +102
#define	WM_WPFUI_FILEPROCESSWIN				WM_USER +103
#define	WM_WPFUI_WM_WPFUI_REMOVETOOTH		WM_USER +104
#define WM_WPFUI_ALIGN						WM_USER +105
#define WM_WPFUI_MANUALALIGN				WM_USER +106
#define WM_WPFUI_EXTRACT					WM_USER +107
#define WM_WPFUI_INFOSETTING				WM_USER +108
#define WM_WPFUI_SHOWSETTING				WM_USER +109
#define WM_WPFUI_MODELCONTROL				WM_USER +110


enum Extracttype
{
	extract_non,
	extract_sinus,
	extract_airway,
	extract_root,
	extract_bone
};

enum MainProcess
{
	Read_file,
	Model_align,
	Model_manual,
	Extract_feature,
	Save_file
};

enum InfoSettingtype
{
	non,
	show_info,
	show_setting
};

enum alignstype
{
	CT,
	UPPERJAW,
	LOWERJAW,
	UPPERJAW_CROWN,
	LOWERJAW_CROWN,
	FACE_2D,
	FACE_3D
};

enum ShowType
{
	SHOWDLG,
	HIDEDLG,
	VIEW_LEFT,
	VIEW_FRONT,
	VIEW_RIGHT,
	SHOW_3D,
	HIDE_3D,
	SHOW_INFOR,
	HIDE_INFOR,
	SHOW_GRID,
	HIDE_GRID,
	SHOW_COLORMAP,
	HIDE_COLORMAP,
	VOLUME_1,
	VOLUME_2,
	VOLUME_3,
	VOLUME_4,
	VOLUME_5,
	VOLUME_6,
	BUTTON_CT,
	BUTTON_UPPER,
	BUTTON_LOWER,
	BUTTON_CROWN,
	BUTTON_FACE
};

enum  ModelcontrolType
{
	MODEL_ROTATE_CLOCK,
	MODEL_ROTATE_COUNTERCLOCK,
	MODEL_MOVE_UP,
	MODEL_MOVE_DOWN,
	MODEL_MOVE_LEFT,
	MODEL_MOVE_RIGHT
};

// 2008/07/24 kenny, 執行Message queue裡面的東西,讓單執行緒的UI看起來不至於沒有回應
// 暫時的做法而已,多執行緒才是正確的做法
inline void DoEvents()
{
	CFrameWnd* pFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	pFrame->UpdateWindow();
	::MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}

inline LRESULT MSG_WpfUI_BtnFuncBar(WPARAM wParam, LPARAM lParam)
{
	CView *m_pView = (CView*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->CFrameWnd::GetActiveView();
	return m_pView->SendMessage(WM_WPFUI_BTNFUNCBAR, wParam, lParam);
}

inline LRESULT  MSG_WpfUI_TEST(WPARAM wParam, LPARAM lParam)
{
	CView *m_pView = (CView*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->CFrameWnd::GetActiveView();
	return m_pView->SendMessage(WM_WPFUI_TEST, wParam, lParam);
}

inline LRESULT  MSG_WpfUI_PROCESSBAR(WPARAM wParam, LPARAM lParam)
{
	CView *m_pView = (CView*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->CFrameWnd::GetActiveView();
	return m_pView->SendMessage(WM_WPFUI_PROCESSBAR, wParam, lParam);
}

#endif