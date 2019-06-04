//HPUFountainView.cpp:implementationoftheCHPUFountainViewclass
//

#include"stdafx.h"
#include"HPUFountain.h"

#include"HPUFountainDoc.h"
#include"HPUFountainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

//����ˮ�صĳ�,����
#define m_weizhi0				100
#define NUM_X_OSCILLATORS	200
#define NUM_Z_OSCILLATORS	200
#define OSCILLATOR_DISTANCE		2
#define MAXX					(NUM_X_OSCILLATORS*OSCILLATOR_DISTANCE)
#define MAXZ					(NUM_Z_OSCILLATORS*OSCILLATOR_DISTANCE)
#define POOL_HEIGHT				3
/////////////////////////////////////////////////////////////////////////////
//CHPUFountainView

IMPLEMENT_DYNCREATE(CHPUFountainView,CView)

BEGIN_MESSAGE_MAP(CHPUFountainView,CView)
	//{{AFX_MSG_MAP(CHPUFountainView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CANCELMODE()
	ON_WM_TIMER()
	ON_COMMAND(IDM_HUIFU,OnHuifu)
	ON_COMMAND(IDM_MODEL1,OnModel1)
	ON_COMMAND(IDM_MODEL4, OnModel4)
	ON_COMMAND(IDM_MODEL5, OnModel5)	
	ON_COMMAND(IDM_MODEL8,OnModel8)
	ON_COMMAND(IDM_MODEL9,OnModel9)
	ON_COMMAND(IDM_MODEL10,OnModel10)
	ON_COMMAND(IDM_MODEL12,OnModel12)
	ON_WM_ERASEBKGND()
	ON_WM_ACTIVATE()
	ON_COMMAND(IDM_MODEL15, OnModel15)
	ON_COMMAND(IDM_MODEL33, OnModel33)
	ON_COMMAND(IDM_MODEL40, OnModel40)
	ON_COMMAND(IDM_MODEL41, OnModel41)
	ON_COMMAND(IDM_MODEL42, OnModel42)
	ON_COMMAND(IDM_MODEL2, OnModel2)
	ON_COMMAND(IDM_MODEL3, OnModel3)
	ON_COMMAND(IDM_MODEL6, OnModel6)
	//}}AFX_MSG_MAP
	//Standardprintingcommands
	ON_COMMAND(ID_FILE_PRINT,CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT,CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW,CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//CHPUFountainViewconstruction/destruction

CHPUFountainView::CHPUFountainView()
{
	//TODO:addconstructioncodehere

}

CHPUFountainView::~CHPUFountainView()
{
}

BOOL CHPUFountainView::PreCreateWindow(CREATESTRUCT&cs)
{
	//TODO:ModifytheWindowclassorstylesherebymodifying
	//theCREATESTRUCTcs
	cs.style|=WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
//CHPUFountainViewdrawing

void CHPUFountainView::OnDraw(CDC*pDC)
{
	CHPUFountainDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	//TODO:adddrawcodefornativedatahere
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	RenderScene();
}

/////////////////////////////////////////////////////////////////////////////
//CHPUFountainViewprinting

BOOL CHPUFountainView::OnPreparePrinting(CPrintInfo*pInfo)
{
	//defaultpreparation
	return DoPreparePrinting(pInfo);
}

void CHPUFountainView::OnBeginPrinting(CDC* /*pDC*/,CPrintInfo* /*pInfo*/)
{
	//TODO:addextrainitializationbeforeprinting
}

void CHPUFountainView::OnEndPrinting(CDC* /*pDC*/,CPrintInfo* /*pInfo*/)
{
	//TODO:addcleanupafterprinting
}

/////////////////////////////////////////////////////////////////////////////
//CHPUFountainViewdiagnostics

#ifdef _DEBUG
void CHPUFountainView::AssertValid()const
{
	CView::AssertValid();
}

void CHPUFountainView::Dump(CDumpContext&dc)const
{
	CView::Dump(dc);
}

CHPUFountainDoc*CHPUFountainView::GetDocument()//non-debugversionisinline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHPUFountainDoc)));
	return (CHPUFountainDoc*)m_pDocument;
}
#endif//_DEBUG

/////////////////////////////////////////////////////////////////////////////
//CHPUFountainViewmessagehandlers

int CHPUFountainView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{	
	if(CView::OnCreate(lpCreateStruct)==-1)
		return-1;
	
	//TODO:Addyourspecializedcreationcodehere
	m_pDC=new CClientDC(this);
	SetTimer(1,10,NULL);
	InitializeOpenGL(m_pDC);
	Init();
	return 0;
}
//��ʼ��OpenGL����
BOOL CHPUFountainView::InitializeOpenGL(CDC*pDC)
{	
	m_pDC=pDC;
	SetupPixelFormat();
	m_hRC=::wglCreateContext(m_pDC->GetSafeHdc());
	::wglMakeCurrent(m_pDC->GetSafeHdc(),m_hRC);
	HuiFu();
	return TRUE;
}
//�������ظ�ʽ
BOOL CHPUFountainView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd={
		sizeof(PIXELFORMATDESCRIPTOR),//pfd�ṹ�Ĵ�С
			1,//�汾��
			PFD_DRAW_TO_WINDOW|//֧���ڴ����л�ͼ
			PFD_SUPPORT_OPENGL|//֧��OpenGL
			PFD_DOUBLEBUFFER,//˫����ģʽ
			PFD_TYPE_RGBA,//RGBA��ɫģʽ
			24,//24λ��ɫ���
			0,0,0,0,0,0,//������ɫλ
			0,//û�з�͸���Ȼ���
			0,//������λλ
			0,//���ۼӻ���
			0,0,0,0,//�����ۼ�λ
			32,//32λ��Ȼ���
			0,//��ģ�建��
			0,//�޸�������
			PFD_MAIN_PLANE,//����
			0,//����
			0,0,0//���Բ�,�ɼ��Ժ������ģ
	};	
	int pixelformat;
	pixelformat=::ChoosePixelFormat(m_pDC->GetSafeHdc(),&pfd);//ѡ�����ظ�ʽ
	::SetPixelFormat(m_pDC->GetSafeHdc(),pixelformat,&pfd);	//�������ظ�ʽ
	//if(pfd.dwFlags&PFD_NEED_PALETTE)
	//SetLogicalPalette();	//�����߼���ɫ��
	return TRUE;
}

void CHPUFountainView::OnSize(UINT nType,int cx,int cy)
{
	CView::OnSize(nType,cx,cy);
	
	//TODO:Addyourmessagehandlercodehere
	glViewport(0,0,cx,cy);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5,0.5,-0.5,0.5,1,1500);
	glMatrixMode(GL_MODELVIEW);
}

void CHPUFountainView::OnDestroy()
{
	CView::OnDestroy();
	
	//TODO:Addyourmessagehandlercodehere
	::wglMakeCurrent(0,0);
	::wglDeleteContext(m_hRC);
	//if(m_hPalette)
	//	DeleteObject(m_hPalette);
	if(m_pDC)
		delete m_pDC;
	KillTimer(1);
}

void CHPUFountainView::CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType)
{
	//TODO:Addyourspecializedcodehereand/orcallthebaseclass
	
	CView::CalcWindowRect(lpClientRect,nAdjustType);
}

void CHPUFountainView::OnCancelMode()
{
	CView::OnCancelMode();
	
	//TODO:Addyourmessagehandlercodehere
	
}
//����Ļ������ַ���
void CHPUFountainView::DrawString()
{
/*	frame_count++;	//����֡Ƶ��
	if(frame_count%40==0)
	{
		frame_count=0;

		starttime=clock();
		passtime=starttime-endtime;
		endtime=starttime;
		cur_time=(float)passtime/(float)CLOCKS_PER_SEC;//time.h�º궨��ĳ���,��ֵΪ1000
			sprintf(tem,"FPS:%f",40/cur_time);
	}
	//������ʾ���ַ���
	glColor3f(1.0,0.5,0.5);
	glDisable(GL_TEXTURE_2D);
	glLoadIdentity();
	glTranslatef(-4.9,4.5,-10);
	glScalef(0.003,0.003,0.004);
	draw_string(GLUT_STROKE_ROMAN,tem);
	glEnable(GL_TEXTURE_2D);
*/}
void CHPUFountainView::draw_string(void *font,const char *string)
{
	while(*string)
		glutStrokeCharacter(font,*string++);
}
//����װ�뺯��
void CHPUFountainView::LoadTexture(char *fn,int t_num)
{
	int texwid,texht;
	int texcomps;
	
	teximage=m_Tex->read_texture(fn,&texwid,&texht,&texcomps);
	if(!teximage)
	{
		MessageBox("Sorry, can't read texture file...","ERROR",MB_OK);
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D,texture[t_num]);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE,texwid,texht,0,GL_RGBA,GL_UNSIGNED_BYTE,teximage);
	
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	
	if((t_num==0) || (t_num==2))glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	if(t_num==1)
	{
		//���ڵ�������,�ظ��������
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	}
	free(teximage);
}
//����
void CHPUFountainView::Light()
{
	//����һ
	GLfloat mat_ambient[]={0.5f,0.8f,0.2f,1.0f};	//������
	GLfloat mat_diffuse[]={0.8f,0.0f,0.3f,1.0f};	//�������
	GLfloat mat_shininess[]={40.0f};	//�����

	GLfloat light_diffuse[]={0.8f,1.0f,0.0f,1.0f};
	GLfloat light_position[]={0.0f,0.0f,0.0f,1.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	//���ն�
	GLfloat mat1_ambient[]={0.2f,0.2f,0.2f,1.0f};	//������
	GLfloat mat1_diffuse[]={0.6f,0.5f,0.8f,1.0f};	//�������
	GLfloat mat1_shininess[]={40.0f};	//�����

	GLfloat light1_diffuse[]={0.3f,1.0f,0.5f,1.0f};
	GLfloat light1_position[]={50.0f,50.0f,50.0f,1.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat1_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat1_diffuse);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat1_shininess);
	
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
	glLightfv(GL_LIGHT1,GL_POSITION,light1_position);

	//���տ����
	if(m_nlighting==1)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glDepthFunc(GL_LESS);
}

