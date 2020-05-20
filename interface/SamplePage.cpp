#include "pch.h"
#include "SamplePage.h"
#include "MessageID.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Interop;

gcroot<UI::SamplePage^> WpfSamplePage = nullptr;
gcroot<System::Windows::Interop::HwndSource^> gHwndSourceSamplePage = nullptr;
HWND hwndWPF_SamplePage;

SamplePage::SamplePage(HWND hView, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hView = hView;

	HwndSourceParameters^ sourceParams = gcnew HwndSourceParameters("");
	sourceParams->PositionX = 0;
	sourceParams->PositionY = 0;
	sourceParams->ParentWindow = IntPtr(m_hWnd);
	sourceParams->WindowStyle = WS_POPUP;// WS_CHILD | WS_VISIBLE; // style, use WS_POPUP to show transparency style
	sourceParams->UsesPerPixelOpacity = true;

	gHwndSourceSamplePage = gcnew HwndSource(*sourceParams);
	WpfSamplePage = gcnew UI::SamplePage();
	FrameworkElement^ myPage = WpfSamplePage;

	gHwndSourceSamplePage->RootVisual = myPage;
	hwndWPF_SamplePage = (HWND)gHwndSourceSamplePage->Handle.ToPointer();
}

SamplePage::~SamplePage()
{
	if (System::Object::ReferenceEquals(WpfSamplePage, nullptr) == false)
	{
		Show(SW_HIDE);
	}
}

void SamplePage::Show(BOOL _show)
{
	::ShowWindow(hwndWPF_SamplePage, _show);
}

float SamplePage::GetTestValue()
{
	return WpfSamplePage->GetTestValue();
}