#include "pch.h"
#include "ManualWin.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource_MANUALALIGNWIN;
gcroot<UI::ManualWin^> gwcObject = nullptr;

ManualWin::ManualWin(HWND hView, HWND hWnd)
{
	gwcObject = gcnew UI::ManualWin();
	gwcObject->SetParentHwnd((IntPtr)hView);
}

ManualWin::~ManualWin()
{
	Is_Show = FALSE;
}

void ManualWin::Show()
{
	gwcObject->Show();
	Is_Show = TRUE;
}

void ManualWin::Hide()
{
	gwcObject->Hide();
	Is_Show = FALSE;
}

HWND ManualWin::GetHWND()
{
	return hwndWPF;
}

int ManualWin::GetWidth()
{
	return gwcObject->GetWidth();
}

int ManualWin::GetHeight()
{
	return gwcObject->GetHeight();
}

void ManualWin::SetPosition(int MFCFrameTop, int MFCFrameLeft)
{
	gwcObject->SetFramePosition(MFCFrameTop, MFCFrameLeft);
}
