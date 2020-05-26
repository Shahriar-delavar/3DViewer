#include "pch.h"
#include "FileImport_Upperjaw.h"
#include "MessageID.h"
#include <msclr/marshal_atl.h>

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource_FILEIMPORTUPPERJAW;
gcroot<UI::FileImport_Upperjaw^> gwcObject = nullptr;

FileImport_Upperjaw::FileImport_Upperjaw(HWND hView, HWND hWnd)
{
	gwcObject = gcnew UI::FileImport_Upperjaw();
	gwcObject->SetParentHwnd((IntPtr)hView);
}

FileImport_Upperjaw::~FileImport_Upperjaw()
{
	Is_Show = FALSE;
}

void FileImport_Upperjaw::Show()
{
	gwcObject->ShowDialog();
	Is_Show = TRUE;
}

void FileImport_Upperjaw::Hide()
{
	gwcObject->Hide();
	Is_Show = FALSE;
}

HWND FileImport_Upperjaw::GetHWND()
{
	return hwndWPF;
}

int FileImport_Upperjaw::GetWidth()
{
	return (int)gwcObject->Width;
}

int FileImport_Upperjaw::GetHeight()
{
	return (int)gwcObject->Height;
}

void FileImport_Upperjaw::SetPosition(int MFCFrameTop, int MFCFrameLeft)
{
	gwcObject->SetFramePosition(MFCFrameTop, MFCFrameLeft);
}


void MarshalString1(String ^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalString1(String ^ s, wstring& os) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

string FileImport_Upperjaw::GetCTFolderPath()
{
	string folderpath = "";
	MarshalString1(gwcObject->GetCTFolderPath(), folderpath);
	return folderpath;
}
