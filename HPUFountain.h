// HPUFountain.h : main header file for the HPUFOUNTAIN application
//

#if !defined(AFX_HPUFOUNTAIN_H__2CE8E626_A746_4553_BB51_11EE78890806__INCLUDED_)
#define AFX_HPUFOUNTAIN_H__2CE8E626_A746_4553_BB51_11EE78890806__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHPUFountainApp:
// See HPUFountain.cpp for the implementation of this class
//

class CHPUFountainApp : public CWinApp
{
public:
	CHPUFountainApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHPUFountainApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHPUFountainApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HPUFOUNTAIN_H__2CE8E626_A746_4553_BB51_11EE78890806__INCLUDED_)
