#include "pch.h"
#include "BtnFuncBar.h"
#include "MessageID.h"
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource;
gcroot<UI::BtnFuncBar^> gwcObject;

BtnFuncBar::BtnFuncBar(HWND hView, HWND hWnd)
{
	HwndSourceParameters^ sourceParams = gcnew HwndSourceParameters("hi");
	sourceParams->PositionX = 0;
	sourceParams->PositionY = 0;
	sourceParams->Height = 480;
	sourceParams->Width = 480;
	sourceParams->ParentWindow = System::IntPtr::IntPtr(hView);
	sourceParams->WindowStyle = WS_POPUP; // style, use WS_POPUP to show transparency style
	sourceParams->UsesPerPixelOpacity = true;

	gHwndSource = gcnew HwndSource(*sourceParams);
	gwcObject = gcnew UI::BtnFuncBar();
	gwcObject->HostHandle = (IntPtr)hView;
	System::Windows::FrameworkElement^ myPage = gwcObject;
	gHwndSource->RootVisual = myPage;

	////加了鍵盤事件才可以傳到WPF
	//gHwndSource->AddHook(gcnew System::Windows::Interop::HwndSourceHook(ChildHwndSourceHook));
	hwndWPF =  (HWND)gHwndSource->Handle.ToPointer();
}

BtnFuncBar::~BtnFuncBar()
{
	/*if (System::Object::ReferenceEquals(WpfBtnFuncBar, nullptr) == false)
	{
		WpfBtnFuncBar->Close();
		WpfBtnFuncBar = nullptr;
	}*/
}

void BtnFuncBar::Show()
{
	//WpfBtnFuncBar->Show();
}

HWND BtnFuncBar::GetHWND()
{
	return hwndWPF;
}

int BtnFuncBar::GetWidth()
{
	return gwcObject->GetWidth();
	//int width = 420;
	//return width;
}

int BtnFuncBar::GetHeight()
{
	return gwcObject->GetHeight();
	//int height = 90;
	//return height;
}
