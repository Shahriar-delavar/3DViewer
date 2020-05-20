// CDlgAdjustDicom.cpp: 實作檔案
//

#include "stdafx.h"
#include "VTKMFC_TEST.h"
#include "CDlgAdjustDicom.h"
#include "MainFrm.h"
#include "VTKMFC_TESTDoc.h"
#include "VTKMFC_TESTView.h"
#include <vtkPropPicker.h>

// Handle mouse events
class PropPickerInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static PropPickerInteractorStyle* New();
	vtkTypeMacro(PropPickerInteractorStyle, vtkInteractorStyleTrackballCamera);

	PropPickerInteractorStyle()
	{
		LastPickedActor = NULL;
		LastPickedProperty = vtkProperty::New();
	}
	virtual ~PropPickerInteractorStyle()
	{
		LastPickedProperty->Delete();
	}
	virtual void OnLeftButtonDown()
	{
		CDlgAdjustDicom* dlg = new CDlgAdjustDicom();
		int* clickPos = this->GetInteractor()->GetEventPosition();

		// Pick from this location.
		vtkSmartPointer<vtkPropPicker>  picker =
			vtkSmartPointer<vtkPropPicker>::New();
		//picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
		picker->Pick(clickPos[0], clickPos[1], 0, dlg->m_RendererMain3);

		double* pos = picker->GetPickPosition();
		// If we picked something before, reset its property
		if (this->LastPickedActor)
		{
			this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);
		}
		this->LastPickedActor = picker->GetActor();
		if (this->LastPickedActor)
		{
			// Save the property of the picked actor so that we can restore it next time
			this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());
			// Highlight the picked actor by changing its properties
			this->LastPickedActor->GetProperty()->SetColor(0.0, 1.0, 0.0);
			this->LastPickedActor->GetProperty()->SetDiffuse(1.0);
			this->LastPickedActor->GetProperty()->SetSpecular(0.0);
		}

		// Forward events
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}

private:
	vtkActor    *LastPickedActor;
	vtkProperty *LastPickedProperty;
};

vtkStandardNewMacro(PropPickerInteractorStyle);


// CDlgAdjustDicom 對話方塊

IMPLEMENT_DYNAMIC(CDlgAdjustDicom, CDialog)

CDlgAdjustDicom::CDlgAdjustDicom(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ADJUST_DICOM, pParent)
{
	//for (int i = 0; i < 2; i++)
	//	m_ActorOutline1[i] = NULL;
	for (int i = 0; i < 2; i++)
		m_ActorOutline2[i] = NULL;
	/*for (int i = 0; i < 2; i++)
		m_ActorOutline3[i] = NULL;*/
	m_RendererMain1 = NULL;
	m_RendererMain1 = vtkRenderer::New();

	m_RendererMain2 = NULL;
	m_RendererMain2 = vtkRenderer::New();

	m_RendererMain3 = NULL;
	m_RendererMain3 = vtkRenderer::New();
}

CDlgAdjustDicom::~CDlgAdjustDicom()
{
}

void CDlgAdjustDicom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAdjustDicom, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgAdjustDicom 訊息處理常式
BOOL CDlgAdjustDicom::OnInitDialog()
{
	CDialog::OnInitDialog();
	//ShowAdjustDicom();
	//TestAdjustDicom();
	RenderFirstDicom();
	RenderMiddleDicom();
	RenderLastDicom();
	return TRUE;
}


