
// VTKMFC_TESTView.cpp : implementation of the CVTKMFCTESTView class
//
#include "pch.h"
#include "framework.h"
#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VTKMFC_TEST.h"
#endif

#include "MainFrm.h"
#include "BtnFuncBar.h"
#include "FileProcessWin.h"
#include "RemoveTooth.h"
#include "AlignWin.h"
#include "ManualWin.h"

#include "MessageID.h"
#include "VTKMFC_TESTDoc.h"
#include "VTKMFC_TESTView.h"

#include "CDlgOpacity.h"
#include "CDlgAdjustDicom.h"
#include "CDlgCTImageControl.h"
using namespace std;

#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::string folder = "D:\\case2";

class  StatusMessage
{
public:
	static std::string Format(int slice, int maxSlice)
	{
		std::stringstream tmp;
		tmp << "Slice Number " << slice + 1 << "/" << maxSlice + 1;
		return tmp.str();
	}

};
//class myvtkInteractorStyleImage : public vtkInteractorStyleImage
class myvtkInteractorStyleImage : public vtkInteractorStyleTrackballCamera
{
public:
	static myvtkInteractorStyleImage* New();
	vtkTypeMacro(myvtkInteractorStyleImage, vtkInteractorStyleImage);

	myvtkInteractorStyleImage()
	{
		LastPickedActor = NULL;
		LastPickedProperty = vtkProperty::New();
		points = vtkPoints::New();
		splineActor = vtkActor::New();
		//spline = vtkParametricSpline::New();
	}
	virtual ~myvtkInteractorStyleImage()
	{
		LastPickedProperty->Delete();
	}

protected:
	vtkImageReslice* imageResliceSagittal;
	vtkImageReslice* imageResliceCoronal;
	vtkImageReslice* imageResliceAxial;
	vtkVolume*		 volume;

	vtkRenderer* imageRenderSagittal;
	vtkRenderer* imageRenderCoronal;
	vtkRenderer* imageRenderAxial;
	vtkRenderer* imageRenderVolumeRendering;	

	//vtkParametricSpline* spline;
	int functionMode;

	
private:
	vtkActor    *LastPickedActor;
	vtkProperty *LastPickedProperty;
	vtkActor	*splineActor;
	vtkPoints	*points;
	//vtkParametricSpline* spline;

	//double spacingAxial = this->imageResliceAxial->GetOutput()->GetSpacing()[2];
	//double spacingSagittal = this->imageResliceSagittal->GetOutput()->GetSpacing()[2];
	//double spacingCoronal = this->imageResliceCoronal->GetOutput()->GetSpacing()[2];


	//vtkImageViewer2* _ImageViewer;
	//vtkTextMapper* _StatusMapper;
	//CVTKMFCTESTView* _Testview;
	//int _Slice;
	//int _MinSlice;
	//int _MaxSlice;

public:
	void SetResliceSagittal(vtkImageReslice* reslice) {
		this->imageResliceSagittal = reslice;
	}
	void SetResliceCoronal(vtkImageReslice* reslice) {
		this->imageResliceCoronal = reslice;
	}
	void SetResliceAxial(vtkImageReslice* reslice) {
		this->imageResliceAxial = reslice;
	}
	void SetRenderAxial(vtkRenderer* render)
	{
		this->imageRenderAxial = render;
	}
	void SetRenderCoronal(vtkRenderer* render)
	{
		this->imageRenderCoronal = render;
	}
	void SetRenderSagittal(vtkRenderer* render)
	{
		this->imageRenderSagittal = render;
	}
	void SetRenderVolumeRendering(vtkRenderer* render)
	{
		this->imageRenderVolumeRendering = render;
	}
	void SetVolumeRendering(vtkVolume* volume)
	{
		this->volume = volume;
	}
	void ImasgeRegionGrowing(vtkRenderer* render)
	{
		int curPos[2];		
		this->Interactor->GetEventPosition(curPos);

		// 取得目前的切片位置

		int regionSize = 0;
		if (render == imageRenderAxial)
		{

		}
		else if (render == imageRenderSagittal)
		{
		}		
		else if (render == imageRenderCoronal)
		{

		}
			
	}
	void GenerateSpline(vtkPoints* points)
	{		
		//vtkSmartPointer<vtkParametricSpline> spline =
		//	vtkSmartPointer<vtkParametricSpline>::New();
		//spline->SetPoints(points);		

		//vtkSmartPointer<vtkParametricFunctionSource> functionSource =
		//	vtkSmartPointer<vtkParametricFunctionSource>::New();
		//functionSource->SetParametricFunction(spline);
		//functionSource->Update();

		//// Setup actor and mapper
		//vtkSmartPointer<vtkPolyDataMapper> mapper =
		//	vtkSmartPointer<vtkPolyDataMapper>::New();		
		//mapper->SetInputConnection(functionSource->GetOutputPort());
		//
		//splineActor->SetMapper(mapper);
		//renderer->AddActor(splineActor);
	}
	void SetFunctionMode(int mode)
	{
		this->functionMode = mode;
	}
	
	

protected:
	void MoveSliceForward()
	{		
		int curPos[2];		
		this->Interactor->GetEventPosition(curPos);
		vtkRenderer *renderer = this->Interactor->FindPokedRenderer(curPos[0], curPos[1]);

		int deltaY = -1;
		vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
		double point[4], center[4];

		if (renderer == imageRenderAxial)
		{		
			double spacingAxial = this->imageResliceAxial->GetOutput()->GetSpacing()[2];
			point[0] = 0.0;
			point[1] = 0.0;
			point[2] = spacingAxial * deltaY;			
			point[3] = 1.0;
			matrix = this->imageResliceAxial->GetResliceAxes();
			this->imageResliceAxial->Update();
		}
		else if (renderer == imageRenderSagittal)
		{		
			double spacingSagittal = this->imageResliceSagittal->GetOutput()->GetSpacing()[2];
			point[0] = 0.0;
			point[1] = 0.0;
			point[2] = spacingSagittal * deltaY;//0.0;
			point[3] = 1.0;
			matrix = this->imageResliceSagittal->GetResliceAxes();
			this->imageResliceSagittal->Update();
		}
		else if (renderer == imageRenderCoronal)
		{		
			double spacingCoronal = this->imageResliceCoronal->GetOutput()->GetSpacing()[2];
			point[0] = 0.0;
			point[1] = 0.0;
			point[2] = spacingCoronal * deltaY;//0.0;
			point[3] = 1.0;
			matrix = this->imageResliceCoronal->GetResliceAxes();
			this->imageResliceCoronal->Update();
		}
		matrix->MultiplyPoint(point, center);
		matrix->SetElement(0, 3, center[0]);
		matrix->SetElement(1, 3, center[1]);
		matrix->SetElement(2, 3, center[2]);

		this->Interactor->Render();

	}
	void MoveSliceBackward()
	{
		int /*lastPos[2],*/ curPos[2];
		//this->Interactor->GetLastEventPosition(lastPos);
		this->Interactor->GetEventPosition(curPos);
		vtkRenderer *renderer = this->Interactor->FindPokedRenderer(curPos[0], curPos[1]);

		int deltaY = 1;
		vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
		double point[4], center[4];		
		if (renderer == imageRenderAxial)
		{						
			double spacingAxial = this->imageResliceAxial->GetOutput()->GetSpacing()[2];
			point[0] = 0.0;
			point[1] = 0.0;
			point[2] = spacingAxial * deltaY;			
			point[3] = 1.0;
			matrix = this->imageResliceAxial->GetResliceAxes();
			this->imageResliceAxial->Update();
		}
		else if (renderer == imageRenderSagittal)
		{			
			double spacingSagittal = this->imageResliceSagittal->GetOutput()->GetSpacing()[2];
			point[0] = 0.0;
			point[1] = 0.0;
			point[2] = spacingSagittal * deltaY;//0.0;
			point[3] = 1.0;
			matrix = this->imageResliceSagittal->GetResliceAxes();
			this->imageResliceSagittal->Update();
		}
		else if (renderer == imageRenderCoronal)
		{			
			double spacingCoronal = this->imageResliceCoronal->GetOutput()->GetSpacing()[2];
			point[0] = 0.0;
			point[1] = 0.0;
			point[2] = spacingCoronal * deltaY;//0.0;
			point[3] = 1.0;
			matrix = this->imageResliceCoronal->GetResliceAxes();
			this->imageResliceCoronal->Update();
		}
		matrix->MultiplyPoint(point, center);
		matrix->SetElement(0, 3, center[0]);
		matrix->SetElement(1, 3, center[1]);
		matrix->SetElement(2, 3, center[2]);

		this->Interactor->Render();
	}
	void LeftButtonDown()
	{		
		int curPos[2];
		this->Interactor->GetEventPosition(curPos);
		vtkRenderer *renderer = this->Interactor->FindPokedRenderer(curPos[0], curPos[1]);
		
		
		vtkSmartPointer<vtkPointPicker>  picker =
			vtkSmartPointer<vtkPointPicker>::New();
		if (renderer == imageRenderAxial)
			picker->Pick(curPos[0], curPos[1], 0, imageRenderAxial);
		else if (renderer == imageRenderSagittal)
			picker->Pick(curPos[0], curPos[1], 0, imageRenderSagittal);
		else if (renderer == imageRenderCoronal)
			picker->Pick(curPos[0], curPos[1], 0, imageRenderCoronal);
		


		double* pos = picker->GetPickPosition();

		if (renderer!= imageRenderVolumeRendering)
		{
			vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
			sphereSource->SetCenter(pos[0], pos[1], 0);
			sphereSource->SetRadius(2.0);
			sphereSource->SetThetaResolution(10);
			vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
			mapper->SetInputConnection(sphereSource->GetOutputPort());
			vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
			actor->PickableOn();
			actor->SetMapper(mapper);
			actor->VisibilityOn();
			actor->GetProperty()->SetColor(0, 1, 0);
			actor->GetProperty()->SetRepresentationToSurface();
			renderer->AddActor2D(actor);
			if (renderer == imageRenderAxial)
			{
				points->InsertNextPoint(pos[0], pos[1], 10.0);
				if (points->GetNumberOfPoints() > 1)
				{
					//GenerateSpline(points);
					vtkSmartPointer<vtkParametricSpline> spline =
						vtkSmartPointer<vtkParametricSpline>::New();				
					spline->SetPoints(points);

					vtkSmartPointer<vtkParametricFunctionSource> functionSource =
						vtkSmartPointer<vtkParametricFunctionSource>::New();
					functionSource->SetParametricFunction(spline);
					functionSource->Update();

					// Setup actor and mapper
					vtkSmartPointer<vtkPolyDataMapper> mapper =
						vtkSmartPointer<vtkPolyDataMapper>::New();
					mapper->SetInputConnection(functionSource->GetOutputPort());
					mapper->Update();

					renderer->RemoveActor(splineActor);
					splineActor->SetMapper(mapper);
					splineActor->GetProperty()->SetColor(1, 0, 0);
					splineActor->GetProperty()->SetLineWidth(3.0);
					renderer->AddActor(splineActor);
				}
			}
		}
		else
		{
			vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
		}


		renderer->Render();
		renderer->GetRenderWindow()->Render();
		// Forward events
		//vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}

//	virtual void OnKeyDown()
//	{
///*		std::string key = this->GetInteractor()->GetKeySym();
//		if (key.compare("Up") == 0)
//			MoveSliceForward();
//		else if (key.compare("Down") == 0)
//		{
//			MoveSliceBackward();
//		}
//
//		vtkInteractorStyleImage::OnKeyDown();	*/	
//
//		std::string key = this->GetInteractor()->GetKeySym();
//		if (key.compare("Up") == 0)
//		{
//			AfxMessageBox(L"up");
//		}
//		else if (key.compare("Down") == 0)
//		{
//			AfxMessageBox(L"down");
//		}
//
//		vtkInteractorStyleImage::OnKeyDown();
//	}

	virtual void OnMouseWheelForward()
	{		
		MoveSliceForward();
	}
	virtual void OnMouseWheelBackward()
	{			
		MoveSliceBackward();
	}
	virtual void OnLeftButtonDown()
	{
		LeftButtonDown();
	}
};


//2020.03.23
class vtkImageInteractionCallback : public vtkCommand
{
public:
	static vtkImageInteractionCallback* New()
	{
		//return new vtkImageInteractionCallback;
	}
	vtkImageInteractionCallback()
	{
		this->Slicing = 0;
		//this->ImageReslice = nullptr;
		this->Interactor = nullptr;
		this->imageResliceSagittal = nullptr;
		this->imageResliceCoronal = nullptr;
		this->imageResliceAxial = nullptr;
	}

	//void SetImageReslice(vtkImageReslice* reslice)
	//{
	//	this->ImageReslice = reslice;
	//}

	//void SetImageRender(vtkRenderer* render)
	//{
	//	this->ImageRender = render;
	//}

	void SetInteractor(vtkRenderWindowInteractor* interactor)
	{
		this->Interactor = interactor;
	}

	void SetRenderWindow(vtkRenderWindow* window)
	{
		this->RenderWindow = window;
	}

	void Execute(vtkObject* caller, unsigned long eventId, void* callData) override
	{
		if (eventId != vtkCommand::MouseMoveEvent)
		{
			std::string tmp = "[minbear] ";
			tmp += std::to_string(eventId);
			OutputDebugStringA(tmp.c_str());
		}

		int lastPos[2], curPos[2];
		this->Interactor->GetLastEventPosition(lastPos);
		this->Interactor->GetEventPosition(curPos);

		if (eventId == vtkCommand::LeftButtonPressEvent)
		{
			this->Slicing = 1;
		}
		else if (eventId == vtkCommand::LeftButtonReleaseEvent)
		{
			this->Slicing = 0;
		}
		if (eventId == vtkCommand::RightButtonPressEvent)
		{
			this->Slicing = 1;
		}
		else if (eventId == vtkCommand::RightButtonReleaseEvent)
		{
			this->Slicing = 0;
		}
		else if (eventId == vtkCommand::MouseMoveEvent)		
		{			
			vtkRenderer *renderer = this->Interactor->FindPokedRenderer(curPos[0], curPos[1]);			
			if (this->Slicing)			
			{				
				int deltaY = lastPos[1] - curPos[1];																						
				vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
				double point[4], center[4];
				if (renderer == imageRenderAxial)
				{					
					this->imageResliceAxial->Update();
					double spacingAxial = this->imageResliceAxial->GetOutput()->GetSpacing()[2];
					point[0] = 0.0;
					point[1] = 0.0;
					point[2] = spacingAxial * deltaY;
					point[3] = 1.0;
					matrix = this->imageResliceAxial->GetResliceAxes();

				}
				else if (renderer == imageRenderCoronal)
				{
					this->imageResliceCoronal->Update();
					double spacingCoronal = this->imageResliceCoronal->GetOutput()->GetSpacing()[2];
					point[0] = 0.0;
					point[1] = 0.0;//spacingCoronal * deltaY;
					point[2] = spacingCoronal * deltaY;//0.0;
					point[3] = 1.0;
					matrix = this->imageResliceCoronal->GetResliceAxes();

				}
				else if (renderer == imageRenderSagittal)
				{
					this->imageResliceSagittal->Update();
					double spacingSagittal = this->imageResliceSagittal->GetOutput()->GetSpacing()[2];
					point[0] = 0.0;//spacingSagittal * deltaY;
					point[1] = 0.0;
					point[2] = spacingSagittal * deltaY;//0.0;
					point[3] = 1.0;
					matrix = this->imageResliceSagittal->GetResliceAxes();

				}
				else if (renderer == imageRenderVolumeRendering)
				{					
					vtkInteractorStyle* style = vtkInteractorStyle::SafeDownCast(
						this->Interactor->GetInteractorStyle());
					if (style)
						style->OnMouseMove();
				}	
				else {}
				matrix->MultiplyPoint(point, center);
				matrix->SetElement(0, 3, center[0]);
				matrix->SetElement(1, 3, center[1]);
				matrix->SetElement(2, 3, center[2]);

				//this->MapToColors->Update();
				//this->OutputImageData = this->MapToColors->GetOutput();

				this->Interactor->Render();
			}
			else
			{
				vtkInteractorStyle* style = vtkInteractorStyle::SafeDownCast(
					this->Interactor->GetInteractorStyle());
				if (style)
					style->OnMouseMove();
			}
		}
		//else if (eventId == vtkCommand::MouseWheelForwardEvent)
		//{
		//	vtkRenderer *renderer = this->Interactor->FindPokedRenderer(curPos[0], curPos[1]);
		//	//if (this->Slicing)
		//	if (true)
		//	{
		//		int deltaY = lastPos[1] - curPos[1];
		//		deltaY *= -1;
		//		vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
		//		double point[4], center[4];
		//		if (renderer == imageRenderAxial)
		//		{
		//			this->imageResliceAxial->Update();
		//			double spacingAxial = this->imageResliceAxial->GetOutput()->GetSpacing()[2];
		//			point[0] = 0.0;
		//			point[1] = 0.0;
		//			point[2] = spacingAxial * deltaY;
		//			point[3] = 1.0;
		//			matrix = this->imageResliceAxial->GetResliceAxes();

		//		}
		//		else if (renderer == imageRenderCoronal)
		//		{
		//			this->imageResliceCoronal->Update();
		//			double spacingCoronal = this->imageResliceCoronal->GetOutput()->GetSpacing()[2];
		//			point[0] = 0.0;
		//			point[1] = 0.0;//spacingCoronal * deltaY;
		//			point[2] = spacingCoronal * deltaY;//0.0;
		//			point[3] = 1.0;
		//			matrix = this->imageResliceCoronal->GetResliceAxes();

		//		}
		//		else if (renderer == imageRenderSagittal)
		//		{
		//			this->imageResliceSagittal->Update();
		//			double spacingSagittal = this->imageResliceSagittal->GetOutput()->GetSpacing()[2];
		//			point[0] = 0.0;//spacingSagittal * deltaY;
		//			point[1] = 0.0;
		//			point[2] = spacingSagittal * deltaY;//0.0;
		//			point[3] = 1.0;
		//			matrix = this->imageResliceSagittal->GetResliceAxes();

		//		}
		//		else if (renderer == imageRenderVolumeRendering)
		//		{
		//			vtkInteractorStyle* style = vtkInteractorStyle::SafeDownCast(
		//				this->Interactor->GetInteractorStyle());
		//			if (style)
		//				style->OnMouseMove();
		//		}
		//		else {}
		//		matrix->MultiplyPoint(point, center);
		//		matrix->SetElement(0, 3, center[0]);
		//		matrix->SetElement(1, 3, center[1]);
		//		matrix->SetElement(2, 3, center[2]);

		//		//this->MapToColors->Update();
		//		//this->OutputImageData = this->MapToColors->GetOutput();

		//		this->Interactor->Render();
		//	}
		//	else
		//	{
		//		vtkInteractorStyle* style = vtkInteractorStyle::SafeDownCast(
		//			this->Interactor->GetInteractorStyle());
		//		if (style)
		//			style->OnMouseMove();
		//	}
		//}
	}

private:
	int Slicing;	
	vtkRenderWindowInteractor* Interactor;
	vtkRenderWindow* RenderWindow;
	//vtkImageData* OutputImageData;
public:
	vtkRenderer* imageRenderSagittal;
	vtkRenderer* imageRenderCoronal;
	vtkRenderer* imageRenderAxial;
	vtkRenderer* imageRenderVolumeRendering;

	vtkImageReslice* imageResliceSagittal;
	vtkImageReslice* imageResliceCoronal;
	vtkImageReslice* imageResliceAxial;
};

vtkStandardNewMacro(myvtkInteractorStyleImage);

// CVTKMFCTESTView

IMPLEMENT_DYNCREATE(CVTKMFCTESTView, CView)

BEGIN_MESSAGE_MAP(CVTKMFCTESTView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_EDIT_OPENDICOM, &CVTKMFCTESTView::OnEditOpendicom)
	ON_COMMAND(ID_EDIT_BONE, &CVTKMFCTESTView::OnEditBone)
	ON_COMMAND(ID_EDIT_TEETH, &CVTKMFCTESTView::OnEditTeeth)
	ON_COMMAND(ID_EDIT_SKIN, &CVTKMFCTESTView::OnEditSkin)
	ON_COMMAND(ID_EDIT_BONESKIN, &CVTKMFCTESTView::OnEditBoneskin)
	ON_COMMAND(ID_EDIT_TEETHSKIN, &CVTKMFCTESTView::OnEditTeethskin)
	ON_COMMAND(ID_EDIT_MUSLE, &CVTKMFCTESTView::OnEditMusle)
	ON_COMMAND(ID_EDIT_TESTOPACITYUP, &CVTKMFCTESTView::OnEditCloseVLTeeth)
	ON_COMMAND(ID_EDIT_TESTOPACITYDOWN, &CVTKMFCTESTView::OnEditCloseVLSkin)
	ON_COMMAND(ID_EDIT_TESTMUTICOLORFN, &CVTKMFCTESTView::OnEditTestmuticolorfn)
	ON_MESSAGE(WM_WPFUI_BTNFUNCBAR, WPFCALL)
	//5/6/2020 handtan//PROCESSBAR
	ON_MESSAGE(WM_WPFUI_PROCESSBAR,WPFCALL_PROCESSBAR)
	ON_MESSAGE(WM_WPFUI_FILEPROCESSWIN, WPFCALL_FILEPROCESSWIN)
	ON_MESSAGE(WM_WPFUI_WM_WPFUI_REMOVETOOTH, WPFCALL_REMOVETOOTH)
	ON_MESSAGE(WM_WPFUI_ALIGN, WPFCALL_ALIGNWIN)
	ON_MESSAGE(WM_WPFUI_MANUALALIGN, WPFCALL_MANUALALIGNWIN)
	ON_MESSAGE(WM_WPFUI_EXTRACT, WPFCALL_EXTRACT)

