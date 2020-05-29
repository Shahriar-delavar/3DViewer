#include "pch.h"
#include "AlignWin.h"
#include "MessageID.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource_ALIGNWIN;
gcroot<UI::AlignWin^> gwcObject = nullptr;

AlignWin::AlignWin(HWND hView, HWND hWnd)
{
	gwcObject = gcnew UI::AlignWin();
	gwcObject->SetParentHwnd((IntPtr)hView);
}

AlignWin::~AlignWin()
{
	Is_Show = FALSE;
}

void AlignWin::Show()
{
	gwcObject->Show();
	Is_Show = TRUE;
}

void AlignWin::Hide()
{
	gwcObject->Hide();
	Is_Show = FALSE;
}

HWND AlignWin::GetHWND()
{
	return hwndWPF;
}

int AlignWin::GetWidth()
{
	return (int)gwcObject->Width;
}

int AlignWin::GetHeight()
{
	return (int)gwcObject->Height;
}

void AlignWin::SetPosition(int MFCFrameTop, int MFCFrameLeft)
{
	gwcObject->SetFramePosition(MFCFrameTop, MFCFrameLeft);
}

