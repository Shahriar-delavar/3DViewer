#pragma once


// CDlgOpacity 對話方塊

class CDlgOpacity : public CDialog
{
	DECLARE_DYNAMIC(CDlgOpacity)

public:
	CDlgOpacity(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~CDlgOpacity();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPACITY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	// opacity
	CSliderCtrl m_slider_opa1;
	CSliderCtrl m_silder_opa2;
	CSliderCtrl m_silder_color1;
	CSliderCtrl m_silder_color2;

	CEdit m_opacity1;
	CEdit m_opacity2;
	CEdit m_color1;
	CEdit m_color2;

public:
	virtual BOOL OnInitDialog();
	// SliderValue
	int opacity1_pos;
	int opacity2_pos;
	int color1_pos;
	int color2_pos;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