	ON_WM_KEYDOWN()
	ON_WM_CHAR()

END_MESSAGE_MAP()

// CVTKMFCTESTView construction/destruction

////Read dicom series
//typedef float PixelType;
//const unsigned int Dimension = 3;
//
//typedef itk::Image<PixelType, Dimension> ImageType;
//
//typedef itk::ImageSeriesReader<ImageType> ReaderType;
//
//typedef itk::GDCMSeriesFileNames NamesGeneratorType;
//NamesGeneratorType::Pointer namesGenerator = NamesGeneratorType::New();
//
//std::vector<ReaderType::Pointer>dcmreader;
//
//typedef std::vector< std::string > SeriesIdContainer;
//SeriesIdContainer seriesUID;

//

CVTKMFCTESTView::CVTKMFCTESTView() noexcept
{
	// TODO: add construction code here
	pvtkMFCWindow = NULL;
	//pvtkRenderer = NULL;
	//pvtkRenderer_dcm = NULL;
	//pvtkRenderer_cross = NULL;
	//pvtkRenderer_pano = NULL;

	//pvtkRenderer = vtkRenderer::New();
	//pvtkRenderer_dcm = vtkRenderer::New();
	//pvtkRenderer_cross = vtkRenderer::New();
	//pvtkRenderer_pano = vtkRenderer::New();

	//reori
	pvtkReOriVolumeRenderer = vtkRenderer::New();
	pvtkReOriXYRenderer = vtkRenderer::New();
	pvtkReOriXZRenderer = vtkRenderer::New();
	pvtkReOriYZRenderer = vtkRenderer::New();

	//pvtkReOriVolumeRenderer = NULL;
	//pvtkReOriXYRenderer = NULL;
	//pvtkReOriXZRenderer = NULL;
	//pvtkReOriYZRenderer = NULL;


	//test
	opacity_1 = -1000;
	opacity_2 = -500;
	opacity_3 = 700;
	opacity_4 = 900;
	opacity_5 = 1500;
	opacity_6 = 3071;
	opacity_7 = 4000;

	//test
	color_1 = -1000;
	color_2 = -500;
	color_3 = 700;
	color_4 = 900;
	color_5 = 1500;
	color_6 = 3071;
	color_7 = 4000;
	
	num_opacity1 = 0;
	num_color1 = 0;
	num_opacity2 = 0;
	num_color2 = 0;

	//no use
	volume_mode = 1;
	threshold = 200.0;
	threshold_old = 200.0;

	s_dirpath = "";
	c_dirpath = L"";
	testv = 0;
	this->picker = vtkPropPicker::New();
	memset(seed, 0, sizeof(seed));
}

CVTKMFCTESTView::~CVTKMFCTESTView()
{
	if (this->pvtkMFCWindow) delete this->pvtkMFCWindow;
}

BOOL CVTKMFCTESTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVTKMFCTESTView drawing

void CVTKMFCTESTView::OnDraw(CDC* pDC)
{
	CVTKMFCTESTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if (this->pvtkMFCWindow)
	{
		if (pDC->IsPrinting())
			this->pvtkMFCWindow->DrawDC(pDC);
	}
}

// CVTKMFCTESTView printing

BOOL CVTKMFCTESTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVTKMFCTESTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVTKMFCTESTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CVTKMFCTESTView diagnostics

#ifdef _DEBUG
void CVTKMFCTESTView::AssertValid() const
{
	CView::AssertValid();
}

void CVTKMFCTESTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVTKMFCTESTDoc* CVTKMFCTESTView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVTKMFCTESTDoc)));
	return (CVTKMFCTESTDoc*)m_pDocument;
}
#endif //_DEBUG


// CVTKMFCTESTView message handlers


void CVTKMFCTESTView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	if (this->pvtkMFCWindow) delete this->pvtkMFCWindow;

	this->pvtkMFCWindow = new vtkMFCWindow(this);

	this->pvtkMFCWindow->GetRenderWindow()->SetDesiredUpdateRate(1.0);
	//this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->pvtkRenderer);
	//this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->pvtkRenderer_dcm);
	//this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->pvtkRenderer_cross);
	//this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->pvtkRenderer_pano);


	//2020.02.24 add ReOri render
	//this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->pvtkReOriVolumeRenderer);
	//this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->pvtkReOriXYRenderer);
	//this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->pvtkReOriYZRenderer);
	//this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->pvtkReOriXZRenderer);

	this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->vtkVolumeRenderingRender);
	this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->vtkSagittalRenderer);
	this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->vtkCoronalRenderer);
	this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->vtkAxialRenderer);
}
void CVTKMFCTESTView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (this->pvtkMFCWindow)
		this->pvtkMFCWindow->MoveWindow(0, 0, cx, cy);
}
void CVTKMFCTESTView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	if (this->pvtkRenderer)      this->pvtkRenderer->Delete();
	if (this->pvtkRenderer_dcm)      this->pvtkRenderer_dcm->Delete();
	if (this->pvtkRenderer_cross)      this->pvtkRenderer_cross->Delete();
	if (this->pvtkRenderer_pano)      this->pvtkRenderer_pano->Delete();
}
void CVTKMFCTESTView::OnEditOpendicom()
{
//	//minbear
//	//AddVolumeRendering();
//	ChangeModeVolume();
//	//ChangeModeVolume1();
//
//
//
////	// TODO: Add your command handler code here
/////*	vtkSmartPointer<vtkPlaneSource> planeSource =
////		vtkSmartPointer<vtkPlaneSource>::New();
////	planeSource->SetCenter(1.0, 0.0, 0.0);
////	planeSource->SetNormal(1.0, 0.0, 1.0);
////	planeSource->Update();
////
////	vtkPolyData* plane = planeSource->GetOutput();
////
////	// Create a mapper and actor
////	vtkSmartPointer<vtkPolyDataMapper> mapper =
////		vtkSmartPointer<vtkPolyDataMapper>::New();
////	mapper->SetInputData(plane);
////
////	vtkSmartPointer<vtkActor> actor =
////		vtkSmartPointer<vtkActor>::New();
////	actor->SetMapper(mapper);
////
////	// Add the actors to the scene
////	pvtkRenderer->AddActor(actor);
////	pvtkRenderer->SetBackground(.1, .2, .3); // Background color dark blue*/
////
////	vtkSmartPointer<vtkDICOMImageReader> reader =
////		vtkSmartPointer<vtkDICOMImageReader>::New();
////	//reader->SetDirectoryName("c:\\DicomData\\DicomTest");
////	reader->SetDirectoryName("D:\\CT2");
////	reader->Update();
////
////	int dim[3];
////	reader->GetOutput()->GetDimensions(dim);
////
////	vtkSmartPointer<vtkImageCast> cast = vtkSmartPointer<vtkImageCast>::New();
////	cast->SetInputData((vtkDataObject*)reader->GetOutput());
////	cast->SetOutputScalarTypeToFloat();
////	cast->SetOutputScalarTypeToUnsignedChar();
////	cast->Update();
////// 	double maxx = cast->GetOutput()->GetScalarTypeMax();
////// 	double minn = cast->GetOutput()->GetScalarTypeMin();
////
////
////	// Create our volume and mapper
////	vtkSmartPointer<vtkVolume> volume =
////		vtkSmartPointer<vtkVolume>::New();
////
////	vtkSmartPointer<vtkGPUVolumeRayCastMapper> mapper =
////		vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
////
////	mapper->SetInputConnection(reader->GetOutputPort());
////	mapper->AutoAdjustSampleDistancesOn();
//////	mapper->SetSampleDistance(0.01);
//////	mapper->SetImageSampleDistance(1.0);
//////	mapper->SetAutoAdjustSampleDistances(0.0005);
////
////	double spacing[3];
////	reader->GetOutput()->GetSpacing(spacing);
////
////	// Create our transfer function
////	vtkSmartPointer<vtkColorTransferFunction> colorFun =
////		vtkSmartPointer<vtkColorTransferFunction>::New();
////	vtkSmartPointer<vtkPiecewiseFunction> opacityFun =
////		vtkSmartPointer<vtkPiecewiseFunction>::New();
////	// Create the property and attach the transfer functions
////	vtkSmartPointer<vtkVolumeProperty> property =
////		vtkSmartPointer<vtkVolumeProperty>::New();
////	property->SetIndependentComponents(true);
////	property->SetColor(colorFun);
////	property->SetScalarOpacity(opacityFun);
////	property->SetInterpolationTypeToLinear();
////	
////	// connect up the volume to the property and the mapper
////	volume->SetProperty(property);
////	volume->SetMapper(mapper);
////
////	colorFun->AddRGBPoint(700, 0, 0, 0, 0.5, 0.0);
////	colorFun->AddRGBPoint(1400, 0.73, 0.25, 0.30, 0.49, 0);
////	colorFun->AddRGBPoint(2300, .90, .82, .56, .5, 0);
////	colorFun->AddRGBPoint(4000, 1, 1, 1, .5, 1.0);
////
////	opacityFun->AddPoint(700, 0, .5, 0.0);
////	opacityFun->AddPoint(1400, 0.1, .5, 0.0);
////	opacityFun->AddPoint(2300, .2, 0.5, 0.0);
////	opacityFun->AddPoint(4000, .8, 0.5, 0.0);
////
////	mapper->SetBlendModeToComposite();
////	property->ShadeOn();
////	property->SetAmbient(0.1);
////	property->SetDiffuse(0.9);
////	property->SetSpecular(0.2);
////	property->SetSpecularPower(10.0);
////	property->SetScalarOpacityUnitDistance(0.5);
////
////	pvtkRenderer->AddVolume(volume);
////	pvtkRenderer->ResetCamera();
////	pvtkRenderer->SetViewport(0, 0, 0.5, 1.0);
////
////	vtkSmartPointer<vtkImageActor> actor = vtkImageActor::New();
////	actor->SetInputData(cast->GetOutput());
////	actor->InterpolateOff();
////	actor->Update();
////
////	pvtkRenderer_dcm->AddActor(actor);
////	pvtkRenderer_dcm->ResetCamera();
////	pvtkRenderer_dcm->SetViewport(0.5, 0, 1.0, 1.0);
//	
}
//void CVTKMFCTESTView::AddVolumeRendering()
//{
//	//dir path
//	reader->SetDirectoryName(folder.c_str());
//	reader->Update();
//
//	//dim
//	int dim[3];
//	reader->GetOutput()->GetDimensions(dim);
//
//	vtkSmartPointer<vtkImageCast> cast =
//		vtkSmartPointer<vtkImageCast>::New();
//	cast->SetInputData((vtkDataObject*)reader->GetOutput());
//	cast->SetOutputScalarTypeToFloat();
//	cast->SetOutputScalarTypeToUnsignedChar();
//	cast->Update();
//
//	// Create our volume and mapper
//	vtkSmartPointer<vtkVolume> volume =
//		vtkSmartPointer<vtkVolume>::New();
//
//	vtkSmartPointer<vtkSmartVolumeMapper> mapper =
//		vtkSmartPointer<vtkSmartVolumeMapper>::New();
//
//	//use default mode
//	mapper->SetRequestedRenderMode(vtkSmartVolumeMapper::DefaultRenderMode);
//
//	mapper->SetInputConnection(reader->GetOutputPort());
//	mapper->AutoAdjustSampleDistancesOn();
//
//	//get spacing
//	double spacing[3];
//	reader->GetOutput()->GetSpacing(spacing);
//
//	//// Create our transfer function
//	//vtkSmartPointer<vtkColorTransferFunction> colorFun =
//	//	vtkSmartPointer<vtkColorTransferFunction>::New();
//	//vtkSmartPointer<vtkPiecewiseFunction> opacityFun =
//	//	vtkSmartPointer<vtkPiecewiseFunction>::New();
//	// Create the property and attach the transfer functions
//	vtkSmartPointer<vtkVolumeProperty> property =
//		vtkSmartPointer<vtkVolumeProperty>::New();
//	property->SetIndependentComponents(true);
//	property->SetColor(colorFun);
//	property->SetScalarOpacity(opacityFun);
//	property->SetInterpolationTypeToLinear();
//
//	// connect up the volume to the property and the mapper
//	volume->SetProperty(property);
//	volume->SetMapper(mapper);
//
//	//放color fun and opcity fun
//	//CT_Comp();
//	CT_Bone();
//
//	//RGB_Composite
//	//opacityFun->AddPoint(0, 0.0);
//	//opacityFun->AddPoint(5.0, 0.0);
//	//opacityFun->AddPoint(30.0, 0.05);
//	//opacityFun->AddPoint(31.0, 0.0);
//	//opacityFun->AddPoint(90.0, 0.0);
//	//opacityFun->AddPoint(100.0, 0.3);
//	//opacityFun->AddPoint(110.0, 0.0);
//	//opacityFun->AddPoint(190.0, 0.0);
//	//opacityFun->AddPoint(200.0, 0.4);
//	//opacityFun->AddPoint(210.0, 0.0);
//	//opacityFun->AddPoint(245.0, 0.0);
//	//opacityFun->AddPoint(255.0, 0.5);
//
//	//test
//	//colorFun->AddRGBPoint(-2048, 0, 0, 0);
//	//colorFun->AddRGBPoint(128.643, 0, 0, 0);
//	//colorFun->AddRGBPoint(129.982, 0.615686, 0, 0.0156863);
//	//colorFun->AddRGBPoint(173.636, 0.909804, 0.454902, 0);
//	//colorFun->AddRGBPoint(255.884, 0.886275, 0.886275, 0.886275);
//	//colorFun->AddRGBPoint(584.878, 0.968627, 0.968627, 0.968627);
//	//colorFun->AddRGBPoint(3661, 1, 1, 1);
//
//	//opacityFun->AddPoint(-2048, 0);
//	//opacityFun->AddPoint(128.643, 0);
//	//opacityFun->AddPoint(129.982, 0.0982143);
//	//opacityFun->AddPoint(173.636, 0.1);
//	//opacityFun->AddPoint(255.884, 0.1);
//	//opacityFun->AddPoint(3661, 1);
//
//	mapper->SetBlendModeToComposite();
//	property->ShadeOn();
//	property->SetAmbient(0.1);
//	property->SetDiffuse(0.9);
//	property->SetSpecular(0.2);
//	property->SetSpecularPower(10.0);
//	property->SetScalarOpacityUnitDistance(0.5);
//
//
//	//set render
//	//pvtkRenderer->SetLayer(0);
//	double bck[3];
//	bck[0] = bck[1] = bck[2] = 0.5;
//	pvtkRenderer->SetBackground(bck);
//	pvtkRenderer->AddVolume(volume);
//	pvtkRenderer->ResetCamera();
//	//test
//	//pvtkRenderer->SetViewport(0, 0, 0.5, 1.0);
//	pvtkRenderer->SetViewport(0, 0, 1.0, 1.0);
//
//
//
//}
//void CVTKMFCTESTView::AddImageView()
//{
//	//std::string folder = "D:\\case2";
//	vtkSmartPointer<vtkDICOMImageReader> reader =
//		vtkSmartPointer<vtkDICOMImageReader>::New();
//	reader->SetDirectoryName(folder.c_str());
//	reader->Update();
//
//	vtkSmartPointer<vtkImageViewer2> imageViewer = 
//		vtkSmartPointer<vtkImageViewer2>::New();	
//	imageViewer->SetRenderer(pvtkRenderer_dcm);	
//	imageViewer->SetRenderWindow(pvtkRenderer->GetRenderWindow());
//	imageViewer->SetInputConnection(reader->GetOutputPort());
//
//	vtkSmartPointer<vtkTextProperty> sliceTextProp = 
//		vtkSmartPointer<vtkTextProperty>::New();
//	sliceTextProp->SetFontFamilyToCourier();
//	sliceTextProp->SetFontSize(20);
//	sliceTextProp->SetVerticalJustificationToBottom();
//	sliceTextProp->SetJustificationToLeft();
//
//	vtkSmartPointer<vtkTextMapper> sliceTextMapper = 
//		vtkSmartPointer<vtkTextMapper>::New();
//	std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(), imageViewer->GetSliceMax());
//	sliceTextMapper->SetInput(msg.c_str());
//	sliceTextMapper->SetTextProperty(sliceTextProp);
//
//	vtkSmartPointer<vtkActor2D> sliceTextActor = 
//		vtkSmartPointer<vtkActor2D>::New();
//	sliceTextActor->SetMapper(sliceTextMapper);
//	sliceTextActor->SetPosition(15, 10);
//
//	vtkSmartPointer<vtkTextProperty> usageTextProp = 
//		vtkSmartPointer<vtkTextProperty>::New();
//	usageTextProp->SetFontFamilyToCourier();
//	usageTextProp->SetFontSize(14);
//	usageTextProp->SetVerticalJustificationToTop();
//	usageTextProp->SetJustificationToLeft();
//
//	vtkSmartPointer<vtkTextMapper> usageTextMapper = 
//		vtkSmartPointer<vtkTextMapper>::New();
//	//usageTextMapper->SetInput("- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n  mouse button while dragging");
//	usageTextMapper->SetInput("- DICOM viewer test\n Slice with mouse wheel");
//	usageTextMapper->SetTextProperty(usageTextProp);
//
//	vtkSmartPointer<vtkActor2D> usageTextActor = 
//		vtkSmartPointer<vtkActor2D>::New();
//	usageTextActor->SetMapper(usageTextMapper);
//	usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
//	usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);
//
//	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//		vtkSmartPointer<vtkRenderWindowInteractor>::New();
//
//	vtkSmartPointer<myvtkInteractorStyleImage> myInteractorStyle =
//		vtkSmartPointer<myvtkInteractorStyleImage>::New();
//
//	myInteractorStyle->SetImageViewer(imageViewer);
//	myInteractorStyle->SetStatusMapper(sliceTextMapper);
//
//	imageViewer->SetupInteractor(renderWindowInteractor);
//	renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
//
//	imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
//	imageViewer->GetRenderer()->AddActor2D(usageTextActor);
//
//	imageViewer->GetRenderWindow()->SetSize(800, 600);
//	imageViewer->SetColorLevel(100);
//	imageViewer->SetColorWindow(2000);
//	imageViewer->Render();
//
//	//test
//	//imageViewer->GetRenderer()->SetViewport(0.5, 0, 1.0, 1.0);	
//	//imageViewer->GetRenderer()->SetLayer(1);
//	//imageViewer->GetRenderer()->SetBackground(1.0, 0.0, 1.0);
//	imageViewer->GetRenderer()->SetBackgroundAlpha(0.5);
//	imageViewer->GetRenderer()->SetViewport(0.667, 0, 1.0, 0.5);
//	imageViewer->GetRenderer()->ResetCamera();
//
//
//	
//	renderWindowInteractor->Start();
//
//	return;
//}
//void CVTKMFCTESTView::AddCrossSectionView()
//{
//	pvtkRenderer->GetRenderWindow()->AddRenderer(pvtkRenderer_cross);
//	pvtkRenderer_cross->SetViewport(0.333, 0, 0.667, 0.5);
//	pvtkRenderer_cross->ResetCamera();
//	
//
//}
//void CVTKMFCTESTView::AddPanoView()
//{
//	pvtkRenderer->GetRenderWindow()->AddRenderer(pvtkRenderer_pano);
//	pvtkRenderer_pano->SetViewport(0, 0, 0.333, 0.5);
//	pvtkRenderer_cross->ResetCamera();
//	
//}
//void CVTKMFCTESTView::ImageViewTest()
//{
//	//just 備份用
//	vtkSmartPointer<vtkDICOMImageReader> reader =
//		vtkSmartPointer<vtkDICOMImageReader>::New();
//	reader->SetDirectoryName(folder.c_str());
//	reader->Update();
//
//	vtkSmartPointer<vtkImageViewer2> imageViewer =
//		vtkSmartPointer<vtkImageViewer2>::New();
//
//
//	imageViewer->SetInputConnection(reader->GetOutputPort());
//	imageViewer->SetRenderer(pvtkRenderer_dcm);
//
//
//	vtkSmartPointer<vtkTextProperty> sliceTextProp =
//		vtkSmartPointer<vtkTextProperty>::New();
//	sliceTextProp->SetFontFamilyToCourier();
//	sliceTextProp->SetFontSize(20);
//	sliceTextProp->SetVerticalJustificationToBottom();
//	sliceTextProp->SetJustificationToLeft();
//
//	vtkSmartPointer<vtkTextMapper> sliceTextMapper =
//		vtkSmartPointer<vtkTextMapper>::New();
//	std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(), imageViewer->GetSliceMax());
//	sliceTextMapper->SetInput(msg.c_str());
//	sliceTextMapper->SetTextProperty(sliceTextProp);
//
//	vtkSmartPointer<vtkActor2D> sliceTextActor =
//		vtkSmartPointer<vtkActor2D>::New();
//	sliceTextActor->SetMapper(sliceTextMapper);
//	sliceTextActor->SetPosition(15, 10);
//
//	vtkSmartPointer<vtkTextProperty> usageTextProp =
//		vtkSmartPointer<vtkTextProperty>::New();
//	usageTextProp->SetFontFamilyToCourier();
//	usageTextProp->SetFontSize(14);
//	usageTextProp->SetVerticalJustificationToTop();
//	usageTextProp->SetJustificationToLeft();
//
//	vtkSmartPointer<vtkTextMapper> usageTextMapper =
//		vtkSmartPointer<vtkTextMapper>::New();
//	usageTextMapper->SetInput("- DICOM viewer test\n Slice with mouse wheel");
//	usageTextMapper->SetTextProperty(usageTextProp);
//
//	vtkSmartPointer<vtkActor2D> usageTextActor =
//		vtkSmartPointer<vtkActor2D>::New();
//	usageTextActor->SetMapper(usageTextMapper);
//	usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
//	usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);
//
//	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//		vtkSmartPointer<vtkRenderWindowInteractor>::New();
//
//	vtkSmartPointer<myvtkInteractorStyleImage> myInteractorStyle =
//		vtkSmartPointer<myvtkInteractorStyleImage>::New();
//
//	myInteractorStyle->SetImageViewer(imageViewer);
//	//myInteractorStyle->SetStatusMapper(sliceTextMapper);
//
//	imageViewer->SetupInteractor(renderWindowInteractor);
//	renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
//
//	pvtkRenderer_dcm->AddActor2D(sliceTextActor);
//	pvtkRenderer_dcm->AddActor2D(usageTextActor);
//
//
//	imageViewer->GetRenderer()->GetRenderWindow()->SetSize(800, 600);
//	imageViewer->SetColorLevel(100);
//	imageViewer->SetColorWindow(2000);
//	imageViewer->GetRenderer()->Render();
//	imageViewer->GetRenderer()->ResetCamera();
//
//	renderWindowInteractor->Start();
//
//	myInteractorStyle->SetImageViewer(imageViewer);
//	myInteractorStyle->SetStatusMapper(sliceTextMapper);
//
//	imageViewer->SetupInteractor(renderWindowInteractor);
//	renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
//
//	imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
//	imageViewer->GetRenderer()->AddActor2D(usageTextActor);
//
//	imageViewer->GetRenderWindow()->SetSize(800, 600);
//	imageViewer->SetColorLevel(100);
//	imageViewer->SetColorWindow(2000);
//	imageViewer->Render();
//	imageViewer->GetRenderer()->ResetCamera();
//
//	renderWindowInteractor->Start();
//
//
//	pvtkRenderer_dcm->ResetCamera();
//	pvtkRenderer_dcm->SetViewport(0.5, 0, 1.0, 1.0);
//	this->pvtkMFCWindow->GetRenderWindow()->Render();
//
//	//vtkSmartPointer<vtkImageActor> actor =
//	//	vtkImageActor::New();
//	//actor->SetInputData(cast->GetOutput());
//	//actor->InterpolateOff();
//	//actor->Update();
//
//	//pvtkRenderer_dcm->AddActor(actor);
//	//pvtkRenderer_dcm->ResetCamera();
//	//pvtkRenderer_dcm->SetViewport(0.5, 0, 1.0, 1.0);
//}
//void CVTKMFCTESTView::ChangeModeVolume()
//{
//	//dir path
//	reader->SetDirectoryName(folder.c_str());
//	reader->Update();
//
//	//dim
//	int dim[3];
//	reader->GetOutput()->GetDimensions(dim);
//
//	//get spacing
//	double spacing[3]; 
//	reader->GetOutput()->GetSpacing(spacing);
//
//	//use default mode
//	//若有裝顯示卡，會自動選擇GPU
//	mapper->SetRequestedRenderMode(vtkSmartVolumeMapper::DefaultRenderMode);//default mode
//	mapper->SetInteractiveUpdateRate(10.0);
//	mapper->SetInputConnection(reader->GetOutputPort());
//	//mapper->AutoAdjustSampleDistancesOn();
//	mapper->SetBlendModeToComposite();
//
//	//property
//	property->SetIndependentComponents(true);
//	property->SetColor(colorFun);
//	property->SetScalarOpacity(opacityFun);
//	property->SetInterpolationTypeToLinear();
//	property->ShadeOn();
//	property->SetAmbient(0.1);
//	property->SetDiffuse(0.9);
//	property->SetSpecular(0.2);
//	property->SetSpecularPower(10.0);
//	property->SetScalarOpacityUnitDistance(0.5);
//
//	// connect up the volume to the property and the mapper
//	volume->SetProperty(property);
//	volume->SetMapper(mapper);
//
//	//transfer function
//	
//	CT_Teeth();
//
//	//render
//	double bck[3];
//	bck[0] = bck[1] = bck[2] = 0.5;
//	pvtkRenderer->SetBackground(bck);
//	pvtkRenderer->AddVolume(volume);
//	pvtkRenderer->ResetCamera();
//	pvtkRenderer->SetViewport(0, 0, 1.0, 1.0);
//	pvtkRenderer->Render();
//	pvtkRenderer->GetRenderWindow()->Render();
//}
//void CVTKMFCTESTView::ChangeModeVolume1()
//{
//	////dir path
//	//reader1->SetDirectoryName(folder.c_str());
//	//reader1->Update();
//
//	////dim
//	//int dim[3];
//	//reader1->GetOutput()->GetDimensions(dim);
//
//	////get spacing
//	//double spacing[3];
//	//reader1->GetOutput()->GetSpacing(spacing);
//
//	//use default mode
//	//若有裝顯示卡，會自動選擇GPU
//	mapper1->SetRequestedRenderMode(vtkSmartVolumeMapper::DefaultRenderMode);//default mode
//	//mapper1->SetInputConnection(reader1->GetOutputPort());
//	mapper1->SetInputConnection(reader->GetOutputPort());
//	mapper1->AutoAdjustSampleDistancesOn();
//	mapper1->SetBlendModeToComposite();
//
//	//property
//	property1->SetIndependentComponents(true);
//	property1->SetColor(colorFun1);
//	property1->SetScalarOpacity(opacityFun1);
//	property1->SetInterpolationTypeToLinear();
//	property1->ShadeOn();
//	property1->SetAmbient(0.1);
//	property1->SetDiffuse(0.9);
//	property1->SetSpecular(0.2);
//	property1->SetSpecularPower(10.0);
//	property1->SetScalarOpacityUnitDistance(0.5);
//
//	// connect up the volume to the property and the mapper
//	volume1->SetProperty(property1);
//	volume1->SetMapper(mapper1);
//
//	//transfer function
//
//	//CT_Teeth();
//	CT_Skin();
//
//	//render
//	double bck[3];
//	bck[0] = bck[1] = bck[2] = 0.5;
//	pvtkRenderer->SetBackground(bck);
//	pvtkRenderer->AddVolume(volume1);
//	pvtkRenderer->ResetCamera();
//	pvtkRenderer->SetViewport(0, 0, 1.0, 1.0);
//	pvtkRenderer->Render();
//	pvtkRenderer->GetRenderWindow()->Render();
//}
void CVTKMFCTESTView::CT_InteWare()
{
	//CT InteWare
	colorFun->AddRGBPoint(700, 0, 0, 0, 0.5, 0.0);
	colorFun->AddRGBPoint(1400, .74f, .37f, .0f, 0.49, 0);
	colorFun->AddRGBPoint(2300, .90, .82, .56, .5, 0);
	colorFun->AddRGBPoint(4000, 1, 1, 1, .5, 1.0);

	opacityFun->AddPoint(700, 0, .5, 0.0);
	opacityFun->AddPoint(1400, 0.1, .5, 0.0);
	opacityFun->AddPoint(2300, .2, 0.5, 0.0);
	opacityFun->AddPoint(4000, .8, 0.5, 0.0);
}
void CVTKMFCTESTView::CT_Bone()
{
	colorFun->RemoveAllPoints();
	opacityFun->RemoveAllPoints();
	//CT_Bone
	colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
	colorFun->AddRGBPoint(-16, 0.73, 0.25, 0.30, 0.49, .61);
	colorFun->AddRGBPoint(641, .90, .82, .56, .5, 0.0);
	colorFun->AddRGBPoint(3071, 1, 1, 1, .5, 0.0);

	opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
	opacityFun->AddPoint(-16, 0, .49, .61);
	opacityFun->AddPoint(641, .72, .5, 0.0);
	opacityFun->AddPoint(3071, .71, 0.5, 0.0);
}
void CVTKMFCTESTView::CT_Skin()
{
	colorFun1->RemoveAllPoints();
	opacityFun1->RemoveAllPoints();
	////CT_Skin
	//colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
	//colorFun->AddRGBPoint(-1000, .62, .36, .18, 0.5, 0.0);
	//colorFun->AddRGBPoint(-500, .88, .60, .29, 0.33, 0.45);
	//colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);

	//opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
	//opacityFun->AddPoint(-1000, 0, 0.5, 0.0);
	//opacityFun->AddPoint(-500, 1.0, 0.33, 0.45);
	//opacityFun->AddPoint(3071, 1.0, 0.5, 0.0);


	//
	colorFun1->AddRGBPoint(color_1, .75, .60, .75, 0.5, 0.0);
	colorFun1->AddRGBPoint(color_2, .90, .81, .90, 0.11, 0.0);
	//colorFun1->AddRGBPoint(700, 0, 0, 0, 0.5, 0.0);
	//colorFun1->AddRGBPoint(700, 0.9, 0.9, 1.0, 0.5, 0.0);

	opacityFun1->AddPoint(opacity_1, 0.0, 0.0, 0.0);
	//opacityFun1->AddPoint(opacity_2, 0.02, 0.02, 0.02);
	opacityFun1->AddPoint(opacity_2, 0.003, 0.01, 0.01);
	//opacityFun1->AddPoint(700, 0, .5, 0.0);
}
void CVTKMFCTESTView::CT_Musle()
{
	colorFun->RemoveAllPoints();
	opacityFun->RemoveAllPoints();
	// CT_Muscle
	colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
	colorFun->AddRGBPoint(-155, .55, .25, .15, 0.5, .92);
	colorFun->AddRGBPoint(217, .88, .60, .29, 0.33, 0.45);
	colorFun->AddRGBPoint(420, 1, .94, .95, 0.5, 0.0);
	colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);

	opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
	opacityFun->AddPoint(-155, 0, 0.5, 0.92);
	opacityFun->AddPoint(217, .68, 0.33, 0.45);
	opacityFun->AddPoint(420, .83, 0.5, 0.0);
	opacityFun->AddPoint(3071, .80, 0.5, 0.0);
}
void CVTKMFCTESTView::CT_Teeth()
{
	colorFun->RemoveAllPoints();
	opacityFun->RemoveAllPoints();
	// CT_Teeth
	colorFun->AddRGBPoint(color_3, 0, 0, 0, 0.5, 0.0); 
	colorFun->AddRGBPoint(color_4, 0.80, 0.40f, 0.0f, 0.49, 0);
	colorFun->AddRGBPoint(color_5, 1.0, 1.0, .90, .6, 0);
	colorFun->AddRGBPoint(color_7, 1, 1, 1, .5, 1.0);

	opacityFun->AddPoint(opacity_3, 0, .5, 0.0);
	opacityFun->AddPoint(opacity_4, 0.2, .5, 0.5);
	opacityFun->AddPoint(opacity_5, .3, 0.5, 0.5);
	opacityFun->AddPoint(opacity_7, .8, 0.5, 0.5);
}
void CVTKMFCTESTView::CT_BoneSkin()
{
	colorFun->RemoveAllPoints();
	opacityFun->RemoveAllPoints();

	colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
	colorFun->AddRGBPoint(-1000, .75, .60, .75, 0.5, 0.0);
	colorFun->AddRGBPoint(-500, .90, .81, .90, 0.33, 0.0);
	colorFun->AddRGBPoint(-16, 0.73, 0.25, 0.30, 0.49, .61);
	colorFun->AddRGBPoint(641, .90, .82, .56, .5, 0.0);
	colorFun->AddRGBPoint(3071, 1, 1, 1, .5, 0.0);

	opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
	opacityFun->AddPoint(-1000, 0.0, 0.0, 0.0);
	opacityFun->AddPoint(-500, 0.03, 0.03, 0.03);
	opacityFun->AddPoint(-16, 0, .49, .61);
	opacityFun->AddPoint(641, .72, .5, 0.0);
	opacityFun->AddPoint(3071, .71, 0.5, 0.0);
	
}
void CVTKMFCTESTView::CT_TeethSkin()
{
	colorFun->RemoveAllPoints();
	opacityFun->RemoveAllPoints();

	colorFun->AddRGBPoint(-1000, .75, .60, .75, 0.5, 0.0);
	colorFun->AddRGBPoint(-500, .90, .81, .90, 0.33, 0.0);
	colorFun->AddRGBPoint(700, 0, 0, 0, 0.5, 0.0);	
	colorFun->AddRGBPoint(900, 0.80, 0.40f, 0.0f, 0.49, 0);
	colorFun->AddRGBPoint(1500, 1.0, 1.0, .90, .6, 0);
	colorFun->AddRGBPoint(4000, 1, 1, 1, .5, 1.0);

	opacityFun->AddPoint(-1000, 0.0, 0.0, 0.0);
	opacityFun->AddPoint(-500, 0.02, 0.02, 0.02);
	opacityFun->AddPoint(700, 0, .5, 0.0);	
	opacityFun->AddPoint(900, 0.2, .5, 0.5);
	opacityFun->AddPoint(1500, .3, 0.5, 0.5);
	opacityFun->AddPoint(4000, .8, 0.5, 0.5);

}
void CVTKMFCTESTView::CT_MutiColorFn()
{
	colorFun->RemoveAllPoints();
	opacityFun->RemoveAllPoints();
	colorFun1->RemoveAllPoints();
	opacityFun1->RemoveAllPoints();
	colorFun2->RemoveAllPoints();
	opacityFun2->RemoveAllPoints();
	colorFun3->RemoveAllPoints();
	opacityFun3->RemoveAllPoints();

	//skin
	colorFun1->AddRGBPoint(-1000, .75, .60, .75, 0.5, 0.0);
	colorFun1->AddRGBPoint(-500, .90, .81, .90, 0.33, 0.0);
	colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);

	//bone
	colorFun2->AddRGBPoint(700, 0, 0, 0, 0.5, 0.0);
	colorFun2->AddRGBPoint(900, 0.80, 0.40f, 0.0f, 0.49, 0);
	colorFun2->AddRGBPoint(1500, 1.0, 1.0, .90, .6, 0);

	//crown
	colorFun3->AddRGBPoint(1100, 0.90, 0.90f, 0.90f, 0.5, 0.0);
	colorFun3->AddRGBPoint(1700, 1.0, 1.0f, 1.0f, 0.6, 0);
	//colorFun3->AddRGBPoint(3350, 1.0, 1.0, 1.0, .7, 0);
	

	//skin
	opacityFun1->AddPoint(-1000, 0.0, 0.0, 0.0);
	opacityFun1->AddPoint(-500, 0.02, 0.02, 0.02);
	opacityFun->AddPoint(3071, 1.0, 0.5, 0.0);

	//bone
	opacityFun2->AddPoint(700, 0, .5, 0.0);
	opacityFun2->AddPoint(900, 0.2, .5, 0.5);
	opacityFun2->AddPoint(1500, .3, 0.5, 0.5);

	//crown
	opacityFun3->AddPoint(1100, 0, .5, 0.0);
	opacityFun3->AddPoint(1700, 0.2, .5, 0.5);
	//opacityFun3->AddPoint(3350, .3, 0.5, 0.5);

}

