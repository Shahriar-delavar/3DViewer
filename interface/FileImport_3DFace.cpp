#include "pch.h"
#include "FileImport_3DFace.h"
#include "MessageID.h"
#include <msclr/marshal_atl.h>

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Media;
using namespace System::Runtime;
using namespace System::Windows::Interop;

gcroot<HwndSource^> gHwndSource_FILEIMPORT3DFACE;
gcroot<UI::FileImport_3DFace^> gwcObject = nullptr;

FileImport_3DFace::FileImport_3DFace(HWND hView, HWND hWnd)
{
	gwcObject = gcnew UI::FileImport_3DFace();
	gwcObject->SetParentHwnd((IntPtr)hView);
}

FileImport_3DFace::~FileImport_3DFace()
{
	Is_Show = FALSE;
}

void FileImport_3DFace::Show()
{
	gwcObject->ShowDialog();
	Is_Show = TRUE;
}

void FileImport_3DFace::Hide()
{
	gwcObject->Hide();
	Is_Show = FALSE;
}

HWND FileImport_3DFace::GetHWND()
{
	return hwndWPF;
}

int FileImport_3DFace::GetWidth()
{
	return (int)gwcObject->Width;
}

int FileImport_3DFace::GetHeight()
{
	return (int)gwcObject->Height;
}

void FileImport_3DFace::SetPosition(int MFCFrameTop, int MFCFrameLeft)
{
	gwcObject->SetFramePosition(MFCFrameTop, MFCFrameLeft);
}

void MarshalString5(String ^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalString5(String ^ s, wstring& os) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

string FileImport_3DFace::GetCTFolderPath()
{
	string folderpath = "";
	MarshalString5(gwcObject->GetCTFolderPath(), folderpath);
	return folderpath;
}

