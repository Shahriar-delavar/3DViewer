// CDlgCTImageControl.cpp: 實作檔案
//

#include "stdafx.h"
#include "VTKMFC_TEST.h"
#include "CDlgCTImageControl.h"
#include "MainFrm.h"
#include "VTKMFC_TESTDoc.h"
#include "VTKMFC_TESTView.h"



// CDlgCTImageControl 對話方塊

IMPLEMENT_DYNAMIC(CDlgCTImageControl, CDialog)

CDlgCTImageControl::CDlgCTImageControl(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_CTIMAGE_CONTROL, pParent)
	, m_check_align(FALSE)
{

}

CDlgCTImageControl::~CDlgCTImageControl()
{
}

void CDlgCTImageControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR_RX, m_scroll_rx);
	DDX_Control(pDX, IDC_SCROLLBAR_RY, m_scroll_ry);
	DDX_Control(pDX, IDC_SCROLLBAR_RZ, m_scroll_rz);
	DDX_Control(pDX, IDC_SCROLLBAR_TX, m_scroll_tx);
	DDX_Control(pDX, IDC_SCROLLBAR_TY, m_scroll_ty);
	DDX_Control(pDX, IDC_SCROLLBAR_TZ, m_scroll_tz);
	DDX_Check(pDX, IDC_CHECK_LINE, m_check_align);
}


BEGIN_MESSAGE_MAP(CDlgCTImageControl, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_FACE, &CDlgCTImageControl::OnBnClickedButtonFace)
	ON_BN_CLICKED(IDC_BUTTON_SIDE, &CDlgCTImageControl::OnBnClickedButtonSide)
	ON_BN_CLICKED(IDC_BUTTON_TOP, &CDlgCTImageControl::OnBnClickedButtonTop)
	ON_BN_CLICKED(IDC_CHECK_LINE, &CDlgCTImageControl::OnBnClickedCheckLine)
END_MESSAGE_MAP()


// CDlgCTImageControl 訊息處理常式

BOOL CDlgCTImageControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	//setting
	m_scroll_rx.SetScrollRange(-900, 900);
	m_scroll_rx.SetScrollPos(0);
	m_scroll_ry.SetScrollRange(-900, 900);
	m_scroll_ry.SetScrollPos(0);
	m_scroll_rz.SetScrollRange(-900, 900);
	m_scroll_rz.SetScrollPos(0);
	m_scroll_tx.SetScrollRange(-900, 900);
	m_scroll_tx.SetScrollPos(0);
	m_scroll_ty.SetScrollRange(-900, 900);
	m_scroll_ty.SetScrollPos(0);
	m_scroll_tz.SetScrollRange(-900, 900);
	m_scroll_tz.SetScrollPos(0);
	SetDlgItemText(IDC_EDIT_RX, L"0.0");
	SetDlgItemText(IDC_EDIT_RY, L"0.0");
	SetDlgItemText(IDC_EDIT_RZ, L"0.0");
	SetDlgItemText(IDC_EDIT_TX, L"0.0");
	SetDlgItemText(IDC_EDIT_TY, L"0.0");
	SetDlgItemText(IDC_EDIT_TZ, L"0.0");


	return TRUE;
}

