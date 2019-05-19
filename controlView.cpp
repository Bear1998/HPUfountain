// controlView.cpp : implementation file
//

#include "stdafx.h"
#include "HPUFountain.h"
#include "controlView.h"

#include "HPUFountainDoc.h"
#include "HPUFountainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CcontrolView

IMPLEMENT_DYNCREATE(CcontrolView, CFormView)

CcontrolView::CcontrolView()
	: CFormView(CcontrolView::IDD)
{
	//{{AFX_DATA_INIT(CcontrolView)
	m_nLighting = -1;
	m_yanse = -1;
	m_penquanxingzhuang = -1;
	m_xuanzhuan = -1;
	//}}AFX_DATA_INIT
}

CcontrolView::~CcontrolView()
{
}

void CcontrolView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CcontrolView)
	DDX_Control(pDX, IDC_SLIDERJIAODU, m_sliderjiaodu);
	DDX_Control(pDX, IDC_SLIDERGAODU, m_slidergaodu);
	DDX_Control(pDX, IDC_STATICSHULIANG, m_penquanshuliang);
	DDX_Control(pDX, IDC_SLIDERWEIZHI, m_sliderweizhi);
	DDX_Control(pDX, IDC_SLIDERSHULIANG, m_slidershuliang);
	DDX_Control(pDX, IDC_SLIDERR, m_sliderR);
	DDX_Control(pDX, IDC_SLIDERG, m_sliderG);
	DDX_Control(pDX, IDC_SLIDERCUXI, m_slidercuxi);
	DDX_Control(pDX, IDC_SLIDERB, m_sliderB);
	DDX_Control(pDX, IDC_R, m_r);
	DDX_Control(pDX, IDC_PENQUANWEIZHU, m_xianshiweiyi);
	DDX_Control(pDX, IDC_PENQUANCUXI, m_xianshicuxi);
	DDX_Control(pDX, IDC_G, m_g);
	DDX_Control(pDX, IDC_B, m_b);
	DDX_Radio(pDX, IDC_LIGHTING, m_nLighting);
	DDX_Radio(pDX, IDC_PENQUANYANSE, m_yanse);
	DDX_Radio(pDX, IDC_XINGZHUANG, m_penquanxingzhuang);
	DDX_Radio(pDX, IDC_XUANZHUAN1, m_xuanzhuan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CcontrolView, CFormView)
	//{{AFX_MSG_MAP(CcontrolView)
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_LIGHTING, OnLighting)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_XUANZHUAN1, OnXuanzhuan1)
	ON_BN_CLICKED(IDC_XUANZHUAN, OnXuanzhuan)
	ON_BN_CLICKED(IDC_XINGZHUANG, OnXingzhuang)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_PENQUANYANSE, OnPenquanyanse)
	ON_BN_CLICKED(IDC_PENQUANYANSE2, OnPenquanyanse2)
	ON_BN_CLICKED(IDC_PENQUANYANSE3, OnPenquanyanse3)
	ON_BN_CLICKED(IDC_PENQUANYANSE4, OnPenquanyanse4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CcontrolView diagnostics

#ifdef _DEBUG
void CcontrolView::AssertValid() const
{
	CFormView::AssertValid();
}

void CcontrolView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CcontrolView message handlers

BOOL CcontrolView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

LRESULT CcontrolView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFormView::DefWindowProc(message, wParam, lParam);
}

void CcontrolView::OnCancelMode() 
{
	CFormView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CcontrolView::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CFormView::OnCaptureChanged(pWnd);
}

BOOL CcontrolView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFormView::PreCreateWindow(cs);
}

