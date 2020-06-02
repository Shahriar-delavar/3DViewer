
// VTKMFC_TESTView.h : interface of the CVTKMFCTESTView class
//

#pragma once
#include <vtkPropPicker.h>
#include <vtkAlgorithmOutput.h>
#include <vtkImageMagnitude.h>
#include <vtkRenderer.h>
#include <vtkMFCWindow.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkPlaneSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageCast.h>
#include <vtkColorTransferFunction.h>
#include <vtkStructuredPointsReader.h>
#include <vtkStructuredPoints.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolume.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkImageActor.h>
#include <vtkOpenGLGPUVolumeRayCastMapper.h>
#include <vtkThreshold.h>
#include <vtkAutoInit.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkImageViewer2.h>
#include <vtkLODProp3D.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <sstream>
#include <iostream>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCamera.h>
#include <map>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkProperty.h>
#include <vtkMarchingCubes.h>
#include <vtkImplicitPlaneWidget.h>
#include <vtkMatrix4x4.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkImageMapper3D.h>
#include <vtkSphereSource.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <vtkDataSetMapper.h>
#include <vtkLineSource.h>
#include <vtkImageShiftScale.h>
#include <vtkImageSliceMapper.h>
#include "vtkCellPicker.h"
#include "vtkImagePlaneWidget.h"
#include "vtkTextProperty.h"
#include "vtkSTLWriter.h"
#include "vtkSTLReader.h"
#include "vtkImageShrink3D.h"
#include "vtkContourFilter.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkDecimatePro.h"
#include <vtkPointPicker.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageBlend.h>
#include <vtkParametricFunctionSource.h>
#include <vtkParametricSpline.h>

//ITK
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImageSeriesReader.h>
#include <itkImageToVTKImageFilter.h>
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkTIFFImageIO.h"
#include "itkNumericSeriesFileNames.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkConfidenceConnectedImageFilter.h"
#include "itkHoughTransform2DLinesImageFilter.h"
#include "itkThresholdSegmentationLevelSetImageFilter.h"
#include "itkFastMarchingImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkVTKImageExport.h"
#include "itkVTKImageToImageFilter.h"

//
#include <vtkInteractorStyleImage.h>
#include "myVtkInteractorStyleImage.h"

#include "BtnFuncBar.h"
#include "FileProcessWin.h"


class CVTKMFCTESTView : public CView
{
protected: // create from serialization only
	CVTKMFCTESTView() noexcept;
	DECLARE_DYNCREATE(CVTKMFCTESTView)

// Attributes
public:
	CVTKMFCTESTDoc* GetDocument() const;

	vtkRenderer     *pvtkRenderer;
	vtkRenderer     *pvtkRenderer1;
	vtkRenderer     *pvtkRenderer_dcm;
	vtkRenderer     *pvtkRenderer_cross;
	vtkRenderer     *pvtkRenderer_pano;
	vtkMFCWindow    *pvtkMFCWindow;
	// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CVTKMFCTESTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnEditOpendicom();

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	//minbear add
	void AddVolumeRendering();
	void AddImageView();
	void AddCrossSectionView();
	void AddPanoView();
	void ImageViewTest();
	void ChangeModeVolume();
	void ChangeModeVolume1();
	void BoundaryVolume(std::string s_Indirpath);

	//volume rendering set
	//inteware
	void CT_InteWare();
	//bone
	void CT_Bone();
	//skin
	void CT_Skin();
	//musle
	void CT_Musle();
	//teeth
	void CT_Teeth();
	//comp 1
	void CT_BoneSkin();
	//comp 2
	void CT_TeethSkin();

	//test muti color fn
	void CT_MutiColorFn();

	//Update Trans fun
	void UpdateTransferFn();

	//Update Trans fun
	void UpdateTransferFn1();

	bool wpfcall();

	void wpfmainShow();

	void WPFDLG_ALL_HIDE(int level=0);//level=0 所有對話盒 level=1 流程對話盒  level=2 讀檔對話盒  level=3 定位

public:
	//all global var
	//reader
	vtkSmartPointer<vtkDICOMImageReader> reader =
		vtkSmartPointer<vtkDICOMImageReader>::New();

	//mapper & volume
	vtkSmartPointer<vtkVolume> volume =
		vtkSmartPointer<vtkVolume>::New();

	vtkSmartPointer<vtkSmartVolumeMapper> mapper =
		vtkSmartPointer<vtkSmartVolumeMapper>::New();

	//property
	vtkSmartPointer<vtkVolumeProperty> property =
		vtkSmartPointer<vtkVolumeProperty>::New();

	vtkSmartPointer<vtkDICOMImageReader> reader1 =
		vtkSmartPointer<vtkDICOMImageReader>::New();

	//mapper & volume
	vtkSmartPointer<vtkVolume> volume1 =
		vtkSmartPointer<vtkVolume>::New();

	vtkSmartPointer<vtkSmartVolumeMapper> mapper1 =
		vtkSmartPointer<vtkSmartVolumeMapper>::New();