void CHPUFountainView::Init()
{
	frame_count=0;
	a=0;
	count=0;
	for(i=0;i<600;i++)
		fn[i]=NULL;
	cuxi[0]=1;
	cuxi[1]=1;
	cuxi[2]=1;
	upv.x=0;//�����������
	upv.y=2;
	upv.z=-2;
	cam.x=0;//�������λ��
	cam.y=600;
	cam.z=600;
	
	for(i=0;i<40;i++)
	{
		table[i].x=20.0*cosf(i*PI*360/40/180);
		table[i].y=0;
		table[i].z=20.0*sinf(i*PI*360/40/180);
		
		table1[i].x=50.0*cosf(i*PI*360/40/180);
		table1[i].y=43;
		table1[i].z=50.0*sinf(i*PI*360/40/180);
		
		table2[i].x=10.0*cosf(i*PI*360/40/180);
		table2[i].y=43;
		table2[i].z=10.0*sinf(i*PI*360/40/180);
		
		table3[i].x=30.0*cosf(i*PI*360/40/180);
		table3[i].y=73;
		table3[i].z=30.0*sinf(i*PI*360/40/180);
		
		table4[i].x=5.0*cosf(i*PI*360/40/180);
		table4[i].y=73;
		table4[i].z=5.0*sinf(i*PI*360/40/180);
	}
	table[40]=table[0];
	table1[40]=table1[0];
	table2[40]=table2[0];
	table3[40]=table3[0];
	table4[40]=table4[0];
	
	glGenTextures(3,texture);
	glClearColor(0,0,0,0);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//glEnable(GL_ALPHA_TEST);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);//����ɫ�ʻ��
	glEnable(GL_TEXTURE_2D);
	LoadTexture("res/particle1.rgb",0);
	LoadTexture("res/ground1.rgb",1);
	LoadTexture("res/ground2.rgb",2);

	ground.LoadFromFile("res/ground.bmp");
	rock.LoadFromFile("res/rock.bmp");
	water.LoadFromFile("res/water.bmp");
	teapot.LoadFromFile("res/teapot.bmp");
}

void CHPUFountainView::OnTimer(UINT nIDEvent)
{
	//TODO:Addyourmessagehandlercodehereand/orcalldefault
	CHPUFountainDoc *pDoc=(CHPUFountainDoc*)CView::GetDocument();
	UpdateData();
	num=pDoc->m_shuliang;
	weiyi[0]=pDoc->m_weizhi;
	for(i=0;i<3;i++)
		cuxi[i]=pDoc->m_cuxi;
	m_nlighting=pDoc->m_light;
	m_yanse=pDoc->m_color;
	m_xuanzhuan=pDoc->m_xuanzhuan;
	m_xingzhuang=pDoc->m_xingzhuang;
	
	m_sliderR=pDoc->m_sliderR;
	m_sliderG=pDoc->m_sliderG;
	m_sliderB=pDoc->m_sliderB;

	gaodu=2.8/pDoc->m_gaodu;
	jiaodu=pDoc->m_jiaodu;

	InvalidateRect(NULL,FALSE);	
	CView::OnTimer(nIDEvent);
}

void CHPUFountainView::HuiFu()
{
	CHPUFountainDoc *pDoc=(CHPUFountainDoc*)CView::GetDocument();
	UpdateData();
	pDoc->m_shuliang=8;			//��ʼ������
	pDoc->m_light=0;
	pDoc->m_weizhi=0;
	pDoc->m_cuxi=1;
	pDoc->m_color=0;
	pDoc->m_xuanzhuan=0;
	pDoc->m_xingzhuang=0;
	pDoc->m_sliderR=50;
	pDoc->m_sliderG=100;
	pDoc->m_sliderB=0;
	pDoc->m_gaodu=3;
	pDoc->m_jiaodu=1;
}

BOOL CHPUFountainView::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	//upx��upy��upz����ָ�������������ķ���(ע�⣬����һ������������һ������)
	gluLookAt(cam.x,cam.y,cam.z,0,0,0,upv.x,upv.y,upv.z);
	if(m_xuanzhuan==0)a=0;
	else if(m_xuanzhuan==1)a+=0.6;//��ת����
	//���Ƶ���
	//glBindTexture(GL_TEXTURE_2D,texture[1]);
	if(count!=5)
	{
		glPushMatrix();		
		ground.SetActive();
		glRotatef(a,0,-1,0);//��ת��Ȫ		
		glColor3f(0,0,1);
	
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-210,0,-210);
		glTexCoord2f(2,0);glVertex3f(-210,0,210);
		glTexCoord2f(2,2);glVertex3f(210,0,210);
		glTexCoord2f(0,2);glVertex3f(210,0,-210);	
		glEnd();
		
		glPopMatrix();
	}

	DrawFountain();//������Ȫ
	
	if(count==5)
	{
		glPushMatrix();
		DrawTable();//��Բ̨
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D,texture[2]);	
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-210,0,-210);
		glTexCoord2f(1,0);glVertex3f(-210,0,210);
		glTexCoord2f(1,1);glVertex3f(210,0,210);
		glTexCoord2f(0,1);glVertex3f(210,0,-210);
		glEnd();
//		glRotatef(a,1,-1,0);
		glPopMatrix();
		
	}
	
	Light();//����
	DrawEdge();//ˮ����������
	DrawWater();//ˮ�صײ�ʯ��

	if(count==4)
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		DrawTeapot();//�����
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
	}
	
	DrawString();//����֡Ƶ��	

	::SwapBuffers(m_pDC->GetSafeHdc());
	return TRUE;
}

//ˮ�صײ���ʯͷ����
void CHPUFountainView::DrawWater()
{
	float W=200.0;
	water.SetActive();
	glPushMatrix();
	glRotatef(a,0,-1,0);//�ص���ת
	glBegin(GL_QUADS);

	glTexCoord2f(0,0);glVertex3f(-W,0,-W);
	glTexCoord2f(1,0);glVertex3f(-W,0,W);
	glTexCoord2f(1,1);glVertex3f(W,0,W);
	glTexCoord2f(0,1);glVertex3f(W,0,-W);

	glEnd();
	glPopMatrix();
}

//���Ʋ������
void CHPUFountainView::DrawTeapot()
{
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_TEXTURE_ENV_COLOR);
	teapot.SetActive();
	glPushMatrix();
	glRotatef(a,0,-1,0);
	glPushMatrix();
	glRotatef(45,0,1,0);
	glPushMatrix();
	glRotatef(30,0,0,-1);
	glTranslatef(-110,0,0);
	glTranslatef(0,70,0);
	glTexCoord2i(0,0);
	glTexCoord2i(1,0);
	glTexCoord2i(1,1);
	glTexCoord2i(0,1);
	auxSolidTeapot(25.0);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
