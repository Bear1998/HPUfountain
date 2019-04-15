// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "HPUFountain.h"

#include "MainFrm.h"
#include "controlView.h"
#include "HPUFountainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_TIMER,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.ShowWindow(SW_HIDE);//隐藏工具栏
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	//全屏显示
	RECT rc;
 	::GetWindowRect(::GetDesktopWindow(),&rc);
	this->MoveWindow(&rc);

	SetTimer(1,1000,NULL);
	CLoginDlg dlg;//设置启动画面
	dlg.DoModal();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE|WS_VISIBLE|WS_MAXIMIZE;//取消窗口上的文档标题
	cs.lpszName ="基于粒子系统的喷泉三维造型设计与建模仿真";
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CTime t=CTime::GetCurrentTime();
	CString str=t.Format("%H:%M:%S");

	CClientDC dc(this);
	CSize sz=dc.GetTextExtent(str);
	int index=0;
	index=m_wndStatusBar.CommandToIndex(ID_TIMER);
	m_wndStatusBar.SetPaneInfo(index,ID_TIMER,SBPS_NORMAL,sz.cx);
	m_wndStatusBar.SetPaneText(index,str);

	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_splitter.CreateStatic(this,1,2);
	m_splitter.CreateView(0,0,RUNTIME_CLASS(CcontrolView),CSize(210,600),pContext);
	m_splitter.CreateView(0,1,RUNTIME_CLASS(CHPUFountainView),CSize(520,600),pContext);
	
	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