void CDlgAdjustDicom::RenderFirstDicom()
{
	//dicom data
	reader1->SetFileName("D://case2//I0000000002.dcm");
	reader1->Update();
	data1->DeepCopy(reader1->GetOutput());

	//set dlg
	CRect dlgSize;
	GetDlgItem(IDC_PIC_PREVIEW_FIRST)->GetWindowRect(dlgSize);

	//set renderwin
	int ren_size[2] = { dlgSize.Width(), dlgSize.Height() };
	m_RenderWinMain1->SetSize(ren_size);
	m_RenderWinMain1->SetParentId(GetDlgItem(IDC_PIC_PREVIEW_FIRST)->GetSafeHwnd());

	//set Render 
	vtkRenderer *ren = vtkRenderer::New();
	m_RenderWinMain1->AddRenderer(ren);
	SetRendererMain1(ren);
	ren->Delete();

	GetRendererMain1()->SetBackground(0, 0, 0);
	GetRendererMain1()->SetBackground2(0, 0, 0);

	//Set Outline
	double pt[4][3] = { {0.0,				   0.0,				   0},
						{0.0,				  (double)ren_size[1], 0},
						{(double)ren_size[0], (double)ren_size[1], 0},
						{(double)ren_size[0], 0.0,				   0} };



	GenerateOutline1(GetRendererMain1(), pt, 0);

	int DataExtent[6] = { -1,-1,-1,-1,-1,-1 };
	data1->GetExtent(DataExtent);

	// Image
	vtkOpenGLImageMapper* mapper = vtkOpenGLImageMapper::New();
	mapper->SetInputData(data1);
	mapper->RenderToRectangleOn();
	mapper->UseCustomExtentsOn();
	mapper->SetCustomDisplayExtents(DataExtent);
	mapper->SetZSlice(0);
	mapper->SetColorLevel(500);


	double width = GetRendererMain1()->GetSize()[0];
	double height = GetRendererMain1()->GetSize()[1];

	double scaleX = width / DataExtent[1];
	double scaleY = height / DataExtent[3];

	double scale = scaleX * 0.95;

	//double Pos[2] = { ( width + (width - DataExtent2[1] * scale) / 2.0),0 };

	double sizeX = scale * DataExtent[1] / (width);
	double sizeY = scale * DataExtent[3] / (height);

	vtkActor2D *act2d = vtkActor2D::New();
	double Pos[2] = { 5.0,10.0 };
	act2d->SetPosition(Pos);
	act2d->SetPosition2(sizeX, sizeY);
	act2d->SetMapper(mapper);
	

	GetRendererMain1()->AddActor2D(act2d);

	act2d->Delete();
	mapper->Delete();
	data1->Delete();

	RenderMain1();
	
}
void CDlgAdjustDicom::RenderMiddleDicom()
{
	//dicom data
	reader2->SetFileName("D://case2//I0000000333.dcm");	
	reader2->Update();
	data2->DeepCopy(reader2->GetOutput());

	//set dlg
	CRect dlgSize;
	GetDlgItem(IDC_PIC_PREVIEW_MIDDLE)->GetWindowRect(dlgSize);

	//set renderwin
	int ren_size[2] = { dlgSize.Width(), dlgSize.Height() };
	m_RenderWinMain2->SetSize(ren_size);
	m_RenderWinMain2->SetParentId(GetDlgItem(IDC_PIC_PREVIEW_MIDDLE)->GetSafeHwnd());

	//set Render 
	vtkRenderer *ren = vtkRenderer::New();
	m_RenderWinMain2->AddRenderer(ren);
	SetRendererMain2(ren);
	ren->Delete();

	GetRendererMain2()->SetBackground(0, 0, 0);
	GetRendererMain2()->SetBackground2(0, 0, 0);

	//Set Outline
	double pt[4][3] = { {0.0,				   0.0,				   0},
						{0.0,				  (double)ren_size[1], 0},
						{(double)ren_size[0], (double)ren_size[1], 0},
						{(double)ren_size[0], 0.0,				   0} };



	GenerateOutline2(GetRendererMain2(), pt, 0);

	int DataExtent[6] = { -1,-1,-1,-1,-1,-1 };
	data2->GetExtent(DataExtent);

	// Image
	vtkOpenGLImageMapper* mapper = vtkOpenGLImageMapper::New();
	mapper->SetInputData(data2);
	mapper->RenderToRectangleOn();
	mapper->UseCustomExtentsOn();
	mapper->SetCustomDisplayExtents(DataExtent);
	mapper->SetZSlice(0);
	mapper->SetColorLevel(500);
	

	double width = GetRendererMain2()->GetSize()[0];
	double height = GetRendererMain2()->GetSize()[1];

	double scaleX = width / DataExtent[1];
	double scaleY = height / DataExtent[3];

	double scale = scaleX * 0.95;

	//double Pos[2] = { ( width + (width - DataExtent2[1] * scale) / 2.0),0 };

	double sizeX = scale * DataExtent[1] / (width);
	double sizeY = scale * DataExtent[3] / (height);

	vtkActor2D *act2d = vtkActor2D::New();
	double Pos[2] = { 5.0,10.0 };
	act2d->SetPosition(Pos);
	act2d->SetPosition2(sizeX, sizeY);
	act2d->SetMapper(mapper);	

	GetRendererMain2()->AddActor2D(act2d);

	act2d->Delete();
	mapper->Delete();
	data2->Delete();
	
	RenderMain2();
}
void CDlgAdjustDicom::RenderLastDicom()
{
	//dicom data
	reader3->SetFileName("D://case2//I0000000665.dcm");	
	reader3->Update();
	data3->DeepCopy(reader3->GetOutput());

	//set dlg
	CRect dlgSize;
	GetDlgItem(IDC_PIC_PREVIEW_LAST)->GetWindowRect(dlgSize);

	//test
	GetDlgItem(IDC_PIC_PREVIEW_LAST)->GetWindowRect(rect3);
	

	//set renderwin
	int ren_size[2] = { dlgSize.Width(), dlgSize.Height() };
	m_RenderWinMain3->SetSize(ren_size);
	m_RenderWinMain3->SetParentId(GetDlgItem(IDC_PIC_PREVIEW_LAST)->GetSafeHwnd());

	//set Render 
	vtkRenderer *ren = vtkRenderer::New();
	m_RenderWinMain3->AddRenderer(ren);
	SetRendererMain3(ren);
	ren->Delete();

	GetRendererMain3()->SetBackground(0, 0, 0);
	GetRendererMain3()->SetBackground2(0, 0, 0);

	//Set Outline
	double pt[4][3] = { {0.0,				   0.0,				   0},
						{0.0,				  (double)ren_size[1], 0},
						{(double)ren_size[0], (double)ren_size[1], 0},
						{(double)ren_size[0], 0.0,				   0} };

	GenerateOutline3(GetRendererMain3(), pt, 0);

	int DataExtent[6] = { -1,-1,-1,-1,-1,-1 };
	data3->GetExtent(DataExtent);

	// Image
	vtkOpenGLImageMapper* mapper = vtkOpenGLImageMapper::New();
	mapper->SetInputData(data3);
	mapper->RenderToRectangleOn();
	mapper->UseCustomExtentsOn();
	mapper->SetCustomDisplayExtents(DataExtent);
	mapper->SetZSlice(0);
	mapper->SetColorLevel(500);	


	double width = GetRendererMain3()->GetSize()[0];
	double height = GetRendererMain3()->GetSize()[1];

	double scaleX = width / DataExtent[1];
	double scaleY = height / DataExtent[3];

	double scale = scaleX * 0.95;

	//double Pos[2] = { ( width + (width - DataExtent2[1] * scale) / 2.0),0 };

	double sizeX = scale * DataExtent[1] / (width);
	double sizeY = scale * DataExtent[3] / (height);

	vtkActor2D *act2d = vtkActor2D::New();
	double Pos[2] = { 5.0,10.0 };
	act2d->SetPosition(Pos);
	act2d->SetPosition2(sizeX, sizeY);
	act2d->SetMapper(mapper);

	GetRendererMain3()->AddActor2D(act2d);

	act2d->Delete();
	mapper->Delete();
	data3->Delete();

	RenderMain3();
}