void CVTKMFCTESTView::OnEditBone()
{
	CT_Bone();
	UpdateTransferFn();
}
void CVTKMFCTESTView::OnEditTeeth()
{
	CT_Teeth();
	UpdateTransferFn();
}
void CVTKMFCTESTView::OnEditSkin()
{
	CT_Skin();
	UpdateTransferFn();
}
void CVTKMFCTESTView::OnEditBoneskin()
{
	CT_BoneSkin();
	UpdateTransferFn();
}
void CVTKMFCTESTView::OnEditTeethskin()
{
	CT_TeethSkin();
	UpdateTransferFn();
}
void CVTKMFCTESTView::OnEditMusle()
{
	CT_Musle();
	UpdateTransferFn();
}
void CVTKMFCTESTView::OnEditCloseVLTeeth()
{
	colorFun->RemoveAllPoints();
	opacityFun->RemoveAllPoints();
	UpdateTransferFn();
}
void CVTKMFCTESTView::OnEditCloseVLSkin()
{
	colorFun1->RemoveAllPoints();
	opacityFun1->RemoveAllPoints();
	
	UpdateTransferFn1();
}
void CVTKMFCTESTView::OnEditTestmuticolorfn()
{
	CDlgOpacity *dlg = new CDlgOpacity();
	dlg->Create(IDD_DIALOG_OPACITY);
	dlg->ShowWindow(SW_SHOW);
}
void CVTKMFCTESTView::ChangeColorOpacityTeeth()
{
	opacityFun->RemoveAllPoints();
	colorFun->RemoveAllPoints();

	colorFun->AddRGBPoint(color_3 + num_opacity1, 0, 0, 0, 0.5, 0.0);
	colorFun->AddRGBPoint(color_4 + num_opacity1, 0.80, 0.40f, 0.0f, 0.49, 0);
	colorFun->AddRGBPoint(color_5 + num_opacity1, 1.0, 1.0, .90, .6, 0);
	colorFun->AddRGBPoint(color_7 + num_opacity1, 1, 1, 1, .5, 1.0);

	opacityFun->AddPoint(opacity_3 + num_opacity1, 0, .5, 0.0);
	opacityFun->AddPoint(opacity_4 + num_opacity1, 0.2, .5, 0.5);
	opacityFun->AddPoint(opacity_5 + num_opacity1, .3, 0.5, 0.5);
	opacityFun->AddPoint(opacity_7 + num_opacity1, .8, 0.5, 0.5);

	UpdateTransferFn();

}


void CVTKMFCTESTView::ChangeColorOpacitySkin()
{
	colorFun1->RemoveAllPoints();
	opacityFun1->RemoveAllPoints();

	colorFun1->AddRGBPoint(color_1 + num_opacity2, .75, .60, .75, 0.5, 0.0);
	colorFun1->AddRGBPoint(color_2 + num_opacity2, .90, .81, .90, 0.33, 0.0);
	//colorFun1->AddRGBPoint(color_3 + num_opacity2, 0.9, 0.9, 1.0, 0.5, 0.0);

	opacityFun1->AddPoint(opacity_1 + num_opacity2, 0.0, 0.0, 0.0);
	opacityFun1->AddPoint(opacity_2 + num_opacity2, 0.02, 0.02, 0.02);
	//opacityFun1->AddPoint(opacity_3 + num_opacity2, 0, .5, 0.0);

	UpdateTransferFn1();
}

void CVTKMFCTESTView::UpdateTransferFn()
{
	property->SetColor(colorFun);
	property->SetScalarOpacity(opacityFun);
	volume->SetProperty(property);
	volume->GetProperty()->GetRGBTransferFunction()->Modified();
	volume->GetProperty()->GetScalarOpacity()->Modified();
	pvtkRenderer->Render();
	pvtkRenderer->GetRenderWindow()->Render();


	//double aa;
	//aa = this->pvtkMFCWindow->GetRenderWindow()->GetDesiredUpdateRate();
	//CString msg;
	//msg.Format(L"%.1f", aa);
	//AfxMessageBox(msg);
}

void CVTKMFCTESTView::UpdateTransferFn1()
{
	property1->SetColor(colorFun1);
	property1->SetScalarOpacity(opacityFun1);
	volume1->SetProperty(property1);
	volume1->GetProperty()->GetRGBTransferFunction()->Modified();
	volume1->GetProperty()->GetScalarOpacity()->Modified();
	pvtkRenderer->Render();
	pvtkRenderer->GetRenderWindow()->Render();
}

void CVTKMFCTESTView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CVTKMFCTESTView::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message || WM_CHAR == pMsg->message)
	{
		pMsg->hwnd = m_hWnd;
		return FALSE;
	}
	//else if(pMsg->message == WM_LBUTTONDOWN)
	//{

	//	CPoint  pt;
	//	GetCursorPos(&pt);
	//	int* r_size = NULL;
	//	r_size = pvtkReOriVolumeRenderer->GetSize();
	//	double* center = NULL;
	//	center = ReOrivolume->GetCenter();

	//	CString msg;
	//	msg.Format(L"pt.y:%d,tmp_center:%d", pt.y, tmp_center);
	//	AfxMessageBox(msg);
	//	//if (pt.x > 0 && (double)pt.x < center[0]*2)
	//	{
	//	  vtkSmartPointer<vtkTransform> transform =
	//			vtkSmartPointer<vtkTransform>::New();
	//		
	//		if (testv == 0)
	//		{
	//			tmp_center = pt.y;
	//			testv = 1;
	//			return true;
	//		}
	//		else
	//		{
	//			transform->Translate(0, pt.y - tmp_center, 0);
	//			transform->PostMultiply(); //this is the key line
	//			lineActorX->SetUserTransform(transform);
	//			tmp_center = pt.y;
	//		}
	//		
	//	}
	//}
	return CView::PreTranslateMessage(pMsg);
}


void CVTKMFCTESTView::FileOpenDir(std::string s_Indirpath)
{
	//dir path
	reader->SetDirectoryName(s_Indirpath.c_str());
	reader->Update();

	//get extent
	reader->GetOutput()->GetExtent(extent);

	//get spacing
	reader->GetOutput()->GetSpacing(spacing);

	//get origin
	reader->GetOutput()->GetOrigin(origin);

	//get center
	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);


	//save image data
	imageData->DeepCopy(reader->GetOutput());
}
#include<AtlBase.h>
void CVTKMFCTESTView::CFileOpenDir(CString c_Indirpath)
{
	////dir path	
	////const char str[256]= "D://안창석_A+new" ;
	////const char str[256] = "D://我我我";
	////CString str(L"D://我我我");
	////CString str(L"D://안창석_A+new");
	//CString str(L"D://赵_玲凤_1899_12_30(1)//赵_玲凤_1899_12_30");
	//int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	////int len = WideCharToMultiByte(1361, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	//char* pAscii = new char[len + 1];
	//len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), pAscii, len + 1, NULL, NULL);
	////len = WideCharToMultiByte(1361, 0, str, str.GetLength(), pAscii, len + 1, NULL, NULL);
	//pAscii[len] = 0;
	//const char* xxx = (const char*)pAscii;

	//return;
	//USES_CONVERSION;
	//reader->SetDirectoryName(W2CA(c_Indirpath));
	//c_Indirpath = L"D://안창석_A+new";
	//c_Indirpath = L"D://赵_玲凤_1899_12_30(1)//赵_玲凤_1899_12_30";

	//紀錄目前預設資料夾(一般來說就是專案資料夾路徑)
	TCHAR chCurDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, chCurDir);
	//設定選取路徑
	SetCurrentDirectory(c_Indirpath);		
	//do your thing
	reader->SetDirectoryName("./");	
	reader->Update();
	//Set回預設資料夾
	SetCurrentDirectory(chCurDir);

	////get extent
	reader->GetOutput()->GetExtent(extent);

	//get spacing
	reader->GetOutput()->GetSpacing(spacing);

	//get origin
	reader->GetOutput()->GetOrigin(origin);

	//get center
	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);


	//save image data
	imageData->DeepCopy(reader->GetOutput());
}

bool CVTKMFCTESTView::CGetDirPath(CString & s_dirpath)
{
	BROWSEINFO  bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = CSIDL_DESKTOP;//
	bi.pszDisplayName = NULL;
	bi.lpszTitle = NULL;//
	bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;//
	bi.lpfn = NULL;
	bi.iImage = 0;
	LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);//

	if (pidl == NULL)
	{
		std::cout << "no dir" << std::endl;
		return false;
	}
	TCHAR strFolder[MAX_PATH];
	SHGetPathFromIDList(pidl, strFolder);
	wstring tmp(&strFolder[0]); //convert to wstring	
	s_dirpath = tmp.c_str();
	return true;
}
bool CVTKMFCTESTView::GetDirPath(std::string& s_dirpath)
{
	BROWSEINFO  bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = CSIDL_DESKTOP;//
	bi.pszDisplayName = NULL;
	bi.lpszTitle = NULL;//
	bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;//
	bi.lpfn = NULL;
	bi.iImage = 0;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);//

	if (pidl == NULL)
	{
		std::cout << "no dir" << std::endl;
		return false;
	}
	TCHAR strFolder[MAX_PATH];
	SHGetPathFromIDList(pidl, strFolder);
	wstring tmp(&strFolder[0]); //convert to wstring
	std::string tmp1(tmp.begin(), tmp.end()); //and convert to string.
	s_dirpath = tmp1;
	return true;
}

