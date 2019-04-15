// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__2EAA0B0C_58E1_4E64_BD67_DF031AC0CD12__INCLUDED_)
#define AFX_STDAFX_H__2EAA0B0C_58E1_4E64_BD67_DF031AC0CD12__INCLUDED_

#undef WINVER
#define WINVER 0x500 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <gl/GL.H>
#include <gl/GLAUX.H>
#include <gl/GLU.H>
#include <gl/glut.h>
#include <MATH.H>
#include <WINDOWS.H>
#include <TIME.H>
#include <stdio.h>
#include "LoginDlg.h"
#include "MyTexture.h"
#include "LoadTexture.h"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2EAA0B0C_58E1_4E64_BD67_DF031AC0CD12__INCLUDED_)