void CDlgCTImageControl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//Get Wnd
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CVTKMFCTESTView* pView = (CVTKMFCTESTView*)pMainWnd->GetActiveView();

	//rotation degree
	float r_line = 0.1;
	float r_page = 1.0;

	//save
	int i_nowrx = 0;
	int i_nowry = 0;
	int i_nowrz = 0;

	int rx_pos = m_scroll_rx.GetScrollPos();
	int ry_pos = m_scroll_ry.GetScrollPos();
	int rz_pos = m_scroll_rz.GetScrollPos();
	int tx_pos = m_scroll_tx.GetScrollPos();
	int ty_pos = m_scroll_ty.GetScrollPos();
	int tz_pos = m_scroll_tz.GetScrollPos();

	CWnd *pSliderRx = GetDlgItem(IDC_SCROLLBAR_RX);
	CWnd *pSliderRy = GetDlgItem(IDC_SCROLLBAR_RY);
	CWnd *pSliderRz = GetDlgItem(IDC_SCROLLBAR_RZ);
	CWnd *pSliderTx = GetDlgItem(IDC_SCROLLBAR_TX);
	CWnd *pSliderTy = GetDlgItem(IDC_SCROLLBAR_TY);
	CWnd *pSliderTz = GetDlgItem(IDC_SCROLLBAR_TZ);
	switch (nSBCode)
	{
	//left 一格
	case SB_LINELEFT:
	{
		if (pScrollBar == pSliderRx)
		{ 			
			rx_pos -= 1;
			pView->ReOriRotationX(-r_line);
			i_nowrx = rx_pos;
		}			
		else if (pScrollBar == pSliderRy)
		{
			ry_pos -= 1;
			pView->ReOriRotationY(-r_line);
			i_nowry = ry_pos;
		}
		else if (pScrollBar == pSliderRz)
		{
			rz_pos -= 1;
			pView->ReOriRotationZ(-r_line);
			i_nowrz = rz_pos;
		}
		else if (pScrollBar == pSliderTx)
			tx_pos -= 1;
		else if (pScrollBar == pSliderTy)
			ty_pos -= 1;
		else 
			tz_pos -= 1;
	}		
		break;
	//right 一格
	case SB_LINERIGHT:
	{
		if (pScrollBar == pSliderRx)
		{
			rx_pos += 1;
			pView->ReOriRotationX(r_line);
			i_nowrx = rx_pos;
		}			
		else if (pScrollBar == pSliderRy)
		{
			ry_pos += 1;
			pView->ReOriRotationY(r_line);
			i_nowry = ry_pos;
		}
		else if (pScrollBar == pSliderRz)
		{
			rz_pos += 1;
			pView->ReOriRotationZ(r_line);
			i_nowrz = rz_pos;
		}
		else if (pScrollBar == pSliderTx)
			tx_pos += 1;
		else if (pScrollBar == pSliderTy)
			ty_pos += 1;
		else
			tz_pos += 1;
	}
		break;
	//left 一頁
	case SB_PAGELEFT:
	{
		if (pScrollBar == pSliderRx)
		{
			rx_pos -= 10;
			pView->ReOriRotationX(-r_page);
			i_nowrx = rx_pos;
		}
		else if (pScrollBar == pSliderRy)
		{
			ry_pos -= 10;
			pView->ReOriRotationY(-r_page);
			i_nowry = ry_pos;
		}
		else if (pScrollBar == pSliderRz)
		{
			rz_pos -= 10;
			pView->ReOriRotationZ(-r_page);
			i_nowrz = rz_pos;

		}
		else if (pScrollBar == pSliderTx)
			tx_pos -= 10;
		else if (pScrollBar == pSliderTy)
			ty_pos -= 10;
		else
			tz_pos -= 10;
	}
	break;
	//right 一頁
	case SB_PAGERIGHT:
	{
		if (pScrollBar == pSliderRx)
		{
			rx_pos += 10;
			pView->ReOriRotationX(r_page);
			i_nowrx = rx_pos;
		}
		else if (pScrollBar == pSliderRy)
		{
			ry_pos += 10;
			pView->ReOriRotationY(r_page);
			i_nowry = ry_pos;
		}
		else if (pScrollBar == pSliderRz)
		{
			rz_pos += 10;
			pView->ReOriRotationZ(r_page);
			i_nowrz = rz_pos;
		}
		else if (pScrollBar == pSliderTx)
			tx_pos += 10;
		else if (pScrollBar == pSliderTy)
			ty_pos += 10;
		else
			tz_pos += 10;
	}
	break;
	//指定位置
	case SB_THUMBPOSITION:
	{
		if (pScrollBar == pSliderRx)
		{
			rx_pos = nPos;
			pView->ReOriRotationX((float)(rx_pos - i_nowrx) / 10.0);
			i_nowrx = rx_pos;
		}			
		else if (pScrollBar == pSliderRy)
		{
			ry_pos = nPos;
			pView->ReOriRotationY((float)(ry_pos - i_nowry) / 10.0);
			i_nowry = ry_pos;
		}
		else if (pScrollBar == pSliderRz)
		{
			rz_pos = nPos;
			pView->ReOriRotationZ((float)(rz_pos - i_nowrz) / 10.0);
			i_nowrz = rz_pos;
		}
		else if (pScrollBar == pSliderTx)
			tx_pos = nPos;
		else if (pScrollBar == pSliderTy)
			ty_pos = nPos;
		else
			tz_pos = nPos;
	}
	break;
	default:
	{
		CString posrx;
		posrx.Format(L"%.1f", (float)rx_pos / 10.0);
		CString posry;
		posry.Format(L"%.1f", (float)ry_pos / 10.0);
		CString posrz;
		posrz.Format(L"%.1f", (float)rz_pos / 10.0);
		CString postx;
		postx.Format(L"%.1f", (float)tx_pos / 10.0);
		CString posty;
		posty.Format(L"%.1f", (float)ty_pos / 10.0);
		CString postz;
		postz.Format(L"%.1f", (float)tz_pos / 10.0);

		SetDlgItemText(IDC_EDIT_RX, posrx);
		SetDlgItemText(IDC_EDIT_RY, posry);
		SetDlgItemText(IDC_EDIT_RZ, posrz);
		SetDlgItemText(IDC_EDIT_TX, postx);
		SetDlgItemText(IDC_EDIT_TY, posty);
		SetDlgItemText(IDC_EDIT_TZ, postz);
	}

	}

	m_scroll_rx.SetScrollPos(rx_pos);
	m_scroll_ry.SetScrollPos(ry_pos);
	m_scroll_rz.SetScrollPos(rz_pos);
	m_scroll_tx.SetScrollPos(tx_pos);
	m_scroll_ty.SetScrollPos(ty_pos);
	m_scroll_tz.SetScrollPos(tz_pos);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgCTImageControl::OnBnClickedButtonFace()
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CVTKMFCTESTView* pView = (CVTKMFCTESTView*)pMainWnd->GetActiveView();
	pView->SetCameraFace();
	pView->pvtkReOriVolumeRenderer->GetRenderWindow()->Render();
}