	//property
	vtkSmartPointer<vtkVolumeProperty> property1 =
		vtkSmartPointer<vtkVolumeProperty>::New();

	// Create our transfer function
	vtkSmartPointer<vtkColorTransferFunction> colorFun =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	vtkSmartPointer<vtkPiecewiseFunction> opacityFun =
		vtkSmartPointer<vtkPiecewiseFunction>::New();

	//test muti color fn
		// Create our transfer function
	vtkSmartPointer<vtkColorTransferFunction> colorFun1 =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	vtkSmartPointer<vtkPiecewiseFunction> opacityFun1 =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	// Create our transfer function
	vtkSmartPointer<vtkColorTransferFunction> colorFun2 =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	vtkSmartPointer<vtkPiecewiseFunction> opacityFun2 =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	// Create our transfer function
	vtkSmartPointer<vtkColorTransferFunction> colorFun3 =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	vtkSmartPointer<vtkPiecewiseFunction> opacityFun3 =
		vtkSmartPointer<vtkPiecewiseFunction>::New();


	//marching cube
	vtkSmartPointer<vtkMarchingCubes> marchingCubes = 
		vtkSmartPointer<vtkMarchingCubes>::New();

	vtkSmartPointer<vtkPolyDataMapper> cubemapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();

	vtkSmartPointer<vtkActor> cubeactor = 
		vtkSmartPointer<vtkActor>::New();

	//reslice
	vtkSmartPointer<vtkImageReslice> pVolumeReslice = 
		vtkSmartPointer<vtkImageReslice>::New();

	//thread hold

	afx_msg void OnEditBone();
	afx_msg void OnEditTeeth();
	afx_msg void OnEditSkin();
	afx_msg void OnEditBoneskin();
	afx_msg void OnEditTeethskin();
	afx_msg void OnEditMusle();
	afx_msg void OnEditCloseVLTeeth();
	afx_msg void OnEditCloseVLSkin();
	afx_msg LRESULT WPFCALL(WPARAM wParam, LPARAM lParam);