void CDlgAdjustDicom::ShowAdjustDicom()
{

	//Create Canvas
	//////////////////////////////////////////////////////////////////////////////////////
	//CRect dlgSize1;
	//GetDlgItem(IDC_PIC_PREVIEW_FIRST)->GetWindowRect(dlgSize1);
	//int ren_size1[2] = { dlgSize1.Width(), dlgSize1.Height() };

	//// setup the parent window
	//m_RenderWinMain1->SetSize(ren_size1);
	//m_RenderWinMain1->SetParentId(GetDlgItem(IDC_PIC_PREVIEW_FIRST)->GetSafeHwnd());

	////Set Render 
	//vtkRenderer *ren1 = vtkRenderer::New();
	//m_RenderWinMain1->AddRenderer(ren1);
	//SetRendererMain1(ren1);
	//ren1->Delete();

	//GetRendererMain1()->SetBackground(0, 0, 0);
	//GetRendererMain1()->SetBackground2(0, 0, 0);

	////Set Outline
	//double pt1[4][3] = { {0.0,				   0.0,				   0},
	//					{0.0,				  (double)ren_size1[1], 0},
	//					{(double)ren_size1[0], (double)ren_size1[1], 0},
	//					{(double)ren_size1[0], 0.0,				   0} };



	//GenerateOutline(GetRendererMain1(), pt1, -1);

	//int DataExtent1[6] = { -1,-1,-1,-1,-1,-1 };
	//data1->GetExtent(DataExtent1);
	//// Image
	//vtkOpenGLImageMapper* mapper1 = vtkOpenGLImageMapper::New();
	//mapper1->SetInputData(data1);
	//mapper1->RenderToRectangleOn();
	//mapper1->UseCustomExtentsOn();
	//mapper1->SetCustomDisplayExtents(DataExtent1);
	//mapper1->SetZSlice(0);

	////double width = GetRendererMain()->GetSize()[0];
	////double height = GetRendererMain()->GetSize()[1];

	////double scaleX = width / DataExtent[1];
	////double scaleY = height / DataExtent[3];

	////double scale = scaleX * 0.95;

	////double Pos[2] = { ( width + (width - DataExtent[1] * scale) / 2.0),0 };

	////double sizeX = scale * DataExtent[1] / (width);
	////double sizeY = scale * DataExtent[3] / (height);

	//vtkActor2D *act2d1 = vtkActor2D::New();
	////act2d->SetPosition(Pos);
	////act2d->SetPosition2(sizeX, sizeY);
	//act2d1->SetPosition2(1, 1);
	//act2d1->SetMapper(mapper1);

	//GetRendererMain1()->AddActor2D(act2d1);
	//m_ActorImageMain1.Add(act2d1);

	//act2d1->Delete();
	//mapper1->Delete();
	//data1->Delete();

	//DrawCubeToAdjustDicom(GetRendererMain1());
	//RenderMain1();

	//////////////////////////////////////////////////////////////////////////////////////

	CString msg;	
	CRect dlgSize2;
	GetDlgItem(IDC_PIC_PREVIEW_MIDDLE)->GetWindowRect(dlgSize2);
	int ren_size2[2] = { dlgSize2.Width(), dlgSize2.Height() };

	msg.Format(L"%d,%d", dlgSize2.Width(), dlgSize2.Height());
	//AfxMessageBox(msg);
	// setup the parent window
	m_RenderWinMain2->SetSize(ren_size2);
	m_RenderWinMain2->SetParentId(GetDlgItem(IDC_PIC_PREVIEW_MIDDLE)->GetSafeHwnd());

	//Set Render 
	vtkRenderer *ren2 = vtkRenderer::New();
	m_RenderWinMain2->AddRenderer(ren2);
	SetRendererMain2(ren2);
	ren2->Delete();

	GetRendererMain2()->SetBackground(0, 0, 0);
	GetRendererMain2()->SetBackground2(0, 0, 0);

	//Set Outline
	double pt2[4][3] = { {0.0,				   0.0,				   0},
						{0.0,				  (double)ren_size2[1], 0},
						{(double)ren_size2[0], (double)ren_size2[1], 0},
						{(double)ren_size2[0], 0.0,				   0} };



	GenerateOutline2(GetRendererMain2(), pt2, 0);

	int DataExtent2[6] = { -1,-1,-1,-1,-1,-1 };
	data2->GetExtent(DataExtent2);
	// Image
	vtkOpenGLImageMapper* mapper2 = vtkOpenGLImageMapper::New();
	mapper2->SetInputData(data2);
	mapper2->RenderToRectangleOn();
	mapper2->UseCustomExtentsOn();
	mapper2->SetCustomDisplayExtents(DataExtent2);
	mapper2->SetZSlice(0);

	double width = GetRendererMain2()->GetSize()[0];
	double height = GetRendererMain2()->GetSize()[1];

	double scaleX = width / DataExtent2[1];
	double scaleY = height / DataExtent2[3];

	double scale = scaleX * 0.95;

	//double Pos[2] = { ( width + (width - DataExtent2[1] * scale) / 2.0),0 };

	double sizeX = scale * DataExtent2[1] / (width);
	double sizeY = scale * DataExtent2[3] / (height);

	msg.Format(L"%.f,%.f", (width + (width - DataExtent2[1] * scale) / 2.0), sizeY);
	//AfxMessageBox(msg);
	vtkActor2D *act2d2 = vtkActor2D::New();
	double Pos[2] = { 0.0,10.0};
	act2d2->SetPosition(Pos);
	act2d2->SetPosition2(sizeX, sizeY);
	act2d2->SetMapper(mapper2);

	GetRendererMain2()->AddActor2D(act2d2);

	act2d2->Delete();
	mapper2->Delete();
	data2->Delete();
	RenderMain2();
	//////////////////////////////////////////////////////////////////////////////////////
	//CRect dlgSize3;
	//GetDlgItem(IDC_PIC_PREVIEW_LAST)->GetWindowRect(dlgSize3);
	//int ren_size3[2] = { dlgSize3.Width(), dlgSize3.Height() };

	//// setup the parent window
	//m_RenderWinMain3->SetSize(ren_size3);
	//m_RenderWinMain3->SetParentId(GetDlgItem(IDC_PIC_PREVIEW_LAST)->GetSafeHwnd());

	////Set Render 
	//vtkRenderer *ren3 = vtkRenderer::New();
	//m_RenderWinMain3->AddRenderer(ren3);
	//SetRendererMain3(ren3);
	//ren3->Delete();

	//GetRendererMain3()->SetBackground(0, 0, 0);
	//GetRendererMain3()->SetBackground2(0, 0, 0);

	////Set Outline
	//double pt3[4][3] = { {0.0,				   0.0,				   0},
	//					{0.0,				  (double)ren_size3[1], 0},
	//					{(double)ren_size3[0], (double)ren_size3[1], 0},
	//					{(double)ren_size3[0], 0.0,				   0} };



	//GenerateOutline(GetRendererMain3(), pt3, -1);

	//int DataExtent3[6] = { -1,-1,-1,-1,-1,-1 };
	//data3->GetExtent(DataExtent3);
	//// Image
	//vtkOpenGLImageMapper* mapper3 = vtkOpenGLImageMapper::New();
	//mapper3->SetInputData(data3);
	//mapper3->RenderToRectangleOn();
	//mapper3->UseCustomExtentsOn();
	//mapper3->SetCustomDisplayExtents(DataExtent3);
	//mapper3->SetZSlice(0);

	////double width = GetRendererMain()->GetSize()[0];
	////double height = GetRendererMain()->GetSize()[1];

	////double scaleX = width / DataExtent[1];
	////double scaleY = height / DataExtent[3];

	////double scale = scaleX * 0.95;

	////double Pos[2] = { ( width + (width - DataExtent[1] * scale) / 2.0),0 };

	////double sizeX = scale * DataExtent[1] / (width);
	////double sizeY = scale * DataExtent[3] / (height);

	//vtkActor2D *act2d3 = vtkActor2D::New();
	////act2d->SetPosition(Pos);
	////act2d->SetPosition2(sizeX, sizeY);
	//act2d3->SetPosition2(1, 1);
	//act2d3->SetMapper(mapper3);

	//GetRendererMain3()->AddActor2D(act2d3);
	//m_ActorImageMain3.Add(act2d3);

	//act2d3->Delete();
	//mapper3->Delete();
	//data3->Delete();
	//DrawCubeToAdjustDicom(GetRendererMain3());
	//RenderMain3();
	//////////////////////////////////////////////////////////////////////////////////////


	
}

