#include "pch.h"
#include "InfoSetting.h"
#include "MessageID.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHw_infoseeting;
gcroot<UI::InfoSetting^> gwcObject;

InfoSetting::InfoSetting(HWND hView, HWND hWnd)
{
	HwndSourceParameters^ sourceParams = gcnew HwndSourceParameters("hi");
	sourceParams->PositionX = 0;
	sourceParams->PositionY = 0;
	sourceParams->Height = 480;
	sourceParams->Width = 480;
	sourceParams->ParentWindow = System::IntPtr::IntPtr(hView);
	sourceParams->WindowStyle = WS_POPUP; // style, use WS_POPUP to show transparency style
	sourceParams->UsesPerPixelOpacity = true;

	gHw_infoseeting = gcnew HwndSource(*sourceParams);
	gwcObject = gcnew UI::InfoSetting();
	gwcObject->HostHandle = (IntPtr)hView;
	System::Windows::FrameworkElement^ myPage = gwcObject;
	gHw_infoseeting->RootVisual = myPage;

	////加了鍵盤事件才可以傳到WPF
	//gHwndSource->AddHook(gcnew System::Windows::Interop::HwndSourceHook(ChildHwndSourceHook));
	hwndWPF = (HWND)gHw_infoseeting->Handle.ToPointer();
}

InfoSetting::~InfoSetting()
{
}

void InfoSetting::Show()
{
}

HWND InfoSetting::GetHWND()
{
	return hwndWPF;
}

int InfoSetting::GetWidth()
{
	return gwcObject->GetWidth();
}

int InfoSetting::GetHeight()
{
	return gwcObject->GetHeight();
}
