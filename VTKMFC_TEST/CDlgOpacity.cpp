// CDlgOpacity.cpp: 實作檔案
//

#include "stdafx.h"
#include "VTKMFC_TEST.h"
#include "CDlgOpacity.h"
#include "MainFrm.h"
#include "VTKMFC_TESTDoc.h"
#include "VTKMFC_TESTView.h"


// CDlgOpacity 對話方塊

IMPLEMENT_DYNAMIC(CDlgOpacity, CDialog)

CDlgOpacity::CDlgOpacity(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPACITY, pParent)
{
	opacity1_pos = 0;
	opacity2_pos = 0;
	color1_pos = 0;
	color2_pos = 0;
}

CDlgOpacity::~CDlgOpacity()
{
}

void CDlgOpacity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_EDIT_OPACITYVALUE1, m_opacity1);
	DDX_Control(pDX, IDC_EDIT_OPACITYVALUE2, m_opacity2);
	DDX_Control(pDX, IDC_EDIT_COLORVALUE1, m_color1);
	DDX_Control(pDX, IDC_EDIT_COLORVALUE2, m_color2);
	DDX_Control(pDX, IDC_SLIDER_OPA1, m_slider_opa1);
	DDX_Control(pDX, IDC_SLIDER_OPA2, m_silder_opa2);
	DDX_Control(pDX, IDC_SLIDER_COLOR1, m_silder_color1);
	DDX_Control(pDX, IDC_SLIDER_COLOR2, m_silder_color2);
}


BEGIN_MESSAGE_MAP(CDlgOpacity, CDialog)
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CDlgOpacity 訊息處理常式
BOOL CDlgOpacity::OnInitDialog()
{
	CDialog::OnInitDialog();
	//m_slider_opa1	
	m_slider_opa1.SetRangeMin(-1500, false);
	m_slider_opa1.SetRangeMax(1500, false);
	m_slider_opa1.SetPos(0);
	m_slider_opa1.SetLineSize(100);	
	m_slider_opa1.SetTicFreq(100);
	m_opacity1.SetWindowText(TEXT("0"));

	//m_slider_opa2
	m_silder_opa2.SetRangeMin(-1500, false);
	m_silder_opa2.SetRangeMax(1500, false);
	m_silder_opa2.SetPos(0);
	m_silder_opa2.SetLineSize(100);
	m_silder_opa2.SetTicFreq(100);
	m_opacity2.SetWindowText(TEXT("0"));

	//m_silder_color1	
	m_silder_color1.SetRangeMin(-1000, false);
	m_silder_color1.SetRangeMax(1000, false);
	m_silder_color1.SetPos(0);
	m_silder_color1.SetLineSize(100);
	m_silder_color1.SetTicFreq(100);
	m_color1.SetWindowText(TEXT("0"));

	//m_silder_color2
	m_silder_color2.SetRangeMin(-1000, false);
	m_silder_color2.SetRangeMax(1000, false);
	m_silder_color2.SetPos(0);
	m_silder_color2.SetLineSize(100);
	m_silder_color2.SetTicFreq(100);
	m_color2.SetWindowText(TEXT("0"));


	return TRUE;
}




void CDlgOpacity::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{	
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CVTKMFCTESTView* pView = (CVTKMFCTESTView*)pMainWnd->GetActiveView();

	////IDC_SLIDER_OPA1
	////CSliderCtrl	*pSlidCtrl_opa_1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_OPA1);
	////opacity1_pos = pSlidCtrl_opa_1->GetPos();
	//opacity1_pos = m_slider_opa1.GetPos();
	//pView->num_opacity1 = opacity1_pos;
	//pView->ChangeColorOpacityTeeth();
	////pView->ChangeOpacityTeeth();
	////pView->ChangeOpacitySkinTeeth();
	//TCHAR ptcTemp_opa1[10];	
	//wsprintf(ptcTemp_opa1, TEXT("%.d"), opacity1_pos);

	////CSliderCtrl	*pSlidCtrl_color_1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_COLOR1);
	////color1_pos = pSlidCtrl_color_1->GetPos();
	//opacity2_pos = m_silder_opa2.GetPos();
	//pView->num_opacity2 = opacity2_pos;
	//pView->ChangeColorOpacitySkin();
	//TCHAR ptcTemp_opa2[10];
	//wsprintf(ptcTemp_opa2, TEXT("%.d"), opacity2_pos);
	

	//marching cube
	color1_pos = m_silder_color1.GetPos();
	pView->num_color1 = color1_pos;
	pView->ChangeMarchingCube();
	TCHAR ptcTemp_color1[10];
	wsprintf(ptcTemp_color1, TEXT("%.d"), color1_pos);



	UpdateData(TRUE);
	//m_opacity1.SetWindowText(ptcTemp_opa1);
	//m_opacity2.SetWindowText(ptcTemp_opa2);
	m_color1.SetWindowText(ptcTemp_color1);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgOpacity::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
