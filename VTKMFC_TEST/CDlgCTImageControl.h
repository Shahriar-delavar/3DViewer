#pragma once


// CDlgCTImageControl 對話方塊

class CDlgCTImageControl : public CDialog
{
	DECLARE_DYNAMIC(CDlgCTImageControl)

public:
	CDlgCTImageControl(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~CDlgCTImageControl();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CTIMAGE_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// rx
	
	// rx
	CScrollBar m_scroll_rx;
	// ry
	CScrollBar m_scroll_ry;
	// rz
	CScrollBar m_scroll_rz;
	// tx
	CScrollBar m_scroll_tx;
	// ty
	CScrollBar m_scroll_ty;
	// tz
	CScrollBar m_scroll_tz;
	afx_msg void OnBnClickedButtonFace();
	afx_msg void OnBnClickedButtonSide();
	afx_msg void OnBnClickedButtonTop();
	BOOL m_check_align;
	afx_msg void OnBnClickedCheckLine();
};
