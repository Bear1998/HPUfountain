// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HPUFountain.h"
#include "LoginDlg.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_WM_CANCELMODE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

BOOL CLoginDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

void CLoginDlg::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::CalcWindowRect(lpClientRect, nAdjustType);
}

void CLoginDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();
	SetMenu(NULL);//去掉菜单栏
	//AnimateWindow(GetSafeHwnd(),3000,AW_HOR_NEGATIVE|AW_SLIDE);//3秒内窗口从右向左弹出
	//AnimateWindow(GetSafeHwnd(),4000,AW_HIDE|AW_BLEND);
	AnimateWindow(GetSafeHwnd(),2000,AW_BLEND);//设置登陆界面图片显示的渐现效果
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		EndDialog(-1);
		return 0;
	default:
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

int CLoginDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(-1);
	CDialog::OnLButtonDown(nFlags, point);
}
