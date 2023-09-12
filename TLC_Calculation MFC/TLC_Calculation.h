
// TLC_Calculation.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTLC_CalculationApp:
// See TLC_Calculation.cpp for the implementation of this class
//

class CTLC_CalculationApp : public CWinApp
{
public:
	CTLC_CalculationApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTLC_CalculationApp theApp;