//ˮ�����ܵı�Ե����
void CHPUFountainView::DrawEdge()
{
	float edgeheight=20+POOL_HEIGHT;
	float edgewidth=10;
	float TexBorderDistance=edgewidth/(MAXX+2*edgewidth);

	rock.SetActive();

//	glColor3f(0.5,0.3,1.0);
	glColor3f(0,0.4,0.8);
	glPushMatrix();
	glRotatef(a,0,-1,0);//ˮ����ת
	glTranslatef(-200,0,-200);
	glBegin(GL_QUADS);
	//����
	glNormal3f(0.0f,1.0f,0.0f);//���߷���

	glTexCoord2f(TexBorderDistance,TexBorderDistance);glVertex3f(0.0,edgeheight,0.0);
	glTexCoord2f(1.0-TexBorderDistance,TexBorderDistance);glVertex3f(MAXX,edgeheight,0.0);
	glTexCoord2f(1.0-TexBorderDistance,0.0);glVertex3f(MAXX,edgeheight,-edgewidth);
	glTexCoord2f(TexBorderDistance,0.0);glVertex3f(0.0,edgeheight,-edgewidth);

	glTexCoord2f(TexBorderDistance,0.0);glVertex3f(0.0,edgeheight,-edgewidth);
	glTexCoord2f(0.0,0.0);glVertex3f(-edgewidth,edgeheight,-edgewidth);
	glTexCoord2f(0.0,1.0-TexBorderDistance);glVertex3f(-edgewidth,edgeheight,MAXZ);
	glTexCoord2f(TexBorderDistance,1.0-TexBorderDistance);glVertex3f(0.0,edgeheight,MAXZ);

	glTexCoord2f(1.0,0.0);glVertex3f(MAXX+edgewidth,edgeheight,-edgewidth);
	glTexCoord2f(1.0-TexBorderDistance,0.0);glVertex3f(MAXX,edgeheight,-edgewidth);
	glTexCoord2f(1.0-TexBorderDistance,1.0-TexBorderDistance);glVertex3f(MAXX,edgeheight,MAXZ);
	glTexCoord2f(1.0,1.0-TexBorderDistance);glVertex3f(MAXX+edgewidth,edgeheight,MAXZ);
	
	glTexCoord2f(1.0,1.0-TexBorderDistance);glVertex3f(MAXX+edgewidth,edgeheight,MAXZ);
	glTexCoord2f(0.0,1.0-TexBorderDistance);glVertex3f(-edgewidth,edgeheight,MAXZ);
	glTexCoord2f(0.0,1.0);glVertex3f(-edgewidth,edgeheight,MAXZ+edgewidth);
	glTexCoord2f(1.0,1.0);glVertex3f(MAXX+edgewidth,edgeheight,MAXZ+edgewidth);

	//����
	glNormal3f(0.0,0.0,-1.0);

	glTexCoord2f(TexBorderDistance,TexBorderDistance);glVertex3f(0.0,edgeheight,MAXZ);
	glTexCoord2f(1.0-TexBorderDistance,TexBorderDistance);glVertex3f(MAXX,edgeheight,MAXZ);
	glTexCoord2f(1.0-TexBorderDistance,0.0);glVertex3f(MAXX,0.0,MAXZ);
	glTexCoord2f(TexBorderDistance,0.0);glVertex3f(0.0,0.0,MAXZ);

	glTexCoord2f(0.0,1.0-TexBorderDistance);glVertex3f(-edgewidth,edgeheight,-edgewidth);
	glTexCoord2f(1.0,1.0-TexBorderDistance);glVertex3f(MAXX+edgewidth,edgeheight,-edgewidth);
	glTexCoord2f(1.0,1.0);glVertex3f(MAXX+edgewidth,0.0,-edgewidth);
	glTexCoord2f(0.0,1.0);glVertex3f(-edgewidth,0.0,-edgewidth);

	//ǰ��
	glNormal3f(0.0,0.0,1.0);

	glTexCoord2f(TexBorderDistance,TexBorderDistance);glVertex3f(0.0,edgeheight,0.0);
	glTexCoord2f(1.0-TexBorderDistance,TexBorderDistance);glVertex3f(MAXX,edgeheight,0.0);
	glTexCoord2f(1.0-TexBorderDistance,0.0);glVertex3f(MAXX,0.0,0.0);
	glTexCoord2f(TexBorderDistance,0.0);glVertex3f(0.0,0.0,0.0);
	
	glTexCoord2f(0.0,1.0-TexBorderDistance);glVertex3f(-edgewidth,edgeheight,MAXZ+edgewidth);
	glTexCoord2f(1.0,1.0-TexBorderDistance);glVertex3f(MAXX+edgewidth,edgeheight,MAXZ+edgewidth);
	glTexCoord2f(1.0,1.0);glVertex3f(MAXX+edgewidth,0.0,MAXZ+edgewidth);
	glTexCoord2f(0.0,1.0);glVertex3f(-edgewidth,0.0,MAXZ+edgewidth);

	//����
	glNormal3f(-1.0,0.0,0.0);

	glTexCoord2f(1.0,1.0-TexBorderDistance);glVertex3f(MAXX,edgeheight,0.0);
	glTexCoord2f(1.0,TexBorderDistance);glVertex3f(MAXX,edgeheight,MAXZ);
	glTexCoord2f(1.0-TexBorderDistance,TexBorderDistance);glVertex3f(MAXX,0.0,MAXZ);
	glTexCoord2f(1.0-TexBorderDistance,1.0-TexBorderDistance);glVertex3f(MAXX,0.0,0.0);

	glTexCoord2f(0.0,0.0);glVertex3f(-edgewidth,edgeheight,-edgewidth);
	glTexCoord2f(1.0,0.0);glVertex3f(-edgewidth,edgeheight,MAXZ+edgewidth);
	glTexCoord2f(1.0,TexBorderDistance);glVertex3f(-edgewidth,0.0,MAXZ+edgewidth);
	glTexCoord2f(0.0,TexBorderDistance);glVertex3f(-edgewidth,0.0,-edgewidth);

	glNormal3f(1.0,0.0,0.0);

	glTexCoord2f(1.0-TexBorderDistance,0.0);glVertex3f(0.0,edgeheight,MAXZ);
	glTexCoord2f(TexBorderDistance,0.0);glVertex3f(0.0,edgeheight,0.0);
	glTexCoord2f(TexBorderDistance,TexBorderDistance);glVertex3f(0.0,0.0,0.0);
	glTexCoord2f(1.0-TexBorderDistance,TexBorderDistance);glVertex3f(0.0,0.0,MAXZ);

	glTexCoord2f(1.0,1.0);glVertex3f(MAXX+edgewidth,edgeheight,MAXZ+edgewidth);
	glTexCoord2f(1.0,0.0);glVertex3f(MAXX+edgewidth,edgeheight,-edgewidth);
	glTexCoord2f(1.0-TexBorderDistance,0.0);glVertex3f(MAXX+edgewidth,0.0,-edgewidth);
	glTexCoord2f(1.0-TexBorderDistance,1.0);glVertex3f(MAXX+edgewidth,0.0,MAXZ+edgewidth);

	glEnd();
	glPopMatrix();
}
//ģ����Ļ�Բ̨
void CHPUFountainView::DrawTable()
{
	float f=0.025;
	glPushMatrix();
	glRotatef(a,0,-1,0);	 //��ת,��y��
	glColor3f(1.0,0.5,1.0);
	water.SetActive();
	glBegin(GL_QUADS);
	glNormal3f(1,1,0);
	for(i=0;i<41-1;i++)
	{
		//�ײ�Բ������һ������������Ƭ���
		glVertex3f(table[i].x,table[i].y,table[i].z);
		glVertex3f(table[i+1].x,table[i+1].y,table[i+1].z);
		glVertex3f(table[i+1].x,table[i+1].y+43,table[i+1].z);
		glVertex3f(table[i].x,table[i].y+43,table[i].z);
		//�²�̨��
		glVertex3f(table[i].x,table[i].y+43,table[i].z);
		glVertex3f(table[i+1].x,table[i+1].y+43,table[i+1].z);
		glVertex3f(table1[i+1].x,table1[i+1].y,table1[i+1].z);
		glVertex3f(table1[i].x,table1[i].y,table1[i].z);
		//glColor3f(0.0,1.0,1.0);
		//�в�Բ��
		glVertex3f(table2[i].x,table2[i].y,table2[i].z);
		glVertex3f(table2[i+1].x,table2[i+1].y,table2[i+1].z);
		glVertex3f(table2[i+1].x,table2[i+1].y+30,table2[i+1].z);
		glVertex3f(table2[i].x,table2[i].y+30,table2[i].z);
		//�ϲ�̨��
		glVertex3f(table2[i].x,table2[i].y+30,table2[i].z);
		glVertex3f(table2[i+1].x,table2[i+1].y+30,table2[i+1].z);
		glVertex3f(table3[i+1].x,table3[i+1].y,table3[i+1].z);
		glVertex3f(table3[i].x,table3[i].y,table3[i].z);
		//�ϲ�Բ��
		glVertex3f(table4[i].x,table4[i].y,table4[i].z);
		glVertex3f(table4[i+1].x,table4[i+1].y,table4[i+1].z);
		glVertex3f(table4[i+1].x,table4[i+1].y+20,table4[i+1].z);
		glVertex3f(table4[i].x,table4[i].y+20,table4[i].z);
	}
	glEnd();
	glPopMatrix();
}