	//5/6/2020 handtan//PROCESSBAR
	afx_msg LRESULT WPFCALL_PROCESSBAR(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT WPFCALL_FILEPROCESSWIN(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT WPFCALL_REMOVETOOTH(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT WPFCALL_ALIGNWIN(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT WPFCALL_MANUALALIGNWIN(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT WPFCALL_EXTRACT(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT WPFCALL_INFOSETTING(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT WPFCALL_SHOWSETTING(WPARAM wParam, LPARAM lParam);
public:
	double threshold;
	double threshold_old;
	afx_msg void OnEditTestmuticolorfn();


	double opacity_1;
	double opacity_2;
	double opacity_3;
	double opacity_4;
	double opacity_5;
	double opacity_6;
	double opacity_7;

	double color_1;
	double color_2;
	double color_3;
	double color_4;
	double color_5;
	double color_6;
	double color_7;

	double num_opacity1;
	double num_color1;
	double num_opacity2;
	double num_color2;

	int volume_mode;

	std::string s_dirpath;
	CString c_dirpath;

	void ChangeColorOpacityTeeth();
	void ChangeColorOpacitySkin();

	
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void TestChangeDicomColor();
	BOOL PreTranslateMessage(MSG* pMsg);

public:
	void FileOpenDir(std::string s_Indirpath);
	void CFileOpenDir(CString s_Indirpath);
	bool GetDirPath(std::string& s_dirpath);
	bool CGetDirPath(CString & s_dirpath);
	void MarchingCube();
	void ChangeMarchingCube();

//ReOri
public:
	//function
	void ReOriVolumeRendering();
	void ReOriXYCut();
	void ReOriXZCut();
	void ReOriYZCut();
	void ReOriRotationX(float angle);
	void ReOriRotationY(float angle);
	void ReOriRotationZ(float angle);
	void ReOriTranslationX(float distance);
	void ReOriTranslationY(float distance);
	void ReOriTranslationZ(float distance);
	void ShowXYPlaneImg();
	void ShowXZPlaneImg();
	void ShowYZPlaneImg();
	void DrawCoorLineX();
	void DrawCoorLineY();
	void DrawCoorLineZ();
	void Coordinate();
	void SetCameraSide();
	void SetCameraTop();
	void SetCameraFace();
	void UpdateXYPlaneImg();
	
	void UpdateXZPlaneImg();
	void UpdateYZPlaneImg();
	bool FileOpenMergeImgData(std::string s_Indirpath);
	void TestITK(std::string s_Indirpath);
	

	//val
	vtkRenderer     *pvtkReOriVolumeRenderer;
	vtkRenderer     *pvtkReOriXYRenderer;
	vtkRenderer     *pvtkReOriYZRenderer;
	vtkRenderer     *pvtkReOriXZRenderer;

	vtkSmartPointer<vtkVolume> ReOrivolume =
		vtkSmartPointer<vtkVolume>::New();

	vtkSmartPointer<vtkSmartVolumeMapper> ReOrimapper =
		vtkSmartPointer<vtkSmartVolumeMapper>::New();

	vtkSmartPointer<vtkVolumeProperty> ReOriproperty =
		vtkSmartPointer<vtkVolumeProperty>::New();

	vtkSmartPointer<vtkMatrix4x4> resliceAxesXY =
		vtkSmartPointer<vtkMatrix4x4>::New();

	vtkSmartPointer<vtkMatrix4x4> resliceAxesYZ =
		vtkSmartPointer<vtkMatrix4x4>::New();

	vtkSmartPointer<vtkMatrix4x4> resliceAxesXZ =
		vtkSmartPointer<vtkMatrix4x4>::New();

	vtkSmartPointer<vtkImageViewer2> viewerXY =
		vtkSmartPointer<vtkImageViewer2>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> InteractorXY =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<vtkImageViewer2> viewerXZ =
		vtkSmartPointer<vtkImageViewer2>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> InteractorXZ =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<vtkImageViewer2> viewerYZ =
		vtkSmartPointer<vtkImageViewer2>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> InteractorYZ =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();

	//dicom
	int extent[6];
	double spacing[3];
	double origin[3];
	double center[3];



	vtkSmartPointer<vtkActor> lineActorX =
		vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> lineActorY =
		vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> lineActorZ =
		vtkSmartPointer<vtkActor>::New();

	std::vector<vtkSmartPointer<vtkImageData>>imageData2D;

	vtkSmartPointer<vtkImageData> imageData =
		vtkSmartPointer<vtkImageData>::New();

	int tmp_center;
	int testv;

	//debug view
	public:
	void OutPutDebugView(std::string s_string);

	//2020.03.23

	public:
		//voulme rendering
		vtkSmartPointer<vtkVolume> volumeData =
			vtkSmartPointer<vtkVolume>::New();

		vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper =
			vtkSmartPointer<vtkSmartVolumeMapper>::New();

		vtkSmartPointer<vtkVolumeProperty> volumeProperty =
			vtkSmartPointer<vtkVolumeProperty>::New();
		//slice
		vtkSmartPointer<vtkImageReslice> imageResliceAxial =
			vtkSmartPointer<vtkImageReslice>::New();
		vtkSmartPointer<vtkImageReslice> imageResliceCoronal =
			vtkSmartPointer<vtkImageReslice>::New();
		vtkSmartPointer<vtkImageReslice> imageResliceSagittal =
			vtkSmartPointer<vtkImageReslice>::New();

		//matrix
		vtkSmartPointer<vtkMatrix4x4> axesAxial =
			vtkSmartPointer<vtkMatrix4x4>::New();
		vtkSmartPointer<vtkMatrix4x4> axesCoronal =
			vtkSmartPointer<vtkMatrix4x4>::New();
		vtkSmartPointer<vtkMatrix4x4> axesSagittal =
			vtkSmartPointer<vtkMatrix4x4>::New();

		//viewer
		vtkSmartPointer<vtkImageViewer2> viewerAxial =
			vtkSmartPointer<vtkImageViewer2>::New();
		vtkSmartPointer<vtkImageViewer2> viewerCoronal =
			vtkSmartPointer<vtkImageViewer2>::New();
		vtkSmartPointer<vtkImageViewer2> viewerSagittal =
			vtkSmartPointer<vtkImageViewer2>::New();

		//interactor
		vtkSmartPointer<vtkRenderWindowInteractor> rootExtractionInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();

		//render
		vtkSmartPointer<vtkRenderer> vtkVolumeRenderingRender =
			vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkRenderer> vtkSagittalRenderer =
			vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkRenderer> vtkCoronalRenderer =
			vtkSmartPointer<vtkRenderer>::New();
		vtkSmartPointer<vtkRenderer> vtkAxialRenderer =
			vtkSmartPointer<vtkRenderer>::New();

	void SetResliceSagittalRender();
	void SetResliceCoronalRender();
	void SetResliceAxialRender();
	void SetVolumeRenderingRender();
	

	void ShowSagittalImage();
	void ShowCoronalImage();
	void ShowAxialImage();
	void ShowVolumeRendering();

	void SetInteractor();

	//test reigion growing
	void SetPickerPoints();
	void TestITKRegionGrowing(std::string path);
	void TestRegionGrowing();
	std::vector<float> SD;
	//vtkImageInteractionCallback *callback;
	myVtkInteractorStyleImage *myStyle;
	int seed[2];
	itk::Size<3> size;
	std::vector<POINT>pixelData;
	vtkPropPicker *picker;
};

#ifndef _DEBUG  // debug version in VTKMFC_TESTView.cpp
inline CVTKMFCTESTDoc* CVTKMFCTESTView::GetDocument() const
   { return reinterpret_cast<CVTKMFCTESTDoc*>(m_pDocument); }
#endif