void CVTKMFCTESTView::MarchingCube()
{	
	marchingCubes->SetInputConnection(reader->GetOutputPort());	
	marchingCubes->SetValue(0, 1500);		
	cubemapper->SetInputConnection(marchingCubes->GetOutputPort());	
	cubeactor->SetMapper(cubemapper);
	pvtkRenderer->AddActor(cubeactor);
	double bck[3];
	bck[0] = bck[1] = bck[2] = 0.5;
	pvtkRenderer->SetBackground(bck);
	pvtkRenderer->ResetCamera();
	pvtkRenderer->SetViewport(0, 0, 1.0, 1.0);
	return ;
}

void CVTKMFCTESTView::ChangeMarchingCube()
{		
	//pvtkRenderer->RemoveActor(cubeactor);
	//marchingCubes->SetValue(0, 1500 + num_color1);
	//cubemapper->SetInputConnection(marchingCubes->GetOutputPort());
	//cubeactor->SetMapper(cubemapper);
	//pvtkRenderer->AddActor(cubeactor);
	//pvtkRenderer->Render();
	//pvtkRenderer->GetRenderWindow()->Render();

	marchingCubes->SetValue(0, 1500 + num_color1);
	//cubemapper = (vtkPolyDataMapper*)cubeactor->GetMapper();
	//cubemapper->SetInputConnection(marchingCubes->GetOutputPort());
	//cubeactor->SetMapper(cubemapper);
	pvtkRenderer->GetRenderWindow()->Render();
	
}

void CVTKMFCTESTView::BoundaryVolume(std::string s_Indirpath)
{
	reader->SetDirectoryName(folder.c_str());
	reader->Update();

	int extent[6];
	double center[3];
	double origin[3];
	double spacing[3];
	reader->GetUpdateExtent(extent);
	reader->GetOutput()->GetOrigin(origin);
	reader->GetOutput()->GetSpacing(spacing);

	double* bounds = NULL;
	bounds = reader->GetOutput()->GetBounds();

	//CString msg;
	//msg.Format(L"b1:%f,b2:%f,b3:%f,b4:%f,b5:%f,b6:%f", bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5]);
	//AfxMessageBox(msg);


	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

	pVolumeReslice->SetInputConnection(reader->GetOutputPort());
	pVolumeReslice->SetOutputDimensionality(3);

	//static double axialX[3] = { 0.707, -0.707, 0 };
	//static double axialY[3] = { 0.707, 0.707, 0 };
	//static double axialZ[3] = { 0, 0, 1 };

	static double axialX[3] = { 1, 0, 0 };
	static double axialY[3] = { 0, 1, 0 };
	static double axialZ[3] = { 0, 0, 1 };

	pVolumeReslice->SetResliceAxesOrigin(center);
	pVolumeReslice->SetResliceAxesDirectionCosines(axialX, axialY, axialZ);

	pVolumeReslice->SetInterpolationModeToLinear();
	pVolumeReslice->Update();

	vtkSmartPointer<vtkImageData> image =
		vtkSmartPointer<vtkImageData>::New();
	image = pVolumeReslice->GetOutput();

	vtkSmartPointer<vtkSmartVolumeMapper> mapper =
		vtkSmartPointer<vtkSmartVolumeMapper>::New();

	//use default mode
	mapper->SetRequestedRenderMode(vtkSmartVolumeMapper::DefaultRenderMode);
	mapper->SetInputData(image);
	//mapper->SetInputData(reader->GetOutput());
	mapper->AutoAdjustSampleDistancesOn();
	mapper->SetBlendModeToComposite();

	//vtkSmartPointer<vtkPlane> plane =
	//	vtkSmartPointer<vtkPlane>::New();

	//plane->SetOrigin(0,0,-50);
	//plane->SetNormal(0, 0, 1);
	//mapper->AddClippingPlane(plane);

	//vtkSmartPointer<vtkPlane> plane1 =
	//	vtkSmartPointer<vtkPlane>::New();

	//plane1->SetOrigin(-50, 0, 0);
	//plane1->SetNormal(1, 0, 0);
	//mapper->AddClippingPlane(plane1);

	// Create our transfer function
	vtkSmartPointer<vtkColorTransferFunction> colorFun =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	vtkSmartPointer<vtkPiecewiseFunction> opacityFun =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	// Create the property and attach the transfer functions
	vtkSmartPointer<vtkVolumeProperty> property =
		vtkSmartPointer<vtkVolumeProperty>::New();
	property->SetIndependentComponents(true);
	property->SetColor(colorFun);
	property->SetScalarOpacity(opacityFun);
	property->SetInterpolationTypeToLinear();
	

	// Create our volume and mapper
	vtkSmartPointer<vtkVolume> volume =
		vtkSmartPointer<vtkVolume>::New();
	volume->SetProperty(property);
	volume->SetMapper(mapper);


	colorFun->AddRGBPoint(700, 0, 0, 0, 0.5, 0.0);
	colorFun->AddRGBPoint(1400, .74f, .37f, .0f, 0.49, 0);
	colorFun->AddRGBPoint(2300, .90, .82, .56, .5, 0);
	colorFun->AddRGBPoint(4000, 1, 1, 1, .5, 1.0);

	opacityFun->AddPoint(700, 0, .5, 0.0);
	opacityFun->AddPoint(1400, 0.1, .5, 0.0);
	opacityFun->AddPoint(2300, .2, 0.5, 0.0);
	opacityFun->AddPoint(4000, .8, 0.5, 0.0);


	property->ShadeOn();
	property->SetAmbient(0.1);
	property->SetDiffuse(0.9);
	property->SetSpecular(0.2);
	property->SetSpecularPower(10.0);
	property->SetScalarOpacityUnitDistance(0.5);


	//set render
	//double bck[3];
	//bck[0] = bck[1] = bck[2] = 0.5;
	//pvtkRenderer->SetBackground(bck);
	pvtkRenderer->AddVolume(volume);
	pvtkRenderer->ResetCamera();
	//pvtkRenderer->SetViewport(0, 0, 1.0, 1.0);

	pvtkRenderer->GetRenderWindow()->Render();
}

//ReOrientation

void CVTKMFCTESTView::ReOriVolumeRendering()
{
	//dir path
	//reader->SetDirectoryName(folder.c_str());
	//reader->Update();

	//dim
	int dim[3];
	reader->GetOutput()->GetDimensions(dim);

	vtkSmartPointer<vtkImageCast> cast =
		vtkSmartPointer<vtkImageCast>::New();
	cast->SetInputData((vtkDataObject*)reader->GetOutput());
	cast->SetOutputScalarTypeToFloat();
	cast->SetOutputScalarTypeToUnsignedChar();
	cast->Update();

	// Create our volume and mapper
	//vtkSmartPointer<vtkVolume> volume =
	//	vtkSmartPointer<vtkVolume>::New();

	//vtkSmartPointer<vtkSmartVolumeMapper> mapper =
	//	vtkSmartPointer<vtkSmartVolumeMapper>::New();

	//use default mode
	ReOrimapper->SetRequestedRenderMode(vtkSmartVolumeMapper::DefaultRenderMode);

	ReOrimapper->SetInputConnection(reader->GetOutputPort());
	ReOrimapper->AutoAdjustSampleDistancesOn();

	//get spacing
	double spacing[3];
	reader->GetOutput()->GetSpacing(spacing);

	// Create our transfer function
	// Create the property and attach the transfer functions
	//vtkSmartPointer<vtkVolumeProperty> property =
	//	vtkSmartPointer<vtkVolumeProperty>::New();
	ReOriproperty->SetIndependentComponents(true);
	ReOriproperty->SetColor(colorFun);
	ReOriproperty->SetScalarOpacity(opacityFun);
	ReOriproperty->SetInterpolationTypeToLinear();

	// connect up the volume to the property and the mapper
	ReOrivolume->SetProperty(ReOriproperty);
	ReOrivolume->SetMapper(ReOrimapper);
	ReOrivolume->RotateX(90);
	//must mark
	//ReOrivolume->RotateZ(-90);

	
	//ReOrivolume->SetPosition(0, 0, 0);
	//ReOrivolume->SetOrigin(0, 0, 0);
	ReOrivolume->SetPosition(ReOrivolume->GetCenter()[0], ReOrivolume->GetCenter()[1], ReOrivolume->GetCenter()[2]);
	ReOrivolume->SetOrigin(ReOrivolume->GetCenter()[0], ReOrivolume->GetCenter()[1], ReOrivolume->GetCenter()[2]);
	
	
	

	//double* vcenter = NULL;
	//vcenter = ReOrivolume->GetCenter();
	//CString msg;
	//msg.Format(L"x:%.2f,y:%.2f,z:%.2f", vcenter[0], vcenter[1], vcenter[2]);
	//AfxMessageBox(msg);

	//放color fun and opcity fun
	CT_Teeth();


	ReOrimapper->SetBlendModeToComposite();
	ReOriproperty->ShadeOn();
	ReOriproperty->SetAmbient(0.1);
	ReOriproperty->SetDiffuse(0.9);
	ReOriproperty->SetSpecular(0.2);
	ReOriproperty->SetSpecularPower(10.0);
	ReOriproperty->SetScalarOpacityUnitDistance(0.5);


	//set render
	double bck[3];
	bck[0] = bck[1] = bck[2] = 0.0;
	pvtkReOriVolumeRenderer->SetBackground(bck);
	pvtkReOriVolumeRenderer->AddVolume(ReOrivolume);
	pvtkReOriVolumeRenderer->ResetCamera();	
	pvtkReOriVolumeRenderer->SetViewport(0, 0, 0.7, 1.0);
	//pvtkReOriVolumeRenderer->SetViewport(0, 0, 1.0, 1.0);
	pvtkReOriVolumeRenderer->GetRenderWindow()->Render();

}
void CVTKMFCTESTView::ReOriXYCut()
{
	double bck[3];
	bck[0] = bck[1] = bck[2] = 0.0;
	pvtkReOriXYRenderer->SetBackground(bck);

	pvtkReOriXYRenderer->ResetCamera();

	pvtkReOriXYRenderer->SetViewport(0.7, 0, 1.0, 0.3333);
}
void CVTKMFCTESTView::ReOriYZCut()
{
	double bck[3];
	bck[0] = bck[1] = bck[2] = 0.0;
	pvtkReOriYZRenderer->SetBackground(bck);

	pvtkReOriYZRenderer->ResetCamera();
	pvtkReOriYZRenderer->SetViewport(0.7, 0.33, 1.0, 0.6666);
}
void CVTKMFCTESTView::ReOriXZCut()
{
	double bck[3];
	bck[0] = bck[1] = bck[2] = 0.0;
	pvtkReOriXZRenderer->SetBackground(bck);

	pvtkReOriXZRenderer->ResetCamera();
	pvtkReOriXZRenderer->SetViewport(0.7, 0.66, 1.0, 0.9999);
}


void CVTKMFCTESTView::ReOriRotationX(float angle)
{
	ReOrivolume->RotateX(angle);
	//ReOrivolume->RotateWXYZ(angle, 1, 0, 0);
	pvtkReOriVolumeRenderer->GetRenderWindow()->Render();
}
void CVTKMFCTESTView::ReOriRotationY(float angle)
{
	ReOrivolume->RotateY(angle);
	//ReOrivolume->RotateWXYZ(angle, 0, 1, 0);
	pvtkReOriVolumeRenderer->GetRenderWindow()->Render();
}
void CVTKMFCTESTView::ReOriRotationZ(float angle)
{
	ReOrivolume->RotateZ(angle);
	//ReOrivolume->RotateWXYZ(angle, 0, 0, 1);
	pvtkReOriVolumeRenderer->GetRenderWindow()->Render();
}

void CVTKMFCTESTView::ReOriTranslationX(float distance)
{
	
}
void CVTKMFCTESTView::ReOriTranslationY(float distance)
{

}
void CVTKMFCTESTView::ReOriTranslationZ(float distance)
{

}

void CVTKMFCTESTView::ShowXYPlaneImg()
{
	imageData->GetExtent(extent);
	imageData->GetSpacing(spacing);
	imageData->GetOrigin(origin);
	imageData->GetCenter(center);
	//imagw viewer2
	static double axialElements[16] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
	};
	resliceAxesXY->DeepCopy(axialElements);
	resliceAxesXY->SetElement(0, 3, center[0]);
	resliceAxesXY->SetElement(1, 3, center[1]);
	resliceAxesXY->SetElement(2, 3, center[2]);

	vtkSmartPointer<vtkImageReslice> reslice =
		vtkSmartPointer<vtkImageReslice>::New();	
	//reslice->SetInputConnection(reader->GetOutputPort());
	reslice->SetInputData(imageData);
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(resliceAxesXY);
	reslice->SetInterpolationModeToLinear();
	reslice->AutoCropOutputOn();

	vtkSmartPointer<vtkLookupTable> colorTable =
		vtkSmartPointer<vtkLookupTable>::New();	
	colorTable->SetRange(0, 1000);
	colorTable->SetValueRange(0.0, 1.0);
	colorTable->SetSaturationRange(0.0, 0.0);
	colorTable->SetRampToLinear();
	colorTable->Build();

	vtkSmartPointer<vtkImageMapToColors> colorMap =
		vtkSmartPointer<vtkImageMapToColors>::New();
	colorMap->SetLookupTable(colorTable);
	colorMap->SetInputConnection(reslice->GetOutputPort());	
	colorMap->Update();

	viewerXY->SetInputConnection(colorMap->GetOutputPort());
	viewerXY->SetRenderer(pvtkReOriXYRenderer);
	viewerXY->SetRenderWindow(pvtkReOriVolumeRenderer->GetRenderWindow());
	viewerXY->SetupInteractor(InteractorXY);
	//窗框是圖像的灰度範圍，窗位是窗寬的中心位置
	//SetColorWindow和SetColorLevel共同確定把輸入的image pixels values線性映射到的範圍。
	//實際映射的範圍是[2 * SetColorLevel – SetColorWindow, SetColorWindow]

	viewerXY->SetColorLevel(1574);//設置窗位
	viewerXY->SetColorWindow(5096);//設置窗寬
	viewerXY->SetSlice(40);
	viewerXY->SetSliceOrientationToXY();
	viewerXY->Render();

	InteractorXY->Initialize();
	//Interactor->Start();


	////image actor
	//static double axialElements[16] = {
	//1, 0, 0, 0,
	//0, 1, 0, 0,
	//0, 0, 1, 0,
	//0, 0, 0, 1
	//};
	//resliceAxesXY->DeepCopy(axialElements);
	//resliceAxesXY->SetElement(0, 3, center[0]);
	//resliceAxesXY->SetElement(1, 3, center[1]);
	//resliceAxesXY->SetElement(2, 3, center[2]);

	//vtkSmartPointer<vtkImageReslice> reslice =
	//	vtkSmartPointer<vtkImageReslice>::New();
	//reslice->SetInputConnection(reader->GetOutputPort());
	//reslice->SetOutputDimensionality(2);
	//reslice->SetResliceAxes(resliceAxesXY);
	//reslice->SetInterpolationModeToLinear();
	//reslice->AutoCropOutputOn();

	//vtkSmartPointer<vtkLookupTable> colorTable =
	//	vtkSmartPointer<vtkLookupTable>::New();	
	//colorTable->SetRange(0, 1000);
	//colorTable->SetValueRange(0.0, 1.0);
	//colorTable->SetSaturationRange(0.0, 0.0);
	//colorTable->SetRampToLinear();
	//colorTable->Build();

	//vtkSmartPointer<vtkImageMapToColors> colorMap =
	//	vtkSmartPointer<vtkImageMapToColors>::New();
	//colorMap->SetLookupTable(colorTable);
	//colorMap->SetInputConnection(reslice->GetOutputPort());	
	//colorMap->Update();



	//vtkSmartPointer<vtkImageActor> imgActor =
	//	vtkSmartPointer<vtkImageActor>::New();
	//imgActor->SetInputData(colorMap->GetOutput());	
	//pvtkReOriXYRenderer->AddActor(imgActor);	
	//pvtkReOriXYRenderer->GetRenderWindow()->Render();
}
void CVTKMFCTESTView::ShowXZPlaneImg()
{
	imageData->GetExtent(extent);
	imageData->GetSpacing(spacing);
	imageData->GetOrigin(origin);
	imageData->GetCenter(center);
	//imagw viewer2
	static double coronalElements[16] = {
			 1, 0, 0, 0,
			 0, 0, 1, 0,
			 0,-1, 0, 0,
			 0, 0, 0, 1 };


	resliceAxesXZ->DeepCopy(coronalElements);

	resliceAxesXZ->SetElement(0, 3, center[0]);
	resliceAxesXZ->SetElement(1, 3, center[1]);
	resliceAxesXZ->SetElement(2, 3, center[2]);

	vtkSmartPointer<vtkImageReslice> reslice =
		vtkSmartPointer<vtkImageReslice>::New();
	//reslice->SetInputConnection(reader->GetOutputPort());
	reslice->SetInputData(imageData);
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(resliceAxesXZ);
	reslice->SetInterpolationModeToLinear();	
	reslice->AutoCropOutputOn();

	vtkSmartPointer<vtkLookupTable> colorTable =
		vtkSmartPointer<vtkLookupTable>::New();
	colorTable->SetRange(0, 1000);
	colorTable->SetValueRange(0.0, 1.0);
	colorTable->SetSaturationRange(0.0, 0.0);
	colorTable->SetRampToLinear();
	colorTable->Build();

	vtkSmartPointer<vtkImageMapToColors> colorMap =
		vtkSmartPointer<vtkImageMapToColors>::New();
	colorMap->SetLookupTable(colorTable);
	colorMap->SetInputConnection(reslice->GetOutputPort());
	colorMap->Update();

	viewerXZ->SetInputConnection(colorMap->GetOutputPort());
	viewerXZ->SetRenderer(pvtkReOriXZRenderer);
	viewerXZ->SetRenderWindow(pvtkReOriVolumeRenderer->GetRenderWindow());	
	viewerXZ->SetupInteractor(InteractorXZ);
	viewerXZ->SetColorLevel(1574);
	viewerXZ->SetColorWindow(5096);
	viewerXZ->SetSlice(40);
	viewerXZ->SetSliceOrientationToXY();
	viewerXZ->Render();

	InteractorXZ->Initialize();
	//Interactor->Start();

	//static double coronalElements[16] = {
	//		 1, 0, 0, 0,
	//		 0, 0, 1, 0,
	//		 0,-1, 0, 0,
	//		 0, 0, 0, 1 };


	//resliceAxesXZ->DeepCopy(coronalElements);

	//resliceAxesXZ->SetElement(0, 3, center[0]);
	//resliceAxesXZ->SetElement(1, 3, center[1]);
	//resliceAxesXZ->SetElement(2, 3, center[2]);

	//vtkSmartPointer<vtkImageReslice> reslice =
	//	vtkSmartPointer<vtkImageReslice>::New();
	//reslice->SetInputConnection(reader->GetOutputPort());
	//reslice->SetOutputDimensionality(2);
	//reslice->SetResliceAxes(resliceAxesXZ);
	//reslice->SetInterpolationModeToLinear();	

	//vtkSmartPointer<vtkLookupTable> colorTable =
	//	vtkSmartPointer<vtkLookupTable>::New();
	//colorTable->SetRange(0, 1000);
	//colorTable->SetValueRange(0.0, 1.0);
	//colorTable->SetSaturationRange(0.0, 0.0);
	//colorTable->SetRampToLinear();
	//colorTable->Build();

	//vtkSmartPointer<vtkImageMapToColors> colorMap =
	//	vtkSmartPointer<vtkImageMapToColors>::New();
	//colorMap->SetLookupTable(colorTable);
	//colorMap->SetInputConnection(reslice->GetOutputPort());
	//colorMap->Update();

	//vtkSmartPointer<vtkImageActor> imgActor =
	//	vtkSmartPointer<vtkImageActor>::New();
	//imgActor->SetInputData(colorMap->GetOutput());
	//pvtkReOriXZRenderer->AddActor(imgActor);
	//pvtkReOriXZRenderer->GetRenderWindow()->Render();
}
void CVTKMFCTESTView::ShowYZPlaneImg()
{
	imageData->GetExtent(extent);
	imageData->GetSpacing(spacing);
	imageData->GetOrigin(origin);
	imageData->GetCenter(center);
	//imagw viewer2
	static double sagittalElements[16] = {
			 0, 0,-1, 0,
			 1, 0, 0, 0,
			 0,-1, 0, 0,
			 0, 0, 0, 1 };

	resliceAxesYZ->DeepCopy(sagittalElements);


	resliceAxesYZ->SetElement(0, 3, center[0]);
	resliceAxesYZ->SetElement(1, 3, center[1]);
	resliceAxesYZ->SetElement(2, 3, center[2]);

	vtkSmartPointer<vtkImageReslice> reslice =
		vtkSmartPointer<vtkImageReslice>::New();
	//reslice->SetInputConnection(reader->GetOutputPort());
	reslice->SetInputData(imageData);
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(resliceAxesYZ);
	reslice->SetInterpolationModeToLinear();
	reslice->AutoCropOutputOn();

	vtkSmartPointer<vtkLookupTable> colorTable =
		vtkSmartPointer<vtkLookupTable>::New();
	colorTable->SetRange(0, 1000);
	colorTable->SetValueRange(0.0, 1.0);
	colorTable->SetSaturationRange(0.0, 0.0);
	colorTable->SetRampToLinear();
	colorTable->Build();

	vtkSmartPointer<vtkImageMapToColors> colorMap =
		vtkSmartPointer<vtkImageMapToColors>::New();
	colorMap->SetLookupTable(colorTable);
	colorMap->SetInputConnection(reslice->GetOutputPort());
	colorMap->Update();
	
	viewerYZ->SetInputConnection(colorMap->GetOutputPort());
	viewerYZ->SetRenderer(pvtkReOriYZRenderer);
	viewerYZ->SetRenderWindow(pvtkReOriVolumeRenderer->GetRenderWindow());
	viewerYZ->SetupInteractor(InteractorYZ);
	viewerYZ->SetColorLevel(750);
	viewerYZ->SetColorWindow(3500);
	viewerYZ->SetSlice(0);
	viewerYZ->SetSliceOrientationToXY();
	viewerYZ->Render();

	InteractorYZ->Initialize();
	//Interactor->Start();

	//
	//static double sagittalElements[16] = {
	//		 0, 0,-1, 0,
	//		 1, 0, 0, 0,
	//		 0,-1, 0, 0,
	//		 0, 0, 0, 1 };

	//resliceAxesYZ->DeepCopy(sagittalElements);

	//resliceAxesYZ->SetElement(0, 3, center[0]);
	//resliceAxesYZ->SetElement(1, 3, center[1]);
	//resliceAxesYZ->SetElement(2, 3, center[2]);

	//vtkSmartPointer<vtkImageReslice> reslice =
	//	vtkSmartPointer<vtkImageReslice>::New();
	//reslice->SetInputConnection(reader->GetOutputPort());
	//reslice->SetOutputDimensionality(2);
	//reslice->SetResliceAxes(resliceAxesYZ);
	//reslice->SetInterpolationModeToLinear();

	//vtkSmartPointer<vtkLookupTable> colorTable =
	//	vtkSmartPointer<vtkLookupTable>::New();
	//colorTable->SetRange(0, 1000);
	//colorTable->SetValueRange(0.0, 1.0);
	//colorTable->SetSaturationRange(0.0, 0.0);
	//colorTable->SetRampToLinear();
	//colorTable->Build();

	//vtkSmartPointer<vtkImageMapToColors> colorMap =
	//	vtkSmartPointer<vtkImageMapToColors>::New();
	//colorMap->SetLookupTable(colorTable);
	//colorMap->SetInputConnection(reslice->GetOutputPort());
	//colorMap->Update();

	//vtkSmartPointer<vtkImageActor> imgActor =
	//	vtkSmartPointer<vtkImageActor>::New();
	//imgActor->SetInputData(colorMap->GetOutput());
	//pvtkReOriYZRenderer->AddActor(imgActor);
	//pvtkReOriYZRenderer->GetRenderWindow()->Render();
}