void CHPUFountainView::DrawFountain()
{
	struct particle *tempp;
	struct point vectd,vectl;
	float alpha,ttx,ttz;

	glBindTexture(GL_TEXTURE_2D,texture[0]);
	
	if(count==0)//�ָ�
	{
		AddParticles();
		MoveParticles();
	}
	else if(count==1)//��ת��
	{
		AddParticles1();
		MoveParticles1();	
	}
	else if(count==2)//�ʹ�
	{
		AddParticles1();
		MoveParticles();	
	}
	else if(count==3)
	{
		num=245;
		AddParticles1();
		MoveParticles1();
	}
	else if(count==4)//����ٲ�
	{
		num=1;
		AddParticles1();
		MoveParticles1();
	}
	else if(count==5)//Բ̨
	{
		AddParticles1();
		MoveParticles1();
	}
	else if(count==6)//����2
	{
		num=327;
		AddParticles1();
		MoveParticles1();
	}
	else if(count==9)//HPU����
	{
		num=108;
		AddParticles1();
		MoveParticles1();
	}
	else if(count==10)//��Ҷ��
	{
		AddParticles1();
		MoveParticles1();
	}
	else if(count==12)//ǣţ��
	{
		AddParticles1();
		MoveParticles1();
	}
	else if(count==33)//������
	{
		AddParticles1();
		MoveParticles1();
	}
	else if(count==40)//��ת�任
	{
		AddParticles1();
		MoveParticles1();
	}
	else if(count==41)//ƽ�Ʊ任
	{
		AddParticles1();
		MoveParticles1();
	}
	else if(count==42)//�ԳƱ任
	{
		AddParticles1();
		MoveParticles1();
	}
	else if(count==15)//����Ƕ�
	{
		num=160;
		AddParticles1();
		MoveParticles1();
	}
	DeleteParticles();


	glPushMatrix();
	for(i=0;i<num;i++)
	{
		glBegin(GL_QUADS);
		tempp=fn[i];
		while(tempp)
		{
			if(count==0)
				alpha=(i*360/num+a)*PI/180;
			else if(count==1)//��ת
			{
				alpha=(i*360/num+a)*PI/180;
			}
			else if(count==2)//�ʹ�
			{
				alpha=(i*360/num+a)*PI/180;
				
			}
			else if(count==3)//����
			{
				if(i<30)
					alpha=(i*360/30+a)*PI/180;
				else if(i<50)
					alpha=((i-30)*360/20+a)*PI/180;
				else if(i<170)
					alpha=((i-50)*360/1+a)*PI/180;
				else if(i>=170 && i<242)
					alpha=((i-50)*360/1+a)*PI/180;
			}
			else if(count==4)//���
				alpha=a*PI/180;
			else if(count==5)
			{
				if(i<10)
					alpha=(i*360/10+a)*PI/180;
				else if(i>=10 && i<30)
					alpha=(i*360/20+a)*PI/180;
				else if(i>=30)
					alpha=(i*360/(num-30)+a)*PI/180;
			}
			else if(count==6)
			{
				if(i<104)
					alpha=(i*360/1+a)*PI/180;
				//else if(i>=104 && i<168)
				//	alpha=(i*360/1+a)*PI/180;
				else if(i>=168 && i<232)
					alpha=(i*360/1+a)*PI/180;
				else if(i>=232 && i<290)
					alpha=(i*360/58+a)*PI/180;
				else if(i>=290 && i<310)
					alpha=(i*360/20+a)*PI/180;
				else if(i>=310 && i<330)
					alpha=(i*360/20+a)*PI/180;
				else
					alpha=(i*360/(num-330))*PI/180;
			}
			
			else if(count==8)//����
			{
				if(i<32)
					alpha=(i*360+a)*PI/180;
				else
					alpha=(i*360/(num-32)+a)*PI/180;
			}
			else if(count==9)//HPU
				alpha=(i*360/1+a)*PI/180;
			else if(count==10)//��Ҷ��
			{
				if(i<72)
					alpha=(i*360/1+a)*PI/180;
				else if(i>=72 && i<90)
					alpha=(i*360/18+a)*PI/180;
				else
					alpha=(i*360/(num-90)+a)*PI/180;
			}
			else if(count==12)//ǣţ��
			{
				if(i<72)
					alpha=(i*360/1+a)*PI/180;
				else if(i>=72 && i<126)
					alpha=(i*360/54+a)*PI/180;
				else if(i>=126 && i<162)
					alpha=(i*360/36+a)*PI/180;
				else
					alpha=(i*360/(num-162))*PI/180;
			}
			else if(count>=13 && count<=16)//�����
			{
				if(i<80)
					alpha=(i*360/1+a)*PI/180;
				else
					alpha=(i*360/(num-80))*PI/180;
			}
			else if(count==17)
			{
				if(i<120)
					alpha=(i*360/1+a)*PI/180;
				else
					alpha=(i*360/(num-120)+a)*PI/180;
			}
			else if(count==31)//��������
			{
				if(i<20)
					alpha=(i*360/1+a)*PI/180;
				else
					alpha=(i*360/(num-20))*PI/180;
			}
			else if(count==32)//��������
			{
				if(i<10)
					alpha=(i*360/1+a)*PI/180;
				else
					alpha=(i*360/(num-10))*PI/180;
			}
			else if(count==33)//������
			{
				if(i<40)
					alpha=(i*360/40+a)*PI/180;
				else if(i>=40 && i<70)
					alpha=(i*360/30+a)*PI/180;
				else if(i>=70 && i<90)
					alpha=(i*360/20+a)*PI/180;
				else if(i>=90 && i<100)
					alpha=(i*360/10+a)*PI/180;
				else
					alpha=(i*360/(num-100))*PI/180;
			}
			else if(count==40)//��ת�任
			{
				if(i<104)
					alpha=(i*360/1+a)*PI/180;
				else
					alpha=(i*360/(num-104))*PI/180;
			}
			else if(count==41)//ƽ�Ʊ任
			{
				if(i<117)
					alpha=(i*360/1+a)*PI/180;
				else
					alpha=(i*360/(num-117))*PI/180;
			}
			else if(count==42)//�ԳƱ任
			{
				if(i<52)
					alpha=(i*360/1+a)*PI/180;
				else
					alpha=(i*360/(num-52))*PI/180;
			}
			ttx=tempp->x*cos(alpha)-tempp->z*sin(alpha);
			ttz=tempp->x*sin(alpha)+tempp->z*cos(alpha);
			//���㷽��ʸ��
			/*
			����һ����۲췽��ֱ�ķ���ʸ�������÷���ʸ������һ������
			�۲췽��ľ��Σ��Ա�֤���ܱ�����������������
			*/
			//vectd.x=ttx-cam.x;
			vectd.x=tempp->x-cam.x;
			vectd.y=tempp->y-cam.y;
			//vectd.z=ttz-cam.z;
			vectd.z=tempp->z-cam.z;

			vect_mult(&vectd,&upv,&vectl);
			normalize(&vectl);
			vectl.x*=cuxi[0];//Ϊ�������ͼ��׼������ͼ���ھ����еģ�����+-vectl.x��Ϊ�˵õ����ε�x������
			vectl.y*=cuxi[1];
			vectl.z*=cuxi[2];

			//������ɫ�ı仯ֵ
			tempp->r=(float)(rand()%256)/255;
			tempp->g=(float)(rand()%256)/255;
			tempp->b=(float)(rand()%256)/255;
			if(m_yanse==0)//��ɫ
				glColor4f(0.8,0.8,0.8,tempp->a);
			else if(m_yanse==1)//��ɫ
				glColor4f(tempp->r,tempp->g,tempp->b,tempp->a);
			else if(m_yanse==2)//�Զ�����ɫ
				glColor4f(float(m_sliderR/100),float(m_sliderG/100),float(m_sliderB/100),tempp->a);
			else if(m_yanse==3)//��ɫ����
			{
				float color=0.0f;
				if(count==9)
				{
					if(i<36)
						glColor4f(1,0,0,tempp->a);
					else if(i>=36 && i<71)
						glColor4f(0,1,0,tempp->a);
					else if(i>=71 && i<108)
						glColor4f(0,0,1,tempp->a);
					else
						glColor4f(0,1,1,tempp->a);
				}
				else if(count==12)
				{
					int j=floor(i/9);
					{
						if(j==0 || j==4)
							glColor4f(1,0,0,tempp->a);
						else if(j==1 || j==5)
							glColor4f(0,1,0,tempp->a);
						else if(j==2 || j==6)
							glColor4f(0,1,1,tempp->a);
						else if(j==3 || j==7)
							glColor4f(1,1,0,tempp->a);
						else if(j>=8 && j<14)
							glColor4f(1,0,1,tempp->a);
						else if(j>=14)
							glColor4f(1,1,1,tempp->a);
					}
				}
				else if(count==15)
				{
					if(i<80)
					{
						int j;
						j=i%8;
						color=1-0.143*j;
						glColor4f(0.2,1-color,color,tempp->a);
					}
					else
						glColor4f(1,0.5,0,tempp->a);
				}
				else
				{
					int k=i/6;
					if(k==0)
						glColor4f(1,0,0,tempp->a);
					else if(k==1)
						glColor4f(1,1,0,tempp->a);
					else if(k==2)
						glColor4f(0,1,0,tempp->a);
					else if(k==3)
						glColor4f(0,1,1,tempp->a);
					else if(k==4)
						glColor4f(0,0,1,tempp->a);
					else if(k==5)
						glColor4f(1,0,1,tempp->a);
					else
						glColor4f(1,1,1,tempp->a);
				}
			}

			//���ƶ���κ���������ӳ��
			glTexCoord2f(0,0);glVertex3f((ttx-vectl.x),(tempp->y-upv.y),(ttz-vectl.z));
			glTexCoord2f(1,0);glVertex3f((ttx+vectl.x),(tempp->y-upv.y),(ttz+vectl.z));
			glTexCoord2f(1,1);glVertex3f((ttx+vectl.x),(tempp->y+upv.y),(ttz+vectl.z));
			glTexCoord2f(0,1);glVertex3f((ttx-vectl.x),(tempp->y+upv.y),(ttz-vectl.z));
		
			tempp=tempp->next;//������һ�������б�
		}
		glEnd();
	}
	glPopMatrix();
}
//ԭʼģ��������Ӻ���
void CHPUFountainView::AddParticles()
{
	struct particle *tempp;
	for(i=0;i<num;i++)
		for(j=0;j<4;j++)
		{
			tempp=(struct particle*)malloc(sizeof(struct particle));
			if(fn[i])
				fn[i]->prev=tempp;
			tempp->next=fn[i];
			fn[i]=tempp;
			tempp->t=-9.9;

			tempp->v=(float)(rand()%200000)/100000+1;//�����ٶ�
			tempp->d=(float)(rand()%400)/100-2;//���ӷ���rand()%400����һ��[0,400)�ڵ���ֵ[-2,2)
			//��ʼλ�õ�����
			tempp->x=weiyi[0];
			tempp->y=0;//weiyi[1];
			tempp->z=0;//weiyi[2];
			//��֧��Ȫ��ҡ�ڽǶ� cos((tempp->d*PI)/180)
			tempp->xd=(cos((tempp->d*PI)/180)*tempp->v/4)/jiaodu;
			tempp->zd=(sin((tempp->d*PI)/180)*tempp->v)/jiaodu;

			tempp->type=0;//���ӵ�״̬Ϊ�˶�
			tempp->a=1;//���ӵ���
		}
}
//ԭʼģ�������˶�����
void CHPUFountainView::MoveParticles()
{
	struct particle *tempp;
	for(i=0;i<num;i++)
	{
		tempp=fn[i];
		while(tempp)
		{
			if(tempp->type==0)//������Ӵ����˶�״̬
			{
				tempp->x+=tempp->xd;
				tempp->z+=tempp->zd;
				// tempp->z=20*tempp->t-5.8*tempp->t*tempp->t/2;
				tempp->y=(-(9.8*(tempp->t*tempp->t/4))/2+122.5)/gaodu;
				// tempp->y=50*tempp->t-9.8*tempp->t*tempp->t/2;
				tempp->t+=0.1;
				if(tempp->y<0)//�������λ�ڵ�������ı����ӵ�״̬
					tempp->type=1;
			}
			else
			{
				tempp->y=(-(9.8*(tempp->t*tempp->t/4))/2+122.5)/gaodu;
				//tempp->y=50*tempp->t-9.8*tempp->t*tempp->t/2;
				tempp->a-=0.1;//���ӵ���
			}
			tempp=tempp->next;//��һ������
		}
	}
}
//ɾ������
void CHPUFountainView::DeleteParticles()
{
	struct particle *tempp,*temp1;
	for(i=0;i<num;i++)
	{
		tempp=fn[i];
		while(tempp)
		{
			if(tempp->type==1 && tempp->a<=0)//��������
			{
				//ɾ������
				temp1=tempp->prev;
				tempp->prev->next=tempp->next;
				if(tempp->next)
					tempp->next->prev=temp1;
				free(tempp);
				tempp=temp1;
			}
			tempp=tempp->next;
		}
	}
}
/*
���������Ĳ�ˣ��ٽ����������ʽ�ó��Ĺ�ʽ����ֱ��ʹ��
����a������b=
����|ijk|
����|a1b1c1|
����|a2b2c2|
��������һ����������ʽ
������ֵΪ(b1c2-b2c1,c1a2-a1c2,a1b2-a2b1)����ǵó��ķ�����������
������i��j��k�ֱ�Ϊ�ռ����໥��ֱ������������ĵ�λ��������
*/
void CHPUFountainView::vect_mult(point* A,point* B,point* C)
{
	//ʸ����ˣ���ˣ�
	C->x=A->y*B->z-A->z*B->y;
	C->y=A->z*B->x-A->x*B->z;
	C->z=A->x*B->y-A->y*B->x;
}
//ʸ����λ��
void CHPUFountainView::normalize(point* V)
{
	float d;
	//ʸ������
	d=sqrt(V->x*V->x+V->y*V->y+V->z*V->z);
	//��λ��
	V->x/=d;
	V->y/=d;
	V->z/=d;
}
//������Ӻ���
void CHPUFountainView::AddParticles1()
{
	int number;
	struct particle *tempp;
	if(count==3)
		number=2;
	else if(count==2)
		number=2;
	else
		number=1;
	for(i=0;i<num;i++)
		for(j=0;j<number;j++)
		{
			tempp=(struct particle*)malloc(sizeof(struct particle));
			if(fn[i])
				fn[i]->prev=tempp;
			tempp->next=fn[i];
			fn[i]=tempp;

			tempp->t=0;
			tempp->v=(float)(rand()%200000)/100000+1;//�����ٶ�(��xzƽ����)
			tempp->d=(float)(rand()%400)/100;//���ӷ���rand()%400��ȡ400���ڵ������,[0,399]����d������[-2,2)��
			tempp->y=0;
			tempp->z=0;
			tempp->xd=(cos((tempp->d*PI)/180)*tempp->v/4)/jiaodu;
			tempp->zd=(sin((tempp->d*PI)/180)*tempp->v/4)/jiaodu;

			if(count==1)//ģ��һ
			{	
				tempp->x=weiyi[0]+40; //������40
			}
			else if(count==2)
			{
				tempp->t = -9.9;
				
				if((j>=0) && (j<2))
				{
					tempp->v=(float)(rand()%200000)/100000+1+4;//�����ٶ�
					tempp->d=(float)(rand()%500)/100;//���ӷ���
					tempp->x=50;
					tempp->z=50;
					tempp->xd=(cos((tempp->d*3.14159)/180)*tempp->v/8)/(jiaodu+4);
					tempp->zd=(sin((tempp->d*3.14159)/180)*tempp->v-1)/(jiaodu+4);
				}
				/*	����
				if((j>=2) && (j<4))
				{
					tempp->v=(float)(rand()%200000)/100000+1+jiaodu;//�����ٶ�
					tempp->d=(float)(rand()%400)/100.0-2;//���ӷ���
					tempp->x=weiyi[0];
					tempp->y=0;
					tempp->z=0;
					tempp->xd=(cos((tempp->d*3.14159)/180)*tempp->v/8)/jiaodu;
					tempp->zd=sin((tempp->d*3.14159)/180)*tempp->v;
				}
				if((j>=4) && (j<6))
				{
					tempp->v=(float)(rand()%200000)/100000+1+4;//�����ٶ�
					tempp->d=(float)(rand()%500)/100;//���ӷ���
					tempp->x=70;
					tempp->y=17;
					tempp->z=70;
					tempp->xd=(cos((tempp->d*3.14159)/180)*tempp->v/8)/(jiaodu+4);
					tempp->zd=(sin((tempp->d*3.14159)/180)*tempp->v-1)/(jiaodu+4);
				}
				*/
			}
			else if(count==3)
			{
				if(i<30)
				{
					tempp->x=weiyi[0]+15;
				}
				else if(i<50)
				{
					tempp->x=weiyi[0]+30;
				}
				else if(i<170)
				{
					float a,b,c;
					a=80;//��㻷�����а뾶
					b=a*(cos(30*PI/180)+sin(30*PI/180));
					c=a*(cos(30*PI/180)-sin(30*PI/180));
						
				if(i<60) //���С��Ȫ��������
					{
						tempp->x=weiyi[0]+a;
						tempp->z=weiyi[0]+a;
					}
					else if(i>=60 && i<70)
					{
						tempp->x=weiyi[0]+c;
						tempp->z=weiyi[0]+b;
					}
					else if(i>=70 && i<80)
					{
						tempp->x=weiyi[0]-c;
						tempp->z=weiyi[0]+b;
					}
					else if(i>=80 && i<90)
					{
						tempp->x=weiyi[0]-a;
						tempp->z=weiyi[0]+a;
					}
					else if(i>=90 && i<100)
					{
						tempp->x=weiyi[0]-b;
						tempp->z=weiyi[0]+c;
					}
					else if(i>=100 && i<110)
					{
						tempp->x=weiyi[0]-b;
						tempp->z=weiyi[0]-c;
					}
					else if(i>=110 && i<120)
					{
						tempp->x=weiyi[0]-a;
						tempp->z=weiyi[0]-a;
					}
					else if(i>=120 && i<130)
					{
						tempp->x=weiyi[0]-c;
						tempp->z=weiyi[0]-b;
					}
					else if(i>=130 && i<140)
					{
						tempp->x=weiyi[0]+c;
						tempp->z=weiyi[0]-b;
					}
					else if(i>=140 && i<150)
					{
						tempp->x=weiyi[0]+a;
						tempp->z=weiyi[0]-a;
					}
					else if(i>=150 && i<160)
					{
						tempp->x=weiyi[0]+b;
						tempp->z=weiyi[0]-c;
					}
					else
					{
						tempp->x=weiyi[0]+b;
						tempp->z=weiyi[0]+c;
					}
				}
				else if(i<245)
				{
					float a,b,c;
					a=140;//��㻷�����а뾶
					b=i%6;
					c=i/6;
					tempp->x=weiyi[0]+a*cos((b*4+20+c*30)*PI/180);
					tempp->z=weiyi[0]+a*sin((b*4+20+c*30)*PI/180);
				}
			}
			else if(count==4)//ģ���Ĳ��
			{
				tempp->x=-15;
				tempp->z=15;
				tempp->v+=jiaodu;
				tempp->xd=(cos((tempp->d*PI)/180)*tempp->v/4);
			}
			else if(count==5)//ģ����Բ̨
			{
				if(i<10)
				{
					tempp->x=table4[0].x;
					tempp->y=table4[0].y+20;
				}
				else if(i>=10 && i<30)
				{
					tempp->x=table3[0].x;
					tempp->y=table3[0].y;
				}
				else if(i>=30)
				{
					tempp->x=table1[0].x;
					tempp->y=table1[0].y;
				}
			}
			else if(count==6)
			{
				int c=140;
				if(i<104)
				{
					int a,b;
					a=i/13;
					b=i%13;
					tempp->x = (weiyi[0]+b*3-18)*cos(a*45*PI/180)-(weiyi[0]+c)*sin(a*45*PI/180);
					tempp->z = (weiyi[0]+b*3-18)*sin(a*45*PI/180)+(weiyi[0]+c)*cos(a*45*PI/180);
				}
				/*else if(i>=104 && i<120)
				{
					tempp->x=weiyi[0]+c;
					tempp->z=weiyi[0]+c;
				}
				else if(i>=120 && i<136)
				{
					tempp->x=weiyi[0]-c;
					tempp->z=weiyi[0]-c;
				}
				else if(i>=136 && i<152)
				{
					tempp->x=weiyi[0]+c;
					tempp->z=weiyi[0]-c;
				}
				else if(i>=152 && i<168)
				{
					tempp->x=weiyi[0]-c;
					tempp->z=weiyi[0]+c;
				}*/
				else if(i>=168 && i<232)
				{
					float a,b,c;
					a=100;//��㻷�����а뾶
					b=i%8;
					c=i/8;
					tempp->x=weiyi[0]+a*cos((b*1.5+20+c*45)*PI/180);
					tempp->z=weiyi[0]+a*sin((b*1.5+20+c*45)*PI/180);
				}
				else if(i>=232 && i<290)
				{
					tempp->x=weiyi[0]+90;
				}
				else if(i>=290 && i<310)
				{
					tempp->x=weiyi[0]+40;
				}
				else if(i>=310 && i<330)
				{
					tempp->x=weiyi[0]+15;
				}
				else
				{
					tempp->x=weiyi[0];
				}
			}
			else if(count==9)//��������HPU
			{
				if(i<15)
				{
					tempp->x=weiyi[0]-70;
					tempp->z=70-i*10;
				}
				else if(i>=15 && i<21)
				{
					tempp->z=0;
					tempp->x=weiyi[0]-64+5*(i-15);
				}
				else if(i>=21 && i<36)
				{
					tempp->x=weiyi[0]-35;
					tempp->z=70-(i-21)*10;
				}
				else if(i>=36 && i<51)
				{
					tempp->x=weiyi[0]-17.5;
					tempp->z=70-(i-36)*10;
				}
				else if(i>=51 && i<57)
				{
					tempp->z=0;
					tempp->x=weiyi[0]-11.5+5*(i-51);
				}
				else if(i>=57 && i<65)
				{
					tempp->x=weiyi[0]+17.5;
					tempp->z=-10*(i-57);
				}
				else if(i>=65 && i<71)
				{
					tempp->z=-70;
					tempp->x=weiyi[0]-11.5+5*(i-65);
				}
				else if(i>=71 && i<86)
				{
					tempp->x=weiyi[0]+35;
					tempp->z=70-(i-71)*10;
				}
				else if(i>=86 && i<93)
				{
					tempp->z=70;
					tempp->x=weiyi[0]+41+5*(i-86);
				}
				else if(i>=93 && i<108)
				{
					tempp->x=weiyi[0]+70;
					tempp->z=70-(i-93)*10;
				}
			}
			else if(count==10)//ģ��14
			{
				if(i<18)
				{
					tempp->x=weiyi[0]+35*(cos(10*i*PI/180));
					tempp->z=35*(sin(10*i*PI/180))+35;
				}
				else if(i>=18 && i<36)
				{
					tempp->x=weiyi[0]+35*(cos(10*(i-9)*PI/180))-35;
					tempp->z=35*(sin(10*(i-9)*PI/180));
				}
				else if(i>=36 && i<54)
				{
					tempp->x=weiyi[0]+35*(cos(10*(i-18)*PI/180));
					tempp->z=35*(sin(10*(i-18)*PI/180))-35;
				}
				else if(i>=54 && i<72)
				{
					tempp->x=weiyi[0]+35*(cos(10*(i-27)*PI/180))+35;
					tempp->z=35*(sin(10*(i-27)*PI/180));
				}
				else if(i>=72 && i<90)
					tempp->x=weiyi[0]+10;
				else
					tempp->x=weiyi[0]+90;
			}
			else if(count==12)//ǣţ��
			{	
				if(i<9)
				{
					tempp->x=weiyi[0]+20*(cos((13*(i+2)+6)*PI/180));
					tempp->z=20*(sin((13*(i+2)+6)*PI/180))+30;
				}
				else if(i>=9 && i<18)
				{
					tempp->x=weiyi[0]+20*(cos((13*(i-3)-1)*PI/180))-15*sqrt(2);
					tempp->z=20*(sin((13*(i-3)-1)*PI/180))+15*sqrt(2);
				}
				else if(i>=18 && i<27)
				{
					tempp->x=weiyi[0]+20*(cos((13*(i-9)+5)*PI/180))-30;
					tempp->z=20*(sin((13*(i-9)+5)*PI/180));
				}
				else if(i>=27 && i<36)
				{
					tempp->x=weiyi[0]+20*(cos((13*(i-14)-2)*PI/180))-15*sqrt(2);
					tempp->z=20*(sin((13*(i-14)-2)*PI/180))-15*sqrt(2);
				}
				else if(i>=36 && i<45)
				{
					tempp->x=weiyi[0]+20*(cos((13*(i-20)+4)*PI/180));
					tempp->z=20*(sin((13*(i-20)+4)*PI/180))-30;
				}
				else if(i>=45 && i<54)
				{
					tempp->x=weiyi[0]+20*(cos((13*(i-25)-3)*PI/180))+15*sqrt(2);
					tempp->z=20*(sin((13*(i-25)-3)*PI/180))-15*sqrt(2);
				}
				else if(i>=54 && i<63)
				{
					tempp->x=weiyi[0]+20*(cos((13*(i-31)+3)*PI/180))+30;
					tempp->z=20*(sin((13*(i-31)+3)*PI/180));
				}
				else if(i>=63 && i<72)
				{
					tempp->x=weiyi[0]+20*(cos((13*(i-36)-4)*PI/180))+15*sqrt(2);
					tempp->z=20*(sin((13*(i-36)-4)*PI/180))+15*sqrt(2);
				}
				else if(i>=72 && i<126)
				{
					tempp->x=weiyi[0]+28;
				}
				else if(i>=126 && i<162)
				{
					tempp->x=weiyi[0]+20;
				}
				else
				{
					tempp->x=weiyi[0]+10;
				}
			}
			else if(count==15)//�����
			{	
				if(i<8)
				{//һ��  (С--��)
					tempp->x=weiyi[0]-15.266+2.181*(7-i);
					tempp->z=weiyi[0]-21.012-6.713*(7-i);
				}
				else if(i>=8 && i<16)
				{//һ��  (С--��)
					tempp->x=weiyi[0]+15.266-2.181*(15-i);
					tempp->z=weiyi[0]-21.012-6.713*(15-i);
				}
				else if(i>=16 && i<24)
				{
					tempp->x=(weiyi[0]-15.266+2.181*(23-i)-weiyi[0])*cos((72*PI)/180)-(weiyi[0]-21.012-6.713*(23-i)-weiyi[0])*sin((72*PI)/180)+weiyi[0];
					tempp->z=(weiyi[0]-15.266+2.181*(23-i)-weiyi[0])*sin((72*PI)/180)+(weiyi[0]-21.012-6.713*(23-i)-weiyi[0])*cos((72*PI)/180)+weiyi[0];
				}
				else if(i>=24 && i<32)
				{
					tempp->x=(weiyi[0]+15.266-2.181*(31-i)-weiyi[0])*cos((72*PI)/180)-(weiyi[0]-21.012-6.713*(31-i)-weiyi[0])*sin((72*PI)/180)+weiyi[0];
					tempp->z=(weiyi[0]+15.266-2.181*(31-i)-weiyi[0])*sin((72*PI)/180)+(weiyi[0]-21.012-6.713*(31-i)-weiyi[0])*cos((72*PI)/180)+weiyi[0];
				}
				else if(i>=32 && i<40)
				{
					tempp->x=(weiyi[0]-15.266+2.181*(39-i)-weiyi[0])*cos((144*PI)/180)-(weiyi[0]-21.012-6.713*(39-i)-weiyi[0])*sin((144*PI)/180)+weiyi[0];
					tempp->z=(weiyi[0]-15.266+2.181*(39-i)-weiyi[0])*sin((144*PI)/180)+(weiyi[0]-21.012-6.713*(39-i)-weiyi[0])*cos((144*PI)/180)+weiyi[0];
				}
				else if(i>=40 && i<48)
				{
					tempp->x=(weiyi[0]+15.266-2.181*(47-i)-weiyi[0])*cos((144*PI)/180)-(weiyi[0]-21.012-6.713*(47-i)-weiyi[0])*sin((144*PI)/180)+weiyi[0];
					tempp->z=(weiyi[0]+15.266-2.181*(47-i)-weiyi[0])*sin((144*PI)/180)+(weiyi[0]-21.012-6.713*(47-i)-weiyi[0])*cos((144*PI)/180)+weiyi[0];
				}
				else if(i>=48 && i<56)
				{
					tempp->x=(weiyi[0]-15.266+2.181*(55-i)-weiyi[0])*cos((216*PI)/180)-(weiyi[0]-21.012-6.713*(55-i)-weiyi[0])*sin((216*PI)/180)+weiyi[0];
					tempp->z=(weiyi[0]-15.266+2.181*(55-i)-weiyi[0])*sin((216*PI)/180)+(weiyi[0]-21.012-6.713*(55-i)-weiyi[0])*cos((216*PI)/180)+weiyi[0];
				}
				else if(i>=56 && i<64)
				{
					tempp->x=(weiyi[0]+15.266-2.181*(63-i)-weiyi[0])*cos((216*PI)/180)-(weiyi[0]-21.012-6.713*(63-i)-weiyi[0])*sin((216*PI)/180)+weiyi[0];
					tempp->z=(weiyi[0]+15.266-2.181*(63-i)-weiyi[0])*sin((216*PI)/180)+(weiyi[0]-21.012-6.713*(63-i)-weiyi[0])*cos((216*PI)/180)+weiyi[0];
				}
				else if(i>=64 && i<72)
				{
					tempp->x=(weiyi[0]-15.266+2.181*(71-i)-weiyi[0])*cos((288*PI)/180)-(weiyi[0]-21.012-6.713*(71-i)-weiyi[0])*sin((288*PI)/180)+weiyi[0];
					tempp->z=(weiyi[0]-15.266+2.181*(71-i)-weiyi[0])*sin((288*PI)/180)+(weiyi[0]-21.012-6.713*(71-i)-weiyi[0])*cos((288*PI)/180)+weiyi[0];
				}
				else if(i>=72 && i<80)
				{
					tempp->x=(weiyi[0]+15.266-2.181*(79-i)-weiyi[0])*cos((288*PI)/180)-(weiyi[0]-21.012-6.713*(79-i)-weiyi[0])*sin((288*PI)/180)+weiyi[0];
					tempp->z=(weiyi[0]+15.266-2.181*(79-i)-weiyi[0])*sin((288*PI)/180)+(weiyi[0]-21.012-6.713*(79-i)-weiyi[0])*cos((288*PI)/180)+weiyi[0];
				}
				else
				{
					tempp->x=weiyi[0]+80;
				}
			}
			else if(count==33)//������
			{
				if(i<40)
				{
					tempp->x = weiyi[0]+20;
				}
				else if(i>=40 && i<70)
				{
					tempp->x = weiyi[0]+10;
				}
				else if(i>=70 && i<90)
				{
					tempp->x = weiyi[0]+5;
				}
				else if(i>=90 && i<100)
				{
					tempp->x = weiyi[0];
				}
				else
					tempp->x = weiyi[0]+100;
			}
			else if(count==40)//��ת�任
			{
				int c=140;
				if(i<104)
				{
					int a,b;
					a=i/13;
					b=i%13;
					tempp->x = (weiyi[0]+b*3-18)*cos(a*45*PI/180)-(weiyi[0]+c)*sin(a*45*PI/180);
					tempp->z = (weiyi[0]+b*3-18)*sin(a*45*PI/180)+(weiyi[0]+c)*cos(a*45*PI/180);
				}
				else
					tempp->x=weiyi[0]+60;
			}
			else if(count==41)//ƽ�Ʊ任
			{
				if(i<117)
				{
					if(i<13)
					{
						tempp->x = weiyi[0]+i*2.5+70;
						tempp->z = weiyi[0]+85;
					}
					else if(i>=13 && i<26)
					{
						tempp->x = weiyi[0]+i%13*2.5+70;
						tempp->z = weiyi[0]+0;
					}
					else if(i>=26 && i<39)
					{
						tempp->x = weiyi[0]+i%13*2.5+70;
						tempp->z = weiyi[0]-85;
					}
					else if(i>=39 && i<52)
					{
						tempp->x = weiyi[0]+i%13*2.5-15;
						tempp->z = weiyi[0]-85;
					}
					else if(i>=52 && i<65)
					{
						tempp->x = weiyi[0]+i%13*2.5-100;
						tempp->z = weiyi[0]-85;
					}
					else if(i>=65 && i<78)
					{
						tempp->x = weiyi[0]+i%13*2.5-100;
						tempp->z = weiyi[0]+0;
					}
					else if(i>=78 && i<91)
					{
						tempp->x = weiyi[0]+i%13*2.5-100;
						tempp->z = weiyi[0]+85;
					}
					else if(i>=91 && i<104)
					{
						tempp->x = weiyi[0]+i%13*2.5-15;
						tempp->z = weiyi[0]+85;
					}
					else if(i>=104 && i<117)
					{
						tempp->x = weiyi[0]+i%13*2.5-15;
						tempp->z = weiyi[0]+0;
					}
				}
				else
					tempp->x=weiyi[0]+120;
			}
			else if(count==42)//�ԳƱ任
			{
				if(i<52)
				{
					if(i<13)
					{
						tempp->x = weiyi[0]+i*2.5+70;
						tempp->z = weiyi[0]+85;
					}
					else if(i>=13 && i<26)
					{
						tempp->x = weiyi[0]+i%13*2.5+70;
						tempp->z = weiyi[0]-85;
					}
					else if(i>=26 && i<39)
					{
						tempp->x = weiyi[0]+i%13*2.5-100;
						tempp->z = weiyi[0]-85;
					}
					else if(i>=39 && i<52)
					{
						tempp->x = weiyi[0]+i%13*2.5-100;
						tempp->z = weiyi[0]+85;
					}
				}
				else
					tempp->x=weiyi[0]+40;
			}
			tempp->type=0;//���ӵ�״̬Ϊ�˶�
			tempp->a=1;
		}
}
//�����˶�����
void CHPUFountainView::MoveParticles1()
{
	struct particle *tempp;
	float hudu;//����
	for(i=0;i<num;i++)
	{
		tempp=fn[i];
		while(tempp)
		{
			if(tempp->type==0)
			{
				if(count==1)//ģ��һ��������
				{	
					{
						tempp->x+=tempp->xd;
						tempp->z+=tempp->zd;
						tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
				}
				
				else if(count==2)//ģ�ͻʹ�
				{
					tempp->x+=tempp->xd;
					tempp->z+=tempp->zd;
					tempp->y=(-(9.8*(tempp->t*tempp->t/4))/2+122.5)/gaodu;
					if(tempp->y < 0)
						tempp->type=1;
				}
				else if(count==3)//�����ۺ�
				{
					if(i<30)
					{
						tempp->x+=tempp->xd/6;
						tempp->y=(12*tempp->t-0.24*tempp->t*tempp->t)/gaodu;
					}
					else if(i<50)
					{
						tempp->x+=tempp->xd;
						tempp->z+=tempp->zd;
						tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
					}
					else if(i<170)
					{
						int k=(i-50)%20;
						tempp->x += (tempp->xd/2*cos((36*k+60)*PI/180));
						tempp->z += (tempp->xd/2*sin((36*k+60)*PI/180));
						tempp->y = (3*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
					}
					else if(i<245)
					{
						float a,b,c;
						a=140;//��㻷�����а뾶
						b=(i-50)%6;
						c=(i-50)/6;
						tempp->x -= (tempp->xd*1.5*cos((b*4+20+c*30)*PI/180));
						tempp->z -= (tempp->xd*1.5*sin((b*4+20+c*30)*PI/180));
						tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
					}
					if(tempp->y<0)
						tempp->type=1;
				}
				else if(count==4)//ģ���Ĳ��
				{
					{
						tempp->x+=tempp->xd;
						tempp->z-=tempp->xd;
						tempp->y=(110+0.5*tempp->t-0.1*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					
				}
				else if(count==5)//ģ����Բ̨
				{
					{
						tempp->x+=tempp->xd*1.2;
						tempp->z+=tempp->zd;
						if(i<10)
						{
							tempp->y=(table4[0].y+20+0.6*tempp->t-0.1*tempp->t*tempp->t/2);
							if(tempp->y<table3[0].y)
								tempp->type=1;
						}
						else if(i>=10 && i<30)
						{
							tempp->y=(table3[0].y+0.6*tempp->t-0.1*tempp->t*tempp->t/2);
							if(tempp->y<table1[0].y)
								tempp->type=1;
						}
						else if(i>=30)
						{
							tempp->y=(table1[0].y+0.6*tempp->t-0.1*tempp->t*tempp->t/2);
							if(tempp->y<0)
								tempp->type=1;
						}
					}
					
				}
				else if(count==6)
				{
					if(i<104)
					{//��״������
						if(i%13<6)
						{
							int a=i/13;
							tempp->x -= tempp->xd/2*(6-i%13)*0.3*cos(a*45*PI/180)-tempp->zd*sin(a*45*PI/180);
							tempp->z -= tempp->xd/2*(6-i%13)*0.3*sin(a*45*PI/180)-tempp->zd*cos(a*45*PI/180);
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*(i%13*0.5+0.3);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i%13==6)
						{
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*(i%13*0.5+0.3);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i%13>6)
						{
							int a=i/13;
							tempp->x += tempp->xd/2*(i%13-6)*0.3*cos(a*45*PI/180)-tempp->zd*sin(a*45*PI/180);
							tempp->z += tempp->xd/2*(i%13-6)*0.3*sin(a*45*PI/180)-tempp->zd*cos(a*45*PI/180);
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*((12-i%13)*0.5+0.3);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
					}
					/*else if(i>=104 && i<168)
					{//�ĸ��ǵ���
						tempp->x += (tempp->xd*sin((22.5*i)*PI/180));
						tempp->z += (tempp->xd*cos((22.5*i)*PI/180));
						tempp->y=(4*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}*/
					else if(i>=168 && i<232)
					{//����
						float a,b,c;
						if(i>=168 && i<232)
						{
							a=100;//��㻷�����а뾶
							b=i%8;
							c=i/8;
							tempp->x += tempp->xd*2.5*cos((b*1.5+20+c*45)*PI/180);
							tempp->z += tempp->xd*2.5*sin((b*1.5+20+c*45)*PI/180);
							tempp->y=(4*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
					}
					else if(i>=232 && i<290)
					{
						tempp->x -= tempp->xd*2;
						tempp->z -= tempp->zd*2;
						tempp->y=(6*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>=290 && i<310)
					{
						tempp->x -= tempp->xd;
						tempp->z -= tempp->zd;
						tempp->y=(8*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>=310 && i<330)
					{
						tempp->x -= tempp->xd/3;
						tempp->z -= tempp->zd/3;
						tempp->y=(9.5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else
					{
						tempp->y=(10.5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
				}
				else if(count==9)//��������HPU��
				{
					//��������ʱ��仯���ٶȺ��������ֶ�̬����
					{
						if(i<15)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i>=15 && i<21)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i>=21 && i<36)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i>=36 && i<51)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}else if(i>=51 && i<57)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i>=57 && i<65)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i>=65 && i<71)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i>=71 && i<86)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i>=86 && i<93)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i>=93 && i<108)
						{
							tempp->x+=tempp->xd/6;
							tempp->z+=tempp->zd/6;
							tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
							if(tempp->y<0)
								tempp->type=1;
						}
					}
					
				}
				else if(count==10)//ģ��14������
				{
					if(i<72)
					{
						tempp->x += (tempp->xd*cos((5.0*i+45)*PI/180));
						tempp->z += (tempp->xd*sin((5.0*i+45)*PI/180));
						tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>=72  &&  i<90)
					{
						tempp->x += tempp->xd;
						tempp->z += tempp->zd;
						tempp->y = (3*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else
					{
						tempp->x += tempp->xd;
						tempp->z += tempp->zd;
						tempp->y = (5*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					
				}
				else if(count==12)//ģ��16��ǣţ��
				{
					if(i<72)
					{
						tempp->x += tempp->xd*cos((5*i+67.5)*PI/180);
						tempp->z += tempp->xd*sin((5*i+67.5)*PI/180);
						tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>=72 && i<126)
					{
						tempp->x += tempp->xd;
						tempp->z += tempp->zd;
						tempp->y = (5*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>=126  &&  i<162)
					{
						tempp->x -= tempp->xd/2;
						tempp->z -= tempp->zd/2;
						tempp->y = (7*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else
					{
						tempp->x -= tempp->xd/4;
						tempp->z -= tempp->zd/4;
						tempp->y = (8*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					
				}
				else if(count==15)//�����2
				{
					int s=5;
					if(!(i%8) && i<80)
					{
						tempp->x += 0;
						tempp->z += tempp->zd/8;
						tempp->y = (s*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/8;
						if(tempp->y<0)
							tempp->type=1;
					}
				    else if(i<8)
					{
						tempp->x += (tempp->xd*((i%8)+1)/4)*cos(54*PI/180)-tempp->zd*sin(54*PI/180);
						tempp->z += (tempp->xd*((i%8)+1)/4)*sin(54*PI/180)+tempp->zd*cos(54*PI/180);
						tempp->y = (s*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if(tempp->x>0)
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>8 && i<16)
					{
						tempp->x += (-tempp->xd*((i%8)+1)/4)*cos(-54*PI/180)+tempp->zd*sin(-54*PI/180);
						tempp->z += (-tempp->xd*((i%8)+1)/4)*sin(-54*PI/180)-tempp->zd*cos(-54*PI/180);
						tempp->y = (s*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if(tempp->x<0)
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>16 && i<24)
					{
						tempp->x += (tempp->xd*((i%8)+1)/4)*cos(72*PI/180+54*PI/180)-tempp->zd*sin(72*PI/180+54*PI/180);
						tempp->z += (tempp->xd*((i%8)+1)/4)*sin(72*PI/180+54*PI/180)+tempp->zd*cos(72*PI/180+54*PI/180);
						tempp->y = (s*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if((-tempp->z*40)<(13*tempp->x))
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>24 && i<32)
					{
						tempp->x += (-tempp->xd*((i%8)+1)/4)*cos(72*PI/180-54*PI/180)+tempp->zd*sin(72*PI/180-54*PI/180);
						tempp->z += (-tempp->xd*((i%8)+1)/4)*sin(72*PI/180-54*PI/180)-tempp->zd*cos(72*PI/180-54*PI/180);
						tempp->y = (s*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if((-tempp->z*40)>(13*tempp->x))
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>32 && i<40)
					{
						tempp->x += (tempp->xd*((i%8)+1)/4)*cos(144*PI/180+54*PI/180)-tempp->zd*sin(144*PI/180+54*PI/180);
						tempp->z += (tempp->xd*((i%8)+1)/4)*sin(144*PI/180+54*PI/180)+tempp->zd*cos(144*PI/180+54*PI/180);
						tempp->y = (s*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if((tempp->z*2500)>(3441*tempp->x))
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>40 && i<48)
					{
						tempp->x += (-tempp->xd*((i%8)+1)/4)*cos(144*PI/180-54*PI/180)+tempp->zd*sin(144*PI/180-54*PI/180);
						tempp->z += (-tempp->xd*((i%8)+1)/4)*sin(144*PI/180-54*PI/180)-tempp->zd*cos(144*PI/180-54*PI/180);
						tempp->y = (s*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if((tempp->z*2500)<(3441*tempp->x))
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>48 && i<56)
					{
						tempp->x += (tempp->xd*((i%8)+1)/4)*cos(216*PI/180+54*PI/180)-tempp->zd*sin(216*PI/180+54*PI/180);
						tempp->z += (tempp->xd*((i%8)+1)/4)*sin(216*PI/180+54*PI/180)+tempp->zd*cos(216*PI/180+54*PI/180);
						tempp->y = (s*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if((tempp->z*2500)<(-3441*tempp->x))
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>56 && i<64)
					{
						tempp->x += (-tempp->xd*((i%8)+1)/4)*cos(216*PI/180-54*PI/180)+tempp->zd*sin(216*PI/180-54*PI/180);
						tempp->z += (-tempp->xd*((i%8)+1)/4)*sin(216*PI/180-54*PI/180)-tempp->zd*cos(216*PI/180-54*PI/180);
						tempp->y = (s*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if((tempp->z*2500)>(-3441*tempp->x))
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>64 && i<72)
					{
						tempp->x += (tempp->xd*((i%8)+1)/4)*cos(288*PI/180+54*PI/180)-tempp->zd*sin(288*PI/180+54*PI/180);
						tempp->z += (tempp->xd*((i%8)+1)/4)*sin(288*PI/180+54*PI/180)+tempp->zd*cos(288*PI/180+54*PI/180);
						tempp->y = (s*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if((-tempp->z*40)>(-13*tempp->x))
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>72 && i<80)
					{
						tempp->x += (-tempp->xd*((i%8)+1)/4)*cos(288*PI/180-54*PI/180)+tempp->zd*sin(288*PI/180-54*PI/180);
						tempp->z += (-tempp->xd*((i%8)+1)/4)*sin(288*PI/180-54*PI/180)-tempp->zd*cos(288*PI/180-54*PI/180);
						tempp->y = (s*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu*((i%8)+1)/6;
						if((-tempp->z*40)<(-13*tempp->x))
						{
							tempp->xd=0;
							tempp->zd=0;
						}
						if(tempp->y<0)
							tempp->type=1;
					}
					else
					{
						tempp->x += tempp->xd;
						tempp->z += tempp->zd;
						tempp->y = (2*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					
				}
				else if(count==33)//������
				{
					if(i<40)
					{
						tempp->x += tempp->xd;
						tempp->z += tempp->zd;
						tempp->y = (3.5*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>=40 && i<70)
					{
						tempp->x += tempp->xd/2;
						tempp->z += tempp->zd/2;
						tempp->y = (5.5*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>=70 && i<90)
					{
						tempp->x += tempp->xd/3;
						tempp->z += tempp->zd/3;
						tempp->y = (7*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else if(i>=90 && i<100)
					{
						tempp->x += tempp->xd/5;
						tempp->z += tempp->xd/5;
						tempp->y = (8*tempp->t - 0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
					else
					{
						tempp->x+=tempp->xd/3;
						tempp->z+=tempp->zd/3;
						tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}	
				}
				else if(count==40)//��ת�任
				{
					if(i<104)
					{
						if(i%13<6)
						{
							int a=i/13;
							tempp->x -= tempp->xd/2*(9-i%13)*0.3*cos(a*45*PI/180)-tempp->zd*sin(a*45*PI/180);
							tempp->z -= tempp->xd/2*(9-i%13)*0.3*sin(a*45*PI/180)-tempp->zd*cos(a*45*PI/180);
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*(i%13*0.5+1);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i%13==6)
						{
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*(i%13*0.5+1.2);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i%13>6)
						{
							int a=i/13;
							tempp->x += tempp->xd/2*(i%13-3)*0.3*cos(a*45*PI/180)-tempp->zd*sin(a*45*PI/180);
							tempp->z += tempp->xd/2*(i%13-3)*0.3*sin(a*45*PI/180)-tempp->zd*cos(a*45*PI/180);
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*((12-i%13)*0.5+1);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
					}
					else
					{
						tempp->x+=tempp->xd;
						tempp->z+=tempp->zd;
						tempp->y=(3*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
				}
				else if(count==41)//ƽ�Ʊ任
				{
					if(i<117)
					{
						if(i%13<6)
						{
							int a=i/13;
							tempp->x -= tempp->xd*(6-i%13)*0.1;//*(10-i)*0.1
							tempp->z -= tempp->zd;
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*(i%13*0.5+1);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i%13==6)
						{
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*(i%13*0.5+1.2);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i%13>6)
						{
							int a=i/13;
							tempp->x += tempp->xd*(i%13-5)*0.1;
							tempp->z += tempp->zd;
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*((12-i%13)*0.5+1);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
					}
					else
					{
						tempp->x+=tempp->xd;
						tempp->z+=tempp->zd;
						tempp->y=(6*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
				}
				else if(count==42)//�ԳƱ任
				{
					if(i<52)
					{
						if(i%13<6)
						{
							int a=i/13;
							tempp->x -= tempp->xd*(6-i%13)*0.1;//*(10-i)*0.1
							tempp->z -= tempp->zd;
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*(i%13*0.5+1);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i%13==6)
						{
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*(i%13*0.5+1.2);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
						else if(i%13>6)
						{
							int a=i/13;
							tempp->x += tempp->xd*(i%13-5)*0.1;
							tempp->z += tempp->zd;
							tempp->y = (4*tempp->t - 0.2*tempp->t*tempp->t/2)/2/gaodu*((12-i%13)*0.5+1);//((i%10)+1)/6
							if(tempp->y<0)
								tempp->type=1;
						}
					}
					else
					{
						tempp->x+=tempp->xd;
						tempp->z+=tempp->zd;
						tempp->y=(3*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
						if(tempp->y<0)
							tempp->type=1;
					}
				}
				tempp->t += 0.5;
			}
			else
			{
				if(count==1)//ģ��һ������
				{
					tempp->y=(5*tempp->t-0.2*tempp->t*tempp->t/2)/gaodu;
				}
				else if(count==4)//ģ���Ĳ��
				{
					tempp->y=(110+0.5*tempp->t-0.1*tempp->t*tempp->t/2)/gaodu;
				}
				else if(count==5)//ģ����Բ̨
				{
					if(i<10)
					{
						tempp->y=(table4[0].y+20+0.6*tempp->t-0.1*tempp->t*tempp->t/2);
						if(tempp->y=table3[0].y)
							tempp->d=tempp->d-2*((tempp->d)*(0,1,0))*(0,1,0);
					}
					else if(i>=10 && i<30)
					{
						tempp->y=(table3[0].y+0.6*tempp->t-0.1*tempp->t*tempp->t/2);
					}
					else if(i>=30)
					{
						tempp->y=(table1[0].y+0.6*tempp->t-0.1*tempp->t*tempp->t/2);
					}
				}
				tempp->a-=0.1;
			}
			tempp=tempp->next;
		}
	}
}

BOOL CHPUFountainView::PreTranslateMessage(MSG* pMsg)
{
	//TODO:Addyourspecializedcodehereand/orcallthebaseclass
	if(pMsg->message==WM_KEYDOWN || pMsg->message==WM_SYSKEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_LEFT:
		//	cam.x+=2;
			cam.z+=4;
			break;
		case VK_RIGHT:
		//	cam.x-=2;
			cam.z-=4;
			break;
		case VK_UP:
			cam.y+=6;
			break;
		case VK_DOWN:
			cam.y-=6;
			break;
		case VK_SPACE://���λ���趨�ո��
			cam.y=cam.z=500;
			break;
		}
	}
	return CView::PreTranslateMessage(pMsg);
}

void CHPUFountainView::OnHuifu()
{
	//TODO:Addyourcommandhandlercodehere
	HuiFu();
	count=0;
	Invalidate(FALSE);
}

void CHPUFountainView::OnModel1()
{
	//TODO:Addyourcommandhandlercodehere
	HuiFu();
	count=1;
	Invalidate(FALSE);
}
void CHPUFountainView::OnModel2() //�ʹ�
{
	// TODO: Add your command handler code here
	HuiFu();
	count=2;
	Invalidate(FALSE);
}
void CHPUFountainView::OnModel3() 
{
	// TODO: Add your command handler code here
	HuiFu();
	count=3;
	Invalidate(FALSE);
}

void CHPUFountainView::OnModel4() //����ٲ�
{
	// TODO: Add your command handler code here
	HuiFu();
	count=4;
	Invalidate(FALSE);
}

void CHPUFountainView::OnModel5() //Բ̨
{
	// TODO: Add your command handler code here
	HuiFu();
	count=5;
	Invalidate(FALSE);
}
void CHPUFountainView::OnModel6() 
{
	// TODO: Add your command handler code here
	HuiFu();
	count=6;
	Invalidate(FALSE);
}

void CHPUFountainView::OnModel8()
{
	//TODO:Addyourcommandhandlercodehere
	HuiFu();
	count=8;
	Invalidate(FALSE);
}
//��������HPU
void CHPUFountainView::OnModel9()
{
	//TODO:Addyourcommandhandlercodehere
	HuiFu();
	count=9;
	Invalidate(FALSE);
}
//������
void CHPUFountainView::OnModel10()
{
	//TODO:Addyourcommandhandlercodehere
	HuiFu();
	count=10;
	Invalidate(FALSE);
}

//ǣţ��
void CHPUFountainView::OnModel12()
{
	//TODO:Addyourcommandhandlercodehere
	HuiFu();
	count=12;
	Invalidate(FALSE);
}
//�����111
void CHPUFountainView::OnModel15() 
{
	// TODO: Add your command handler code here
	HuiFu();
	count=15;
	Invalidate(FALSE);
}

BOOL CHPUFountainView::OnEraseBkgnd(CDC* pDC)
{
	//TODO:Addyourmessagehandlercodehereand/orcalldefault
	return true;
//	returnCView::OnEraseBkgnd(pDC);
}

void CHPUFountainView::OnActivate(UINT nState,CWnd* pWndOther,BOOL bMinimized)
{
	CView::OnActivate(nState,pWndOther,bMinimized);
	
	//TODO:Addyourmessagehandlercodehere
	
}

void CHPUFountainView::OnModel33() 
{
	// TODO: Add your command handler code here
	HuiFu();
	count=33;
	Invalidate(FALSE);
}

void CHPUFountainView::OnModel40() 
{
	// TODO: Add your command handler code here
	HuiFu();
	count=40;
	Invalidate(FALSE);
}

void CHPUFountainView::OnModel41() 
{
	// TODO: Add your command handler code here
	HuiFu();
	count=41;
	Invalidate(FALSE);
}

void CHPUFountainView::OnModel42() 
{
	// TODO: Add your command handler code here
	HuiFu();
	count=42;
	Invalidate(FALSE);
}

void CHPUFountainView::OnModel43() 
{
	// TODO: Add your command handler code here
	HuiFu();
	count=43;
	Invalidate(FALSE);
}




