// interface.h : main header file for the interface DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CinterfaceApp
// See interface.cpp for the implementation of this class
//

class CinterfaceApp : public CWinApp
{
public:
	CinterfaceApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
