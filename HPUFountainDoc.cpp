// HPUFountainDoc.cpp : implementation of the CHPUFountainDoc class
//

#include "stdafx.h"
#include "HPUFountain.h"

#include "HPUFountainDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHPUFountainDoc

IMPLEMENT_DYNCREATE(CHPUFountainDoc, CDocument)

BEGIN_MESSAGE_MAP(CHPUFountainDoc, CDocument)
	//{{AFX_MSG_MAP(CHPUFountainDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHPUFountainDoc construction/destruction

CHPUFountainDoc::CHPUFountainDoc()
{
	// TODO: add one-time construction code here
	m_shuliang=9;
	m_light=0;
	m_weizhi=0;
	m_cuxi=1;
	m_color=0;
	m_xuanzhuan=0;
	m_xingzhuang=0;
	m_sliderR=50;
	m_sliderG=100;
	m_sliderB=0;
	m_gaodu=1;
	m_jiaodu=1;
}

CHPUFountainDoc::~CHPUFountainDoc()
{
}

BOOL CHPUFountainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHPUFountainDoc serialization

void CHPUFountainDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHPUFountainDoc diagnostics

#ifdef _DEBUG
void CHPUFountainDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHPUFountainDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHPUFountainDoc commands
