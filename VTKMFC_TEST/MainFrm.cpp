
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VTKMFC_TEST.h"

#include "MainFrm.h"
#include "BtnFuncBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//5/5/2020 handtan//mfc介面加title bar
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCMOUSEMOVE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	m_FileProcessHandle = nullptr;
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("Failed to create toolbar\n");
	//	return -1;      // fail to create
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("Failed to create status bar\n");
	//	return -1;      // fail to create
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//// TODO: Delete these three lines if you don't want the toolbar to be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	//BtnFuncBar *b = new BtnFuncBar(this, m_hWnd);
	//b->Show();

	ModifyStyle(WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, 0, 0);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

//5/5/2020 handtan//mfc介面加title bar
void CMainFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: Add your message handler code here and/or call default
	lpncsp->rgrc[0].top += 40;

	CFrameWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}

LRESULT CMainFrame::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	RECT rectWindows, rectClient;
	this->GetWindowRect(&rectWindows);
	this->GetClientRect(&rectClient);

	if (point.y > rectWindows.top && point.y <= rectWindows.top + 41)
	{
		return HTCAPTION;
	}
	else
	{
		return CFrameWnd::OnNcHitTest(point);
	}
}

void CMainFrame::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	bool doClose = false;
	if (m_rtButtExit.PtInRect(point))
	{
		doClose = true;
	}
	else if (m_rtButtMax.PtInRect(point))
	{
		if (IsZoomed())
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
		else
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y));
			Invalidate();
		}
	}
	else if (m_rtButtMin.PtInRect(point))
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y));
	}
	else if (!IsZoomed())
		Default();

	CFrameWnd::OnNcLButtonDown(nHitTest, point);

	if (doClose)
		SendMessage(WM_CLOSE);
}

LRESULT CMainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	LRESULT lrst = CFrameWnd::DefWindowProc(message, wParam, lParam);
	if (!::IsWindow(m_hWnd))
		return lrst;

	if (message == WM_MOVE
		|| message == WM_PAINT
		|| message == WM_NCPAINT
		|| message == WM_NCACTIVATE
		|| message == WM_NOTIFY)
	{
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}

	return lrst;
}

void CMainFrame::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC = GetWindowDC();
	CDC* pDisplayMemDC = new CDC;
	pDisplayMemDC->CreateCompatibleDC(pDC);
	CBitmap* pBitmap = new CBitmap;
	CBitmap* pOldBitmap;
	CRect rtWnd, rtButton;

	if (pDC)
	{
		GetWindowRect(&rtWnd);

		m_rtButtExit.bottom -= 5;
		if (m_rtButtExit.PtInRect(point))
			pBitmap->LoadBitmap(IDB_CLOSE_FOCUS);
		else
			pBitmap->LoadBitmap(IDB_CLOSE_NORMAL);
		m_rtButtExit.bottom += 5;
		rtButton = m_rtButtExit;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		m_rtButtMin.bottom -= 5;
		if (m_rtButtMin.PtInRect(point))
			pBitmap->LoadBitmap(IDB_MIN_FOCUS);
		else
			pBitmap->LoadBitmap(IDB_MIN_NORMAL);
		m_rtButtMin.bottom += 5;
		rtButton = m_rtButtMin;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		m_rtButtMax.bottom -= 5;
		if (IsZoomed())
		{
			if (m_rtButtMax.PtInRect(point))
				pBitmap->LoadBitmap(IDB_RESTORE_FOCUS);
			else
				pBitmap->LoadBitmap(IDB_RESTORE_NORMAL);
		}
		else
		{
			if (m_rtButtMax.PtInRect(point))
				pBitmap->LoadBitmap(IDB_MAX_FOCUS);
			else
				pBitmap->LoadBitmap(IDB_MAX_NORMAL);
		}
		m_rtButtMax.bottom += 5;
		rtButton = m_rtButtMax;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
	}

	ReleaseDC(pDisplayMemDC);
	ReleaseDC(pDC);
	delete pDisplayMemDC;
	delete pBitmap;

	CFrameWnd::OnNcMouseMove(nHitTest, point);
}