void CDlgAdjustDicom::GenerateOutline1(vtkRenderer* Render, double Pt[4][3], int Index)
{
	vtkPoints* points = vtkPoints::New(VTK_DOUBLE);
	points->SetNumberOfPoints(4);

	vtkCellArray *cells = vtkCellArray::New();
	cells->InsertNextCell(5);

	for (int i = 0; i < 4; i++)
	{
		points->SetPoint(i, Pt[i]);
		cells->InsertCellPoint(i);
	}
	cells->InsertCellPoint(0);

	vtkPolyData* polydata = vtkPolyData::New();
	polydata->SetPoints(points);
	polydata->SetLines(cells);

	vtkPolyDataMapper2D *mapper = vtkPolyDataMapper2D::New();
	mapper->SetInputData(polydata);
	

	vtkActor2D *actor = vtkActor2D::New();
	actor->SetMapper(mapper);
	actor->PickableOff();
	actor->SetPosition2(1.0, 1.0);

	if (Index > -1)
		m_ActorOutline1[Index] = actor;

	vtkProperty2D *prop = actor->GetProperty();
	prop->SetColor(1.0, 0.0, 0.0);
	prop->SetLineWidth(3.f);
	Render->AddActor2D(actor);

	//release memory
	points->Delete();
	cells->Delete();
	polydata->Delete();
	mapper->Delete();
	actor->Delete();
}
void CDlgAdjustDicom::GenerateOutline2(vtkRenderer* Render, double Pt[4][3], int Index)
{
	vtkPoints* points = vtkPoints::New(VTK_DOUBLE);
	points->SetNumberOfPoints(4);

	vtkCellArray *cells = vtkCellArray::New();
	cells->InsertNextCell(5);

	for (int i = 0; i < 4; i++)
	{
		points->SetPoint(i, Pt[i]);
		cells->InsertCellPoint(i);
	}
	cells->InsertCellPoint(0);

	vtkPolyData* polydata = vtkPolyData::New();
	polydata->SetPoints(points);
	polydata->SetLines(cells);

	vtkPolyDataMapper2D *mapper = vtkPolyDataMapper2D::New();
	mapper->SetInputData(polydata);


	vtkActor2D *actor = vtkActor2D::New();
	actor->SetMapper(mapper);
	actor->PickableOff();
	actor->SetPosition2(1.0, 1.0);

	if (Index > -1)
		m_ActorOutline2[Index] = actor;

	vtkProperty2D *prop = actor->GetProperty();
	prop->SetColor(1.0, 0.0, 0.0);
	prop->SetLineWidth(3.f);
	Render->AddActor2D(actor);

	//release memory
	points->Delete();
	cells->Delete();
	polydata->Delete();
	mapper->Delete();
	actor->Delete();
}
void CDlgAdjustDicom::GenerateOutline3(vtkRenderer* Render, double Pt[4][3], int Index)
{
	vtkPoints* points = vtkPoints::New(VTK_DOUBLE);
	points->SetNumberOfPoints(4);

	vtkCellArray *cells = vtkCellArray::New();
	cells->InsertNextCell(5);

	for (int i = 0; i < 4; i++)
	{
		points->SetPoint(i, Pt[i]);
		cells->InsertCellPoint(i);
	}
	cells->InsertCellPoint(0);

	vtkPolyData* polydata = vtkPolyData::New();
	polydata->SetPoints(points);
	polydata->SetLines(cells);

	vtkPolyDataMapper2D *mapper = vtkPolyDataMapper2D::New();
	mapper->SetInputData(polydata);


	vtkActor2D *actor = vtkActor2D::New();
	actor->SetMapper(mapper);
	actor->PickableOff();
	actor->SetPosition2(1.0, 1.0);

	if (Index > -1)
		m_ActorOutline3[Index] = actor;

	vtkProperty2D *prop = actor->GetProperty();
	prop->SetColor(1.0, 0.0, 0.0);
	prop->SetLineWidth(3.f);
	Render->AddActor2D(actor);

	//release memory
	points->Delete();
	cells->Delete();
	polydata->Delete();
	mapper->Delete();
	actor->Delete();
}

