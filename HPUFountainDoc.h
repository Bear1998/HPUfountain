// HPUFountainDoc.h : interface of the CHPUFountainDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HPUFOUNTAINDOC_H__2C88BCCF_1CBB_40B9_8AD8_B3B94B99ABA9__INCLUDED_)
#define AFX_HPUFOUNTAINDOC_H__2C88BCCF_1CBB_40B9_8AD8_B3B94B99ABA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHPUFountainDoc : public CDocument
{
protected: // create from serialization only
	CHPUFountainDoc();
	DECLARE_DYNCREATE(CHPUFountainDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHPUFountainDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
	UINT m_shuliang;
	UINT m_weizhi;
	UINT m_cuxi;
	UINT m_light;
	UINT m_color;
	UINT m_xuanzhuan;
	UINT m_xingzhuang;
	UINT m_sliderR;
	UINT m_sliderG;
	UINT m_sliderB;
	UINT m_gaodu;
	UINT m_jiaodu;
public:
	virtual ~CHPUFountainDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHPUFountainDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HPUFOUNTAINDOC_H__2C88BCCF_1CBB_40B9_8AD8_B3B94B99ABA9__INCLUDED_)