void CVTKMFCTESTView::DrawCoorLineX()
{
	int* r_size = NULL;
	r_size = pvtkReOriVolumeRenderer->GetSize();
	double* center = NULL;
	center = ReOrivolume->GetCenter();


	double p0[3] = { 0, center[1] - center[1]*0.05, center[2] };
	double p1[3] = { center[0]*2, center[1] - center[1] * 0.05, center[2] };

	vtkSmartPointer<vtkLineSource> lineSource =
		vtkSmartPointer<vtkLineSource>::New();
	lineSource->SetPoint1(p0);
	lineSource->SetPoint2(p1);
	lineSource->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(lineSource->GetOutputPort());


	lineActorX->SetMapper(mapper);
	lineActorX->GetProperty()->SetColor(1, 0, 0);
	lineActorX->GetProperty()->SetLineWidth(1);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(pvtkReOriVolumeRenderer->GetRenderWindow());

	pvtkReOriVolumeRenderer->AddActor(lineActorX);
	
	renderWindowInteractor->Initialize();

}
void CVTKMFCTESTView::DrawCoorLineY()
{
	int* r_size = NULL;
	r_size = pvtkReOriVolumeRenderer->GetSize();
	double* center = NULL;
	center = ReOrivolume->GetCenter();


	double p0[3] = { center[0], 0, center[2] };
	double p1[3] = { center[0], center[1]*2, center[2] };

	vtkSmartPointer<vtkLineSource> lineSource =
		vtkSmartPointer<vtkLineSource>::New();
	lineSource->SetPoint1(p0);
	lineSource->SetPoint2(p1);
	lineSource->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(lineSource->GetOutputPort());


	lineActorY->SetMapper(mapper);
	lineActorY->GetProperty()->SetColor(0, 1, 0);
	lineActorY->GetProperty()->SetLineWidth(1);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(pvtkReOriVolumeRenderer->GetRenderWindow());

	pvtkReOriVolumeRenderer->AddActor(lineActorY);

	renderWindowInteractor->Initialize();

}
void CVTKMFCTESTView::DrawCoorLineZ()
{
	int* r_size = NULL;
	r_size = pvtkReOriVolumeRenderer->GetSize();
	double* center = NULL;
	center = ReOrivolume->GetCenter();


	double p0[3] = { center[0], center[1] - center[1] * 0.05, 0 };
	double p1[3] = { center[0], center[1] - center[1] * 0.05, center[2]*2 };

	vtkSmartPointer<vtkLineSource> lineSource =
		vtkSmartPointer<vtkLineSource>::New();
	lineSource->SetPoint1(p0);
	lineSource->SetPoint2(p1);
	lineSource->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(lineSource->GetOutputPort());


	lineActorZ->SetMapper(mapper);
	lineActorZ->GetProperty()->SetColor(0, 0, 1);
	lineActorZ->GetProperty()->SetLineWidth(1);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(pvtkReOriVolumeRenderer->GetRenderWindow());

	pvtkReOriVolumeRenderer->AddActor(lineActorZ);

	renderWindowInteractor->Initialize();

}

void CVTKMFCTESTView::Coordinate()
{
	vtkSmartPointer<vtkTransform> transform =
		vtkSmartPointer<vtkTransform>::New();
	transform->Translate(1.0, 0.0, 0.0);
	vtkSmartPointer<vtkAxesActor> axes =
		vtkSmartPointer<vtkAxesActor>::New();
	axes->SetPosition(0, 0, 0);
	axes->SetTotalLength(20.0, 20.0, 20.0);
	axes->SetShaftType(0);
	axes->SetAxisLabels(0);
	axes->SetCylinderRadius(0.02);
	axes->SetUserTransform(transform);
	pvtkReOriVolumeRenderer->AddActor(axes);
	pvtkReOriVolumeRenderer->ResetCamera();

}

void CVTKMFCTESTView::SetCameraSide()
{
	vtkCamera* vCamera = pvtkReOriVolumeRenderer->GetActiveCamera();
	vCamera->SetPosition(20, 0, 0);
	vCamera->SetFocalPoint(0, 0, 0);
	vCamera->SetViewUp(0, 1, 0);
	pvtkReOriVolumeRenderer->SetActiveCamera(vCamera);
	pvtkReOriVolumeRenderer->ResetCamera();
}
void CVTKMFCTESTView::SetCameraTop()
{
	vtkCamera* vCamera = pvtkReOriVolumeRenderer->GetActiveCamera();
	vCamera->SetPosition(0, 20, 0);
	vCamera->SetFocalPoint(0, 0, 0);	
	vCamera->SetViewUp(0, 0, -1);
	pvtkReOriVolumeRenderer->SetActiveCamera(vCamera);
	pvtkReOriVolumeRenderer->ResetCamera();
}
void CVTKMFCTESTView::SetCameraFace()
{
	vtkCamera* vCamera = pvtkReOriVolumeRenderer->GetActiveCamera();
	vCamera->SetPosition(0, 0, 20);
	vCamera->SetFocalPoint(0, 0, 0);
	vCamera->SetViewUp(0, 1, 0);
	pvtkReOriVolumeRenderer->SetActiveCamera(vCamera);
	pvtkReOriVolumeRenderer->ResetCamera();
}
void CVTKMFCTESTView::UpdateXYPlaneImg()
{

}
void CVTKMFCTESTView::UpdateXZPlaneImg()
{
}
void CVTKMFCTESTView::UpdateYZPlaneImg()
{
}

#include <vtkStripper.h>
bool CVTKMFCTESTView::FileOpenMergeImgData(std::string s_Indirpath)
{
	typedef unsigned char PixelType;
	const unsigned int Dimension = 3;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::ImageSeriesReader<ImageType> ReaderType;

	typedef itk::GDCMSeriesFileNames NamesGeneratorType;
	NamesGeneratorType::Pointer namesGenerator = NamesGeneratorType::New();

	std::vector<ReaderType::Pointer>reader;

	typedef std::vector< std::string > SeriesIdContainer;
	SeriesIdContainer seriesUID;

	using NamesGeneratorType = itk::GDCMSeriesFileNames;
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();

	nameGenerator->SetUseSeriesDetails(true);
	nameGenerator->AddSeriesRestriction("0008|0021");	
	nameGenerator->SetGlobalWarningDisplay(false);	
	nameGenerator->SetDirectory(s_Indirpath);

	try
	{
		using SeriesIdContainer = std::vector<std::string>;
		const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();
		auto                      seriesItr = seriesUID.begin();
		auto                      seriesEnd = seriesUID.end();

		while (seriesItr != seriesEnd)
		{
			std::cout << seriesItr->c_str() << std::endl;
			++seriesItr;
		}

		seriesItr = seriesUID.begin();
		using ReaderType = itk::ImageSeriesReader<ImageType>;
		ReaderType::Pointer ireader = ReaderType::New();
		while (seriesItr != seriesUID.end())
		{
			std::string seriesIdentifier;
			{
				seriesIdentifier = seriesItr->c_str();
				seriesItr++;
			}
			
			using FileNamesContainer = std::vector<std::string>;
			FileNamesContainer fileNames = nameGenerator->GetFileNames(seriesIdentifier);


			using ImageIOType = itk::GDCMImageIO;
			ImageIOType::Pointer dicomIO = ImageIOType::New();
			ireader->SetImageIO(dicomIO);
			ireader->SetFileNames(fileNames);
			ireader->ForceOrthogonalDirectionOff(); // properly read CTs with gantry tilt

			typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
			ConnectorType::Pointer connector = ConnectorType::New();
			
			connector->SetInput(ireader->GetOutput());
			connector->Update();

			imageData->DeepCopy(connector->GetOutput());
		}
		////dim
		//int dim[3];
		//imageData->GetDimensions(dim);

		//vtkSmartPointer<vtkImageCast> cast =
		//	vtkSmartPointer<vtkImageCast>::New();
		//cast->SetInputData(imageData);
		//cast->SetOutputScalarTypeToFloat();
		//cast->SetOutputScalarTypeToUnsignedChar();
		//cast->Update();

		//// Create our volume and mapper
		////vtkSmartPointer<vtkVolume> volume =
		////	vtkSmartPointer<vtkVolume>::New();

		////vtkSmartPointer<vtkSmartVolumeMapper> mapper =
		////	vtkSmartPointer<vtkSmartVolumeMapper>::New();

		////use default mode
		//ReOrimapper->SetRequestedRenderMode(vtkSmartVolumeMapper::DefaultRenderMode);

		//ReOrimapper->SetInputConnection(cast->GetOutputPort());
		//ReOrimapper->AutoAdjustSampleDistancesOn();

		////get spacing
		//double spacing[3];
		//cast->GetOutput()->GetSpacing(spacing);

		//// Create our transfer function
		//// Create the property and attach the transfer functions
		////vtkSmartPointer<vtkVolumeProperty> property =
		////	vtkSmartPointer<vtkVolumeProperty>::New();
		//ReOriproperty->SetIndependentComponents(true);
		//ReOriproperty->SetColor(colorFun);
		//ReOriproperty->SetScalarOpacity(opacityFun);
		//ReOriproperty->SetInterpolationTypeToLinear();

		//// connect up the volume to the property and the mapper
		//ReOrivolume->SetProperty(ReOriproperty);
		//ReOrivolume->SetMapper(ReOrimapper);
		//ReOrivolume->RotateX(90);
		////must mark
		////ReOrivolume->RotateZ(-90);


		////ReOrivolume->SetPosition(0, 0, 0);
		////ReOrivolume->SetOrigin(0, 0, 0);
		//ReOrivolume->SetPosition(ReOrivolume->GetCenter()[0], ReOrivolume->GetCenter()[1], ReOrivolume->GetCenter()[2]);
		//ReOrivolume->SetOrigin(ReOrivolume->GetCenter()[0], ReOrivolume->GetCenter()[1], ReOrivolume->GetCenter()[2]);




		////double* vcenter = NULL;
		////vcenter = ReOrivolume->GetCenter();
		////CString msg;
		////msg.Format(L"x:%.2f,y:%.2f,z:%.2f", vcenter[0], vcenter[1], vcenter[2]);
		////AfxMessageBox(msg);

		////放color fun and opcity fun
		//CT_Teeth();


		//ReOrimapper->SetBlendModeToComposite();
		//ReOriproperty->ShadeOn();
		//ReOriproperty->SetAmbient(0.1);
		//ReOriproperty->SetDiffuse(0.9);
		//ReOriproperty->SetSpecular(0.2);
		//ReOriproperty->SetSpecularPower(10.0);
		//ReOriproperty->SetScalarOpacityUnitDistance(0.5);


		////set render
		//double bck[3];
		//bck[0] = bck[1] = bck[2] = 0.0;
		//pvtkReOriVolumeRenderer->SetBackground(bck);
		//pvtkReOriVolumeRenderer->AddVolume(ReOrivolume);
		//pvtkReOriVolumeRenderer->ResetCamera();
		//pvtkReOriVolumeRenderer->SetViewport(0, 0, 1.0, 1.0);
		//pvtkReOriVolumeRenderer->GetRenderWindow()->Render();

	vtkSmartPointer<vtkDataSetMapper> mapper =
			vtkSmartPointer<vtkDataSetMapper>::New();
	#if VTK_MAJOR_VERSION <= 5
		mapper->SetInputConnection(imageData->GetProducerPort());
	#else
		mapper->SetInputData(imageData);
	#endif
		vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);

		vtkSmartPointer<vtkRenderWindow> renderWindow =
			vtkSmartPointer<vtkRenderWindow>::New();

		vtkSmartPointer<vtkRenderer> renderer =
			vtkSmartPointer<vtkRenderer>::New();

		// Add both renderers to the window		
		renderWindow->AddRenderer(renderer);

		// Add a sphere to the left and a cube to the right
		renderer->AddActor(actor);
		renderer->SetBackground(0, 0, 0);

		renderer->ResetCamera();

		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		renderWindowInteractor->SetRenderWindow(renderWindow);
		renderWindow->Render();
		renderWindowInteractor->Start();
	}
	catch (itk::ExceptionObject & ex)
	{
		std::cout << ex << std::endl;
		return EXIT_FAILURE;
	}
//	//typedef signed short    PixelType;
//	//const unsigned int      Dimension = 3;
//	//typedef itk::Image< PixelType, Dimension >         ImageType;
//	//typedef itk::ImageSeriesReader< ImageType >        ReaderType;
//	//ReaderType::Pointer itkReader = ReaderType::New();
//	//typedef itk::GDCMImageIO       ImageIOType;
//	//ImageIOType::Pointer dicomIO = ImageIOType::New();
//	//itkReader->SetImageIO(dicomIO);
//	//typedef itk::GDCMSeriesFileNames NamesGeneratorType;
//	//NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
//	//nameGenerator->SetUseSeriesDetails(true);
//	//nameGenerator->AddSeriesRestriction("0008|0021");
//	//nameGenerator->SetDirectory(s_Indirpath);
//
//	//typedef std::vector< std::string >    SeriesIdContainer;
//	//const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();
//	//SeriesIdContainer::const_iterator seriesItr = seriesUID.begin();
//	//SeriesIdContainer::const_iterator seriesEnd = seriesUID.end();
//	//std::string seriesIdentifier;
//	//seriesIdentifier = seriesUID.begin()->c_str();
//	//typedef std::vector< std::string >   FileNamesContainer;
//	//FileNamesContainer fileNames;
//	//fileNames = nameGenerator->GetFileNames(seriesIdentifier);
//	//itkReader->SetFileNames(fileNames);
//	//itkReader->Update();
//	//dicomIO->GetMetaDataDictionary();
//
//	///////////////////////////////////////////////////////////////////
//	namesGenerator->SetUseSeriesDetails(true);
//	// (0008, 0021) 系列資料
//	// (0008, 103E) 系列說明
//	namesGenerator->AddSeriesRestriction("0008|0021");
//	//namesGenerator->AddSeriesRestriction("0008|103E");
//	namesGenerator->SetInputDirectory(s_Indirpath);
//
//	typedef std::vector< std::string > SeriesIdContainer;
//	seriesUID = namesGenerator->GetSeriesUIDs();
//	SeriesIdContainer::const_iterator seriesItr = seriesUID.begin();
//	SeriesIdContainer::const_iterator seriesEnd = seriesUID.end();
//	std::string seriesIdentifier;
//	seriesIdentifier = seriesUID.begin()->c_str();
//
//	// ITK to VTK
//	typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
//	ConnectorType::Pointer connector = ConnectorType::New();
//	
//
//	// 使用GDCM來讀取DICOM，ITK內有許多不同的影像的IO可做選擇
//	typedef itk::GDCMImageIO ImageIOType;
//	ImageIOType::Pointer gdcmIO = ImageIOType::New();
//
//	typedef std::vector< std::string > FileNamesContainer;
//	FileNamesContainer fileNames;
//
//	dcmreader.clear();
//
//	// Read Select DICOM Series
//	ReaderType::Pointer reader_buffer = ReaderType::New();			
//	fileNames = namesGenerator->GetFileNames(seriesIdentifier);
//	
//
//	reader_buffer->SetImageIO(gdcmIO);
//	reader_buffer->SetFileNames(fileNames);
//	dcmreader.push_back(reader_buffer);
//
//	for (int i = 0; i < dcmreader.size(); i++)
//	{
//		dcmreader[i]->Update();
//	}
//
//	for (int i = 0; i < dcmreader.size(); i++)
//	{
//		// ITK to VTK
//		connector->SetInput(dcmreader[i]->GetOutput());
//		connector->Update();
//
//		imageData->DeepCopy(connector->GetOutput());
//
//		int resilceExtent[6];
//		connector->GetOutput()->GetExtent(resilceExtent);
//
//		// 軟體利用vector進行影像資料的儲存
//		// vector的樣板為vtkImageData
//		// 為了要方便控管所使用的vtkImageData為二維型式
//		// 因此vector的大小等於影像的切片數
//
//		// Get output image data
//		for (int z = resilceExtent[5]; z >= resilceExtent[4]; z--)
//		{
//			// 換一個切片就重新創建一個新的vtkImageData，因為VTK與ITK皆使用指標運作，所以不重新創建一個新的會造成存放在vector中的影像一直被變動
//			vtkSmartPointer<vtkImageData> pixelBuffer = vtkSmartPointer<vtkImageData>::New();
//			pixelBuffer->SetExtent(resilceExtent[0], resilceExtent[1], resilceExtent[2], resilceExtent[3], 0, 0);
//			// 影像的格式為float，通道數為三(三通道的影像才能是彩色的)
//			pixelBuffer->AllocateScalars(VTK_FLOAT, 3);
//
//			imageData2D.push_back(pixelBuffer);
//
//#pragma omp parallel for
//			for (int y = resilceExtent[2]; y <= resilceExtent[3]; y++)
//			{
//				for (int x = resilceExtent[0]; x <= resilceExtent[1]; x++)
//				{
//					float intensity;
//
//					// 以下為vtkImageData取值的方式如下，如果等到左邊用float*的型式其配合的為static_cast<float*>
//					float* connectorPixel = static_cast<float*>(connector->GetOutput()->GetScalarPointer(x, resilceExtent[3] - y, z));
//					float* imageData2DPixel = static_cast<float*>(imageData2D[resilceExtent[5] - z]->GetScalarPointer(x, y, 0));
//					intensity = connectorPixel[0];
//
//					imageData2DPixel[0] = intensity;
//					imageData2DPixel[1] = intensity;
//					imageData2DPixel[2] = intensity;
//				}
//			}
//		}
//		// 設定影像的切片數		
//	}
//	vtkSmartPointer<vtkDataSetMapper> mapper =
//		vtkSmartPointer<vtkDataSetMapper>::New();
//#if VTK_MAJOR_VERSION <= 5
//	mapper->SetInputConnection(imageData->GetProducerPort());
//#else
//	mapper->SetInputData(imageData);
//#endif
//	vtkSmartPointer<vtkActor> actor =
//		vtkSmartPointer<vtkActor>::New();
//	actor->SetMapper(mapper);
//
//	vtkSmartPointer<vtkRenderWindow> renderWindow =
//		vtkSmartPointer<vtkRenderWindow>::New();
//
//	vtkSmartPointer<vtkRenderer> renderer =
//		vtkSmartPointer<vtkRenderer>::New();
//
//	// Add both renderers to the window
//	renderWindow->AddRenderer(renderer);
//
//	// Add a sphere to the left and a cube to the right
//	renderer->AddActor(actor);
//
//	renderer->ResetCamera();
//
//	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//		vtkSmartPointer<vtkRenderWindowInteractor>::New();
//	renderWindowInteractor->SetRenderWindow(renderWindow);
//	renderWindow->Render();
//	renderWindowInteractor->Start();

}