void CMainFrame::DrawTitleBar(CDC *pDC)
{
	if (m_hWnd)
	{
		CBrush Brush(RGB(224, 138, 30));
		CBrush* pOldBrush = pDC->SelectObject(&Brush);

		CRect rtWnd, rtTitle, rtButtons;
		GetWindowRect(&rtWnd);

		rtTitle.left = 0;
		rtTitle.top = 0;
		rtTitle.right = rtWnd.right - rtWnd.left;
		rtTitle.bottom = 40;

		CPoint point;

		point.x = rtWnd.Width();
		point.y = 41;
		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);

		pDC->SelectObject(pOldBrush);

		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC = new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);

		//draw clost button
		pBitmap->LoadBitmap(IDB_CLOSE_NORMAL);
		rtButtons.left = rtTitle.right - 46;
		rtButtons.top = rtTitle.top;
		rtButtons.right = rtButtons.left + 46;
		rtButtons.bottom = rtButtons.top + 40;
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		m_rtButtExit = rtButtons;
		m_rtButtExit.OffsetRect(rtWnd.TopLeft());

		//draw max/restore button
		if (IsZoomed())
		{
			pBitmap->LoadBitmap(IDB_RESTORE_NORMAL);
			rtButtons.left = rtTitle.right - 92;
			rtButtons.top = rtTitle.top;
			rtButtons.right = rtButtons.left + 46;
			rtButtons.bottom = rtButtons.top + 40;
			pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
			pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
			pDisplayMemDC->SelectObject(pOldBitmap);
			pBitmap->DeleteObject();
		}
		else
		{
			pBitmap->LoadBitmap(IDB_MAX_NORMAL);
			rtButtons.left = rtTitle.right - 92;
			rtButtons.top = rtTitle.top;
			rtButtons.right = rtButtons.left + 46;
			rtButtons.bottom = rtButtons.top + 40;
			pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
			pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
			pDisplayMemDC->SelectObject(pOldBitmap);
			pBitmap->DeleteObject();
		}

		m_rtButtMax = rtButtons;
		m_rtButtMax.OffsetRect(rtWnd.TopLeft());

		//draw min
		pBitmap->LoadBitmap(IDB_MIN_NORMAL);
		rtButtons.left = rtTitle.right - 138;
		rtButtons.top = rtTitle.top;
		rtButtons.right = rtButtons.left + 46;
		rtButtons.bottom = rtButtons.top + 40;
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		m_rtButtMin = rtButtons;
		m_rtButtMin.OffsetRect(rtWnd.TopLeft());

		point.x = 250;
		point.y = 40;
		pBitmap->LoadBitmap(IDB_TITLE);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(16, 0, point.x, point.y, pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		COLORREF clOldText = pDC->SetTextColor(RGB(255, 255, 255));
		NONCLIENTMETRICS ncm;
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
		CFont m_captionTextFont;
		ncm.lfCaptionFont.lfHeight -= 2;
		_tcsncpy_s(ncm.lfCaptionFont.lfFaceName, LF_FACESIZE, _T("Arial"), 7);
		m_captionTextFont.CreateFontIndirect(&ncm.lfCaptionFont);
		pDC->SelectObject(&m_captionTextFont);
		CString m_strTitle;
		GetWindowText(m_strTitle);
		m_strTitle.Replace(_T("Inteware Root Extraction"), _T(""));

		//CSafeImplantDoc* pDoc = (CSafeImplantDoc*)GetActiveDocument();
		//CString softwarename = pDoc->m_ProjectDefine.GetSoftwareName() + _T(" v") 
		//	+ pDoc->m_ProjectDefine.GetVersionText() + pDoc->m_ProjectDefine.GetVersionText2() + _T(" ") + pDoc->m_ProjectDefine.GetModuleName();

		m_strTitle = _T("");
		rtTitle.top += 14;
		rtTitle.left += (214 + 40);
		pDC->DrawText(m_strTitle, &rtTitle, DT_LEFT);
		pDC->SetBkMode(nOldMode);
		pDC->SetTextColor(clOldText);

		ReleaseDC(pDisplayMemDC);
		delete pDisplayMemDC;
		delete pBitmap;
	}
}

void CMainFrame::CreateWpfDialog()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if (m_btnfunbar == NULL)
	{
		m_btnfunbar = new BtnFuncBar(GetActiveView()->GetSafeHwnd(), m_hWnd);

		CRect nowSizeClient;
		GetClientRect(nowSizeClient);
		
		int mid_x = (nowSizeClient.left + nowSizeClient.right) / 2 - m_btnfunbar->GetWidth() / 2;
		::SetWindowPos(m_btnfunbar->GetHWND(), NULL, mid_x, 50, m_btnfunbar->GetWidth(), m_btnfunbar->GetHeight(), NULL);
		::ShowWindow(m_btnfunbar->GetHWND(), SW_SHOW);
	}

	if (m_fileprocesswin == NULL)
	{
		//CRect nowSizeClient;
		//GetClientRect(nowSizeClient);

		//int min_x = 0;
		//int min_y = 0;

		//CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		m_fileprocesswin = new FileProcessWin(GetActiveView()->GetSafeHwnd(), pFrame->m_hWnd);
		//m_fileprocesswin->SetPosition(min_y, min_x);
	}

	if (m_removetooth == NULL)
	{
		//CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		m_removetooth = new RemoveTooth(GetActiveView()->GetSafeHwnd(), pFrame->m_hWnd);
	}

	if (m_alignwin == NULL)
	{
		//CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		m_alignwin = new AlignWin(GetActiveView()->GetSafeHwnd(), pFrame->m_hWnd);
	}

	if (m_manualwin == NULL)
	{
		//CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		m_manualwin = new ManualWin(GetActiveView()->GetSafeHwnd(), pFrame->m_hWnd);
	}

	if (m_extract == NULL)
	{
		//CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		m_extract = new ExtractWin(GetActiveView()->GetSafeHwnd(), pFrame->m_hWnd);
	}

	if (m_fileimportct == NULL)
	{
		m_fileimportct = new FileImport_CT(GetActiveView()->GetSafeHwnd(), pFrame->m_hWnd);
	}
}