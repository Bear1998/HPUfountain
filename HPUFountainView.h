// HPUFountainView.h : interface of the CHPUFountainView class
//
/////////////////////////////////////////////////////////////////////////////
#include "HPUFountainDoc.h"

#if !defined(AFX_HPUFOUNTAINVIEW_H__CB880519_0135_4405_A411_337BE55B11B7__INCLUDED_)
#define AFX_HPUFOUNTAINVIEW_H__CB880519_0135_4405_A411_337BE55B11B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PI 3.1415926

struct particle
{
	float t;	//粒子的生命期
	float v;	//粒子运动的速度
	float d;	//粒子运动的方向
	float r;	//红色值
	float g;	//绿色值
	float b;	//蓝色值
	float x,y,z;	//粒子的位置坐标
	float xd,zd;	//粒子在x和z方向的增加量
	char type;	//粒子类型（运动或淡化）
	float a;	//淡化alpha值
	float s,rr;   //针对模型三额外添加
	int guocheng; //针对模型八额外添加
	struct particle *next,*prev;
};
struct point
{
	float x,y,z;
};

class CHPUFountainView : public CView
{
protected: // create from serialization only
	CHPUFountainView();
	DECLARE_DYNCREATE(CHPUFountainView)

// Attributes
public:
	CHPUFountainDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHPUFountainView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawTeapot();
	void DrawTable();
	//void OnEraseBkgnd(CDC* pDC);
	void MoveParticles1();
	void AddParticles1();
	void normalize(point *V);
	void vect_mult(point *A, point *B, point *C);
	void DeleteParticles();
	void MoveParticles();
	void AddParticles();
	void DrawFountain();
	void DrawEdge();
	void DrawWater();
	void Light();
	void LoadTexture(char *fn, int t_num);
	void draw_string(void *font, const char* string);
	void DrawString();
	BOOL RenderScene();
	void Init();
	void HuiFu();
	BOOL SetupPixelFormat();
	BOOL InitializeOpenGL(CDC *pDC);
	virtual ~CHPUFountainView();

	HGLRC m_hRC;	//OpenGL绘制描述表
	CDC* m_pDC;	//OpenGL设备描述表

	int count;//控制模型之间的转换
	float a;	//旋转增量
	int i,j,num;	//喷泉数量
	int gaodu,jiaodu; //喷泉高度、角度
	point table[41],table1[41],table2[41],table3[41],table4[41];//模型五的参数
	
	float m_sliderR;//颜色
	float m_sliderG;
	float m_sliderB;
	float weiyi[3];
	float cuxi[3];
	GLuint m_nlighting;	//光照
	GLuint m_yanse;	//颜色
	GLuint m_xuanzhuan;
	GLuint m_xingzhuang;
	struct particle *fn[1000];	//喷泉
	struct point cam,upv;	//相机位置、方向向量
	//计算帧频率的参数
	int frame_count;
	clock_t starttime,endtime,passtime;
	float cur_time;
	char tem[128];

	CMyTexture* m_Tex;
	unsigned *teximage;	//粒子纹理
	GLuint texture[3];	//纹理数据

	//定义水池的纹理
	CLoadTexture ground;
	CLoadTexture rock;
	CLoadTexture water;
	CLoadTexture teapot; 

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	//{{AFX_MSG(CHPUFountainView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnCancelMode();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHuifu();
	afx_msg void OnModel1();
	afx_msg void OnModel2();
	afx_msg void OnModel3();
	afx_msg void OnModel4();
	afx_msg void OnModel5();
	afx_msg void OnModel6();
	afx_msg void OnModel7();
	afx_msg void OnModel8();
	afx_msg void OnModel9();
	afx_msg void OnModel10();
	afx_msg void OnModel11();
	afx_msg void OnModel12();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnModel13();
	afx_msg void OnModel15();
	afx_msg void OnModel16();
	afx_msg void OnModel17();
	afx_msg void OnModel20();
	afx_msg void OnModel21();
	afx_msg void OnModel22();
	afx_msg void OnModel31();
	afx_msg void OnModel32();
	afx_msg void OnModel33();
	afx_msg void OnModel34();
	afx_msg void OnModel35();
	afx_msg void OnModel36();
	afx_msg void OnModel37();
	afx_msg void OnModel40();
	afx_msg void OnModel41();
	afx_msg void OnModel42();
	afx_msg void OnModel43();
	afx_msg void OnModel45();
	afx_msg void OnModel46();
	afx_msg void OnModel47();
	afx_msg void OnModel48();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HPUFountainView.cpp
inline CHPUFountainDoc* CHPUFountainView::GetDocument()
   { return (CHPUFountainDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HPUFOUNTAINVIEW_H__CB880519_0135_4405_A411_337BE55B11B7__INCLUDED_)