void CVTKMFCTESTView::TestITK(std::string s_Indirpath)
{
	if (1)
	{
		typedef signed short InputPixelType;
		const unsigned int   InputDimension = 2;
		typedef itk::Image< InputPixelType, InputDimension > InputImageType;
		typedef itk::ImageSeriesReader< InputImageType > ReaderType;
		ReaderType::Pointer reader = ReaderType::New();
		reader->SetFileName("D://case2//I0000000079.dcm");
		typedef itk::GDCMImageIO           ImageIOType;
		ImageIOType::Pointer gdcmImageIO = ImageIOType::New();

		reader->SetImageIO(gdcmImageIO);
		//try
		{
			reader->Update();
			reader->GetMetaDataDictionary();
			gdcmImageIO->GetMetaDataDictionary();

			//pixelType
			int pixelType = gdcmImageIO->GetPixelType();	
			string str_pixelType = "PixelType:" + to_string(pixelType);
			OutPutDebugView(str_pixelType);

			//componetType
			int componetType = gdcmImageIO->GetComponentType();
			string str_componetType = "ComponetType:" + to_string(componetType);
			OutPutDebugView(str_componetType);

			//fileType
			int fileType = gdcmImageIO->GetFileType();
			string str_fileType = "FileType:" + to_string(fileType);
			OutPutDebugView(str_fileType);

			//??
			ImageIOType::ByteOrder byteOrder;
			byteOrder = gdcmImageIO->GetByteOrder();

			//Dimensions
			unsigned int dim = 0;
			gdcmImageIO->GetDimensions(dim);


			ImageIOType::SizeType imgSize;
			imgSize = gdcmImageIO->GetImageSizeInPixels();
			string str_imgSize = "ImgSize:" + to_string(imgSize);
			OutPutDebugView(str_imgSize);

			//componetSize
			int componetSize = gdcmImageIO->GetComponentSize();
			string str_componetSize = "ComponetSize:" + to_string(componetSize);
			OutPutDebugView(str_componetSize);
			//dimension
			int dimension = gdcmImageIO->GetNumberOfDimensions();
			int ori = 0;
			gdcmImageIO->GetOrigin(ori);
			int spa = 0;
			gdcmImageIO->GetSpacing(spa);

			ImageIOType::TCompressionType compressType;
			compressType = gdcmImageIO->GetCompressionType();

			InputImageType::SpacingType type;
			type = reader->GetOutput()->GetSpacing();
			int stypesize = type.Size();
			for (size_t i = 0; i < stypesize; i++)
			{
				if (i == 0)
				{
					string str_spacing = "SpacingX:" + to_string(type[i]);
					OutPutDebugView(str_spacing);
				}									
				else
				{
					string str_spacing = "SpacingY:" + to_string(type[i]);
					OutPutDebugView(str_spacing);
				}
				
			}

			//return;
			InputImageType::PointType origin;
			origin = reader->GetOutput()->GetOrigin();

			//Get CT Para
			//病患名稱
			char* name = new char[50];
			gdcmImageIO->GetPatientName(name);
			std::string str_name(name);
			std::string out_str_name = "ComponetType:" + str_name;
			OutPutDebugView(out_str_name);

			//Patient ID
			char* patientID = new char[50];
			gdcmImageIO->GetPatientID(patientID);
			std::string str_patientID(patientID);
			std::string out_str_patientID = "patientID:" + str_patientID;
			OutPutDebugView(out_str_patientID);

			//性別
			char* sex = new char[50];
			gdcmImageIO->GetPatientSex(sex);
			std::string str_sex(sex);
			std::string out_str_sex = "性別:" + str_sex;
			OutPutDebugView(out_str_sex);

			//age
			char* age = new char[50];
			gdcmImageIO->GetPatientAge(age);
			std::string str_age(age);
			std::string out_str_age = "age:" + str_age;
			OutPutDebugView(out_str_age);

			//Study ID
			char* studyID = new char[50];
			gdcmImageIO->GetStudyID(studyID);
			std::string str_studyID(studyID);
			std::string out_str_studyID = "Study ID:" + str_studyID;
			OutPutDebugView(out_str_studyID);

			//PatientDOB(Day of Birthday 生日!)
			char* PatientDOB = new char[50];
			gdcmImageIO->GetPatientDOB(PatientDOB);
			std::string str_PatientDOB(PatientDOB);
			std::string out_str_PatientDOB = "PatientDOB:" + str_PatientDOB;
			OutPutDebugView(out_str_PatientDOB);

			//StudyDescription
			char* StudyDescription = new char[50];
			gdcmImageIO->GetStudyDescription(StudyDescription);
			std::string str_StudyDescription(StudyDescription);
			std::string out_str_StudyDescription = "StudyDescription:" + str_StudyDescription;			
			OutPutDebugView(out_str_StudyDescription);
			//test 
			CString strP;
			strP = CString(StudyDescription);
			AfxMessageBox(strP);


			//BodyPart
			char* BodyPart = new char[50];
			gdcmImageIO->GetBodyPart(BodyPart);
			std::string str_BodyPart(BodyPart);
			std::string out_str_BodyPart = "BodyPart:" + str_BodyPart;
			OutPutDebugView(out_str_BodyPart);
			
			//NumberOfSeriesInStudy
			char* SeriesInStudy = new char[50];
			gdcmImageIO->GetNumberOfSeriesInStudy(SeriesInStudy);
			std::string str_SeriesInStudy(SeriesInStudy);
			std::string out_str_SeriesInStudy = "NumberOfSeriesInStudy:" + str_SeriesInStudy;
			OutPutDebugView(out_str_SeriesInStudy);

			//NumberOfStudyRelatedSeries
			char* StudyRelatedSeries = new char[50];
			gdcmImageIO->GetNumberOfStudyRelatedSeries(StudyRelatedSeries);
			std::string str_StudyRelatedSeries(StudyRelatedSeries);
			std::string out_str_StudyRelatedSeries = "NumberOfStudyRelatedSeries:" + str_StudyRelatedSeries;
			OutPutDebugView(out_str_StudyRelatedSeries);

			//掃描時間
			char* time = new char[50];
			gdcmImageIO->GetStudyDate(time);
			std::string str_time(time);
			std::string out_str_time = "掃描時間:" + str_time;
			OutPutDebugView(out_str_time);


			//模態
			char* modility = new char[50];
			gdcmImageIO->GetModality(modility);
			std::string str_modility(modility);
			std::string out_str_modility = "模態:" + str_modility;
			OutPutDebugView(out_str_modility);

			//機台
			char* manufacture = new char[50];
			gdcmImageIO->GetManufacturer(manufacture);
			std::string str_manufacture(manufacture);
			std::string out_str_manufacture = "機台:" + str_manufacture;
			OutPutDebugView(out_str_manufacture);


			//醫院
			char* hospital = new char[50];
			gdcmImageIO->GetInstitution(hospital);
			std::string str_hospital(hospital);
			std::string out_str_hospital = "醫院:" + str_hospital;
			OutPutDebugView(out_str_hospital);

			//Model
			char* Model = new char[50];
			gdcmImageIO->GetModel(Model);
			std::string str_Model(Model);
			std::string out_str_Model = "Model:" + str_Model;
			OutPutDebugView(out_str_Model);

			//ScanOptions
			char* ScanOptions = new char[50];
			gdcmImageIO->GetScanOptions(ScanOptions);
			std::string str_ScanOptions(ScanOptions);
			std::string out_str_ScanOptions = "ScanOptions:" + str_ScanOptions;
			OutPutDebugView(out_str_ScanOptions);

			
			//end
		}
	}	
}



void CVTKMFCTESTView::OutPutDebugView(std::string s_string)
{
	std::string tmp = "[minbear] ";
	tmp += s_string;
	OutputDebugStringA(tmp.c_str());
}

void CVTKMFCTESTView::SetVolumeRenderingRender()
{
	//set render
	double bck[3];
	bck[0] = bck[1] = bck[2] = 0.0;
	vtkVolumeRenderingRender->SetBackground(bck);	
	vtkVolumeRenderingRender->ResetCamera();
	vtkVolumeRenderingRender->SetViewport(0, 0, 0.7, 1.0);
	vtkVolumeRenderingRender->GetRenderWindow()->Render();
}
void CVTKMFCTESTView::SetResliceSagittalRender()
{
	double bck[3];
	bck[0] = bck[1] = bck[2] = 0.0;
	vtkSagittalRenderer->SetBackground(bck);

	vtkSagittalRenderer->ResetCamera();

	vtkSagittalRenderer->SetViewport(0.7, 0, 1.0, 0.3333);
}
void CVTKMFCTESTView::SetResliceCoronalRender()
{
	double bck[3];
	bck[0] = bck[1] = bck[2] = 0.0;
	vtkCoronalRenderer->SetBackground(bck);

	vtkCoronalRenderer->ResetCamera();
	vtkCoronalRenderer->SetViewport(0.7, 0.33, 1.0, 0.6666);
}
void CVTKMFCTESTView::SetResliceAxialRender()
{
	double bck[3];
	bck[0] = bck[1] = bck[2] = 0.0;
	vtkAxialRenderer->SetBackground(bck);

	vtkAxialRenderer->ResetCamera();
	vtkAxialRenderer->SetViewport(0.7, 0.66, 1.0, 0.9999);
}

void CVTKMFCTESTView::ShowSagittalImage()
{
	imageData->GetExtent(extent);
	imageData->GetSpacing(spacing);
	imageData->GetOrigin(origin);
	imageData->GetCenter(center);
	//imagw viewer2
	static double sagittalElements[16] = {
			 0, 0,-1, 0,
			 1, 0, 0, 0,
			 0,-1, 0, 0,
			 0, 0, 0, 1 };

	axesSagittal->DeepCopy(sagittalElements);
	axesSagittal->SetElement(0, 3, center[0]);
	axesSagittal->SetElement(1, 3, center[1]);
	axesSagittal->SetElement(2, 3, center[2]);

	imageResliceSagittal->SetInputData(imageData);
	imageResliceSagittal->SetOutputDimensionality(2);
	imageResliceSagittal->SetResliceAxes(axesSagittal);
	imageResliceSagittal->SetInterpolationModeToLinear();
	imageResliceSagittal->AutoCropOutputOn();

	viewerSagittal->SetInputConnection(imageResliceSagittal->GetOutputPort());
	viewerSagittal->SetRenderer(vtkSagittalRenderer);
	viewerSagittal->SetRenderWindow(vtkVolumeRenderingRender->GetRenderWindow());
	viewerSagittal->SetupInteractor(rootExtractionInteractor);
	viewerSagittal->SetColorLevel(1574);
	viewerSagittal->SetColorWindow(5096);
	viewerSagittal->SetSliceOrientationToXY();
	viewerSagittal->Render();
	vtkSagittalRenderer->ResetCamera();
	vtkSagittalRenderer->Render();
}

void CVTKMFCTESTView::ShowCoronalImage()
{
	imageData->GetExtent(extent);
	imageData->GetSpacing(spacing);
	imageData->GetOrigin(origin);
	imageData->GetCenter(center);
	//imagw viewer2
	static double coronalElements[16] = {
			 1, 0, 0, 0,
			 0, 0, 1, 0,
			 0,-1, 0, 0,
			 0, 0, 0, 1 };


	axesCoronal->DeepCopy(coronalElements);
	axesCoronal->SetElement(0, 3, center[0]);
	axesCoronal->SetElement(1, 3, center[1]);
	axesCoronal->SetElement(2, 3, center[2]);

	imageResliceCoronal->SetInputData(imageData);
	imageResliceCoronal->SetOutputDimensionality(2);
	imageResliceCoronal->SetResliceAxes(axesCoronal);
	imageResliceCoronal->SetInterpolationModeToLinear();
	imageResliceCoronal->AutoCropOutputOn();

	viewerCoronal->SetInputConnection(imageResliceCoronal->GetOutputPort());
	viewerCoronal->SetRenderer(vtkCoronalRenderer);
	viewerCoronal->SetRenderWindow(vtkVolumeRenderingRender->GetRenderWindow());
	viewerCoronal->SetupInteractor(rootExtractionInteractor);
	viewerCoronal->SetColorLevel(1574);
	viewerCoronal->SetColorWindow(5096);
	viewerCoronal->SetSliceOrientationToXY();
	viewerCoronal->Render();
	vtkCoronalRenderer->ResetCamera();
	vtkCoronalRenderer->Render();
}

void CVTKMFCTESTView::ShowAxialImage()
{
	imageData->GetExtent(extent);
	imageData->GetSpacing(spacing);
	imageData->GetOrigin(origin);
	imageData->GetCenter(center);
	//imagw viewer2
	static double axialElements[16] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
	};
	axesAxial->DeepCopy(axialElements);
	axesAxial->SetElement(0, 3, center[0]);
	axesAxial->SetElement(1, 3, center[1]);
	axesAxial->SetElement(2, 3, center[2]);

	//set reslice
	imageResliceAxial->SetInputData(imageData);
	imageResliceAxial->SetOutputDimensionality(2);
	imageResliceAxial->SetResliceAxes(axesAxial);
	imageResliceAxial->SetInterpolationModeToLinear();
	imageResliceAxial->AutoCropOutputOn();
	imageResliceAxial->BorderOn();

	vtkSmartPointer<vtkTextProperty> sliceTextProp = 
	vtkSmartPointer<vtkTextProperty>::New();
	sliceTextProp->SetFontFamilyToCourier();
	sliceTextProp->SetFontSize(20);
	sliceTextProp->SetVerticalJustificationToBottom();
	sliceTextProp->SetJustificationToLeft();

	viewerAxial->SetInputConnection(imageResliceAxial->GetOutputPort());
	viewerAxial->SetRenderer(vtkAxialRenderer);
	viewerAxial->SetRenderWindow(vtkVolumeRenderingRender->GetRenderWindow());
	viewerAxial->SetupInteractor(rootExtractionInteractor);
	viewerAxial->SetColorLevel(1574);//設置窗位
	viewerAxial->SetColorWindow(5096);//設置窗寬	
	viewerAxial->SetSliceOrientationToXY();

	viewerAxial->Render();
	vtkAxialRenderer->ResetCamera();
	vtkAxialRenderer->Render();
}

void CVTKMFCTESTView::SetInteractor()
{	
	vtkSmartPointer<myvtkInteractorStyleImage> myInteractorStyle =
		vtkSmartPointer<myvtkInteractorStyleImage>::New();
	
	myInteractorStyle->SetResliceSagittal(imageResliceSagittal);
	myInteractorStyle->SetResliceCoronal(imageResliceCoronal);
	myInteractorStyle->SetResliceAxial(imageResliceAxial);
	myInteractorStyle->SetRenderAxial(vtkAxialRenderer);
	myInteractorStyle->SetRenderCoronal(vtkCoronalRenderer);
	myInteractorStyle->SetRenderSagittal(vtkSagittalRenderer);
	myInteractorStyle->SetRenderVolumeRendering(vtkVolumeRenderingRender);	
	rootExtractionInteractor->SetInteractorStyle(myInteractorStyle);

	//auto imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
	//rootExtractionInteractor->SetInteractorStyle(imageStyle);
	//
	////////////////////////////////////////////////
	//auto callback = vtkSmartPointer<vtkImageInteractionCallback>::New();
	//callback->imageResliceSagittal = imageResliceSagittal;
	//callback->imageResliceCoronal = imageResliceCoronal;
	//callback->imageResliceAxial = imageResliceAxial;

	//callback->imageRenderVolumeRendering = vtkVolumeRenderingRender;
	//callback->imageRenderSagittal = vtkSagittalRenderer;
	//callback->imageRenderCoronal = vtkCoronalRenderer;
	//callback->imageRenderAxial = vtkAxialRenderer;

	//callback->SetInteractor(rootExtractionInteractor);

	////callback->SetRenderWindow(pvtkReOriVolumeRenderer->GetRenderWindow());
	//callback->SetRenderWindow(vtkVolumeRenderingRender->GetRenderWindow());
	//


	//imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
	//imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);
	//imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);

	//rootExtractionInteractor->Start();
}



void CVTKMFCTESTView::ShowVolumeRendering()
{
	vtkSmartPointer<vtkImageCast> cast =
		vtkSmartPointer<vtkImageCast>::New();
	//cast->SetInputData((vtkDataObject*)imageData);
	cast->SetInputData((vtkDataObject*)reader->GetOutput());
	cast->SetOutputScalarTypeToFloat();
	cast->SetOutputScalarTypeToUnsignedChar();
	cast->Update();


	//use default mode
	volumeMapper->SetRequestedRenderMode(vtkSmartVolumeMapper::DefaultRenderMode);
	volumeMapper->SetInputConnection(reader->GetOutputPort());
	//volumeMapper->SetInputConnection(cast->GetOutputPort());
	volumeMapper->AutoAdjustSampleDistancesOn();
	volumeMapper->SetBlendModeToComposite();	

	//dim
	int dim[3];
	imageData->GetDimensions(dim);
	//get spacing
	double spacing[3];
	imageData->GetSpacing(spacing);

	// Create our transfer function
	// Create the property and attach the transfer functions
	volumeProperty->SetIndependentComponents(true);
	volumeProperty->SetColor(colorFun);
	volumeProperty->SetScalarOpacity(opacityFun);
	volumeProperty->SetInterpolationTypeToLinear();

	// connect up the volume to the property and the mapper	
	volumeData->SetProperty(volumeProperty);
	volumeData->SetMapper(volumeMapper);
	volumeData->RotateX(90);
	volumeData->SetPosition(volumeData->GetCenter()[0], volumeData->GetCenter()[1], volumeData->GetCenter()[2]);
	volumeData->SetOrigin(volumeData->GetCenter()[0], volumeData->GetCenter()[1], volumeData->GetCenter()[2]);

	//放color fun and opcity fun
	CT_Teeth();	
	//CT_Bone();
	volumeProperty->ShadeOn();
	volumeProperty->SetAmbient(0.1);
	volumeProperty->SetDiffuse(0.9);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(10.0);
	volumeProperty->SetScalarOpacityUnitDistance(0.5);
	
	vtkVolumeRenderingRender->AddVolume(volumeData);
}
template <typename ITK_Exporter, typename VTK_Importer>
void ConnectPipelines(ITK_Exporter exporter, VTK_Importer* importer)
{

	importer->SetUpdateInformationCallback(exporter->GetUpdateInformationCallback());

	importer->SetPipelineModifiedCallback(exporter->GetPipelineModifiedCallback());
	importer->SetWholeExtentCallback(exporter->GetWholeExtentCallback());
	importer->SetSpacingCallback(exporter->GetSpacingCallback());
	importer->SetOriginCallback(exporter->GetOriginCallback());
	importer->SetScalarTypeCallback(exporter->GetScalarTypeCallback());

	importer->SetNumberOfComponentsCallback(exporter->GetNumberOfComponentsCallback());

	importer->SetPropagateUpdateExtentCallback(exporter->GetPropagateUpdateExtentCallback());
	importer->SetUpdateDataCallback(exporter->GetUpdateDataCallback());
	importer->SetDataExtentCallback(exporter->GetDataExtentCallback());
	importer->SetBufferPointerCallback(exporter->GetBufferPointerCallback());
	importer->SetCallbackUserData(exporter->GetCallbackUserData());
}

