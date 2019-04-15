#if !defined(AFX_CONTROLVIEW_H__E654F8C3_6AC3_4414_A4CD_86774BC915B6__INCLUDED_)
#define AFX_CONTROLVIEW_H__E654F8C3_6AC3_4414_A4CD_86774BC915B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// controlView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CcontrolView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CcontrolView : public CFormView
{
protected:
	CcontrolView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CcontrolView)

// Form Data
public:
	//{{AFX_DATA(CcontrolView)
	enum { IDD = IDD_DIALOG1 };
	CSliderCtrl	m_sliderjiaodu;
	CSliderCtrl	m_slidergaodu;
	CStatic	m_penquanshuliang;
	CSliderCtrl	m_sliderweizhi;
	CSliderCtrl	m_slidershuliang;
	CSliderCtrl	m_sliderR;
	CSliderCtrl	m_sliderG;
	CSliderCtrl	m_slidercuxi;
	CSliderCtrl	m_sliderB;
	CStatic	m_r;
	CStatic	m_xianshiweiyi;
	CStatic	m_xianshicuxi;
	CStatic	m_g;
	CStatic	m_b;
	int		m_nLighting;
	int		m_yanse;
	int		m_penquanxingzhuang;
	int		m_xuanzhuan;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CcontrolView)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CcontrolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CcontrolView)
	afx_msg void OnCancelMode();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLighting();
	afx_msg void OnRadio2();
	afx_msg void OnXuanzhuan1();
	afx_msg void OnXuanzhuan();
	afx_msg void OnXingzhuang();
	afx_msg void OnRadio5();
	afx_msg void OnPenquanyanse();
	afx_msg void OnPenquanyanse2();
	afx_msg void OnPenquanyanse3();
	afx_msg void OnPenquanyanse4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLVIEW_H__E654F8C3_6AC3_4414_A4CD_86774BC915B6__INCLUDED_)
