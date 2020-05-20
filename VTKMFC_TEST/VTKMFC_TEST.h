
// VTKMFC_TEST.h : main header file for the VTKMFC_TEST application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CVTKMFCTESTApp:
// See VTKMFC_TEST.cpp for the implementation of this class
//

class CVTKMFCTESTApp : public CWinApp
{
public:
	CVTKMFCTESTApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVTKMFCTESTApp theApp;