std::vector<vtkSmartPointer<vtkImageData>>imageData2D;
void CVTKMFCTESTView::TestRegionGrowing()
{		
	imageData->GetExtent(extent);
	for (int z = extent[5]; z >= extent[4]; z--)
	{		
		// 換一個切片就重新創建一個新的vtkImageData，因為VTK與ITK皆使用指標運作，所以不重新創建一個新的會造成存放在vector中的影像一直被變動
		vtkSmartPointer<vtkImageData> pixelBuffer = vtkSmartPointer<vtkImageData>::New();
		pixelBuffer->SetExtent(extent[0], extent[1], extent[2], extent[3], 0, 0);
		// 影像的格式為float，通道數為三(三通道的影像才能是彩色的)
		pixelBuffer->AllocateScalars(VTK_FLOAT, 3);

		imageData2D.push_back(pixelBuffer);
		for (int y = extent[2]; y <= extent[3]; y++)
		{
			for (int x = extent[0]; x <= extent[1]; x++)
			{
				short intensity;

				// 以下為vtkImageData取值的方式如下，如果等到左邊用float*的型式其配合的為static_cast<float*>
				short* connectorPixel = static_cast<short*>(imageData->GetScalarPointer(x, extent[3] - y, z));
				short* imageData2DPixel = static_cast<short*>(imageData2D[extent[5] - z]->GetScalarPointer(x, y, 0));
				intensity = connectorPixel[0];

				imageData2DPixel[0] = intensity;
				imageData2DPixel[1] = intensity;
				imageData2DPixel[2] = intensity;
			}
		}
	}	
	// 移除提取點選點的滑鼠事件
	auto callback = vtkSmartPointer<myvtkInteractorStyleImage>::New();

	// 取得點選點
	//callback->GetPositionX()

	POINT bound;
	bound.x = seed[0];
	bound.y = seed[1];
	int slice = 334/2;
	int regionSize = 0;
	while (1)
	{
		//==============================================================//
		//				weight				為權重值
		//				compensation		為修正函數
		//				initalValue			為初始值
		//				average				為平均
		//				deviation			為標準差
		//				lower				為下閥值
		//				upper				為上閥值
		//				dataSize			為資料大小
		//				center_x,center_y	為下一張切片的種子點
		float weight = 1.0;
		float compensation = 0.0;
		float initalValue = 0.0;
		float average = 0.0;
		float deviation = 0.0;
		float lower = 0.0;
		float upper = 0.0;
		float dataSize = 0.0;

		int center_x = 0;
		int center_y = 0;

		// 用來存放要計算標準差的像素強度值
		SD.clear();

		//============以下為計算周圍影像強度值的標準差的流程============//

		// 取出種子點鄰近的八個像素強度值
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i != 0 || j != 0)
				{
					short* data = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x + i, bound.y + j, 0));
					SD.push_back(data[0]);
				}
			}
		}

		dataSize = SD.size();

		// 計算修正函數
		compensation = 20 / sqrt(dataSize);

		short* inital = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x, bound.y, 0));
		initalValue = inital[0];

		// 計算平均值
		for (int i = 0; i < SD.size(); i++)
		{
			average = average + SD[i] / SD.size();
		}

		// 計算標準差
		for (int i = 0; i < SD.size(); i++)
		{
			deviation = deviation + pow(SD[i] - average, 2) / (SD.size() - 1);
		}

		deviation = sqrt(deviation);

		// 計算權重值
		// 利用前面所算出的標準差與修正函數可得到上下閥值，
		// 再使用種子點判斷是否良好的方法來求出最佳的權重值。
		int error = 0;
		while (1)
		{
			error = 0;
			lower = initalValue - (deviation*weight + compensation);
			upper = initalValue + (deviation*weight + compensation);

			for (int i = 1; i <= 3; i++)
			{
				short* direction_1 = static_cast<short*>(imageData2D[this->myStyle->SetSlice()]->GetScalarPointer(bound.x - i, bound.y, 0));
				if (direction_1[0] <= upper && direction_1[0] >= lower)
				{
					error++;
				}

				short* direction_2 = static_cast<short*>(imageData2D[this->myStyle->SetSlice()]->GetScalarPointer(bound.x - i, bound.y - i, 0));
				if (direction_2[0] <= upper && direction_2[0] >= lower)
				{
					error++;
				}

				short* direction_3 = static_cast<short*>(imageData2D[this->myStyle->SetSlice()]->GetScalarPointer(bound.x, bound.y - i, 0));
				if (direction_3[0] <= upper && direction_3[0] >= lower)
				{
					error++;
				}

				short* direction_4 = static_cast<short*>(imageData2D[this->myStyle->SetSlice()]->GetScalarPointer(bound.x + i, bound.y - i, 0));
				if (direction_4[0] <= upper && direction_4[0] >= lower)
				{
					error++;
				}

				short* direction_5 = static_cast<short*>(imageData2D[this->myStyle->SetSlice()]->GetScalarPointer(bound.x + i, bound.y, 0));
				if (direction_5[0] <= upper && direction_5[0] >= lower)
				{
					error++;
				}

				short* direction_6 = static_cast<short*>(imageData2D[this->myStyle->SetSlice()]->GetScalarPointer(bound.x + i, bound.y + i, 0));
				if (direction_6[0] <= upper && direction_6[0] >= lower)
				{
					error++;
				}

				short* direction_7 = static_cast<short*>(imageData2D[this->myStyle->SetSlice()]->GetScalarPointer(bound.x, bound.y + i, 0));
				if (direction_7[0] <= upper && direction_7[0] >= lower)
				{
					error++;
				}

				short* direction_8 = static_cast<short*>(imageData2D[this->myStyle->SetSlice()]->GetScalarPointer(bound.x - i, bound.y + i, 0));
				if (direction_8[0] <= upper && direction_8[0] >= lower)
				{
					error++;
				}
			}

			if (error == 24 || weight > 3)
			{
				break;
			}

			weight = weight + 0.1;
		}

		lower = initalValue - (deviation*weight + compensation);
		upper = initalValue + (deviation*weight + compensation);

		// 用來存放像素的位置
		pixelData.clear();
		SD.clear();
		//bool* gate = new bool[512][512];

		// 判斷此像素是否已經被成長
		int **gate = new int*[imageData2D[this->myStyle->SetSlice()]->GetExtent()[1] + 1];
		for (int i = 0; i < imageData2D[this->myStyle->SetSlice()]->GetExtent()[1] + 1; ++i)
		{
			gate[i] = new int[imageData2D[this->myStyle->SetSlice()]->GetExtent()[3] + 1]();
		}

		// 符合閥值的區域用TRUE表示，反之就是FALSE
		gate[bound.x][bound.y] = 1;
		pixelData.push_back(bound);
		short* imageData2DPixel;

		// 避免重複判斷
		int count = 0;

		// 用來判斷是否收斂
		int size = 0;

		while (1)
		{
			// 先取得目前成長區域的大小，用來判斷是否有再繼續成長
			size = pixelData.size();
			for (int i = count; i < size; i++)
			{
				bound.x = pixelData[i].x;
				bound.y = pixelData[i].y;

				// 防呆用
				if (bound.x == imageData2D[this->myStyle->SetSlice()]->GetExtent()[0] || bound.x == imageData2D[this->myStyle->SetSlice()]->GetExtent()[1] || bound.y == imageData2D[this->myStyle->SetSlice()]->GetExtent()[2] || bound.y == imageData2D[this->myStyle->SetSlice()]->GetExtent()[3])
				{
					break;
				}

				// 用判斷式來避免重複成長
				imageData2DPixel = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x + 1, bound.y, 0));
				if (gate[bound.x + 1][bound.y] != 1 && gate[bound.x + 1][bound.y] != -1)
				{
					if (imageData2DPixel[0] < upper && imageData2DPixel[0] > lower)
					{
						gate[bound.x + 1][bound.y] = 1;
						pixelData.push_back(bound);
						pixelData[pixelData.size() - 1].x = bound.x + 1;
						SD.push_back(imageData2DPixel[0]);
					}
					else
					{
						gate[bound.x + 1][bound.y] = -1;
					}
				}

				imageData2DPixel = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x + 1, bound.y + 1, 0));
				if (gate[bound.x + 1][bound.y + 1] != 1 && gate[bound.x + 1][bound.y + 1] != -1)
				{
					if (imageData2DPixel[0] < upper && imageData2DPixel[0] > lower)
					{
						gate[bound.x + 1][bound.y + 1] = 1;
						pixelData.push_back(bound);
						pixelData[pixelData.size() - 1].x = bound.x + 1;
						pixelData[pixelData.size() - 1].y = bound.y + 1;
						SD.push_back(imageData2DPixel[0]);
					}
					else
					{
						gate[bound.x + 1][bound.y + 1] = -1;
					}
				}

				imageData2DPixel = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x, bound.y + 1, 0));
				if (gate[bound.x][bound.y + 1] != 1 && gate[bound.x][bound.y + 1] != -1)
				{
					if (imageData2DPixel[0] < upper && imageData2DPixel[0] > lower)
					{
						gate[bound.x][bound.y + 1] = 1;
						pixelData.push_back(bound);
						pixelData[pixelData.size() - 1].y = bound.y + 1;
						SD.push_back(imageData2DPixel[0]);
					}
					else
					{
						gate[bound.x][bound.y + 1] = -1;
					}
				}

				imageData2DPixel = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x - 1, bound.y + 1, 0));
				if (gate[bound.x - 1][bound.y + 1] != 1 && gate[bound.x - 1][bound.y + 1] != -1)
				{
					if (imageData2DPixel[0] < upper && imageData2DPixel[0] > lower)
					{
						gate[bound.x - 1][bound.y + 1] = 1;
						pixelData.push_back(bound);
						pixelData[pixelData.size() - 1].x = bound.x - 1;
						pixelData[pixelData.size() - 1].y = bound.y + 1;
						SD.push_back(imageData2DPixel[0]);
					}
					else
					{
						gate[bound.x - 1][bound.y + 1] = -1;
					}
				}

				imageData2DPixel = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x - 1, bound.y, 0));
				if (gate[bound.x - 1][bound.y] != 1 && gate[bound.x - 1][bound.y] != -1)
				{
					if (imageData2DPixel[0] < upper && imageData2DPixel[0] > lower)
					{
						gate[bound.x - 1][bound.y] = 1;
						pixelData.push_back(bound);
						pixelData[pixelData.size() - 1].x = bound.x - 1;
						SD.push_back(imageData2DPixel[0]);
					}
					else
					{
						gate[bound.x - 1][bound.y] = -1;
					}
				}

				imageData2DPixel = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x - 1, bound.y - 1, 0));
				if (gate[bound.x - 1][bound.y - 1] != 1 && gate[bound.x - 1][bound.y - 1] != -1)
				{
					if (imageData2DPixel[0] < upper && imageData2DPixel[0] > lower)
					{
						gate[bound.x - 1][bound.y - 1] = 1;
						pixelData.push_back(bound);
						pixelData[pixelData.size() - 1].x = bound.x - 1;
						pixelData[pixelData.size() - 1].y = bound.y - 1;
						SD.push_back(imageData2DPixel[0]);
					}
					else
					{
						gate[bound.x - 1][bound.y - 1] = -1;
					}
				}

				imageData2DPixel = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x, bound.y - 1, 0));
				if (gate[bound.x][bound.y - 1] != 1 && gate[bound.x][bound.y - 1] != -1)
				{
					if (imageData2DPixel[0] < upper && imageData2DPixel[0] > lower)
					{
						gate[bound.x][bound.y - 1] = 1;
						pixelData.push_back(bound);
						pixelData[pixelData.size() - 1].x = bound.x;
						pixelData[pixelData.size() - 1].y = bound.y - 1;
						SD.push_back(imageData2DPixel[0]);
					}
					else
					{
						gate[bound.x][bound.y - 1] = -1;
					}
				}

				imageData2DPixel = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x + 1, bound.y - 1, 0));
				if (gate[bound.x + 1][bound.y - 1] != 1 && gate[bound.x + 1][bound.y - 1] != -1)
				{
					if (imageData2DPixel[0] < upper && imageData2DPixel[0] > lower)
					{
						gate[bound.x + 1][bound.y - 1] = 1;
						pixelData.push_back(bound);
						pixelData[pixelData.size() - 1].x = bound.x + 1;
						pixelData[pixelData.size() - 1].y = bound.y - 1;
						SD.push_back(imageData2DPixel[0]);
					}
					else
					{
						gate[bound.x + 1][bound.y - 1] = -1;
					}
				}
			}

			count++;

			dataSize = SD.size();
			compensation = 20 / sqrt(dataSize);
			average = 0.0;
			deviation = 0.0;

			for (int i = 0; i < SD.size(); i++)
			{
				average = average + SD[i] / SD.size();
			}

			for (int i = 0; i < SD.size(); i++)
			{
				deviation = deviation + pow(SD[i] - average, 2) / (SD.size() - 1);
			}

			deviation = sqrt(deviation);

			lower = initalValue - (deviation*weight + compensation);
			upper = initalValue + (deviation*weight + compensation);

			if (size == pixelData.size())
			{
				break;
			}
		}

		if (regionSize)
		{
			if (pixelData.size() / regionSize > 3)
			{
				break;
			}
			else
			{
				regionSize = pixelData.size();
			}
		}
		else
		{
			regionSize = pixelData.size();
		}

		for (int i = 0; i < pixelData.size(); i++)
		{
			short* imageData2DPixel = static_cast<short*>(imageData2D[slice]->GetScalarPointer(pixelData[i].x, pixelData[i].y, 0));
			imageData2DPixel[0] = 1000;

			center_x = center_x + pixelData[i].x;
			center_y = center_y + pixelData[i].y;
		}

		// 計算成長區域的面心，以此面心最為下一個切片的種子點
		center_x = center_x / pixelData.size();
		center_y = center_y / pixelData.size();

		// 清除動態陣列
		for (int i = 0; i < imageData2D[this->myStyle->SetSlice()]->GetExtent()[1] + 1; ++i)
		{
			delete[] gate[i];
		}
		delete[] gate;

		bound.x = center_x;
		bound.y = center_y;

		slice++;

		// 判斷新種子點於下一張切片是否符合閥值
		if (slice < imageData2D.size() - 1)
		{
			short* data = static_cast<short*>(imageData2D[slice]->GetScalarPointer(bound.x, bound.y, 0));
			if (data[0] > upper || data[0] < lower)
			{
				break;
			}
		}
		else
		{
			break;
		}

	}

}
void CVTKMFCTESTView::SetPickerPoints()
{
	vtkSmartPointer<vtkSphereSource> sphereSource =
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->Update();
	vtkSmartPointer<vtkPointPicker> pointPicker =
		vtkSmartPointer<vtkPointPicker>::New();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());
	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);	
	rootExtractionInteractor->SetPicker(pointPicker);

	// Add the actor to the scene
	vtkAxialRenderer->AddActor(actor);
}
void CVTKMFCTESTView::TestITKRegionGrowing(std::string path)
{		
	//char* argv = "";				//Input filename
	//char* argv = "D://TestITK.dcm";	//Output file name 
	//char* argv = "3.0";				//Initial distance
	//char* argv = "1.0";				//Propagation Scaling
	//char* argv = "1.0";				//Curvature Scaling
	//char* argv = "600";				//Upper threshold
	//char* argv = "180";				//Lower threshold
	//char* argv = "0.02";			//RMS
	//char* argv = "2000";			//Number of Iteration
	//char* argv = "243";				//Seed X
	//char* argv = "374";				//seed y
	//char* argv = "5";				//seed z

	typedef float		PixelType;
	const unsigned int	Dimension = 3;
	typedef itk::Image< PixelType, Dimension >	ImageType;
	typedef itk::ImageSeriesReader< ImageType >	ReaderType;
	typedef itk::GDCMImageIO					ImageIOType;
	typedef itk::GDCMSeriesFileNames			NameGeneratorType;

	ImageIOType::Pointer gdcmIO = ImageIOType::New();
	NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();

	nameGenerator->SetInputDirectory(path);
	const ReaderType::FileNamesContainer & filenames =
		nameGenerator->GetInputFileNames();

	unsigned int numberOfFilenames = filenames.size();
	std::string str;
	str = "";
	str = "Number of CT files:" + std::to_string(numberOfFilenames);
	OutPutDebugView(str);
	//std::cout << "Number of CT files:" << numberOfFilenames << std::endl;
	for (unsigned int i = 0; i < numberOfFilenames; i++)
	{
		std::cout << "filename #" << i << "=";
		std::cout << filenames[i] << std::endl;
	}

	ReaderType::Pointer reader = ReaderType::New();
	reader->SetImageIO(gdcmIO);
	reader->SetFileNames(filenames);

	try
	{
		str = "";
		str = "Reading CT files...";
		OutPutDebugView(str);
		//std::cout << "Reading CT files..." << std::endl;
		reader->Update();
		str = "";
		str = "Reading CT files...Completed";
		OutPutDebugView(str);
		//std::cout << "Reading CT files...Completed" << std::endl;
	}
	catch (itk::ExceptionObject &excp)
	{
		std::cout << "Exception thrown when reading CT files." << std::endl;
		std::cout << excp << std::endl;
		return ;
	}

	//Use fast marching to generate the initial level set
	typedef itk::FastMarchingImageFilter< ImageType, ImageType >
		FastMarchingFilterType;
	FastMarchingFilterType::Pointer fastMarching =
		FastMarchingFilterType::New();
	typedef FastMarchingFilterType::NodeContainer		NodeContainerType;
	typedef FastMarchingFilterType::NodeType			NodeType;
	NodeContainerType::Pointer seeds = NodeContainerType::New();

	ImageType::IndexType seedPosition1;
	seedPosition1[0] = atoi("243");
	seedPosition1[1] = atoi("100");
	seedPosition1[2] = atoi("5");

	NodeType node1;
	const double initialDistance = atof("3.0");
	const double seedValue = -initialDistance;
	node1.SetValue(seedValue);
	node1.SetIndex(seedPosition1);

	seeds->Initialize();
	seeds->InsertElement(0, node1);

	fastMarching->SetTrialPoints(seeds);
	fastMarching->SetOutputSize(
	reader->GetOutput()->GetBufferedRegion().GetSize());

	try
	{
		str = "";
		str = "Fastmarching...";
		OutPutDebugView(str);
		//std::cout << "Fastmarching..." << std::endl;
		fastMarching->Update();
		str = "";
		str = "Fastmarching... Completed";
		OutPutDebugView(str);
		std::cout << "Fastmarching... Completed" << std::endl;
	}
	catch (itk::ExceptionObject &excp)
	{
		std::cerr << "Exception thrown while computing initial level set!" <<
			std::endl;
		std::cerr << excp << std::endl;
		return ;
	}


	//Threshold Segmentation Level set
	typedef itk::ThresholdSegmentationLevelSetImageFilter< ImageType,
		ImageType>	ThresholdLeveSetFilterType;
	ThresholdLeveSetFilterType::Pointer thresholdSegmentation =
		ThresholdLeveSetFilterType::New();

	
	thresholdSegmentation->SetPropagationScaling(atof("1.0"));
	thresholdSegmentation->SetCurvatureScaling(atof("1.0"));
	thresholdSegmentation->SetUpperThreshold(atof("2000"));
	thresholdSegmentation->SetLowerThreshold(atof("700"));
	thresholdSegmentation->SetIsoSurfaceValue(0.0);
	thresholdSegmentation->SetMaximumRMSError(atof("0.02"));
	thresholdSegmentation->SetNumberOfIterations(atof("2000"));

	thresholdSegmentation->SetInput(fastMarching->GetOutput());
	thresholdSegmentation->SetFeatureImage(reader->GetOutput());
	thresholdSegmentation->Update();

	typedef itk::BinaryThresholdImageFilter<ImageType, ImageType> ThresholdType;
	ThresholdType::Pointer thresholder = ThresholdType::New();

	thresholder->SetLowerThreshold(-1000);
	thresholder->SetUpperThreshold(0);

	thresholder->SetOutsideValue(0);
	thresholder->SetInsideValue(255);

	thresholder->SetInput(thresholdSegmentation->GetOutput());

	// Print out some useful information 
	str = "";
	str = "Max. no. iterations:" + std::to_string(thresholdSegmentation->GetNumberOfIterations());
	OutPutDebugView(str);
	str = "";
	str = "Max. RMS error: " + std::to_string(thresholdSegmentation->GetMaximumRMSError());
	OutPutDebugView(str);
	str = "";
	str = "No. elpased iterations: " + std::to_string(thresholdSegmentation->GetElapsedIterations());
	OutPutDebugView(str);
	str = "";
	str = "RMS change:" + std::to_string(thresholdSegmentation->GetRMSChange());
	OutPutDebugView(str);
	//std::cout << std::endl;
	//std::cout << "Max. no. iterations: " <<
	//	thresholdSegmentation->GetNumberOfIterations() << std::endl;
	//std::cout << "Max. RMS error: " <<
	//	thresholdSegmentation->GetMaximumRMSError() << std::endl;
	//std::cout << std::endl;
	//std::cout << "No. elpased iterations: " <<
	//	thresholdSegmentation->GetElapsedIterations() << std::endl;
	//std::cout << "RMS change: " << thresholdSegmentation->GetRMSChange() <<
	//	std::endl;

	typedef itk::VTKImageExport <ImageType>			ExportFilterType;
	ExportFilterType::Pointer itkExporter1 = ExportFilterType::New();
	ExportFilterType::Pointer itkExporter2 = ExportFilterType::New();
	itkExporter1->SetInput(reader->GetOutput());
	itkExporter2->SetInput(thresholder->GetOutput());


	//Connect itk to vtk
	vtkImageImport *vtkImporter1 = vtkImageImport::New();
	vtkImageImport *vtkImporter2 = vtkImageImport::New();
	ConnectPipelines(itkExporter1, vtkImporter1);
	ConnectPipelines(itkExporter2, vtkImporter2);

	vtkImporter1->Update();

	ImageType::Pointer inputImage = reader->GetOutput();
	ImageType::SizeType  size = inputImage->GetBufferedRegion().GetSize();

	vtkRenderer *renderer = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	vtkInteractorStyleTrackballCamera *trackballCameraStyle =
		vtkInteractorStyleTrackballCamera::New();

	renWin->SetSize(1270, 950);
	renWin->AddRenderer(renderer);
	iren->SetRenderWindow(renWin);
	iren->SetInteractorStyle(trackballCameraStyle);

	vtkCellPicker *picker = vtkCellPicker::New();
	picker->SetTolerance(0.005);

	vtkProperty *ipwProp = vtkProperty::New();

	vtkImagePlaneWidget *xImagePlaneWidget = vtkImagePlaneWidget::New();
	vtkImagePlaneWidget *yImagePlaneWidget = vtkImagePlaneWidget::New();
	vtkImagePlaneWidget *zImagePlaneWidget = vtkImagePlaneWidget::New();

	xImagePlaneWidget->DisplayTextOn();	
	xImagePlaneWidget->SetInputData(vtkImporter1->GetOutput());
	xImagePlaneWidget->SetPlaneOrientationToXAxes();
	xImagePlaneWidget->SetSliceIndex(size[0] / 2);
	xImagePlaneWidget->SetPicker(picker);
	xImagePlaneWidget->RestrictPlaneToVolumeOn();
	xImagePlaneWidget->SetKeyPressActivationValue('x');
	xImagePlaneWidget->GetPlaneProperty()->SetColor(1, 1, 0);
	xImagePlaneWidget->SetTexturePlaneProperty(ipwProp);
	xImagePlaneWidget->SetResliceInterpolateToNearestNeighbour();
	xImagePlaneWidget->GetTextProperty()->SetColor(1, 0, 0);
	xImagePlaneWidget->GetSelectedPlaneProperty()->SetColor(1, 0, 0);
	xImagePlaneWidget->GetCursorProperty()->SetColor(1, 0, 0);

	yImagePlaneWidget->DisplayTextOn();
	yImagePlaneWidget->SetInputData(vtkImporter1->GetOutput());
	yImagePlaneWidget->SetPlaneOrientationToYAxes();
	yImagePlaneWidget->SetSliceIndex(size[1] / 2);
	yImagePlaneWidget->SetPicker(picker);
	yImagePlaneWidget->RestrictPlaneToVolumeOn();
	yImagePlaneWidget->SetKeyPressActivationValue('y');
	yImagePlaneWidget->GetPlaneProperty()->SetColor(0, 1, 0);
	yImagePlaneWidget->SetTexturePlaneProperty(ipwProp);
	yImagePlaneWidget->SetLookupTable(xImagePlaneWidget->GetLookupTable());
	yImagePlaneWidget->GetTextProperty()->SetColor(1, 0, 0);
	yImagePlaneWidget->GetSelectedPlaneProperty()->SetColor(1, 0, 0);
	yImagePlaneWidget->GetCursorProperty()->SetColor(1, 0, 0);

	zImagePlaneWidget->DisplayTextOn();
	zImagePlaneWidget->SetInputData(vtkImporter1->GetOutput());
	zImagePlaneWidget->SetPlaneOrientationToZAxes();
	zImagePlaneWidget->SetSliceIndex(size[2] / 2);
	zImagePlaneWidget->SetPicker(picker);
	zImagePlaneWidget->SetKeyPressActivationValue('z');
	zImagePlaneWidget->GetPlaneProperty()->SetColor(0, 0, 1);
	zImagePlaneWidget->SetTexturePlaneProperty(ipwProp);
	zImagePlaneWidget->SetLookupTable(xImagePlaneWidget->GetLookupTable());
	zImagePlaneWidget->GetTextProperty()->SetColor(1, 0, 0);
	zImagePlaneWidget->GetSelectedPlaneProperty()->SetColor(1, 0, 0);
	zImagePlaneWidget->GetCursorProperty()->SetColor(1, 0, 0);

	xImagePlaneWidget->SetInteractor(iren);
	xImagePlaneWidget->On();

	yImagePlaneWidget->SetInteractor(iren);
	yImagePlaneWidget->On();

	zImagePlaneWidget->SetInteractor(iren);
	zImagePlaneWidget->On();

	renderer->SetBackground(0.4392, 0.5020, 0.5647);

	vtkImageShrink3D *shrink = vtkImageShrink3D::New();
	shrink->SetInputData(vtkImporter2->GetOutput());
	shrink->SetShrinkFactors(3, 3, 1);

	vtkContourFilter *contour = vtkContourFilter::New();
	contour->SetInputData(shrink->GetOutput());
	contour->SetValue(0, 128);

	vtkSmoothPolyDataFilter *smooth = vtkSmoothPolyDataFilter::New();
	smooth->SetInputData(contour->GetOutput());
	smooth->SetNumberOfIterations(20);
	smooth->BoundarySmoothingOn();
	smooth->SetFeatureAngle(100);
	smooth->SetEdgeAngle(100);

	vtkDecimatePro *deci = vtkDecimatePro::New();
	deci->SetInputConnection(smooth->GetOutputPort());
	deci->SetTargetReduction(0.3);

	vtkSTLWriter * writeSTL = vtkSTLWriter::New();
	writeSTL->SetFileName("poly.stl");
	writeSTL->SetInputData(deci->GetOutput());
	writeSTL->Update();

	vtkPolyDataMapper *polyMapper = vtkPolyDataMapper::New();
	vtkActor		*polyActor = vtkActor::New();

	polyActor->SetMapper(polyMapper);
	polyMapper->SetInputData(deci->GetOutput());
	polyMapper->ScalarVisibilityOff();

	vtkProperty *property = vtkProperty::New();
	property->SetAmbient(0.1);
	property->SetDiffuse(0.1);
	property->SetSpecular(0.5);
	property->SetColor(1.0, 0.0, 0.0);
	property->SetLineWidth(2.0);
	property->SetRepresentationToSurface();

	polyActor->SetProperty(property);

	renderer->AddActor(polyActor);

	vtkCamera *camera = vtkCamera::New();
	camera->SetPosition(0, -1, 0);
	camera->SetFocalPoint(0, 0, 0);
	camera->SetViewUp(0, 0, 1);
	camera->Azimuth(45);
	camera->Pitch(-10);
	camera->Roll(30);
	renderer->SetActiveCamera(camera);
	renderer->ResetCamera();


	renWin->Render();
	iren->Start();

	polyActor->Delete();
	picker->Delete();
	ipwProp->Delete();
	vtkImporter1->Delete();
	vtkImporter2->Delete();
	xImagePlaneWidget->Delete();
	yImagePlaneWidget->Delete();
	zImagePlaneWidget->Delete();
	contour->Delete();
	property->Delete();
	polyMapper->Delete();
	renWin->Delete();
	renderer->Delete();
	iren->Delete();
	shrink->Delete();
	smooth->Delete();
	deci->Delete();

	return;
	//using PixelType = signed short;
	//constexpr unsigned int Dimension = 3;
	//using ImageType = itk::Image<PixelType, Dimension>;
	//using InternalImageType = itk::Image< PixelType, Dimension >;

	//using NamesGeneratorType = itk::GDCMSeriesFileNames;
	//NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();

	//nameGenerator->SetUseSeriesDetails(true);
	//nameGenerator->AddSeriesRestriction("0008|0021");
	//nameGenerator->SetGlobalWarningDisplay(false);
	//nameGenerator->SetDirectory(path);

	//try
	//{
	//	using SeriesIdContainer = std::vector<std::string>;
	//	const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();
	//	auto                      seriesItr = seriesUID.begin();
	//	auto                      seriesEnd = seriesUID.end();

	//	while (seriesItr != seriesEnd)
	//	{
	//		std::cout << seriesItr->c_str() << std::endl;
	//		++seriesItr;
	//	}

	//	seriesItr = seriesUID.begin();
	//	using ReaderType = itk::ImageSeriesReader<ImageType>;
	//	ReaderType::Pointer ireader = ReaderType::New();
	//	while (seriesItr != seriesUID.end())
	//	{
	//		std::string seriesIdentifier;
	//		{
	//			seriesIdentifier = seriesItr->c_str();
	//			seriesItr++;
	//		}

	//		using FileNamesContainer = std::vector<std::string>;
	//		FileNamesContainer fileNames = nameGenerator->GetFileNames(seriesIdentifier);


	//		using ImageIOType = itk::GDCMImageIO;
	//		ImageIOType::Pointer dicomIO = ImageIOType::New();
	//		ireader->SetImageIO(dicomIO);
	//		ireader->SetFileNames(fileNames);
	//		ireader->ForceOrthogonalDirectionOff(); // properly read CTs with gantry tilt
	//	}
	//	//using CurvatureFlowImageFilterType =
	//	//	itk::CurvatureFlowImageFilter< InternalImageType, InternalImageType >;
	//	//CurvatureFlowImageFilterType::Pointer smoothing =
	//	//	CurvatureFlowImageFilterType::New();
	//	//using ConnectedFilterType = itk::ConfidenceConnectedImageFilter<
	//	//	InternalImageType, InternalImageType>;
	//	//ConnectedFilterType::Pointer confidenceConnected
	//	//	= ConnectedFilterType::New();
	//	//smoothing->SetInput(ireader->GetOutput());
	//	//confidenceConnected->SetInput(smoothing->GetOutput());
	//	//caster->SetInput(confidenceConnected->GetOutput());
	//	//writer->SetInput(confidenceConnected->GetOutput());

	//	//using WriterType = itk::ImageFileWriter<ImageType>;
	//	//WriterType::Pointer writer = WriterType::New();
	//	//std::string outFileName = "D://TestITK.dcm";
	//	//writer->SetFileName(outFileName);
	//	//writer->UseCompressionOn();
	//	//writer->SetInput(confidenceConnected->GetOutput());
	//	//smoothing->SetNumberOfIterations(5);
	//	//smoothing->SetTimeStep(0.125);
	//	//confidenceConnected->SetMultiplier(2.5);
	//	//confidenceConnected->SetNumberOfIterations(5);
	//	//confidenceConnected->SetReplaceValue(255);
	//	//InternalImageType::IndexType  index;
	//	//index[0] = 180;
	//	//index[1] = 150;
	//	//confidenceConnected->SetSeed(index);
	//	//confidenceConnected->SetInitialNeighborhoodRadius(2);
	//	//try
	//	//{
	//	//	writer->Update();
	//	//}
	//	//catch (itk::ExceptionObject & excep)
	//	//{
	//	//	std::cerr << "Exception caught !" << std::endl;
	//	//	std::cerr << excep << std::endl;
	//	//}

	//}
	//catch (itk::ExceptionObject & ex)
	//{
	//	std::cout << ex << std::endl;
	//	return ;
	//}
	//return ;
	////reader->setDi
	////writer->SetFileName("D://TestITK.dcm");
	////typedef itk::ConnectedThresholdImageFilter< InternalImageType,
	////	OutputImageType > ConnectedFilterType;

	////ConnectedFilterType::Pointer connectedThreshold =
	////ConnectedFilterType::New();

	////connectedThreshold->SetInput(reader->GetOutput());
	////writer->SetInput(connectedThreshold->GetOutput());

	////const InternalPixelType lowerThreshold = 500;
	////const InternalPixelType upperThreshold = 2000;
	////
	////connectedThreshold->SetLower(lowerThreshold);
	////connectedThreshold->SetUpper(upperThreshold);
	////connectedThreshold->SetReplaceValue(255);
	////
	////InternalImageType::IndexType  index;
	////index[0] = 250;
	////index[1] = 239;
	////
	////connectedThreshold->SetSeed(index);
	////
	////try
	////{
	////writer->Update();
	////}
	////catch (itk::ExceptionObject & excep)
	////	{
	////		std::cerr << "Exception caught !" << std::endl;
	////		std::cerr << excep << std::endl;
	////	}
	////
	////return ;
}

