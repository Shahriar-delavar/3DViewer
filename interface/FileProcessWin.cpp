#include "pch.h"
#include "FileProcessWin.h"
#include "MessageID.h"
#include <iostream>
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource_FILEPROCESS;
gcroot<UI::FileProcessWin^> gwcObject = nullptr;
bool FileProcessWin::isCreate = false;
FileProcessWin::FileProcessWin(HWND hView, HWND hWnd)
{
	std::cout << "fileprocess";
	if (!isCreate)
	{
		std::cout << " fileprocess create";
		gwcObject = gcnew UI::FileProcessWin();
		gwcObject->SetParentHwnd((IntPtr)hView);
		isCreate = true;
	}
	else
	{
		std::cout << " fileprocess redirect";
		gwcObject->SetParentHwnd((IntPtr)hView);
	}

	Is_Show = FALSE;
}

FileProcessWin::~FileProcessWin()
{
	/*if (System::Object::ReferenceEquals(WpfBtnFuncBar, nullptr) == false)
	{
		WpfBtnFuncBar->Close();
		WpfBtnFuncBar = nullptr;
	}*/
}

void FileProcessWin::Setparaent(HWND mother)
{
	gwcObject->SetParentHwnd((IntPtr)mother);
}

void FileProcessWin::Show()
{
	gwcObject->Show();
	Is_Show = TRUE;
}

void FileProcessWin::Hide()
{
	gwcObject->Hide();
	Is_Show = FALSE;
}

HWND FileProcessWin::GetHWND()
{
	return hwndWPF;
}

int FileProcessWin::GetWidth()
{
	return (int)gwcObject->Width;
}

int FileProcessWin::GetHeight()
{
	return (int)gwcObject->Height;
}

void FileProcessWin::SetPosition(int MFCFrameTop, int MFCFrameLeft)
{
	gwcObject->SetFramePosition(MFCFrameTop,MFCFrameLeft);
}