void CDlgAdjustDicom::DeleteOutline1(vtkRenderer* Render)
{
	m_ActorOutline1[0]->VisibilityOff();
}
void CDlgAdjustDicom::DeleteOutline2(vtkRenderer* Render)
{
	m_ActorOutline2[0]->VisibilityOff();
}
void CDlgAdjustDicom::DeleteOutline3(vtkRenderer* Render)
{	
	m_ActorOutline3[0]->VisibilityOff();
}
//void CDlgAdjustDicom::DrawCubeToAdjustDicom(vtkRenderer* ren)
//{
//	//// Create five points.
//	//double origin[3] = { 0.0, 0.0, 0.0 };
//	//double p0[3] = { 1.0, 0.0, 0.0 };
//	//double p1[3] = { 1.0, 1.0, 0.0 };
//	//double p2[3] = { 0.0, 1.0, 0.0 };
//	//double p3[3] = { 0.0, 0.0, 0.0 };
//
//	//// Create a vtkPoints object and store the points in it
//	//vtkSmartPointer<vtkPoints> points =
//	//	vtkSmartPointer<vtkPoints>::New();
//	//points->InsertNextPoint(origin);
//	//points->InsertNextPoint(p0);
//	//points->InsertNextPoint(p1);
//	//points->InsertNextPoint(p2);
//	//points->InsertNextPoint(p3);
//
//	//// Create a cell array to store the lines in and add the lines to it
//	//vtkSmartPointer<vtkCellArray> lines =
//	//	vtkSmartPointer<vtkCellArray>::New();
//
//	//for (unsigned int i = 0; i < 4; i++)
//	//{
//	//	vtkSmartPointer<vtkLine> line =
//	//		vtkSmartPointer<vtkLine>::New();
//	//	line->GetPointIds()->SetId(0, i);
//	//	line->GetPointIds()->SetId(1, i + 1);
//	//	lines->InsertNextCell(line);
//	//}
//
//	//// Create a polydata to store everything in
//	//vtkSmartPointer<vtkPolyData> linesPolyData =
//	//	vtkSmartPointer<vtkPolyData>::New();
//
//	//// Add the points to the dataset
//	//linesPolyData->SetPoints(points);
//
//	//// Add the lines to the dataset
//	//linesPolyData->SetLines(lines);
//
//	//// Setup actor and mapper
//	//vtkSmartPointer<vtkPolyDataMapper> mapper =
//	//	vtkSmartPointer<vtkPolyDataMapper>::New();
//	//mapper->SetInputData(linesPolyData);
//
//	//vtkSmartPointer<vtkActor> actor =
//	//	vtkSmartPointer<vtkActor>::New();
//	//actor->SetMapper(mapper);
//	//actor->GetProperty()->SetLineWidth(4);
//	//actor->GetProperty()->SetColor(1.0,0.0,0.0);
//	////ren->AddActor(actor);
//
//	////  // Setup render window, renderer, and interactor
//	////vtkSmartPointer<vtkRenderer> renderer =
//	////	vtkSmartPointer<vtkRenderer>::New();
//	////vtkSmartPointer<vtkRenderWindow> renderWindow =
//	////	vtkSmartPointer<vtkRenderWindow>::New();
//	////renderWindow->SetWindowName("Long Line");
//	////renderWindow->AddRenderer(renderer);
//	////vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//	////	vtkSmartPointer<vtkRenderWindowInteractor>::New();
//	////renderWindowInteractor->SetRenderWindow(renderWindow);
//	////renderer->AddActor(actor);
//	//GetRendererMain1()->AddActor(actor);
//
//	//GetRendererMain1()->ResetCamera();
//
//	//////renderer->SetBackground(colors->GetColor3d("Silver").GetData());
//	////renderWindow->Render();
//	////renderWindowInteractor->Start();
//}

