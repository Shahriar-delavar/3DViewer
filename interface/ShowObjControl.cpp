#include "pch.h"
#include "ShowObjControl.h"
#include "MessageID.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHw_showobjcontrol;
gcroot<UI::ShowObjControl^> gwcObject;

ShowObjControl::ShowObjControl(HWND hView, HWND hWnd)
{
	HwndSourceParameters^ sourceParams = gcnew HwndSourceParameters("hi");
	sourceParams->PositionX = 0;
	sourceParams->PositionY = 0;
	sourceParams->Height = 480;
	sourceParams->Width = 480;
	sourceParams->ParentWindow = System::IntPtr::IntPtr(hView);
	sourceParams->WindowStyle = WS_POPUP; // style, use WS_POPUP to show transparency style
	sourceParams->UsesPerPixelOpacity = true;

	gHw_showobjcontrol = gcnew HwndSource(*sourceParams);
	gwcObject = gcnew UI::ShowObjControl();
	gwcObject->HostHandle = (IntPtr)hView;
	System::Windows::FrameworkElement^ myPage = gwcObject;
	gHw_showobjcontrol->RootVisual = myPage;

	hwndWPF = (HWND)gHw_showobjcontrol->Handle.ToPointer();
}

ShowObjControl::~ShowObjControl()
{
}

void ShowObjControl::Show()
{
}

HWND ShowObjControl::GetHWND()
{
	return hwndWPF;
}

int ShowObjControl::GetWidth()
{
	return gwcObject->GetWidth();
}

int ShowObjControl::GetHeight()
{
	return gwcObject->GetHeight();
}