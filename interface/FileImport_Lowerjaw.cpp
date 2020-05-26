#include "pch.h"
#include "FileImport_Lowerjaw.h"
#include "MessageID.h"
#include <msclr/marshal_atl.h>

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource_FILEIMPORTLOWERJAW;
gcroot<UI::FileImport_Lowerjaw^> gwcObject = nullptr;

FileImport_Lowerjaw::FileImport_Lowerjaw(HWND hView, HWND hWnd)
{
	gwcObject = gcnew UI::FileImport_Lowerjaw();
	gwcObject->SetParentHwnd((IntPtr)hView);
}

FileImport_Lowerjaw::~FileImport_Lowerjaw()
{
	Is_Show = FALSE;
}

void FileImport_Lowerjaw::Show()
{
	gwcObject->ShowDialog();
	Is_Show = TRUE;
}

void FileImport_Lowerjaw::Hide()
{
	gwcObject->Hide();
	Is_Show = FALSE;
}

HWND FileImport_Lowerjaw::GetHWND()
{
	return hwndWPF;
}

int FileImport_Lowerjaw::GetWidth()
{
	return (int)gwcObject->Width;
}

int FileImport_Lowerjaw::GetHeight()
{
	return (int)gwcObject->Height;
}

void FileImport_Lowerjaw::SetPosition(int MFCFrameTop, int MFCFrameLeft)
{
	gwcObject->SetFramePosition(MFCFrameTop, MFCFrameLeft);
}

void MarshalString2(String ^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalString2(String ^ s, wstring& os) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

string FileImport_Lowerjaw::GetCTFolderPath()
{
	string folderpath = "";
	MarshalString2(gwcObject->GetCTFolderPath(), folderpath);
	return folderpath;
}