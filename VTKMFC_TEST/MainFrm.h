
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "BtnFuncBar.h"
#include "FileProcessWin.h"
#include "RemoveTooth.h"
#include "AlignWin.h"
#include "ManualWin.h"
#include "FileImport_CT.h"
#include "ExtractWin.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	HWND m_FileProcessHandle;
// Operations
public:
	BtnFuncBar *m_btnfunbar = NULL;
	FileProcessWin *m_fileprocesswin = NULL;
	RemoveTooth *m_removetooth = NULL;
	AlignWin *m_alignwin = NULL;
	ManualWin *m_manualwin = NULL;
	FileImport_CT *m_fileimportct = NULL;
	ExtractWin *m_extract = NULL;

	void CreateWpfDialog();

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP();

	//5/5/2020 handtan//mfc¤¶­±¥[title bar
public:
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void DrawTitleBar(CDC *pDC);
	CRect m_rtButtExit, m_rtIcon, m_rtButtMin, m_rtButtMax;
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
};