void CcontrolView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_slidershuliang.SetRange(1,600); //设置喷泉数目的变化范围
	m_slidershuliang.SetTicFreq(6); //设置每次推进的个数
	m_slidershuliang.SetPos(1); //设置喷泉数目的初始数量
	
	m_sliderweizhi.SetRange(0,25); //设置位移的变化范围
	m_sliderweizhi.SetPos(0); //位移的初始值

	m_slidercuxi.SetRange(1,5); //水柱粗细
	m_slidercuxi.SetPos(2);

	m_sliderR.SetRange(0,100);
	m_sliderR.SetPos(50);

	m_sliderG.SetRange(0,100);
	m_sliderG.SetPos(30);

	m_sliderB.SetRange(0,100);
	m_sliderB.SetPos(100);

	m_slidergaodu.SetRange(0,5);//高度变化
	m_slidergaodu.SetPos(1);

	m_sliderjiaodu.SetRange(-5,10);//角度变化
	m_sliderjiaodu.SetPos(1);

	m_nLighting=0; //光照
	m_yanse=0; // 颜色
	m_xuanzhuan=0;//旋转
	m_penquanxingzhuang=0; //喷泉形状

	CString str(""); //显示喷泉数目
	str.Format("%d",m_slidershuliang.GetPos());
	m_penquanshuliang.SetWindowText(str);

	CString weiyi(""); //喷泉位置
	weiyi.Format("%d",m_sliderweizhi.GetPos());
	m_xianshiweiyi.SetWindowText(weiyi);

	CString cuxi(""); //喷泉粗细
	cuxi.Format("%d",m_slidercuxi.GetPos());
	m_xianshicuxi.SetWindowText(cuxi);

	CString strR(""); //颜色R
	strR.Format("%d",m_sliderR.GetPos());
	m_r.SetWindowText(strR);

	CString strG(""); // 颜色G
	strG.Format("%d",m_sliderG.GetPos());
	m_g.SetWindowText(strG);
	
	CString strB(""); // 颜色B
	strB.Format("%d",m_sliderB.GetPos());
	m_b.SetWindowText(strB);

	UpdateData(FALSE);
}

void CcontrolView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	UpdateData();
	pDoc->m_shuliang=m_slidershuliang.GetPos();
	pDoc->m_weizhi=m_sliderweizhi.GetPos();
	pDoc->m_cuxi=m_slidercuxi.GetPos();
	pDoc->m_sliderR=m_sliderR.GetPos();
	pDoc->m_sliderG=m_sliderG.GetPos();
	pDoc->m_sliderB=m_sliderB.GetPos();
	pDoc->m_gaodu=m_slidergaodu.GetPos();
	pDoc->m_jiaodu=m_sliderjiaodu.GetPos();

	/**
	 * 查看角度范围-5 ~ 10
	CString tt("");
	tt.Format("%d",pDoc->m_jiaodu);
	MessageBox(tt);
	*/

	//显示喷泉的数量
	CString str("");
	str.Format("%d",m_slidershuliang.GetPos());
	m_penquanshuliang.SetWindowText(str);
	UpdateData(FALSE);   
	//显示颜色的变化
    CString strR("");
	strR.Format("%d",m_sliderR.GetPos());
	m_r.SetWindowText(strR);
	UpdateData(FALSE);
	
	CString strG("");
    strG.Format("%d",m_sliderG.GetPos());
	m_g.SetWindowText(strG);
	UpdateData(FALSE);
	
	CString strB("");
    strB.Format("%d",m_sliderB.GetPos());
	m_b.SetWindowText(strB);
	UpdateData(FALSE);
    //显示位移
	CString weiyi("");
	weiyi.Format("%d",m_sliderweizhi.GetPos());
	m_xianshiweiyi.SetWindowText(weiyi);
	UpdateData(FALSE);
    //显示粗细
	CString cuxi("");
	cuxi.Format("%d",m_slidercuxi.GetPos());
	m_xianshicuxi.SetWindowText(cuxi);
    UpdateData(FALSE);

	pDoc->UpdateAllViews(this);
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CcontrolView::OnLighting() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
 	pDoc->m_light=0;
	pDoc->UpdateAllViews(this);
}

void CcontrolView::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	pDoc->m_light=1;
	pDoc->UpdateAllViews(this);
}

void CcontrolView::OnXuanzhuan1() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	pDoc->m_xuanzhuan=0;
	pDoc->UpdateAllViews(this);
}

void CcontrolView::OnXuanzhuan() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	pDoc->m_xuanzhuan=1;
	pDoc->UpdateAllViews(this);
}

void CcontrolView::OnXingzhuang() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	pDoc->m_xingzhuang=0;
	pDoc->UpdateAllViews(this);
}

void CcontrolView::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	pDoc->m_xingzhuang=1;
	pDoc->UpdateAllViews(this);
}

void CcontrolView::OnPenquanyanse() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	pDoc->m_color=0;
	pDoc->UpdateAllViews(this);
}

void CcontrolView::OnPenquanyanse2() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	pDoc->m_color=1;
	pDoc->UpdateAllViews(this);
}

void CcontrolView::OnPenquanyanse3() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	pDoc->m_color=2;
	pDoc->UpdateAllViews(this);
}

void CcontrolView::OnPenquanyanse4() 
{
	// TODO: Add your control notification handler code here
	CHPUFountainDoc* pDoc=(CHPUFountainDoc*)CView::GetDocument();
	pDoc->m_color=3;
	pDoc->UpdateAllViews(this);
}