void CDlgCTImageControl::OnBnClickedButtonSide()
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CVTKMFCTESTView* pView = (CVTKMFCTESTView*)pMainWnd->GetActiveView();
	pView->SetCameraSide();
	pView->pvtkReOriVolumeRenderer->GetRenderWindow()->Render();
}


void CDlgCTImageControl::OnBnClickedButtonTop()
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CVTKMFCTESTView* pView = (CVTKMFCTESTView*)pMainWnd->GetActiveView();
	pView->SetCameraTop();
	pView->pvtkReOriVolumeRenderer->GetRenderWindow()->Render();
}


void CDlgCTImageControl::OnBnClickedCheckLine()
{
	UpdateData(TRUE);
	if (m_check_align)
	{
		CMainFrame* pMainWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CVTKMFCTESTView* pView = (CVTKMFCTESTView*)pMainWnd->GetActiveView();
		pView->lineActorX->VisibilityOn();
		pView->lineActorY->VisibilityOn();
		pView->lineActorZ->VisibilityOn();
		pView->pvtkReOriVolumeRenderer->GetRenderWindow()->Render();
	}
	else
	{
		CMainFrame* pMainWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CVTKMFCTESTView* pView = (CVTKMFCTESTView*)pMainWnd->GetActiveView();
		pView->lineActorX->VisibilityOff();
		pView->lineActorY->VisibilityOff();
		pView->lineActorZ->VisibilityOff();
		pView->pvtkReOriVolumeRenderer->GetRenderWindow()->Render();
		
	}
}
