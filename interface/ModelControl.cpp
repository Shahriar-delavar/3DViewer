#include "pch.h"
#include "ModelControl.h"
#include "MessageID.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHw_modelcontrol;
gcroot<UI::ModelControl^> gwcObject;

ModelControl::ModelControl(HWND hView, HWND hWnd)
{
	HwndSourceParameters^ sourceParams = gcnew HwndSourceParameters("hi");
	sourceParams->PositionX = 0;
	sourceParams->PositionY = 0;
	sourceParams->Height = 480;
	sourceParams->Width = 480;
	sourceParams->ParentWindow = System::IntPtr::IntPtr(hView);
	sourceParams->WindowStyle = WS_POPUP; // style, use WS_POPUP to show transparency style
	sourceParams->UsesPerPixelOpacity = true;

	gHw_modelcontrol = gcnew HwndSource(*sourceParams);
	gwcObject = gcnew UI::ModelControl();
	gwcObject->HostHandle = (IntPtr)hView;
	System::Windows::FrameworkElement^ myPage = gwcObject;
	gHw_modelcontrol->RootVisual = myPage;

	////加了鍵盤事件才可以傳到WPF
	//gHwndSource->AddHook(gcnew System::Windows::Interop::HwndSourceHook(ChildHwndSourceHook));
	hwndWPF = (HWND)gHw_modelcontrol->Handle.ToPointer();
}

ModelControl::~ModelControl()
{
}

void ModelControl::Show()
{
}

HWND ModelControl::GetHWND()
{
	return hwndWPF;
}

int ModelControl::GetWidth()
{
	return gwcObject->GetWidth();
}

int ModelControl::GetHeight()
{
	return gwcObject->GetHeight();
}