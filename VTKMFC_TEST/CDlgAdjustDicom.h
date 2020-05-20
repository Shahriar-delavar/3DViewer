#pragma once

#include <vtkActor.h>
#include <vtkImageData.h>
#include <vtkActor2DCollection.h>
#include <vtkActor2D.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyData.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkOpenGLImageMapper.h>
#include <vtkLine.h>
#include <vtkDICOMImageReader.h>

// CDlgAdjustDicom 對話方塊

class CDlgAdjustDicom : public CDialog
{
	DECLARE_DYNAMIC(CDlgAdjustDicom)

public:
	CDlgAdjustDicom(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~CDlgAdjustDicom();

	vtkSmartPointer<vtkWin32OpenGLRenderWindow> m_RenderWinMain =
		vtkSmartPointer<vtkWin32OpenGLRenderWindow>::New();

	vtkRenderer *m_RendererMain1;
	void SetRendererMain1(vtkRenderer* Ren) { m_RendererMain1 = Ren; }
	vtkRenderer* GetRendererMain1() { return m_RendererMain1; }

	vtkRenderer *m_RendererMain2;
	void SetRendererMain2(vtkRenderer* Ren) { m_RendererMain2 = Ren; }
	vtkRenderer* GetRendererMain2() { return m_RendererMain2; }

	vtkRenderer *m_RendererMain3;
	void SetRendererMain3(vtkRenderer* Ren) { m_RendererMain3 = Ren; }
	vtkRenderer* GetRendererMain3() { return m_RendererMain3; }

	vtkSmartPointer<vtkWin32OpenGLRenderWindow> m_RenderWinMain1 =
		vtkSmartPointer<vtkWin32OpenGLRenderWindow>::New();
	vtkSmartPointer<vtkWin32OpenGLRenderWindow> m_RenderWinMain2 =
		vtkSmartPointer<vtkWin32OpenGLRenderWindow>::New();
	vtkSmartPointer<vtkWin32OpenGLRenderWindow> m_RenderWinMain3 =
		vtkSmartPointer<vtkWin32OpenGLRenderWindow>::New();

	void RenderMain1() { m_RenderWinMain1->Render(); }
	CArray<vtkActor2D*> m_ActorImageMain1;
	vtkActor2D* m_ActorOutline1[2];

	void RenderMain2() { m_RenderWinMain2->Render(); }
	CArray<vtkActor2D*> m_ActorImageMain2;
	vtkActor2D* m_ActorOutline2[2];

	void RenderMain3() { m_RenderWinMain3->Render(); }
	CArray<vtkActor2D*> m_ActorImageMain3;
	vtkActor2D* m_ActorOutline3[2];

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADJUST_DICOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void ShowAdjustDicom();

	void GenerateOutline1(vtkRenderer* Render, double Pt[4][3], int Index);
	void GenerateOutline2(vtkRenderer* Render, double Pt[4][3], int Index);
	void GenerateOutline3(vtkRenderer* Render, double Pt[4][3], int Index);

	void DeleteOutline1(vtkRenderer* Render);
	void DeleteOutline2(vtkRenderer* Render);
	void DeleteOutline3(vtkRenderer* Render);

public:
	void BuildImageMarkLine(double* markPt);
//	//draw line
//	void DrawCubeToAdjustDicom(vtkRenderer* ren);



public:
	///test
	void RenderFirstDicom();
	void RenderMiddleDicom();
	void RenderLastDicom();

	vtkSmartPointer<vtkDICOMImageReader> reader1 =
		vtkSmartPointer<vtkDICOMImageReader>::New();
	vtkSmartPointer<vtkDICOMImageReader> reader2 =
		vtkSmartPointer<vtkDICOMImageReader>::New();
	vtkSmartPointer<vtkDICOMImageReader> reader3 =
		vtkSmartPointer<vtkDICOMImageReader>::New();

	vtkSmartPointer<vtkImageData> data1 =
		vtkSmartPointer<vtkImageData>::New();
	vtkSmartPointer<vtkImageData> data2 =
		vtkSmartPointer<vtkImageData>::New();
	vtkSmartPointer<vtkImageData> data3 =
		vtkSmartPointer<vtkImageData>::New();
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	BOOL PreTranslateMessage(MSG *pMsg);

	CRect rect3;
};