void CDlgAdjustDicom::BuildImageMarkLine(double* markPt)
{
	//int ext[6] = { 0 };
	//GetImageData()->GetExtent(ext);

	//vtkPropCollection* PropAll2D = GetCurrentRenderer()->GetViewProps();

	////MarkLine
	//vtkPropAssembly* PropMeasMarkLineAll = (vtkPropAssembly*)PropAll2D->GetItemAsObject(ACTOR_IMPSECT_MARKLINE);
	//vtkPropCollection* Props = PropMeasMarkLineAll->GetParts();
	//vtkActor2D* act_markline = (vtkActor2D*)Props->GetItemAsObject(PROP_MARKLINE_1);

	//act_markline->SetPosition(m_ImgPos);
	//act_markline->VisibilityOn();
	//vtkPolyDataMapper2D* mapper = (vtkPolyDataMapper2D*)act_markline->GetMapper();
	//vtkPoints* MarkLinePts = mapper->GetInput()->GetPoints();

	//CSafeImplantDoc* pDoc = (CSafeImplantDoc*)GetDocument();

	//CViewAxial* pView_Axial = (CViewAxial*)pDoc->GetCurrentView(CTImg);

	//MarkLinePts->SetPoint(0, 0.f, (markPt[1] - m_CustExtent[2])*m_ImgScale, 0.f);
	//MarkLinePts->SetPoint(1, ext[1] * m_ImgScale, (markPt[1] - m_CustExtent[2])*m_ImgScale, 0.f);

	//m_MarkPt[0] = markPt[0];
	//m_MarkPt[1] = markPt[1];
}


