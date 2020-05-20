#include "pch.h"
#include "RemoveTooth.h"
#include "MessageID.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource_REMOVETEETH;
gcroot<UI::RemoveTooth^> gwcObject = nullptr;

RemoveTooth::RemoveTooth(HWND hView, HWND hWnd)
{
	gwcObject = gcnew UI::RemoveTooth();
	gwcObject->SetParentHwnd((IntPtr)hView);
}

RemoveTooth::~RemoveTooth()
{
	Is_Show = FALSE;
}

void RemoveTooth::Show()
{
	gwcObject->Show();
	Is_Show = TRUE;
}

void RemoveTooth::Hide()
{
	gwcObject->Hide();
	Is_Show = FALSE;
}

HWND RemoveTooth::GetHWND()
{
	return hwndWPF;
}

int RemoveTooth::GetWidth()
{
	return gwcObject->GetWidth();
}

int RemoveTooth::GetHeight()
{
	return gwcObject->GetHeight();
}

void RemoveTooth::SetPosition(int MFCFrameTop, int MFCFrameLeft)
{
	gwcObject->SetFramePosition(MFCFrameTop, MFCFrameLeft);
}
