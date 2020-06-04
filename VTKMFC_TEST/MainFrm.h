
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "BtnFuncBar.h"
#include "FileProcessWin.h"
#include "RemoveTooth.h"
#include "AlignWin.h"
#include "ManualWin.h"
#include "FileImport_CT.h"
#include "FileImport_Upperjaw.h"
#include "FileImport_Lowerjaw.h"
#include "FileImport_3DFace.h"
#include "ExtractWin.h"
#include "InfoSetting.h"
#include "ShowObjControl.h"
#include "ModelControl.h"

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
	FileImport_Upperjaw *m_fileimportupperjaw = NULL;
	FileImport_Lowerjaw *m_fileimportlowerjaw = NULL;
	FileImport_3DFace *m_fileimport3dface = NULL;
	ExtractWin *m_extract = NULL;
	InfoSetting *m_infosetting = NULL;
	ShowObjControl *m_showobjcontrol = NULL;
	ModelControl *m_modelcontrol1 = NULL;

	void CreateWpfDialog();
	void SetWPFinterfacePos();

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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
};