//void CDlgAdjustDicom::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
//	CDialog::OnLButtonDown(nFlags, point);
//}
//
//
//void CDlgAdjustDicom::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
//
//	CDialog::OnMouseMove(nFlags, point);
//}
//
//
BOOL CDlgAdjustDicom::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		CRect rect;
		GetDlgItem(IDC_PIC_PREVIEW_LAST)->GetWindowRect(&rect);

		CPoint  pt;
		GetCursorPos(&pt);		

		if (rect.PtInRect(pt))
		{
			DeleteOutline1(GetRendererMain1());
			DeleteOutline2(GetRendererMain2());
			DeleteOutline3(GetRendererMain3());
			CString msg;
			msg.Format(L"bottom:%d,top:%d,right:%d,left:%d", rect3.bottom, rect3.top, rect3.right, rect3.left);
			//AfxMessageBox(msg);

			double xx = pt.x;
			double yy = pt.y;

			if (pt.x < rect3.CenterPoint().x && pt.y < rect3.CenterPoint().y)
			{
				double pt3[4][3] = { {(int)xx - rect3.left,abs((int)yy - rect3.bottom),0},
								{(int)xx - rect3.left, rect.top - rect3.top, 0},
								{rect.right - rect3.left, rect.top - rect3.top, 0},
								{rect.right - rect3.left, abs(yy - rect3.bottom), 0} };

				GenerateOutline1(GetRendererMain1(), pt3, 0);				
				GenerateOutline2(GetRendererMain2(), pt3, 0);
				GenerateOutline3(GetRendererMain3(), pt3, 0);
			}
			else if(pt.x < rect3.CenterPoint().x && pt.y > rect3.CenterPoint().y)
			{
				//AfxMessageBox(L"2");
				double pt3[4][3] = { {abs((int)xx - rect3.left),rect3.bottom,0},
							   {abs((int)xx - rect3.left), abs((int)yy - rect3.bottom), 0},
							   {rect.right - rect3.left, abs((int)yy - rect3.bottom), 0},
							   {rect.right - rect3.left, rect3.bottom, 0} };

				GenerateOutline1(GetRendererMain1(), pt3, 0);
				GenerateOutline2(GetRendererMain2(), pt3, 0);
				GenerateOutline3(GetRendererMain3(), pt3, 0);
			}
			else if (pt.x > rect3.CenterPoint().x && pt.y > rect3.CenterPoint().y)
			{
				//AfxMessageBox(L"3");
				double pt3[4][3] = { {rect3.left,rect3.bottom,0},
							   {rect3.left, abs((int)yy - rect3.bottom) , 0},
							   {abs((int)xx - rect3.left), abs((int)yy - rect3.bottom), 0},
							   {abs((int)xx - rect3.left), rect3.bottom, 0} };

				//GenerateOutline3(GetRendererMain3(), pt3, 0);
			}
			else
			{
				//AfxMessageBox(L"4");
				double pt3[4][3] = { {0,abs((int)yy - rect3.bottom),0},
							   {0, rect3.top , 0},
							   {(int)xx - rect3.left, rect3.top, 0},
							   {(int)xx - rect3.left, abs((int)yy - rect3.bottom), 0} };

				//GenerateOutline3(GetRendererMain3(), pt3, 0);
			}
				
			RenderMain1();
			RenderMain2();
			RenderMain3();		
		}

	}

	return CDialog::PreTranslateMessage(pMsg);
}