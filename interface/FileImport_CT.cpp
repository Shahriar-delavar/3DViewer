#include "pch.h"
#include "FileImport_CT.h"
#include "MessageID.h"
#include <msclr/marshal_atl.h>

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource_FILEIMPORTCT;
gcroot<UI::FileImport_CT^> gwcObject = nullptr;

FileImport_CT::FileImport_CT(HWND hView, HWND hWnd)
{
	gwcObject = gcnew UI::FileImport_CT();
	gwcObject->SetParentHwnd((IntPtr)hView);
}

FileImport_CT::~FileImport_CT()
{
	Is_Show = FALSE;
}

void FileImport_CT::Show()
{
	gwcObject->Show();
	Is_Show = TRUE;
}

void FileImport_CT::Hide()
{
	gwcObject->Hide();
	Is_Show = FALSE;
}

HWND FileImport_CT::GetHWND()
{
	return hwndWPF;
}

int FileImport_CT::GetWidth()
{
	return (int)gwcObject->Width;
	//return gwcObject->GetWidth();
}

int FileImport_CT::GetHeight()
{
	return (int)gwcObject->Height;
	//return gwcObject->GetHeight();
}

void FileImport_CT::SetPosition(int MFCFrameTop, int MFCFrameLeft)
{
	gwcObject->SetFramePosition(MFCFrameTop, MFCFrameLeft);
}

void MarshalString(String ^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalString(String ^ s, wstring& os) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

string FileImport_CT::GetCTFolderPath()
{
	//string report;
	//report = "";
	//return report;
	string folderpath = "";
	MarshalString(gwcObject->GetCTFolderPath(), folderpath);
	return folderpath;
}