void CVTKMFCTESTView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	switch (nChar)
	{
	case '1':
	{
		//CFileOpenDir(c_dirpath);


		//CDlgAdjustDicom *dlg = new CDlgAdjustDicom();
		//dlg->Create(IDD_ADJUST_DICOM);
		//dlg->ShowWindow(SW_SHOW);
	}
	break;
	case '2':
	{
		BoundaryVolume(s_dirpath);
	}
	break;
	case '3':
		MarchingCube();
		break;
	case '4':
	{
		CDlgOpacity *dlg = new CDlgOpacity();
		dlg->Create(IDD_DIALOG_OPACITY);
		dlg->ShowWindow(SW_SHOW);
	}
	break;
	case '5':
	{

		//if (!GetDirPath(s_dirpath))
		//	break;

		//
		////FileOpenMergeImgData(s_dirpath);
		//
		////Coordinate();
		//FileOpenDir(s_dirpath);

		if (!CGetDirPath(c_dirpath))
			break;
		CFileOpenDir(c_dirpath);
		ReOriVolumeRendering();
		ReOriXYCut();
		ReOriYZCut();
		ReOriXZCut();
		//ShowXYPlaneImg();
		//ShowXZPlaneImg();
		//ShowYZPlaneImg();

		//DrawCoorLineX();
		//DrawCoorLineY();
		//DrawCoorLineZ();
		//lineActorX->VisibilityOff();
		//lineActorY->VisibilityOff();
		//lineActorZ->VisibilityOff();

		//CDlgCTImageControl *dlg = new CDlgCTImageControl();
		//dlg->Create(IDD_DIALOG_CTIMAGE_CONTROL);
		//dlg->ShowWindow(SW_SHOW);

		pvtkReOriVolumeRenderer->GetRenderWindow()->Render();
	}
	break;
	case '6':
	{
		//if (!GetDirPath(s_dirpath))
		//	break;
		FileOpenMergeImgData(s_dirpath);
	}
	break;
	case '7':
	{
		if (!CGetDirPath(c_dirpath))
			break;
		CFileOpenDir(c_dirpath);
		//ReOriVolumeRendering();		
		SetResliceSagittalRender();
		SetResliceCoronalRender();
		SetResliceAxialRender();
		ShowVolumeRendering();
		ShowSagittalImage();
		ShowCoronalImage();
		ShowAxialImage();
		SetVolumeRenderingRender();
		SetInteractor();
		//SetPickerPoints();
		//vtkVolumeRenderingRender->GetRenderWindow()->Render();
	}
	break;
	case '8':
	{
		if (!CGetDirPath(c_dirpath))
			break;
		CFileOpenDir(c_dirpath);
		TestRegionGrowing();
	}
	break;
	case '9':
	{
		TestChangeDicomColor();
	}
	break;
	}

	CView::OnChar(nChar, nRepCnt, nFlags);

}

void CVTKMFCTESTView::TestChangeDicomColor()
{
	vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetFileName("D://I0051318.dcm");
	//reader->SetDataScalarTypeToShort();
	reader->Update();

	//#define VTK_VOID            0
	//#define VTK_BIT             1
	//#define VTK_CHAR            2
	//#define VTK_SIGNED_CHAR    15
	//#define VTK_UNSIGNED_CHAR   3
	//#define VTK_SHORT           4
	//#define VTK_UNSIGNED_SHORT  5
	//#define VTK_INT             6
	//#define VTK_UNSIGNED_INT    7
	//#define VTK_LONG            8
	//#define VTK_UNSIGNED_LONG   9
	//#define VTK_FLOAT          10
	//#define VTK_DOUBLE         11
	//#define VTK_ID_TYPE        12

	//#define VTK_STRING         13
	//#define VTK_OPAQUE         14
	int type = reader->GetDataScalarType();
	CString msg;
	msg.Format(L"type:%d", type);
	AfxMessageBox(msg);

	int dims[3];
	reader->GetOutput()->GetDimensions(dims);
	//reader->GetOutput()->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
	int nbofcomp;
	nbofcomp = reader->GetOutput()->GetNumberOfScalarComponents();



	vector<int> aaa;
	int totalpoint = 0;
	int totalok = 0;
	int totalno = 0;
	for (int k = 0; k < dims[2]; k++) {
		for (int j = 0; j < dims[1]; j++) {
			for (int i = 0; i < dims[0]; i++)
			{
				short *pixel = (short*)(reader->GetOutput()->GetScalarPointer(i, j, k));
				int aa = *pixel;
				//OutPutDebugView(std::to_string(aa));

				if (aa>1300)
				{
					aaa.push_back(1);
					//*pixel = 255 - *pixel;
					//*(pixel + 1) = 255 - *(pixel + 1);
					//*(pixel + 2) = 255 - *(pixel + 2);
					totalok++;
				}
				else
				{
					aaa.push_back(0);
					totalno++;
				}
				totalpoint++;

			}
		}
	}

	reader->GetOutput()->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
	//nbofcomp = reader->GetOutput()->GetNumberOfScalarComponents();
	msg.Format(L"totalok:%d,totalno:%d,totalpoint:%d", totalok, totalno, totalpoint);
	AfxMessageBox(msg);
	int bbb = 0;
	for (int k = 0; k < dims[2]; k++) {
		for (int j = 0; j < dims[1]; j++) {
			for (int i = 0; i < dims[0]; i++)
			{
				short *pixel = (short*)(reader->GetOutput()->GetScalarPointer(i, j, k));
				if (aaa[bbb] == 1)
				{
					//OutPutDebugView("OK");
					*pixel = 255;
					//*(pixel + 1) = 255 - *(pixel + 1);
					//*(pixel + 2) = 255 - *(pixel + 2);
				}
				bbb++;
			}
		}
	}
	vtkSmartPointer<vtkImageViewer2> imgViewer = vtkSmartPointer<vtkImageViewer2>::New();
	imgViewer->SetInputData(reader->GetOutput());
	vtkSmartPointer<vtkRenderWindowInteractor> rwi = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imgViewer->SetupInteractor(rwi);
	imgViewer->Render();
	imgViewer->GetRenderer()->ResetCamera();
	imgViewer->Render();
	imgViewer->GetRenderer()->SetBackground(1, 1, 1);
	imgViewer->SetSize(640, 480);
	imgViewer->GetRenderWindow()->SetWindowName("VisitImagePixelDirectly");
	rwi->Start();
}

bool  CVTKMFCTESTView::wpfcall()
{
	AfxMessageBox(_T("UI hello"));
	return true;
}

//5/6/2020 handtan//PROCESSBAR
LRESULT CVTKMFCTESTView::WPFCALL_PROCESSBAR(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(_T("ENTER MFC PROCESSBAR MESSAGE"));
	return 1;
}

LRESULT CVTKMFCTESTView::WPFCALL_REMOVETOOTH(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		AfxMessageBox(_T("area add"));
	}
	else if (wParam == 1)
	{
		AfxMessageBox(_T("area delete"));
	}
	else if (wParam == 2)
	{
		AfxMessageBox(_T("area reset"));
	}
	return 1;
}

LRESULT CVTKMFCTESTView::WPFCALL_ALIGNWIN(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		AfxMessageBox(_T("COMBO1"));
	}
	else if (wParam == 1)
	{
		AfxMessageBox(_T("COMBO2"));
	}
	else if (wParam == 2)
	{
		if (lParam == 0)
		{
			AfxMessageBox(_T("point add"));
		}
		else if (lParam == 1)
		{
			AfxMessageBox(_T("point confirm"));
		}
		else if (lParam == 2)
		{
			AfxMessageBox(_T("point reset"));
		}
	}
	return 1;
}

LRESULT CVTKMFCTESTView::WPFCALL_MANUALALIGNWIN(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		if (lParam == 0)
		{
			AfxMessageBox(_T("point add"));
		}
		else if (lParam == 1)
		{
			AfxMessageBox(_T("point confirm"));
		}
		else if (lParam == 2)
		{
			AfxMessageBox(_T("point reset"));
		}
	}
	return 1;
}

LRESULT CVTKMFCTESTView::WPFCALL_EXTRACT(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)//add extract
	{
		if (lParam == extract_sinus)
		{
			//AfxMessageBox(_T("sinus"));
		}
		else if (lParam == extract_airway)
		{
			//AfxMessageBox(_T("airway"));
		}
		else if (lParam == extract_root)
		{
			//AfxMessageBox(_T("root"));
		}
		else if (lParam == extract_bone)
		{
			//AfxMessageBox(_T("bone"));
		}
	}
	else if (wParam == 1)//confirm extract
	{
		if (lParam == extract_sinus)
		{
			//AfxMessageBox(_T("sinus"));
		}
		else if (lParam == extract_airway)
		{
			//AfxMessageBox(_T("airway"));
		}
		else if (lParam == extract_root)
		{
			//AfxMessageBox(_T("root"));
		}
		else if (lParam == extract_bone)
		{
			//AfxMessageBox(_T("bone"));
		}
	}
	else if (wParam == 2)//reset extract
	{
		if (lParam == extract_sinus)
		{
			//AfxMessageBox(_T("sinus"));
		}
		else if (lParam == extract_airway)
		{
			//AfxMessageBox(_T("airway"));
		}
		else if (lParam == extract_root)
		{
			//AfxMessageBox(_T("root"));
		}
		else if (lParam == extract_bone)
		{
			//AfxMessageBox(_T("bone"));
		}
	}

	return 1;
}

LRESULT CVTKMFCTESTView::WPFCALL_FILEPROCESSWIN(WPARAM wParam, LPARAM lParam)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	WPFDLG_ALL_HIDE(2);

	if (wParam == 0)//ct process
	{
		if (lParam == 1)
		{
			CRect nowSizeClient;
			GetClientRect(nowSizeClient);

			int mid_x = (nowSizeClient.left + nowSizeClient.right) / 2 - pFrame->m_fileimportct->GetWidth() / 2;
			int mid_y = (nowSizeClient.top + nowSizeClient.bottom) / 2 - pFrame->m_fileimportct->GetHeight() / 2;

			pFrame->m_fileimportct->SetPosition(mid_y, mid_x);
			pFrame->m_fileimportct->Show();
		}
		else if (lParam == 2)
		{
			AfxMessageBox(_T("ct range"));
		}
		else if (lParam == 3)
		{

		}
	}
	else if (wParam == 1)//upper jaw process
	{
		if (lParam == 1)
		{
			AfxMessageBox(_T("upper jaw load"));
		}
		else if (lParam == 2)
		{
			AfxMessageBox(_T("upper crown load"));
		}
		else if (lParam == 3)
		{
			int min_x = 0;
			int min_y = 550;
			pFrame->m_removetooth->SetPosition(min_y, min_x);
			pFrame->m_removetooth->Show();
		}
	}
	else if (wParam == 2)//lower jaw process
	{
		if (lParam == 1)
		{
			AfxMessageBox(_T("lower jaw load"));
		}
		else if (lParam == 2)
		{
			AfxMessageBox(_T("lower crown load"));
		}
		else if (lParam == 3)
		{
			int min_x = 0;
			int min_y = 550;
			pFrame->m_removetooth->SetPosition(min_y, min_x);
			pFrame->m_removetooth->Show();
		}
	}
	else if (wParam == 3)//face process
	{
		if (lParam == 1)
		{
			AfxMessageBox(_T("2d face load"));
		}
		else if (lParam == 2)
		{
			AfxMessageBox(_T("3d face load"));
		}
	}
	else if (wParam == 10)//ct load dialog
	{
		if (lParam == 0)
		{

		}
		else if (lParam == 1)
		{
			CString path_name;
			path_name = pFrame->m_fileimportct->GetCTFolderPath().c_str();
			pFrame->m_fileimportct->Hide();

			//讀入ct
			CFileOpenDir(path_name);
			SetResliceSagittalRender();
			SetResliceCoronalRender();
			SetResliceAxialRender();
			ShowVolumeRendering();
			ShowSagittalImage();
			ShowCoronalImage();
			ShowAxialImage();
			SetVolumeRenderingRender();
			SetInteractor();
		}
		else if (lParam == 2)
		{
			pFrame->m_fileimportct->Hide();
		}
	}

	return 1;
}

void CVTKMFCTESTView::WPFDLG_ALL_HIDE(int level)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	if (level == 0)
	{
		pFrame->m_fileprocesswin->Hide();
		pFrame->m_alignwin->Hide();
		pFrame->m_manualwin->Hide();
		pFrame->m_removetooth->Hide();
		pFrame->m_fileimportct->Hide();
		pFrame->m_extract->Hide();
	}
	else if (level == 1)
	{
		pFrame->m_fileprocesswin->Hide();
		pFrame->m_alignwin->Hide();
		pFrame->m_manualwin->Hide();
		pFrame->m_extract->Hide();
	}
	else if (level == 2)
	{
		pFrame->m_removetooth->Hide();

	}
}

LRESULT CVTKMFCTESTView::WPFCALL(WPARAM wParam, LPARAM lParam)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	WPFDLG_ALL_HIDE(0);

	if (wParam == 0)//開檔
	{
		int min_x = 0;
		int min_y = 679;
		pFrame->m_fileprocesswin->SetPosition(min_y, min_x);
		pFrame->m_fileprocesswin->Show();
	}
	else if (wParam == 1)//定位
	{
		int min_x = 0;
		int min_y = 679;
		pFrame->m_alignwin->SetPosition(min_y, min_x);
		pFrame->m_alignwin->Show();
	}
	else if (wParam == 2)//手調
	{
		int min_x = 0;
		int min_y = 679;
		pFrame->m_manualwin->SetPosition(min_y, min_x);
		pFrame->m_manualwin->Show();
	}
	else if (wParam == 3)//萃取
	{
		int min_x = 0;
		int min_y = 679;
		pFrame->m_extract->SetPosition(min_y, min_x);
		pFrame->m_extract->Show();
	}
	else if (wParam == 4)//存檔
	{
		int kk = pFrame->m_fileprocesswin->GetHeight();
		CString yy;
		yy.Format(_T("%d"), kk);
		AfxMessageBox(yy);
		//AfxMessageBox(_T("存檔"));
		//CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		//pFrame->m_fileprocesswin->Hide();
	}
	else if (wParam == 5)
	{

	}
	else if (wParam == 6)
	{

	}
	else if (wParam == 7)
	{

	}
	else if (wParam == 8)
	{

	}
	else if (wParam == 9)
	{

	}
	else if (wParam == 10)
	{
		//患者資訊
		AfxMessageBox(_T("患者"));
	}
	else if (wParam == 11)
	{
		//設定
		AfxMessageBox(_T("設定"));
	}
	else if (wParam == 12)
	{

	}
	else if (wParam == 13)
	{

	}
	else if (wParam == 14)
	{

	}
	else if (wParam == 15)
	{

	}

	//wpfcall();

	return 1;
}

void CVTKMFCTESTView::wpfmainShow()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	BtnFuncBar *b = new BtnFuncBar(this->GetSafeHwnd(), pFrame->m_hWnd);

	CRect nowSizeClient;
	GetClientRect(nowSizeClient);

	int mid_x = (nowSizeClient.left + nowSizeClient.right) / 2 - b->GetWidth() / 2;
	::SetWindowPos(b->GetHWND(), NULL, mid_x, 50, b->GetWidth(), b->GetHeight(), NULL);
	::ShowWindow(b->GetHWND(), SW_SHOW);
}
