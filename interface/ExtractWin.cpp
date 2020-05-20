#include "pch.h"
#include "ExtractWin.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource_EXTRACT;
gcroot<UI::ExtractWin^> gwcObject = nullptr;

ExtractWin::ExtractWin(HWND hView, HWND hWnd)
{
	gwcObject = gcnew UI::ExtractWin();
	gwcObject->SetParentHwnd((IntPtr)hView);
}

ExtractWin::~ExtractWin()
{
	Is_Show = FALSE;
}

void ExtractWin::Show()
{
	gwcObject->Show();
	Is_Show = TRUE;
}

void ExtractWin::Hide()
{
	gwcObject->Hide();
	Is_Show = FALSE;
}

HWND ExtractWin::GetHWND()
{
	return hwndWPF;
}

int ExtractWin::GetWidth()
{
	return gwcObject->GetWidth();
}

int ExtractWin::GetHeight()
{
	return gwcObject->GetHeight();
}

void ExtractWin::SetPosition(int MFCFrameTop, int MFCFrameLeft)
{
	gwcObject->SetFramePosition(MFCFrameTop, MFCFrameLeft);
}